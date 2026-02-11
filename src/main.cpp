#include<cstdlib>
#include<limits>
#include<random>
#include<ranges>
#include<system.hpp>

namespace
{
chip8::memory_t memory{};
chip8::display_t display{};
chip8::stack_t stack{};
chip8::timer_t delay_timer{};
chip8::timer_t sound_timer{};
chip8::keypad_t keypad{};
}

namespace loop
{
[[nodiscard]] static constexpr auto fetch_instruction (chip8::memory_t& memory) noexcept -> chip8::instruction_t
{
	std::uint16_t first_half{ memory.get_ram_value (memory.get_program_counter ()) };
	std::uint16_t second_half{ memory.get_ram_value (memory.get_program_counter () + 1) };
	std::uint16_t instruction_raw = (first_half << 8) | second_half;
	return chip8::instruction_t::build (instruction_raw);
}

static constexpr auto decode_arithmetic_instruction (chip8::instruction_t instruction) noexcept -> void
{
	// pre(instruction.get_category() == 0x8)
	std::uint8_t new_value{};

	switch (instruction.get_n ())
		{
			case 0x0:
				new_value = memory.get_general_register_value (instruction.get_y ());
				break;
			case 0x1:
				new_value = memory.get_general_register_value (instruction.get_x ()) |
										memory.get_general_register_value (instruction.get_y ());
				break;
			case 0x2:
				new_value = memory.get_general_register_value (instruction.get_x ()) &
										memory.get_general_register_value (instruction.get_y ());
				break;
			case 0x3:
				new_value = memory.get_general_register_value (instruction.get_x ()) ^
										memory.get_general_register_value (instruction.get_y ());
				break;
			case 0x4:
				new_value = memory.get_general_register_value (instruction.get_x ()) +
										memory.get_general_register_value (instruction.get_y ());
				if (new_value < memory.get_general_register_value (instruction.get_x ()))
					memory.set_general_register_value (0xF, 1);
				break;
			case 0x5:
				new_value = memory.get_general_register_value (instruction.get_x ()) -
										memory.get_general_register_value (instruction.get_y ());
				if (memory.get_general_register_value (instruction.get_x ()) >
						memory.get_general_register_value (instruction.get_y ()))
					memory.set_general_register_value (0xF, 1);
				break;
			case 0x7:
				new_value = memory.get_general_register_value (instruction.get_y ()) -
										memory.get_general_register_value (instruction.get_x ());
				if (memory.get_general_register_value (instruction.get_y ()) >
						memory.get_general_register_value (instruction.get_x ()))
					memory.set_general_register_value (0xF, 1);
				break;
			case 0x6:
				new_value = memory.get_general_register_value (instruction.get_x ()) >> 1;
				memory.set_general_register_value (
					0xF, memory.get_general_register_value (instruction.get_x () % 2 == 0));
				break;
			case 0xE:
				new_value =
					static_cast<std::uint8_t> (memory.get_general_register_value (instruction.get_x ()) << 1);
				memory.set_general_register_value (
					0xF,
					memory.get_general_register_value (
						instruction.get_x () % (std::numeric_limits<std::uint8_t>::max () / 2) == 0));
				break;
			default: ///error? maybe an always false post-condition
				break;
		}
	memory.set_general_register_value (instruction.get_x (), new_value);
}

static constexpr auto decode_f_instructions (chip8::instruction_t instruction) -> void
{
	// pre(instruction.get_category() == 0xF)
	switch (instruction.get_nn ())
		{
			case 0x07:
				memory.set_general_register_value (instruction.get_x (), delay_timer.get_value ());
				break;
			case 0x15:
				delay_timer.set_value (memory.get_general_register_value (instruction.get_x ()));
				break;
			case 0x18:
				sound_timer.set_value (memory.get_general_register_value (instruction.get_x ()));
				break;
			case 0x1E:
				memory.set_index_register (memory.get_index_register () +
																	 memory.get_general_register_value (instruction.get_x ()));
				break;
			case 0x0A:
				//implement get key
				break;
			case 0x29:
				// implement font character
				break;
			case 0x33:
				{
					memory.set_ram_value (memory.get_index_register (),
																memory.get_general_register_value (instruction.get_x ()) / 100);
					memory.set_ram_value (memory.get_index_register () + 1,
																memory.get_general_register_value (instruction.get_x ()) / 10 % 10);
					memory.set_ram_value (memory.get_index_register () + 2,
																memory.get_general_register_value (instruction.get_x ()) % 100);
				}
				break;
			case 0x55:
				// pre(instruction.get_x() <= 16)
				for (std::uint8_t index : std::views::iota (0, instruction.get_x () + 1))
					{
						// for (std::uint8_t index{0}; index <= instruction.get_x();
						// index++)
						// {
						memory.set_ram_value (memory.get_index_register () + index,
																	memory.get_general_register_value (index));
					}
				break;
			case 0x65:
				for (std::uint8_t index : std::views::iota (0, instruction.get_x () + 1))
					{
						memory.set_general_register_value (
							index, memory.get_ram_value (memory.get_index_register () + index));
					}
				break;
			default:
				//maybe an always false post-condition
				break;
		}
}

static constexpr auto exec () -> void
{
	while (true)
		{
			//fetch
			auto instruction = fetch_instruction (memory);
			memory.increment_program_counter ();

			//decode
			switch (instruction.get_category ())
				{
					case 0x0:
						switch (instruction.get_nnn ())
							{
								case 0x0E0:
									display.clear_screen ();
									break;
								case 0x0EE:
									memory.set_program_counter (stack.pop_value ());
									break;
							}
						break;
					case 0x1:
						memory.set_program_counter (instruction.get_nnn ());
						break;
					case 0x2:
						stack.push_value (memory.get_program_counter ());
						memory.set_program_counter (instruction.get_nnn ());
						break;
					case 0x3:
						if (instruction.get_nn () == memory.get_general_register_value (instruction.get_x ()))
							memory.increment_program_counter ();
						break;
					case 0x4:
						if (instruction.get_nn () != memory.get_general_register_value (instruction.get_x ()))
							memory.increment_program_counter ();
						break;
					case 0x5:
						if (memory.get_general_register_value (instruction.get_x ()) ==
								memory.get_general_register_value (instruction.get_y ()))
							memory.increment_program_counter ();
						break;
					case 0x6:
						memory.set_general_register_value (instruction.get_x (), instruction.get_nn ());
						break;
					case 0x7:
						memory.add_general_register_value (instruction.get_x (), instruction.get_nn ());
						break;
					case 0x8:
						decode_arithmetic_instruction (instruction);
						break;
					case 0x9:
						if (memory.get_general_register_value (instruction.get_x ()) !=
								memory.get_general_register_value (instruction.get_y ()))
							memory.increment_program_counter ();
						break;
					case 0xA:
						memory.set_index_register (instruction.get_nnn ());
						break;
					case 0xB:
						memory.set_program_counter (memory.get_general_register_value (0x0) +
																				instruction.get_nnn ());
						break;
					case 0xC:
						{
							std::random_device rd;
							std::mt19937 gen (rd ());
							// memory.set_general_register_value (instruction.get_x (),
							//(std::generate_canonical<std::uint16_t, 10> (gen) *
							//std::numeric_limits<std::uint16_t>::max ()) &
							//instruction.get_nn ());
						}
						break;
					case 0xD:
						//implement display decode
						break;
					case 0xE:
						//implement skip if they
						break;
					case 0xF:
						decode_f_instructions (instruction);
						break;
				}
		};
}
}

//manage a game loop that executes around 700 instructions per second
int main ()
{
	loop::exec ();
	return 0;
}

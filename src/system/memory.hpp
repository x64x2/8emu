#ifndef SYSTEM_MEMORY_HPP_
#define SYSTEM_MEMORY_HPP_

#include <array>
#include <cstdint>

namespace chip8
{
class memory_t
{
	static constexpr auto max_size{ 4096 };
	static constexpr auto last_reserved_register{ 0x1FF };

	std::array<std::uint8_t, max_size> ram{};
	std::uint16_t program_counter{};
	std::uint16_t index_register{};
	std::array<std::uint8_t, 16> general_registers{};

public:
	[[nodiscard]] constexpr auto get_ram_value (std::uint16_t address) noexcept -> std::uint8_t
	{
		//pre(address > last_reserved_register )
		return ram.at (address);
	}

	constexpr auto set_ram_value (std::uint16_t address, std::uint8_t value) noexcept -> void
	{
		//pre(address > last_reserved_register)
		ram.at (address) = value;
		//post(memory.at(address) == value)
	}

	constexpr auto set_program_counter (std::uint16_t value) noexcept -> void
	{
		this->program_counter = value;
	}

	[[nodiscard]] constexpr auto get_program_counter () noexcept -> std::uint16_t
	{
		return this->program_counter;
	}

	constexpr auto increment_program_counter (std::uint16_t increment = 2) noexcept -> void
	{
		//pre(program_counter < max_size)
		//pre(program_counter + increment < max_size)
		program_counter += increment;
		//post(program_counter < max_size)
	}

	constexpr auto set_index_register (std::uint16_t new_value) noexcept -> void
	{
		this->index_register = new_value;
	}

	[[nodiscard]] constexpr auto get_index_register () noexcept -> std::uint16_t
	{
		return this->index_register;
	}

	[[nodiscard]] constexpr auto get_general_register_value (std::uint8_t register_address) noexcept
		-> std::uint8_t
	{
		//pre(register_address <= 0xF)
		return this->general_registers.at (register_address);
	}

	constexpr auto set_general_register_value (std::uint8_t register_address,
																						 std::uint8_t new_value) noexcept -> void
	{
		//pre(register_address <= 0xF)
		this->general_registers.at (register_address) = new_value;
	}

	constexpr auto add_general_register_value (std::uint8_t register_address,
																						 std::uint8_t add_value) noexcept -> void
	{
		this->general_registers.at (register_address) += add_value;
	}
};

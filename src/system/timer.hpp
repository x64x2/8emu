#ifndef SYSTEM_TIMER_HPP
#define SYSTEM_TIMER_HPP

#include <cstdint>

namespace chip8
{
class timer_t
{
	std::uint8_t value{};

public:
	[[nodiscard]] constexpr auto get_value () noexcept -> std::uint8_t
	{
		return value;
	}

	constexpr auto set_value (std::uint8_t new_value) noexcept -> void
	{
		this->value = new_value;
	}

	// TODO async function (coroutines?) that decrements value by one 60 times per second (60Hz)
	// TODO sound function (idk how to do that)
};
}
#endif

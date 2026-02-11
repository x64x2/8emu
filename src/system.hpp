#ifndef SYSTEM_H_
#define SYSTEM_H_

#include <array>
#include <cstdint>

#include <display.hpp>
#include <memory.hpp>
#include <stack.hpp>
#include <timer.hpp>

namespace chip8
{
	class instruction_t
{
	std::uint16_t category : 4;
	std::uint16_t x : 4;
	std::uint16_t y : 4;
	std::uint16_t n : 4;

public:
	[[nodiscard]] constexpr auto get_category () noexcept -> std::uint8_t
	{
		return this->category;
	}

	[[nodiscard]] constexpr auto get_x () noexcept -> std::uint8_t
	{
		return this->x;
	}

	[[nodiscard]] constexpr auto get_y () noexcept -> std::uint8_t
	{
		return this->y;
	}

	[[nodiscard]] constexpr auto get_n () noexcept -> std::uint8_t
	{
		return this->n;
	}

	[[nodiscard]] constexpr auto get_nn () noexcept -> std::uint8_t
	{
		return static_cast<std::uint8_t> ((y << 4) | (n));
	}

	[[nodiscard]] constexpr auto get_nnn () noexcept -> std::uint16_t
	{
		return static_cast<std::uint8_t> ((x << 8) | get_nn ());
	}

	[[nodiscard]] static constexpr auto build (std::uint16_t value) noexcept -> instruction_t
	{
		instruction_t ret;
		ret.category = ((value & 0xF000) >> 12);
		ret.x = ((value & 0x0F00) >> 8);
		ret.y = ((value & 0x00F0) >> 4);
		ret.n = (value & 0x000F);

		return ret;
	}
};

class keypad_t
{
	static constexpr std::array cosmac_vip_layout = {
		'1', '2', '3', 'C', '4', '5', '6', 'D', '7', '8', '9', 'E', 'A', '0', 'B', 'F',
	};
	// static constexpr std::map<> scancodes_to_layout =
};


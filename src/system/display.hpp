#ifndef SYSTEM_DISPLAY_HPP
#define SYSTEM_DISPLAY_HPP

#include <array>
#include <cstdint>

namespace chip8
{
class display_t
{
	static constexpr auto wide_max_value{ 64 };
	static constexpr auto tall_max_value{ 32 };

	using column_t = std::array<bool, tall_max_value>;
	using line_t = std::array<bool, wide_max_value>;

	std::array<line_t, wide_max_value> monitor{};

public:
	[[nodiscard]] constexpr auto get_pixel (std::uint8_t x, std::uint8_t y) noexcept -> bool
	{
		//pre(x <= wide_max_value)
		//pre(y <= tall_max_value)
		return monitor.at (x).at (y);
	}

	constexpr auto set_pixel (std::uint8_t x, std::uint8_t y, bool value) noexcept -> void
	{
		//pre(x <= wide_max_value)
		//pre(y <= tall_max_value)
		monitor.at (x).at (y) = value;
		//post(monitor.at(x).at(y) == value)
	}

	constexpr auto clear_screen () noexcept -> void
	{
		monitor = {};
	}
};

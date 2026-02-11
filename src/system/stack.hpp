#ifndef SYSTEM_STACK_HPP
#define SYSTEM_STACK_HPP

#include <cstdint>
#include <stack>

namespace chip8
{
class stack_t
{
	static constexpr auto max_size{ 16 };

	std::stack<std::uint16_t> stack{};

public:
	[[nodiscard]] constexpr auto pop_value () noexcept -> std::uint16_t
	{
		//pre(not stack.empty())
		auto ret = this->stack.top ();
		this->stack.pop ();
		return ret;
	}

	constexpr auto push_value (std::uint16_t value) noexcept -> void
	{
		//pre(not stack.size() >= max_size)
		stack.push (value);
		//post(stack.top() == value)
	}
};

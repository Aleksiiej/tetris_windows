#pragma once

#include "BaseBlock.hpp"

class Block1 : public BaseBlock
{
public:
	Block1() = delete;
	Block1(BlockBoard& blockBoardRef) noexcept;
	Block1(const Block1& other) = delete;
	Block1(const Block1&& other) = delete;
	~Block1() = default;

	const bool isRotationPossible() const noexcept;
	void rotate() noexcept;
};

// *--*
// |01|
// |23|
// *--*


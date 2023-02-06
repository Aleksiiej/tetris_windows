#pragma once

#include "BaseBlock.hpp"

class Block7 : public BaseBlock
{
public:
	Block7() = delete;
	Block7(BlockBoard& blockBoardRef) noexcept;
	Block7(const Block7& other) = delete;
	Block7(const Block7&& other) = delete;
	~Block7() = default;

	const bool isRotationPossible() const noexcept;
	void rotate() noexcept;

private:
	TwoBlockPositions currentPosition_{};
};

// *---* *---*
// |   | | 0 |
// |01 | |21 |
// | 23| |3  |
// *---* *---*

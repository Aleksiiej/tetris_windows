#pragma once

#include "BaseBlock.hpp"

class Block6 : public BaseBlock
{
public:
	Block6() = delete;
	Block6(BlockBoard& blockBoardRef) noexcept;
	Block6(const Block6& other) = delete;
	Block6(const Block6&& other) = delete;
	~Block6() = default;

	const bool isRotationPossible() const noexcept;
	void rotate() noexcept;

private:
	TwoBlockPositions currentPosition_{};
};

// *---* *---*
// | 23| | 0 |
// |01 | | 12|
// |   | |  3|
// *---* *---*

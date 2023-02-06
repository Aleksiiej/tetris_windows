#pragma once

#include "BaseBlock.hpp"

class BlockBoard;

class Block5 : public BaseBlock
{
public:
	Block5() = delete;
	Block5(BlockBoard& blockBoardRef) noexcept;
	Block5(const Block5& other) = delete;
	Block5(const Block5&& other) = delete;
	~Block5() = default;

	const bool isRotationPossible() const noexcept;
	void rotate() noexcept;

private:
	FourBlockPositions currentPosition_{};
};

// *---* *--* *---* *--*
// |012| | 0| |3  | |23|
// |  3| | 1| |210| |1 |
// *---* |32| *---* |0 |
//       *--*       *--*     

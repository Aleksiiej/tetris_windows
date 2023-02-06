#pragma once

#include "BaseBlock.hpp"

class Block4 : public BaseBlock
{
public:
	Block4() = delete;
	Block4(BlockBoard& blockBoardRef) noexcept;
	Block4(const Block4& other) = delete;
	Block4(const Block4&& other) = delete;
	~Block4() = default;

	const bool isRotationPossible() const noexcept;
	void rotate() noexcept;

private:
	FourBlockPositions currentPosition_{};
};

// *---* *--* *---* *--*
// |012| |30| |  3| |2 |
// |3  | | 1| |210| |1 |
// *---* | 2| *---* |03|
//       *--*       *--*     

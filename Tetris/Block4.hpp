#pragma once

#include <SFML/Graphics.hpp>

#include "BaseBlock.hpp"

using namespace sf;
using namespace std;

class BlockBoard;

class Block4 : public BaseBlock
{
public:
	Block4() = delete;
	Block4(BlockBoard& blockBoardRef) noexcept;
	Block4(const Block4& other) = delete;
	Block4(const Block4&& other) = delete;
	~Block4() = default;

	const bool checkIfLost() const noexcept;
	const bool isFallingPossible() noexcept;
	const bool isMoveRightPossible() const noexcept;
	const bool isMoveLeftPossible() const noexcept;
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

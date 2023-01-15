#pragma once

#include <SFML/Graphics.hpp>

#include "BaseBlock.hpp"

using namespace sf;
using namespace std;

class BlockBoard;

class Block7 : public BaseBlock
{
public:
	Block7() = delete;
	Block7(BlockBoard& blockBoardRef) noexcept;
	Block7(const Block7& other) = delete;
	Block7(const Block7&& other) = delete;
	~Block7() = default;

	const bool checkIfLost() const noexcept;
	const bool isFallingPossible() noexcept;
	const bool isMoveRightPossible() const noexcept;
	const bool isMoveLeftPossible() const noexcept;
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

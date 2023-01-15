#pragma once

#include <SFML/Graphics.hpp>

#include "BaseBlock.hpp"

using namespace sf;
using namespace std;

class BlockBoard;

class Block6 : public BaseBlock
{
public:
	Block6() = delete;
	Block6(BlockBoard& blockBoardRef) noexcept;
	Block6(const Block6& other) = delete;
	Block6(const Block6&& other) = delete;
	~Block6() = default;

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
// | 23| | 0 |
// |01 | | 12|
// |   | |  3|
// *---* *---*

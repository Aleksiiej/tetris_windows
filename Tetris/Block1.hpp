#pragma once

#include <SFML/Graphics.hpp>

#include "BaseBlock.hpp"

using namespace sf;
using namespace std;

class BlockBoard;

class Block1 : public BaseBlock
{
public:
	Block1() = delete;
	Block1(BlockBoard& blockBoardRef) noexcept;
	Block1(const Block1& other) = delete;
	Block1(const Block1&& other) = delete;
	~Block1() = default;

	const bool checkIfLost() const noexcept;
	const bool isFallingPossible() noexcept;
	const bool isMoveRightPossible() const noexcept;
	const bool isMoveLeftPossible() const noexcept;
	const bool isRotationPossible() const noexcept;
	void rotate() noexcept;
};

// *--*
// |01|
// |23|
// *--*


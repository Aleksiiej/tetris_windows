#pragma once

#include <SFML/Graphics.hpp>

#include "BaseBlock.hpp"
#include "GlobalValues.hpp"

using namespace sf;
using namespace std;

class BlockBoard;

class Block2: public BaseBlock
{
public:
	Block2() = delete;
	Block2(BlockBoard& blockBoardRef) noexcept;
	Block2(const Block2& other) = delete;
	Block2(const Block2&& other) = delete;
	~Block2() = default;

	const bool checkIfLost() const noexcept;
	const bool isFallingPossible() noexcept;
	const bool isMoveRightPossible() const noexcept;
	const bool isMoveLeftPossible() const noexcept;
	const bool isRotationPossible() const noexcept;
	void rotate() noexcept;

private:
	TwoBlockPositions currentPosition_{};
};

// *----*
// |0123|
// *----*

#pragma once

#include <SFML/Graphics.hpp>

#include "BaseBlock.hpp"

using namespace sf;
using namespace std;

class BlockBoard;

class Block3 : public BaseBlock
{
public:
	Block3() = delete;
	Block3(BlockBoard& blockBoardRef) noexcept;
	Block3(const Block3& other) = delete;
	Block3(const Block3&& other) = delete;
	~Block3() = default;

	const bool checkIfLost() const noexcept;
	const bool isFallingPossible() noexcept;
	const bool isMoveRightPossible() const noexcept;
	const bool isMoveLeftPossible() const noexcept;
	const bool isRotationPossible() const noexcept;
	void rotate() noexcept;

private:
	FourBlockPositions currentPosition_{};
};

// *---* *---* *---* *---*
// |012| | 0 | | 3 | | 2 |
// | 3 | |31 | |210| | 13|
// *---* | 2 | *---* | 0 |
//       *---*       *---*       

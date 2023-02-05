#pragma once

#include "BaseBlock.hpp"

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

	const bool isRotationPossible() const noexcept;
	void rotate() noexcept;

private:
	TwoBlockPositions currentPosition_{};
};

// *----*
// |0123|
// *----*

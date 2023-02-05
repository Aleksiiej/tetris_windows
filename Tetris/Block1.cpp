#include "BlockBoard.hpp"
#include "Block1.hpp"
#include "GlobalValues.hpp"

Block1::Block1(BlockBoard& blockBoardRef) noexcept
	: BaseBlock(blockBoardRef)
{
	for_each(begin(blockArray_), end(blockArray_), [](auto& block) { block = RectangleShape{ Vector2f{ GRID, GRID } }; });
	for_each(begin(blockArray_), end(blockArray_), [](auto& block) { block.setFillColor(Color::Red); });
	blockArray_.at(0).setPosition((NUMBER_OF_COLUMNS / 2) * GRID, GRID);
	blockArray_.at(1).setPosition((NUMBER_OF_COLUMNS / 2) * GRID + GRID, GRID);
	blockArray_.at(2).setPosition((NUMBER_OF_COLUMNS / 2) * GRID, 2 * GRID);
	blockArray_.at(3).setPosition((NUMBER_OF_COLUMNS / 2) * GRID + GRID, 2 * GRID);
}

const bool Block1::isFallingPossible() noexcept
{
	if (blockArray_.at(2).getPosition().y >= GRID * NUMBER_OF_ROWS and blockArray_.at(3).getPosition().y >= GRID * NUMBER_OF_ROWS
		or blockBoardRef_.getBoardArrayRef().at(gridToX(2)).at(gridToY(2) + 1) != Color::White
		or blockBoardRef_.getBoardArrayRef().at(gridToX(3)).at(gridToY(3) + 1) != Color::White)
	{
		setColorsInBlockBoard();
		return false;
	}
	return true;
}

const bool Block1::isRotationPossible() const noexcept
{
	return false;
}

void Block1::rotate() noexcept
{
	return;
}

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

const bool Block1::checkIfLost() const noexcept
{
	if (blockArray_.at(0).getPosition().y == GRID
		and (blockBoardRef_.getBoardArrayRef().at(gridToX(2)).at(gridToY(2)) == Color::Red
			or blockBoardRef_.getBoardArrayRef().at(gridToX(3)).at(gridToY(3)) == Color::Red))
	{
		return false;
	}
	return true;
}

const bool Block1::isFallingPossible() noexcept
{
	if (blockArray_.at(2).getPosition().y >= GRID * NUMBER_OF_ROWS and blockArray_.at(3).getPosition().y >= GRID * NUMBER_OF_ROWS)
	{
		setColorsInBlockBoard();
		return false;
	}
	else if (blockBoardRef_.getBoardArrayRef().at(gridToX(2)).at(gridToY(2) + 1) != Color::White
		or blockBoardRef_.getBoardArrayRef().at(gridToX(3)).at(gridToY(3) + 1) != Color::White)
	{
		setColorsInBlockBoard();
		return false;
	}
	return true;
}

const bool Block1::isMoveRightPossible() const noexcept
{
	if (blockArray_.at(1).getPosition().x >= GRID * NUMBER_OF_COLUMNS
		or blockBoardRef_.getBoardArrayRef().at(gridToX(1) + 1).at(gridToY(1)) != Color::White
		or blockBoardRef_.getBoardArrayRef().at(gridToX(3) + 1).at(gridToY(3)) != Color::White)
	{
		return false;
	}
	return true;
}

const bool Block1::isMoveLeftPossible() const noexcept
{
	if (blockArray_.at(0).getPosition().x <= GRID
		or blockBoardRef_.getBoardArrayRef().at(gridToX(0) - 1).at(gridToY(0)) != Color::White
		or blockBoardRef_.getBoardArrayRef().at(gridToX(2) - 1).at(gridToY(2)) != Color::White)
	{
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

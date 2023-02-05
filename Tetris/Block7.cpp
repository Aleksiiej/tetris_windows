#include "BlockBoard.hpp"
#include "Block7.hpp"

Block7::Block7(BlockBoard& blockBoardRef) noexcept
	: BaseBlock(blockBoardRef), currentPosition_(TwoBlockPositions::Horizontal)
{
	for_each(begin(blockArray_), end(blockArray_), [](auto& block) { block = RectangleShape{ Vector2f{ GRID, GRID } }; });
	for_each(begin(blockArray_), end(blockArray_), [](auto& block) { block.setFillColor(Color::Red); });
	blockArray_.at(0).setPosition((NUMBER_OF_COLUMNS / 2) * GRID - GRID, GRID);
	blockArray_.at(1).setPosition((NUMBER_OF_COLUMNS / 2) * GRID, GRID);
	blockArray_.at(2).setPosition((NUMBER_OF_COLUMNS / 2) * GRID, 2 * GRID);
	blockArray_.at(3).setPosition((NUMBER_OF_COLUMNS / 2) * GRID + GRID, 2 * GRID);
}

const bool Block7::isRotationPossible() const noexcept
{
	if (currentPosition_ == TwoBlockPositions::Horizontal)
	{
		if (blockArray_.at(1).getPosition().y > GRID
			and blockBoardRef_.getBoardArrayRef().at(gridToX(1) - 1).at(gridToY(1) + 1) == Color::White)
		{
			return true;
		}
		else return false;
	}
	else if (currentPosition_ == TwoBlockPositions::Vertical)
	{
		if (blockArray_.at(1).getPosition().x < GRID * NUMBER_OF_COLUMNS
			and blockBoardRef_.getBoardArrayRef().at(gridToX(1)).at(gridToY(1) + 1) == Color::White
			and blockBoardRef_.getBoardArrayRef().at(gridToX(1) + 1).at(gridToY(1) + 1) == Color::White)
		{
			return true;
		}
		else return false;
	}
	return false;
}

void Block7::rotate() noexcept
{
	if (isRotationPossible())
	{
		if (currentPosition_ == TwoBlockPositions::Horizontal)
		{
			blockArray_.at(0).setPosition(blockArray_.at(0).getPosition().x + GRID, blockArray_.at(0).getPosition().y - GRID);
			blockArray_.at(2).setPosition(blockArray_.at(2).getPosition().x - GRID, blockArray_.at(2).getPosition().y - GRID);
			blockArray_.at(3).setPosition(blockArray_.at(3).getPosition().x - 2 * GRID, blockArray_.at(3).getPosition().y);
			currentPosition_ = TwoBlockPositions::Vertical;
		}
		else if (currentPosition_ == TwoBlockPositions::Vertical)
		{
			blockArray_.at(0).setPosition(blockArray_.at(0).getPosition().x - GRID, blockArray_.at(0).getPosition().y + GRID);
			blockArray_.at(2).setPosition(blockArray_.at(2).getPosition().x + GRID, blockArray_.at(2).getPosition().y + GRID);
			blockArray_.at(3).setPosition(blockArray_.at(3).getPosition().x + 2 * GRID, blockArray_.at(3).getPosition().y);
			currentPosition_ = TwoBlockPositions::Horizontal;
		}
	}
}


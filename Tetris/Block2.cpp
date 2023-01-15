#include "BlockBoard.hpp"
#include "Block2.hpp"

Block2::Block2(BlockBoard& blockBoardRef) noexcept
	: BaseBlock(blockBoardRef), currentPosition_(TwoBlockPositions::Horizontal)
{
	for_each(begin(blockArray_), end(blockArray_), [](auto& block) { block = RectangleShape{ Vector2f{ GRID, GRID } }; });
	for_each(begin(blockArray_), end(blockArray_), [](auto& block) { block.setFillColor(Color::Red); });
	blockArray_.at(0).setPosition((NUMBER_OF_COLUMNS / 2) * GRID - GRID, GRID);
	blockArray_.at(1).setPosition((NUMBER_OF_COLUMNS / 2) * GRID, GRID);
	blockArray_.at(2).setPosition((NUMBER_OF_COLUMNS / 2) * GRID + GRID, GRID);
	blockArray_.at(3).setPosition((NUMBER_OF_COLUMNS / 2) * GRID + 2 * GRID, GRID);
}

const bool Block2::checkIfLost() const noexcept
{
	if (blockArray_.at(0).getPosition().y == GRID
		and (blockBoardRef_.getBoardArrayRef().at(gridToX(0)).at(gridToY(0)) == Color::Red
			or blockBoardRef_.getBoardArrayRef().at(gridToX(1)).at(gridToY(1)) == Color::Red
			or blockBoardRef_.getBoardArrayRef().at(gridToX(2)).at(gridToY(3)) == Color::Red
			or blockBoardRef_.getBoardArrayRef().at(gridToX(3)).at(gridToY(3)) == Color::Red))
	{
		return false;
	}
	return true;
}

const bool Block2::isFallingPossible() noexcept
{
	if (currentPosition_ == TwoBlockPositions::Horizontal)
	{
		if (blockArray_.at(0).getPosition().y >= GRID * NUMBER_OF_ROWS or blockArray_.at(3).getPosition().y >= GRID * NUMBER_OF_ROWS)
		{
			setColorsInBlockBoard();
			return false;
		}
		else if (blockBoardRef_.getBoardArrayRef().at(gridToX(0)).at(gridToY(0) + 1) != Color::White
			or blockBoardRef_.getBoardArrayRef().at(gridToX(1)).at(gridToY(1) + 1) != Color::White
			or blockBoardRef_.getBoardArrayRef().at(gridToX(2)).at(gridToY(2) + 1) != Color::White
			or blockBoardRef_.getBoardArrayRef().at(gridToX(3)).at(gridToY(3) + 1) != Color::White)
		{
			setColorsInBlockBoard();
			return false;
		}
		return true;
	}
	else if (currentPosition_ == TwoBlockPositions::Vertical)
	{
		if (blockArray_.at(3).getPosition().y >= GRID * NUMBER_OF_ROWS)
		{
			setColorsInBlockBoard();
			return false;
		}
		else if (blockBoardRef_.getBoardArrayRef().at(gridToX(3)).at(gridToY(3) + 1) != Color::White)
		{
			setColorsInBlockBoard();
			return false;
		}
		return true;
	}
	else return false;
}

const bool Block2::isMoveRightPossible() const noexcept
{
	if (currentPosition_ == TwoBlockPositions::Horizontal)
	{
		if (blockArray_.at(3).getPosition().x >= GRID * NUMBER_OF_COLUMNS
			or blockBoardRef_.getBoardArrayRef().at(gridToX(3) + 1).at(gridToY(3)) != Color::White)
		{
			return false;
		}
		return true;
	}
	else if (currentPosition_ == TwoBlockPositions::Vertical)
	{
		if (blockArray_.at(3).getPosition().x >= GRID * NUMBER_OF_COLUMNS
			or blockBoardRef_.getBoardArrayRef().at(gridToX(0) + 1).at(gridToY(3)) != Color::White
			or blockBoardRef_.getBoardArrayRef().at(gridToX(1) + 1).at(gridToY(3)) != Color::White
			or blockBoardRef_.getBoardArrayRef().at(gridToX(2) + 1).at(gridToY(3)) != Color::White
			or blockBoardRef_.getBoardArrayRef().at(gridToX(3) + 1).at(gridToY(3)) != Color::White)
		{
			return false;
		}
		return true;
	}
	else return false;
}

const bool Block2::isMoveLeftPossible() const noexcept
{
	if (currentPosition_ == TwoBlockPositions::Horizontal)
	{
		if (blockArray_.at(0).getPosition().x <= GRID
			or blockBoardRef_.getBoardArrayRef().at(gridToX(0) - 1).at(gridToY(0)) != Color::White)
		{
			return false;
		}
		return true;
	}
	else if (currentPosition_ == TwoBlockPositions::Vertical)
	{
		if (blockArray_.at(3).getPosition().x <= GRID
			or blockBoardRef_.getBoardArrayRef().at(gridToX(0) - 1).at(gridToY(3)) != Color::White
			or blockBoardRef_.getBoardArrayRef().at(gridToX(1) - 1).at(gridToY(3)) != Color::White
			or blockBoardRef_.getBoardArrayRef().at(gridToX(2) - 1).at(gridToY(3)) != Color::White
			or blockBoardRef_.getBoardArrayRef().at(gridToX(3) - 1).at(gridToY(3)) != Color::White)
		{
			return false;
		}
		return true;
	}
	else return false;
}

const bool Block2::isRotationPossible() const noexcept
{
	if (blockArray_.at(0).getPosition().y == GRID
		or blockArray_.at(0).getPosition().y == 2 * GRID)
	{
		return false;
	}
	else if (currentPosition_ == TwoBlockPositions::Horizontal)
	{
		if (blockArray_.at(1).getPosition().y > GRID
			and blockArray_.at(1).getPosition().y < GRID * NUMBER_OF_ROWS - GRID
			and blockBoardRef_.getBoardArrayRef().at(gridToX(1)).at(gridToY(1) - 1) == Color::White
			and blockBoardRef_.getBoardArrayRef().at(gridToX(1)).at(gridToY(1) + 1) == Color::White
			and blockBoardRef_.getBoardArrayRef().at(gridToX(1)).at(gridToY(1) + 2) == Color::White)
		{
			return true;
		}
		else return false;
	}
	else if (currentPosition_ == TwoBlockPositions::Vertical)
	{
		if (blockArray_.at(1).getPosition().x > GRID
			and blockArray_.at(1).getPosition().x < GRID * NUMBER_OF_COLUMNS - GRID
			and blockArray_.at(1).getPosition().y > GRID
			and blockArray_.at(1).getPosition().y < GRID * NUMBER_OF_ROWS - GRID
			and blockBoardRef_.getBoardArrayRef().at(gridToX(1) - 1).at(gridToY(1)) == Color::White
			and blockBoardRef_.getBoardArrayRef().at(gridToX(1) + 1).at(gridToY(1)) == Color::White
			and blockBoardRef_.getBoardArrayRef().at(gridToX(1) + 2).at(gridToY(1)) == Color::White)
		{
			return true;
		}
		else return false;
	}
	else return false;
}

void Block2::rotate() noexcept
{
	if (isRotationPossible())
	{
		if (currentPosition_ == TwoBlockPositions::Horizontal)
		{
			blockArray_.at(0).setPosition(blockArray_.at(0).getPosition().x + GRID, blockArray_.at(0).getPosition().y - GRID);
			blockArray_.at(2).setPosition(blockArray_.at(2).getPosition().x - GRID, blockArray_.at(2).getPosition().y + GRID);
			blockArray_.at(3).setPosition(blockArray_.at(3).getPosition().x - 2 * GRID, blockArray_.at(3).getPosition().y + 2 * GRID);
			currentPosition_ = TwoBlockPositions::Vertical;
		}
		else if (currentPosition_ == TwoBlockPositions::Vertical)
		{
			blockArray_.at(0).setPosition(blockArray_.at(0).getPosition().x - GRID, blockArray_.at(0).getPosition().y + GRID);
			blockArray_.at(2).setPosition(blockArray_.at(2).getPosition().x + GRID, blockArray_.at(2).getPosition().y - GRID);
			blockArray_.at(3).setPosition(blockArray_.at(3).getPosition().x + 2 * GRID, blockArray_.at(3).getPosition().y - 2 * GRID);
			currentPosition_ = TwoBlockPositions::Horizontal;
		}
	}
}

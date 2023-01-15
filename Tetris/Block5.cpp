#include "BlockBoard.hpp"
#include "Block5.hpp"

Block5::Block5(BlockBoard& blockBoardRef) noexcept
	: BaseBlock(blockBoardRef), currentPosition_(FourBlockPositions::FlatOnTop)
{
	for_each(begin(blockArray_), end(blockArray_), [](auto& block) { block = RectangleShape{ Vector2f{ GRID, GRID } }; });
	for_each(begin(blockArray_), end(blockArray_), [](auto& block) { block.setFillColor(Color::Red); });
	blockArray_.at(0).setPosition((NUMBER_OF_COLUMNS / 2) * GRID - GRID, GRID);
	blockArray_.at(1).setPosition((NUMBER_OF_COLUMNS / 2) * GRID, GRID);
	blockArray_.at(2).setPosition((NUMBER_OF_COLUMNS / 2) * GRID + GRID, GRID);
	blockArray_.at(3).setPosition((NUMBER_OF_COLUMNS / 2) * GRID + GRID, 2 * GRID);
}

const bool Block5::checkIfLost() const noexcept
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

const bool Block5::isFallingPossible() noexcept
{
	if (currentPosition_ == FourBlockPositions::FlatOnTop)
	{
		if (blockArray_.at(3).getPosition().y >= GRID * NUMBER_OF_ROWS)
		{
			setColorsInBlockBoard();
			return false;
		}
		else if (blockBoardRef_.getBoardArrayRef().at(gridToX(0)).at(gridToY(0) + 1) != Color::White
			or blockBoardRef_.getBoardArrayRef().at(gridToX(1)).at(gridToY(1) + 1) != Color::White
			or blockBoardRef_.getBoardArrayRef().at(gridToX(3)).at(gridToY(3) + 1) != Color::White)
		{
			setColorsInBlockBoard();
			return false;
		}
		return true;
	}
	else if (currentPosition_ == FourBlockPositions::FlatOnRigth)
	{
		if (blockArray_.at(2).getPosition().y >= GRID * NUMBER_OF_ROWS)
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
	else if (currentPosition_ == FourBlockPositions::FlatOnBottom)
	{
		if (blockArray_.at(1).getPosition().y >= GRID * NUMBER_OF_ROWS)
		{
			setColorsInBlockBoard();
			return false;
		}
		else if (blockBoardRef_.getBoardArrayRef().at(gridToX(0)).at(gridToY(0) + 1) != Color::White
			or blockBoardRef_.getBoardArrayRef().at(gridToX(1)).at(gridToY(1) + 1) != Color::White
			or blockBoardRef_.getBoardArrayRef().at(gridToX(2)).at(gridToY(2) + 1) != Color::White)
		{
			setColorsInBlockBoard();
			return false;
		}
		return true;
	}
	else if (currentPosition_ == FourBlockPositions::FlatOnLeft)
	{
		if (blockArray_.at(0).getPosition().y >= GRID * NUMBER_OF_ROWS)
		{
			setColorsInBlockBoard();
			return false;
		}
		else if (blockBoardRef_.getBoardArrayRef().at(gridToX(0)).at(gridToY(0) + 1) != Color::White
			or blockBoardRef_.getBoardArrayRef().at(gridToX(3)).at(gridToY(3) + 1) != Color::White)
		{
			setColorsInBlockBoard();
			return false;
		}
		return true;
	}
	return false;
}

const bool Block5::isMoveRightPossible() const noexcept
{
	if (currentPosition_ == FourBlockPositions::FlatOnTop)
	{
		if (blockArray_.at(2).getPosition().x >= GRID * NUMBER_OF_COLUMNS
			or blockBoardRef_.getBoardArrayRef().at(gridToX(2) + 1).at(gridToY(2)) != Color::White
			or blockBoardRef_.getBoardArrayRef().at(gridToX(3) + 1).at(gridToY(3)) != Color::White)
		{
			return false;
		}
		return true;
	}
	else if (currentPosition_ == FourBlockPositions::FlatOnRigth)
	{
		if (blockArray_.at(1).getPosition().x >= GRID * NUMBER_OF_COLUMNS
			or blockBoardRef_.getBoardArrayRef().at(gridToX(0) + 1).at(gridToY(0)) != Color::White
			or blockBoardRef_.getBoardArrayRef().at(gridToX(1) + 1).at(gridToY(1)) != Color::White
			or blockBoardRef_.getBoardArrayRef().at(gridToX(2) + 1).at(gridToY(2)) != Color::White)
		{
			return false;
		}
		return true;
	}
	else if (currentPosition_ == FourBlockPositions::FlatOnBottom)
	{
		if (blockArray_.at(0).getPosition().x >= GRID * NUMBER_OF_COLUMNS
			or blockBoardRef_.getBoardArrayRef().at(gridToX(0) + 1).at(gridToY(0)) != Color::White
			or blockBoardRef_.getBoardArrayRef().at(gridToX(3) + 1).at(gridToY(3)) != Color::White)
		{
			return false;
		}
		return true;
	}
	else if (currentPosition_ == FourBlockPositions::FlatOnLeft)
	{
		if (blockArray_.at(3).getPosition().x >= GRID * NUMBER_OF_COLUMNS
			or blockBoardRef_.getBoardArrayRef().at(gridToX(0) + 1).at(gridToY(0)) != Color::White
			or blockBoardRef_.getBoardArrayRef().at(gridToX(1) + 1).at(gridToY(1)) != Color::White
			or blockBoardRef_.getBoardArrayRef().at(gridToX(3) + 1).at(gridToY(3)) != Color::White)
		{
			return false;
		}
		return true;
	}
	return false;
}

const bool Block5::isMoveLeftPossible() const noexcept
{
	if (currentPosition_ == FourBlockPositions::FlatOnTop)
	{
		if (blockArray_.at(0).getPosition().x <= GRID
			or blockBoardRef_.getBoardArrayRef().at(gridToX(0) - 1).at(gridToY(0)) != Color::White
			or blockBoardRef_.getBoardArrayRef().at(gridToX(3) - 1).at(gridToY(3)) != Color::White)
		{
			return false;
		}
		return true;
	}
	else if (currentPosition_ == FourBlockPositions::FlatOnRigth)
	{
		if (blockArray_.at(3).getPosition().x <= GRID
			or blockBoardRef_.getBoardArrayRef().at(gridToX(0) - 1).at(gridToY(0)) != Color::White
			or blockBoardRef_.getBoardArrayRef().at(gridToX(1) - 1).at(gridToY(1)) != Color::White
			or blockBoardRef_.getBoardArrayRef().at(gridToX(3) - 1).at(gridToY(3)) != Color::White)
		{
			return false;
		}
		return true;
	}
	else if (currentPosition_ == FourBlockPositions::FlatOnBottom)
	{
		if (blockArray_.at(2).getPosition().x <= GRID
			or blockBoardRef_.getBoardArrayRef().at(gridToX(2) - 1).at(gridToY(2)) != Color::White
			or blockBoardRef_.getBoardArrayRef().at(gridToX(3) - 1).at(gridToY(3)) != Color::White)
		{
			return false;
		}
		return true;
	}
	else if (currentPosition_ == FourBlockPositions::FlatOnLeft)
	{
		if (blockArray_.at(1).getPosition().x <= GRID
			or blockBoardRef_.getBoardArrayRef().at(gridToX(0) - 1).at(gridToY(0)) != Color::White
			or blockBoardRef_.getBoardArrayRef().at(gridToX(1) - 1).at(gridToY(1)) != Color::White
			or blockBoardRef_.getBoardArrayRef().at(gridToX(2) - 1).at(gridToY(2)) != Color::White)
		{
			return false;
		}
		return true;
	}
	return false;
}

const bool Block5::isRotationPossible() const noexcept
{
	if (blockArray_.at(0).getPosition().y >= GRID * NUMBER_OF_ROWS + GRID
		or blockArray_.at(1).getPosition().y >= GRID * NUMBER_OF_ROWS + GRID
		or blockArray_.at(2).getPosition().y >= GRID * NUMBER_OF_ROWS + GRID
		or blockArray_.at(3).getPosition().y == GRID * NUMBER_OF_ROWS + GRID
		or blockArray_.at(0).getPosition().y == GRID)
	{
     		return false;
	}
	else if (currentPosition_ == FourBlockPositions::FlatOnTop)
	{
		if (blockArray_.at(1).getPosition().y < GRID * NUMBER_OF_ROWS
			and blockBoardRef_.getBoardArrayRef().at(gridToX(1)).at(gridToY(1) - 1) == Color::White
			and blockBoardRef_.getBoardArrayRef().at(gridToX(1) - 1).at(gridToY(1) + 1) == Color::White
			and blockBoardRef_.getBoardArrayRef().at(gridToX(1)).at(gridToY(1) + 1) == Color::White)
		{
			return true;
		}
		else return false;
	}
	else if (currentPosition_ == FourBlockPositions::FlatOnRigth)
	{
		if (blockArray_.at(1).getPosition().x > GRID
			and blockArray_.at(1).getPosition().x < GRID * NUMBER_OF_COLUMNS
			and blockBoardRef_.getBoardArrayRef().at(gridToX(1) + 1).at(gridToY(1)) == Color::White
			and blockBoardRef_.getBoardArrayRef().at(gridToX(1) - 1).at(gridToY(1)) == Color::White
			and blockBoardRef_.getBoardArrayRef().at(gridToX(1) - 1).at(gridToY(1) - 1) == Color::White)
		{
			return true;
		}
		else return false;
	}
	else if (currentPosition_ == FourBlockPositions::FlatOnBottom)
	{
		if (blockBoardRef_.getBoardArrayRef().at(gridToX(1)).at(gridToY(1) + 1) == Color::White
			and blockBoardRef_.getBoardArrayRef().at(gridToX(1)).at(gridToY(1) - 1) == Color::White
			and blockBoardRef_.getBoardArrayRef().at(gridToX(1) + 1).at(gridToY(1) - 1) == Color::White)
		{
			return true;
		}
		else return false;
	}
	else if (currentPosition_ == FourBlockPositions::FlatOnLeft)
	{
		if (blockArray_.at(1).getPosition().x > GRID
			and blockArray_.at(1).getPosition().x < GRID * NUMBER_OF_COLUMNS
			and blockBoardRef_.getBoardArrayRef().at(gridToX(1) - 1).at(gridToY(1)) == Color::White
			and blockBoardRef_.getBoardArrayRef().at(gridToX(1)).at(gridToY(1) + 1) == Color::White
			and blockBoardRef_.getBoardArrayRef().at(gridToX(1) + 1).at(gridToY(1) + 1) == Color::White)
		{
			return true;
		}
		else return false;
	}
	return false;
}

void Block5::rotate() noexcept
{
	if (isRotationPossible())
	{
		if (currentPosition_ == FourBlockPositions::FlatOnTop)
		{
			blockArray_.at(0).setPosition(blockArray_.at(0).getPosition().x + GRID, blockArray_.at(0).getPosition().y - GRID);
			blockArray_.at(2).setPosition(blockArray_.at(2).getPosition().x - GRID, blockArray_.at(2).getPosition().y + GRID);
			blockArray_.at(3).setPosition(blockArray_.at(3).getPosition().x - 2 * GRID, blockArray_.at(3).getPosition().y);
			currentPosition_ = FourBlockPositions::FlatOnRigth;
		}
		else if (currentPosition_ == FourBlockPositions::FlatOnRigth)
		{
			blockArray_.at(0).setPosition(blockArray_.at(0).getPosition().x + GRID, blockArray_.at(0).getPosition().y + GRID);
			blockArray_.at(2).setPosition(blockArray_.at(2).getPosition().x - GRID, blockArray_.at(2).getPosition().y - GRID);
			blockArray_.at(3).setPosition(blockArray_.at(3).getPosition().x, blockArray_.at(3).getPosition().y - 2 * GRID);
			currentPosition_ = FourBlockPositions::FlatOnBottom;
		}
		else if (currentPosition_ == FourBlockPositions::FlatOnBottom)
		{
			blockArray_.at(0).setPosition(blockArray_.at(0).getPosition().x - GRID, blockArray_.at(0).getPosition().y + GRID);
			blockArray_.at(2).setPosition(blockArray_.at(2).getPosition().x + GRID, blockArray_.at(2).getPosition().y - GRID);
			blockArray_.at(3).setPosition(blockArray_.at(3).getPosition().x + 2 * GRID, blockArray_.at(3).getPosition().y);
			currentPosition_ = FourBlockPositions::FlatOnLeft;
		}
		else if (currentPosition_ == FourBlockPositions::FlatOnLeft)
		{
			blockArray_.at(0).setPosition(blockArray_.at(0).getPosition().x - GRID, blockArray_.at(0).getPosition().y - GRID);
			blockArray_.at(2).setPosition(blockArray_.at(2).getPosition().x + GRID, blockArray_.at(2).getPosition().y + GRID);
			blockArray_.at(3).setPosition(blockArray_.at(3).getPosition().x, blockArray_.at(3).getPosition().y + 2 * GRID);
			currentPosition_ = FourBlockPositions::FlatOnTop;
		}
	}
}

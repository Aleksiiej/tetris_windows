#include "Block5.hpp"

Block5::Block5(BlockBoard& blockBoardRef) noexcept
	: BaseBlock(blockBoardRef), currentPosition_(FourBlockPositions::FlatOnTop)
{
	std::ranges::for_each(blockArray_, [](auto& block) { block = sf::RectangleShape{ sf::Vector2f{ GRID, GRID } };
	block.setFillColor(sf::Color::Red); });
	blockArray_.at(0).setPosition((NUMBER_OF_COLUMNS / 2) * GRID - GRID, GRID);
	blockArray_.at(1).setPosition((NUMBER_OF_COLUMNS / 2) * GRID, GRID);
	blockArray_.at(2).setPosition((NUMBER_OF_COLUMNS / 2) * GRID + GRID, GRID);
	blockArray_.at(3).setPosition((NUMBER_OF_COLUMNS / 2) * GRID + GRID, 2 * GRID);
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
	switch (currentPosition_)
	{
	case FourBlockPositions::FlatOnTop:
		if (blockArray_.at(1).getPosition().y < GRID * NUMBER_OF_ROWS
			and blockBoardRef_.getBoardArrayRef().at(gridToX(1)).at(gridToY(1) - 1) == sf::Color::White
			and blockBoardRef_.getBoardArrayRef().at(gridToX(1) - 1).at(gridToY(1) + 1) == sf::Color::White
			and blockBoardRef_.getBoardArrayRef().at(gridToX(1)).at(gridToY(1) + 1) == sf::Color::White)
		{
			return true;
		}
		return false;

	case FourBlockPositions::FlatOnRigth:
		if (blockArray_.at(1).getPosition().x > GRID
			and blockArray_.at(1).getPosition().x < GRID * NUMBER_OF_COLUMNS
			and blockBoardRef_.getBoardArrayRef().at(gridToX(1) + 1).at(gridToY(1)) == sf::Color::White
			and blockBoardRef_.getBoardArrayRef().at(gridToX(1) - 1).at(gridToY(1)) == sf::Color::White
			and blockBoardRef_.getBoardArrayRef().at(gridToX(1) - 1).at(gridToY(1) - 1) == sf::Color::White)
		{
			return true;
		}
		return false;

	case FourBlockPositions::FlatOnBottom:
		if (blockBoardRef_.getBoardArrayRef().at(gridToX(1)).at(gridToY(1) + 1) == sf::Color::White
			and blockBoardRef_.getBoardArrayRef().at(gridToX(1)).at(gridToY(1) - 1) == sf::Color::White
			and blockBoardRef_.getBoardArrayRef().at(gridToX(1) + 1).at(gridToY(1) - 1) == sf::Color::White)
		{
			return true;
		}
		return false;

	case FourBlockPositions::FlatOnLeft:
		if (blockArray_.at(1).getPosition().x > GRID
			and blockArray_.at(1).getPosition().x < GRID * NUMBER_OF_COLUMNS
			and blockBoardRef_.getBoardArrayRef().at(gridToX(1) - 1).at(gridToY(1)) == sf::Color::White
			and blockBoardRef_.getBoardArrayRef().at(gridToX(1)).at(gridToY(1) + 1) == sf::Color::White
			and blockBoardRef_.getBoardArrayRef().at(gridToX(1) + 1).at(gridToY(1) + 1) == sf::Color::White)
		{
			return true;
		}
		return false;
	}
	return false;
}

void Block5::rotate() noexcept
{
	if (isRotationPossible())
	{
		switch (currentPosition_)
		{
		case FourBlockPositions::FlatOnTop:
			blockArray_.at(0).setPosition(blockArray_.at(0).getPosition().x + GRID, blockArray_.at(0).getPosition().y - GRID);
			blockArray_.at(2).setPosition(blockArray_.at(2).getPosition().x - GRID, blockArray_.at(2).getPosition().y + GRID);
			blockArray_.at(3).setPosition(blockArray_.at(3).getPosition().x - 2 * GRID, blockArray_.at(3).getPosition().y);
			currentPosition_ = FourBlockPositions::FlatOnRigth;
			break;

		case FourBlockPositions::FlatOnRigth:
			blockArray_.at(0).setPosition(blockArray_.at(0).getPosition().x + GRID, blockArray_.at(0).getPosition().y + GRID);
			blockArray_.at(2).setPosition(blockArray_.at(2).getPosition().x - GRID, blockArray_.at(2).getPosition().y - GRID);
			blockArray_.at(3).setPosition(blockArray_.at(3).getPosition().x, blockArray_.at(3).getPosition().y - 2 * GRID);
			currentPosition_ = FourBlockPositions::FlatOnBottom;
			break;

		case FourBlockPositions::FlatOnBottom:
			blockArray_.at(0).setPosition(blockArray_.at(0).getPosition().x - GRID, blockArray_.at(0).getPosition().y + GRID);
			blockArray_.at(2).setPosition(blockArray_.at(2).getPosition().x + GRID, blockArray_.at(2).getPosition().y - GRID);
			blockArray_.at(3).setPosition(blockArray_.at(3).getPosition().x + 2 * GRID, blockArray_.at(3).getPosition().y);
			currentPosition_ = FourBlockPositions::FlatOnLeft;
			break;

		case FourBlockPositions::FlatOnLeft:
			blockArray_.at(0).setPosition(blockArray_.at(0).getPosition().x - GRID, blockArray_.at(0).getPosition().y - GRID);
			blockArray_.at(2).setPosition(blockArray_.at(2).getPosition().x + GRID, blockArray_.at(2).getPosition().y + GRID);
			blockArray_.at(3).setPosition(blockArray_.at(3).getPosition().x, blockArray_.at(3).getPosition().y + 2 * GRID);
			currentPosition_ = FourBlockPositions::FlatOnTop;
			break;
		}
	}
}

#include "Block6.hpp"

Block6::Block6(BlockBoard& blockBoardRef) noexcept
	: BaseBlock(blockBoardRef), currentPosition_(TwoBlockPositions::Horizontal)
{
	std::for_each(begin(blockArray_), end(blockArray_), [](auto& block) { block = sf::RectangleShape{ sf::Vector2f{ GRID, GRID } }; });
	std::for_each(begin(blockArray_), end(blockArray_), [](auto& block) { block.setFillColor(sf::Color::Red); });
	blockArray_.at(0).setPosition((NUMBER_OF_COLUMNS / 2) * GRID - GRID, 2 * GRID);
	blockArray_.at(1).setPosition((NUMBER_OF_COLUMNS / 2) * GRID, 2 * GRID);
	blockArray_.at(2).setPosition((NUMBER_OF_COLUMNS / 2) * GRID, GRID);
	blockArray_.at(3).setPosition((NUMBER_OF_COLUMNS / 2) * GRID + GRID, GRID);
}

const bool Block6::isRotationPossible() const noexcept
{
	if (currentPosition_ == TwoBlockPositions::Horizontal)
	{
		if (blockArray_.at(0).getPosition().y < GRID * NUMBER_OF_ROWS
			and blockBoardRef_.getBoardArrayRef().at(gridToX(1)).at(gridToY(1) - 1) == sf::Color::White
			and blockBoardRef_.getBoardArrayRef().at(gridToX(1) + 1).at(gridToY(1)) == sf::Color::White
			and blockBoardRef_.getBoardArrayRef().at(gridToX(1) + 1).at(gridToY(1) + 1) == sf::Color::White)
		{
			return true;
		}
		else return false;
	}
	else if (currentPosition_ == TwoBlockPositions::Vertical)
	{
		if (blockArray_.at(1).getPosition().x > GRID
			and blockBoardRef_.getBoardArrayRef().at(gridToX(1) - 1).at(gridToY(1)) == sf::Color::White
			and blockBoardRef_.getBoardArrayRef().at(gridToX(1) + 1).at(gridToY(1) - 1) == sf::Color::White)
		{
			return true;
		}
		else return false;
	}
	return false;
}

void Block6::rotate() noexcept
{
	if (isRotationPossible())
	{
		if (currentPosition_ == TwoBlockPositions::Horizontal)
		{
			blockArray_.at(0).setPosition(blockArray_.at(0).getPosition().x + GRID, blockArray_.at(0).getPosition().y - GRID);
			blockArray_.at(2).setPosition(blockArray_.at(2).getPosition().x + GRID, blockArray_.at(2).getPosition().y + GRID);
			blockArray_.at(3).setPosition(blockArray_.at(3).getPosition().x, blockArray_.at(3).getPosition().y + 2 * GRID);
			currentPosition_ = TwoBlockPositions::Vertical;
		}
		else if (currentPosition_ == TwoBlockPositions::Vertical)
		{
			blockArray_.at(0).setPosition(blockArray_.at(0).getPosition().x - GRID, blockArray_.at(0).getPosition().y + GRID);
			blockArray_.at(2).setPosition(blockArray_.at(2).getPosition().x - GRID, blockArray_.at(2).getPosition().y - GRID);
			blockArray_.at(3).setPosition(blockArray_.at(3).getPosition().x, blockArray_.at(3).getPosition().y - 2 * GRID);
			currentPosition_ = TwoBlockPositions::Horizontal;
		}
	}
}

#include "Block2.hpp"

Block2::Block2(BlockBoard& blockBoardRef) noexcept
	: BaseBlock(blockBoardRef), currentPosition_(TwoBlockPositions::Horizontal)
{
	std::ranges::for_each(blockArray_, [](auto& block) { block = sf::RectangleShape{ sf::Vector2f{ GRID, GRID } }; 
	block.setFillColor(sf::Color::Red); });
	blockArray_.at(0).setPosition((NUMBER_OF_COLUMNS / 2) * GRID - GRID, GRID);
	blockArray_.at(1).setPosition((NUMBER_OF_COLUMNS / 2) * GRID, GRID);
	blockArray_.at(2).setPosition((NUMBER_OF_COLUMNS / 2) * GRID + GRID, GRID);
	blockArray_.at(3).setPosition((NUMBER_OF_COLUMNS / 2) * GRID + 2 * GRID, GRID);
}

const bool Block2::isRotationPossible() const noexcept
{
	if (blockArray_.at(1).getPosition().y == GRID
		or blockArray_.at(1).getPosition().y == 2 * GRID)
	{
		return false;
	}
	int newX{ 0 };
	int newY{ 0 };
	std::vector<std::pair<float, float>> newCoords;
	for (const auto& el : blockArray_)
	{
		newX = blockArray_.at(1).getPosition().x + blockArray_.at(1).getPosition().y - el.getPosition().y;
		newY = blockArray_.at(1).getPosition().y - blockArray_.at(1).getPosition().x + el.getPosition().x;
		newCoords.push_back({ newX, newY });
	}
	for (auto& el : newCoords)
	{
		if (el.first < GRID
			or el.first > GRID * NUMBER_OF_COLUMNS
			or el.second < GRID
			or el.second > GRID * NUMBER_OF_ROWS
			or blockBoardRef_.getBoardArrayRef().at(gridToX(el.first)).at(gridToY(el.second)) != sf::Color::White)
		{
			return false;
		}
	}
	return true;
}

void Block2::rotate() noexcept
{
	if (isRotationPossible())
	{
		int newX{ 0 };
		int newY{ 0 };
		for (auto& el : blockArray_)
		{
			newX = blockArray_.at(1).getPosition().x + blockArray_.at(1).getPosition().y - el.getPosition().y;
			newY = blockArray_.at(1).getPosition().y - blockArray_.at(1).getPosition().x + el.getPosition().x;
			el.setPosition(newX, newY);
		}
	}
}

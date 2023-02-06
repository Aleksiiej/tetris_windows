#include "BaseBlock.hpp"

BaseBlock::BaseBlock(BlockBoard& blockBoardRef) noexcept : blockBoardRef_(blockBoardRef)
{}

void BaseBlock::fall() noexcept
{
	std::for_each(begin(blockArray_), end(blockArray_), [](auto& block) { block.move(0, GRID); });
}

void BaseBlock::moveRight() noexcept
{
	if (isMoveRightPossible())
	{
		std::for_each(begin(blockArray_), end(blockArray_), [](auto& block) { block.move(GRID, 0); });
	}
}

void BaseBlock::moveLeft() noexcept
{
	if (isMoveLeftPossible())
	{
		std::for_each(begin(blockArray_), end(blockArray_), [](auto& block) { block.move(-GRID, 0); });
	}
}

void BaseBlock::moveDown() noexcept
{
	while (isFallingPossible())
	{
		std::for_each(begin(blockArray_), end(blockArray_), [](auto& block) { block.move(0, GRID); });
	}
}

bool BaseBlock::isFallingPossible() noexcept
{
	auto blockCoords = getCoords();
	auto newCoords{ blockCoords };
	std::for_each(begin(newCoords), end(newCoords), [](auto& coords) { coords.second += GRID; });
	extractAdjacentCoords(blockCoords, newCoords);

	for (const auto& field : newCoords)
	{
		if (field.second > GRID * NUMBER_OF_ROWS
			or blockBoardRef_.getBoardArrayRef().at(gridToX(field.first)).at(gridToY(field.second)) != sf::Color::White)
		{
			setColorsInBlockBoard();
			return false;
		}
	}
	return true;
}

bool BaseBlock::isMoveRightPossible() noexcept
{
	auto blockCoords = getCoords();
	auto newCoords{ blockCoords };
	std::for_each(begin(newCoords), end(newCoords), [](auto& coords) { coords.first += GRID; });
	extractAdjacentCoords(blockCoords, newCoords);

	for (const auto& field : newCoords)
	{
		if (field.first > GRID * NUMBER_OF_COLUMNS
			or blockBoardRef_.getBoardArrayRef().at(gridToX(field.first)).at(gridToY(field.second)) != sf::Color::White)
		{
			return false;
		}
	}
	return true;
}

bool BaseBlock::isMoveLeftPossible() noexcept
{
	auto blockCoords = getCoords();
	auto newCoords{ blockCoords };
	std::for_each(begin(newCoords), end(newCoords), [](auto& coords) { coords.first -= GRID; });
	extractAdjacentCoords(blockCoords, newCoords);

	for (const auto& field : newCoords)
	{
		if (blockBoardRef_.getBoardArrayRef().at(gridToX(field.first)).at(gridToY(field.second)) != sf::Color::White
			or field.first <= 0)
		{
			return false;
		}
	}
	return true;
}

bool BaseBlock::checkIfLost() const noexcept
{
	bool isAtTopLine = false;
	bool isOccupied = false;
	for (uint8_t i = 0; i < 4; i++)
	{
		if (blockArray_.at(i).getPosition().y == GRID)
		{
			isAtTopLine = true;
		}
		if (blockBoardRef_.getBoardArrayRef().at(gridToX(i)).at(gridToY(i)) != sf::Color::White)
		{
			isOccupied = true;
		}
	}
	return(isAtTopLine and isOccupied);
}

void BaseBlock::setColor(const sf::Color& color) noexcept
{
	std::for_each(begin(blockArray_), end(blockArray_), [&](auto& block) { block.setFillColor(color); });
}

const std::array<sf::RectangleShape, 4>& BaseBlock::getBlockArrayRef() const noexcept
{
	return blockArray_;
}

void BaseBlock::setColorsInBlockBoard() const noexcept
{
	for (uint8_t i = 0; i < 4; i++)
	{
		blockBoardRef_.setFillColor(gridToX(i), gridToY(i), blockArray_.at(0).getFillColor());
	}
}

std::vector<std::pair<float, float>> BaseBlock::getCoords() const noexcept
{
	std::vector<std::pair<float, float>> blockCoords;
	for (uint8_t i = 0; i < 4; i++)
	{
		blockCoords.push_back(std::make_pair(blockArray_.at(i).getPosition().x, blockArray_.at(i).getPosition().y));
	}
	return blockCoords;
}

void BaseBlock::extractAdjacentCoords(std::vector<std::pair<float, float>>& blockCoords, std::vector<std::pair<float, float>>& newCoords) noexcept
{
	for (auto It = begin(newCoords); It != end(newCoords); It++)
	{
		if (std::any_of(cbegin(blockCoords), cend(blockCoords), [&](const auto& coord) { return It->first == coord.first and It->second == coord.second; }))
		{
			newCoords.erase(It);
			It = begin(newCoords);
		}
	}
}

int BaseBlock::gridToX(const float& blockNumber) const noexcept
{
	if (blockNumber >= 0 and blockNumber < 5)
	{
		return static_cast<int>((blockArray_.at(static_cast<std::size_t>(blockNumber)).getPosition().x - GRID) / GRID);
	}
	else return static_cast<int>((blockNumber - GRID) / GRID);
}

int BaseBlock::gridToY(const float& blockNumber) const noexcept
{
	if (blockNumber >= 0 and blockNumber < 5)
	{
		return static_cast<int>((blockArray_.at(static_cast<std::size_t>(blockNumber)).getPosition().y - GRID) / GRID);
	}
	else return static_cast<int>((blockNumber - GRID) / GRID);
}
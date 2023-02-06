#include "BaseBlock.hpp"
#include "BlockBoard.hpp"

#include <algorithm>

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

const bool BaseBlock::isFallingPossible() const noexcept
{
	auto blockCoords = move(getCoords());
	auto coordsToDown = blockCoords;
	std::for_each(begin(coordsToDown), end(coordsToDown), [](auto& coords) { coords.second += GRID; });

	for (auto It = begin(coordsToDown); It != end(coordsToDown); It++)
	{
		if (std::any_of(begin(blockCoords), end(blockCoords), [&](const auto& coord) { return It->first == coord.first and It->second == coord.second; }))
		{
			coordsToDown.erase(It);
			It = begin(coordsToDown);
		}
	}

	for (const auto& field : coordsToDown)
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

const bool BaseBlock::isMoveRightPossible() const noexcept
{
	auto blockCoords = move(getCoords());
	auto coordsToRight = blockCoords;
	std::for_each(begin(coordsToRight), end(coordsToRight), [](auto& coords) { coords.first += GRID; });

	for (auto It = begin(coordsToRight); It != end(coordsToRight); It++)
	{
		if (std::any_of(begin(blockCoords), end(blockCoords), [&](const auto& coord) { return It->first == coord.first and It->second == coord.second; }))
		{
			coordsToRight.erase(It);
			It = begin(coordsToRight);
		}
	}

	for (const auto& field : coordsToRight)
	{
		if (field.first > GRID * NUMBER_OF_COLUMNS
			or blockBoardRef_.getBoardArrayRef().at(gridToX(field.first)).at(gridToY(field.second)) != sf::Color::White)
		{
			return false;
		}
	}
	return true;
}

const bool BaseBlock::isMoveLeftPossible() const noexcept
{
	auto blockCoords = move(getCoords());
	auto coordsToLeft = blockCoords;
	std::for_each(begin(coordsToLeft), end(coordsToLeft), [](auto& coords) { coords.first -= GRID; });

	for (auto It = begin(coordsToLeft); It != end(coordsToLeft); It++)
	{
		if (std::any_of(begin(blockCoords), end(blockCoords), [&](const auto& coord) { return It->first == coord.first and It->second == coord.second; }))
		{
			coordsToLeft.erase(It);
			It = begin(coordsToLeft);
		}
	}

	for (const auto& field : coordsToLeft)
	{
		if (blockBoardRef_.getBoardArrayRef().at(gridToX(field.first)).at(gridToY(field.second)) != sf::Color::White
			or field.first <= 0)
		{
			return false;
		}
	}
	return true;
}

const bool BaseBlock::checkIfLost() const noexcept
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

void BaseBlock::setColorsInBlockBoard() const noexcept
{
	for (uint8_t i = 0; i < 4; i++)
	{
		blockBoardRef_.setFillColor(gridToX(i), gridToY(i), blockArray_.at(0).getFillColor());
	}
}

const std::array<sf::RectangleShape, 4>& BaseBlock::getBlockArrayRef() const noexcept
{
	return blockArray_;
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

const int BaseBlock::gridToX(const float& blockNumber) const noexcept
{
	if (blockNumber >= 0 and blockNumber < 5)
	{
		return static_cast<uint8_t>((blockArray_.at(blockNumber).getPosition().x - GRID) / GRID);
	}
	else return static_cast<int>((blockNumber - GRID) / GRID);
}

const int BaseBlock::gridToY(const float& blockNumber) const noexcept
{
	if (blockNumber >= 0 and blockNumber < 5)
	{
		return static_cast<uint8_t>((blockArray_.at(blockNumber).getPosition().y - GRID) / GRID);
	}
	else return static_cast<int>((blockNumber - GRID) / GRID);
}
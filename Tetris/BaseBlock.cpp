#include "BaseBlock.hpp"
#include "BlockBoard.hpp"
#include "GlobalValues.hpp"

#include <algorithm>
#include <iostream>

BaseBlock::BaseBlock(BlockBoard& blockBoardRef) noexcept : blockBoardRef_(blockBoardRef)
{}

void BaseBlock::fall() noexcept
{
	for_each(begin(blockArray_), end(blockArray_), [](auto& block) { block.move(0, GRID); });
}

void BaseBlock::moveRight() noexcept
{
	for_each(begin(blockArray_), end(blockArray_), [](auto& block) { block.move(GRID, 0); });
}

void BaseBlock::moveLeft() noexcept
{
	for_each(begin(blockArray_), end(blockArray_), [](auto& block) { block.move(-GRID, 0); });
}

const bool BaseBlock::isMoveRightPossible() const noexcept
{
	auto blockCoords = move(getCoords());
	auto coordsToTheRight = blockCoords;
	for_each(begin(coordsToTheRight), end(coordsToTheRight), [](auto& coords) { coords.first += GRID; });

	for (auto It = begin(coordsToTheRight); It != end(coordsToTheRight); It++)
	{
		if (any_of(begin(blockCoords), end(blockCoords), [&](const auto& coord) { return It->first == coord.first and It->second == coord.second; }))
		{
			coordsToTheRight.erase(It);
			It = begin(coordsToTheRight);
		}
	}

	for (const auto& field : coordsToTheRight)
	{
		if (field.first >= GRID * NUMBER_OF_COLUMNS + GRID
			or blockBoardRef_.getBoardArrayRef().at(gridToX(field.first)).at(gridToY(field.second)) != Color::White)
		{
			return false;
		}
	}
	return true;
}

const bool BaseBlock::isMoveLeftPossible() const noexcept
{
	auto blockCoords = move(getCoords());
	auto coordsToTheLeft = blockCoords;
	for_each(begin(coordsToTheLeft), end(coordsToTheLeft), [](auto& coords) { coords.first -= GRID; });

	for (auto It = begin(coordsToTheLeft); It != end(coordsToTheLeft); It++)
	{
		if (any_of(begin(blockCoords), end(blockCoords), [&](const auto& coord) { return It->first == coord.first and It->second == coord.second; }))
		{
			coordsToTheLeft.erase(It);
			It = begin(coordsToTheLeft);
		}
	}

	for (const auto& field : coordsToTheLeft)
	{
		if (blockBoardRef_.getBoardArrayRef().at(gridToX(field.first)).at(gridToY(field.second)) != Color::White
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
		if (blockBoardRef_.getBoardArrayRef().at(gridToX(i)).at(gridToY(i)) != Color::White)
		{
			isOccupied = true;
		}
	}
	return(isAtTopLine and isOccupied);
}

void BaseBlock::setColor(const Color& color) noexcept
{
	for_each(begin(blockArray_), end(blockArray_), [&](auto& block) { block.setFillColor(color); });
}

void BaseBlock::setColorsInBlockBoard() const noexcept
{
	for (uint8_t i = 0; i < 4; i++)
	{
		blockBoardRef_.setFillColor(gridToX(i), gridToY(i), blockArray_.at(0).getFillColor());
	}
}

const array<RectangleShape, 4>& BaseBlock::getBlockArrayRef() const noexcept
{
	return blockArray_;
}

vector<pair<float, float>> BaseBlock::getCoords() const noexcept
{
	vector<pair<float, float>> blockCoords;
	for (uint8_t i = 0; i < 4; i++)
	{
		blockCoords.push_back(make_pair(blockArray_.at(i).getPosition().x, blockArray_.at(i).getPosition().y));
	}
	return blockCoords;
}

const int BaseBlock::gridToX(const float& blockNumber) const noexcept
{
	switch (static_cast<int>(blockNumber))
	{
	case 0:
		return static_cast<uint8_t>((blockArray_.at(0).getPosition().x - GRID) / GRID);
	case 1:
		return static_cast<uint8_t>((blockArray_.at(1).getPosition().x - GRID) / GRID);
	case 2:
		return static_cast<uint8_t>((blockArray_.at(2).getPosition().x - GRID) / GRID);
	case 3:
		return static_cast<uint8_t>((blockArray_.at(3).getPosition().x - GRID) / GRID);
	default:
		return static_cast<int>((blockNumber - GRID) / GRID);
	}
}

const int BaseBlock::gridToY(const float& blockNumber) const noexcept
{
	switch (static_cast<int>(blockNumber))
	{
	case 0:
		return static_cast<uint8_t>((blockArray_.at(0).getPosition().y - GRID) / GRID);
	case 1:
		return static_cast<uint8_t>((blockArray_.at(1).getPosition().y - GRID) / GRID);
	case 2:
		return static_cast<uint8_t>((blockArray_.at(2).getPosition().y - GRID) / GRID);
	case 3:
		return static_cast<uint8_t>((blockArray_.at(3).getPosition().y - GRID) / GRID);
	default:
		return static_cast<int>((blockNumber - GRID) / GRID);
	}
}
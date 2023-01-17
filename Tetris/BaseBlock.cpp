#include "BaseBlock.hpp"
#include "BlockBoard.hpp"
#include "GlobalValues.hpp"

#include <algorithm>
#include <array>

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

const bool BaseBlock::checkColisionWithLeftBand(const array<RectangleShape, 4>& blockArray_) // TODO: Remove if not needed
{
	return std::any_of(begin(blockArray_), end(blockArray_), [](auto& block) { return block.getPosition().x <= GRID; });
}

const bool BaseBlock::checkColisionWithRightBand(const array<RectangleShape, 4>& blockArray_) // TODO: Remove if not needed
{
	return std::any_of(begin(blockArray_), end(blockArray_), [](auto& block) { return block.getPosition().x >= GRID * NUMBER_OF_COLUMNS; });
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

const uint8_t BaseBlock::gridToX(const uint8_t& blockNumber) const noexcept
{
	switch (blockNumber)
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
		return 255;
	}
}

const uint8_t BaseBlock::gridToY(const uint8_t& blockNumber) const noexcept
{
	switch (blockNumber)
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
		return 255;
	}
}
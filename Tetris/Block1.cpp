#include "Block1.hpp"

Block1::Block1(BlockBoard& blockBoardRef) noexcept
	: BaseBlock(blockBoardRef)
{
	std::for_each(begin(blockArray_), end(blockArray_), [](auto& block) { block = sf::RectangleShape{ sf::Vector2f{ GRID, GRID } }; });
	std::for_each(begin(blockArray_), end(blockArray_), [](auto& block) { block.setFillColor(sf::Color::Red); });
	blockArray_.at(0).setPosition((NUMBER_OF_COLUMNS / 2) * GRID, GRID);
	blockArray_.at(1).setPosition((NUMBER_OF_COLUMNS / 2) * GRID + GRID, GRID);
	blockArray_.at(2).setPosition((NUMBER_OF_COLUMNS / 2) * GRID, 2 * GRID);
	blockArray_.at(3).setPosition((NUMBER_OF_COLUMNS / 2) * GRID + GRID, 2 * GRID);
}

const bool Block1::isRotationPossible() const noexcept
{
	return false;
}

void Block1::rotate() noexcept
{
	return;
}

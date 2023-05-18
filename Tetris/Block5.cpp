#include "Block5.hpp"

Block5::Block5(BlockBoard& blockBoardRef) noexcept
	: BaseBlock(blockBoardRef)
{
	std::ranges::for_each(blockArray_, [](auto& block) { block = sf::RectangleShape{ sf::Vector2f{ GRID, GRID } };
	block.setFillColor(sf::Color::Red); });
	blockArray_.at(0).setPosition((NUMBER_OF_COLUMNS / 2) * GRID - GRID, GRID);
	blockArray_.at(1).setPosition((NUMBER_OF_COLUMNS / 2) * GRID, GRID);
	blockArray_.at(2).setPosition((NUMBER_OF_COLUMNS / 2) * GRID + GRID, GRID);
	blockArray_.at(3).setPosition((NUMBER_OF_COLUMNS / 2) * GRID + GRID, 2 * GRID);
}

#pragma once

#include "BlockBoard.hpp"

class BaseBlock
{
public:
	BaseBlock() = delete;
	BaseBlock(BlockBoard& blockBoardRef) noexcept;
	BaseBlock(const BaseBlock& other) = delete;
	BaseBlock(const BaseBlock&& other) = delete;
	~BaseBlock() = default;

	void fall() noexcept;
	void moveRight() noexcept;
	void moveLeft() noexcept;
	void moveDown() noexcept;
	void rotate() noexcept;

	bool isFallingPossible() noexcept;
	bool isMoveRightPossible() noexcept;
	bool isMoveLeftPossible() noexcept;
	const bool isRotationPossible() const noexcept;
	bool checkIfLost() const noexcept;

	void setColor(const sf::Color& color) noexcept;
	const std::array<sf::RectangleShape, 4>& getBlockArrayRef() const noexcept;

protected:
	std::array<sf::RectangleShape, 4> blockArray_;
	BlockBoard& blockBoardRef_;

	void setColorsInBlockBoard() const noexcept;
	std::vector<std::pair<float, float>> getCoords() const noexcept;
	void extractAdjacentCoords(std::vector<std::pair<float, float>>& blockCoords, std::vector<std::pair<float, float>>& newCoords) noexcept;
	int gridToX(const float& blockNumber) const noexcept;
	int gridToY(const float& blockNumber) const noexcept;
};

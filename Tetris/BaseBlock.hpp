#pragma once

#include <array>
#include <SFML/Graphics.hpp>
#include <utility>

#include "BlockBoard.hpp"
#include "GlobalValues.hpp"

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
	virtual void rotate() noexcept {}

	const bool checkIfLost() const noexcept;
	const bool isFallingPossible() noexcept;
	const bool isMoveRightPossible() noexcept;
	const bool isMoveLeftPossible() noexcept;
	virtual const bool isRotationPossible() const noexcept { return false; }

	void setColor(const sf::Color& color) noexcept;
	void setColorsInBlockBoard() const noexcept;
	const std::array<sf::RectangleShape, 4>& getBlockArrayRef() const noexcept;
	std::vector<std::pair<float, float>> getCoords() const noexcept;

protected:
	std::array<sf::RectangleShape, 4> blockArray_;
	BlockBoard& blockBoardRef_;

	void extractAdjacentCoords(std::vector<std::pair<float, float>>& blockCoords, std::vector<std::pair<float, float>>& newCoords) noexcept;
	const int gridToX(const float& blockNumber) const noexcept;
	const int gridToY(const float& blockNumber) const noexcept;
};

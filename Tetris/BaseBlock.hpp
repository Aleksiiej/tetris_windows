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

	bool checkIfLost() const noexcept;
	bool isFallingPossible() noexcept;
	bool isMoveRightPossible() noexcept;
	bool isMoveLeftPossible() noexcept;
	virtual const bool isRotationPossible() const noexcept { return false; }

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

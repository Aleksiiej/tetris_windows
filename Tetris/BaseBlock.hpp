#pragma once

#include <SFML/Graphics.hpp>

#include <array>
#include <utility>

using namespace sf;
using namespace std;

class BlockBoard;

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
	virtual void rotate() noexcept {}

	const bool checkIfLost() const noexcept;
	const bool isFallingPossible() const noexcept;
	const bool isMoveRightPossible() const noexcept;
	const bool isMoveLeftPossible() const noexcept;
	virtual const bool isRotationPossible() const noexcept { return false; }

	void setColor(const Color& color) noexcept;
	void setColorsInBlockBoard() const noexcept;
	const array<RectangleShape, 4>& getBlockArrayRef() const noexcept;
	vector<pair<float, float>> getCoords() const noexcept;

protected:
	array<RectangleShape, 4> blockArray_;
	BlockBoard& blockBoardRef_;

	const int gridToX(const float& blockNumber) const noexcept;
	const int gridToY(const float& blockNumber) const noexcept;
};

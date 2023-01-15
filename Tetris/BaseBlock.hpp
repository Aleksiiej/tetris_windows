#pragma once

#include <SFML/Graphics.hpp>

#include <array>

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

	virtual const bool checkIfLost() const noexcept { return false; }
	virtual const bool isFallingPossible() noexcept { return false; }
	virtual const bool isMoveRightPossible() const noexcept { return false; }
	virtual const bool isMoveLeftPossible() const noexcept { return false; }
	virtual const bool isRotationPossible() const noexcept { return false; }
	virtual void rotate() noexcept {}

	void setColor(const Color& color) noexcept;
	void setColorsInBlockBoard() const noexcept;
	const array<RectangleShape, 4>& getBlockArrayRef() const noexcept;

protected:
	array<RectangleShape, 4> blockArray_;
	BlockBoard& blockBoardRef_;

	const uint8_t gridToX(const uint8_t& blockNumber) const noexcept;
	const uint8_t gridToY(const uint8_t& blockNumber) const noexcept;
};

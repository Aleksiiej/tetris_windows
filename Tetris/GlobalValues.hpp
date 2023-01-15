#pragma once

constexpr uint8_t NUMBER_OF_ROWS = 20;
constexpr uint8_t NUMBER_OF_COLUMNS = 10;
constexpr uint8_t GRID = 25;
constexpr uint8_t GAME_SPEED = 200;

enum class GameStatus
{
	Ongoing, Lost
};

enum class TwoBlockPositions
{
	Horizontal, Vertical
};

enum class FourBlockPositions
{
	FlatOnTop, FlatOnRigth, FlatOnBottom, FlatOnLeft
};

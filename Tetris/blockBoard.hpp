#pragma once

#include <array>

#include "GlobalValues.hpp"
#include "ScoreCounter.hpp"

using namespace sf;
using namespace std;
using BoardArray = array<array<Color, NUMBER_OF_ROWS>, NUMBER_OF_COLUMNS>;

class BlockBoard
{
public:
	BlockBoard(ScoreCounter& scoreCounter) noexcept;
	BlockBoard(const BlockBoard& other) = delete;
	BlockBoard(const BlockBoard&& other) = delete;
	~BlockBoard() = default;

	void handleFilledRows() noexcept;
	const vector<uint8_t> checkWhichRowsFilled() const noexcept;
	void deleteFilledRows(const vector<uint8_t>& vectorOfRows) noexcept;
	void clear() noexcept;

	BoardArray& getBoardArrayRef() noexcept;
	void setFillColor(const uint8_t& x, const uint8_t& y, const Color& color) noexcept;

private:
	BoardArray blockBoard_;
	ScoreCounter& scoreCounter_;
};


#pragma once

#include <SFML/Graphics.hpp>

#include "GlobalValues.hpp"

using namespace sf;

class Band : public sf::Drawable
{
public:
	Band(const uint8_t& bandX, const uint8_t& bandY) noexcept;
	Band() = delete;
	Band(const Band& other) = delete;
	Band(const Band&& other) = delete;
	~Band() = default;

private:
	RectangleShape band_{};
	const Vector2f size_{ NUMBER_OF_COLUMNS * GRID, NUMBER_OF_ROWS * GRID };

	void draw(RenderTarget& target, RenderStates states) const noexcept override;
};


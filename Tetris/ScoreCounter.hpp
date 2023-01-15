#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class ScoreCounter : public Drawable
{
public:
	ScoreCounter() noexcept;
	ScoreCounter(const ScoreCounter& other) = delete;
	ScoreCounter(const ScoreCounter&& other) = delete;
	~ScoreCounter() = default;

	void incrementScore() noexcept;

private:
	short int score_;
	Font font_;
	Text text_;
	void draw(RenderTarget& target, RenderStates states) const noexcept override;
};


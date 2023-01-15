#include "ScoreCounter.hpp"

ScoreCounter::ScoreCounter() noexcept : score_(0)
{
	font_.loadFromFile("arial.ttf");
	text_.setFont(font_);
	text_.setString("Score: " + to_string(score_));
	text_.setCharacterSize(24);
	text_.setFillColor(Color::Red);
	text_.setStyle(Text::Bold | Text::Underlined);
	text_.setPosition(300, 100);
}

void ScoreCounter::incrementScore() noexcept
{
	score_++;
	text_.setString("Score: " + to_string(score_));
}

void ScoreCounter::reset() noexcept
{
	score_ = 0;
	text_.setString("Score: " + to_string(score_));
}

void ScoreCounter::draw(RenderTarget& target, RenderStates states) const noexcept
{
	target.draw(text_, states);
}
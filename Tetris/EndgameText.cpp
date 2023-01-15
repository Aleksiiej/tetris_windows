#include "EndgameText.hpp"

EndgameText::EndgameText() noexcept
{
	font_.loadFromFile("arial.ttf");
	text_.setFont(font_);
	text_.setString("You loose!\nClick ESCAPE button to close game\nOr Space to begin new game");
	text_.setCharacterSize(24);
	text_.setFillColor(Color::Red);
	text_.setStyle(Text::Bold | Text::Underlined);
	text_.setPosition(300, 400);
}

void EndgameText::draw(RenderTarget& target, RenderStates states) const noexcept
{
	target.draw(text_, states);
}

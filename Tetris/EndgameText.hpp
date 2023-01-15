#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class EndgameText : public Drawable
{
public:
	EndgameText() noexcept;
	EndgameText(const EndgameText& other) = delete;
	EndgameText(const EndgameText&& other) = delete;
	~EndgameText() = default;

private:
	Font font_;
	Text text_;
	void draw(RenderTarget& target, RenderStates states) const noexcept override;
};


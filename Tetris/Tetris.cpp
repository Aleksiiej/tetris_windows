#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>

#include "Band.hpp"
#include "BlockBoard.hpp"
#include "BlockCreator.hpp"
#include "BaseBlock.hpp"
#include "EndgameText.hpp"
#include "GlobalValues.hpp"
#include "ScoreCounter.hpp"

using namespace sf;
using namespace std;

void drawBoard(const Band& band, BlockBoard& blockBoardRef, RenderWindow& window) noexcept;

int main()
{
	RenderWindow window{ VideoMode{800, 600}, "Tetris" };
	window.setFramerateLimit(60);
	Event event;

	GameStatus gameStatus{ GameStatus::Ongoing };
	const Band band{ GRID, GRID };
	const EndgameText endgameText;
	ScoreCounter scoreCounter;
	BlockBoard blockBoard{ scoreCounter };
	unique_ptr<BaseBlock> ptrToBlock = move(BlockCreator::createRandomBlock(blockBoard));

	while (true)
	{
		window.clear(Color::White);

		if (ptrToBlock->checkIfLost())
		{
			gameStatus = GameStatus::Lost;
		}

		if (gameStatus == GameStatus::Ongoing)
		{
			while (window.pollEvent(event))
			{
				if (event.type == Event::EventType::Closed)
				{
					window.close();
					break;
				}
				if (event.type == Event::EventType::KeyPressed and event.key.code == Keyboard::Right)
				{
					if (ptrToBlock->isMoveRightPossible())
					{
						ptrToBlock->moveRight();
					}
				}
				if (event.type == Event::EventType::KeyPressed and event.key.code == Keyboard::Left)
				{
					if (ptrToBlock->isMoveLeftPossible())
					{
						ptrToBlock->moveLeft();
					}
				}
				if (event.type == Event::EventType::KeyPressed and event.key.code == Keyboard::Down)
				{
					while (ptrToBlock->isFallingPossible())
					{
						while (window.pollEvent(event));
						ptrToBlock->fall();
					}
				}
				if (event.type == Event::EventType::KeyPressed and event.key.code == Keyboard::Space)
				{
					if (ptrToBlock->isRotationPossible())
					{
						ptrToBlock->rotate();
					}
				}
			}

			blockBoard.handleFilledRows();
			drawBoard(band, blockBoard, window);
			for (const auto& block : ptrToBlock->getBlockArrayRef())
			{
				window.draw(block);
			}
			window.draw(scoreCounter);
			window.display();
			sleep(milliseconds(GAME_SPEED));
			if (ptrToBlock->isFallingPossible())
			{
				ptrToBlock->fall();
			}
			else
			{
				ptrToBlock.reset(nullptr);
				ptrToBlock = move(BlockCreator::createRandomBlock(blockBoard));
			}
		}
		else if (gameStatus == GameStatus::Lost)
		{
			drawBoard(band, blockBoard, window);
			window.draw(scoreCounter);
			window.draw(endgameText);
			window.display();
			while (window.waitEvent(event))
			{
				if (event.type == Event::EventType::Closed or event.key.code == Keyboard::Escape)
				{
					window.close();
					return 0;
				}
				if (event.type == Event::EventType::KeyPressed and event.key.code == Keyboard::Space)
				{
					break;
				}
			}
			gameStatus = GameStatus::Ongoing;
			blockBoard.clear();
			scoreCounter.reset();
		}
	}
	return 0;
}

void drawBoard(const Band& band, BlockBoard& blockBoardRef, RenderWindow& window) noexcept
{
	window.draw(band);

	RectangleShape singleField; // TODO: figure out how to use smaller class than RectangleShape
	singleField.setSize(Vector2f{ GRID, GRID });
	for (uint8_t i = 0; i < NUMBER_OF_COLUMNS; i++)
	{
		for (uint8_t j = 0; j < NUMBER_OF_ROWS; j++)
		{
			singleField.setFillColor(blockBoardRef.getBoardArrayRef().at(i).at(j));
			singleField.setPosition(static_cast<float>(i * GRID + GRID), static_cast<float>(j * GRID + GRID));
			window.draw(singleField);
		}
	}
}

#include "Band.hpp"
#include "BlockBoard.hpp"
#include "BlockCreator.hpp"
#include "BaseBlock.hpp"
#include "EndgameText.hpp"
#include "GlobalValues.hpp"
#include "ScoreCounter.hpp"

using namespace sf;
using namespace std;

void drawBoard(const Band& band, BlockBoard& blockBoardRef, const ScoreCounter& scoreCounter, RenderWindow& window) noexcept;
void resetGame(GameStatus& gameStatus, BlockBoard& blockBoard, ScoreCounter& scoreCounter);

int main()
{
	RenderWindow window{ VideoMode{800, 600}, "Tetris" };
	window.setFramerateLimit(60);
	Event event;
	Time micro = milliseconds(GAME_SPEED);

	GameStatus gameStatus{ GameStatus::Ongoing };
	const Band band{ GRID, GRID };
	const EndgameText endgameText;
	ScoreCounter scoreCounter;
	BlockBoard blockBoard{ scoreCounter };
	random_device rd;
	unique_ptr<BaseBlock> ptrToBlock = move(BlockCreator::createRandomBlock(blockBoard, rd));

	while (true)
	{
		window.clear(Color::White);

		if (gameStatus == GameStatus::Ongoing)
		{
			while (window.pollEvent(event))
			{
				if (event.type == Event::EventType::KeyPressed)
				{
					switch (event.key.code)
					{
					case Keyboard::Right:
						ptrToBlock->moveRight();
						break;

					case Keyboard::Left:
						ptrToBlock->moveLeft();
						break;

					case Keyboard::Down:
						ptrToBlock->moveDown();
						break;

					case Keyboard::Space:
						ptrToBlock->rotate();
						break;
					}
				}
				else if (event.type == Event::EventType::Closed)
				{
					window.close();
					return 0;
				}
			}

			blockBoard.handleFilledRows();
			drawBoard(band, blockBoard, scoreCounter, window);
			for (const auto& block : ptrToBlock->getBlockArrayRef())
			{
				window.draw(block);
			}
			window.display();
			sleep(milliseconds(GAME_SPEED));
			if (ptrToBlock->isFallingPossible())
			{
				ptrToBlock->fall();
			}
			else
			{
				ptrToBlock.reset(nullptr);
				ptrToBlock = move(BlockCreator::createRandomBlock(blockBoard, rd));
				if (ptrToBlock->checkIfLost())
				{
					gameStatus = GameStatus::Lost;
				}
			}
		}
		else if (gameStatus == GameStatus::Lost)
		{
			drawBoard(band, blockBoard, scoreCounter, window);
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
			resetGame(gameStatus, blockBoard, scoreCounter);
		}
	}
	return 0;
}

void drawBoard(const Band& band, BlockBoard& blockBoardRef, const ScoreCounter& scoreCounter, RenderWindow& window) noexcept
{
	window.draw(band);
	window.draw(scoreCounter);

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

void resetGame(GameStatus& gameStatus, BlockBoard& blockBoard, ScoreCounter& scoreCounter)
{
	gameStatus = GameStatus::Ongoing;
	blockBoard.clear();
	scoreCounter.reset();
}

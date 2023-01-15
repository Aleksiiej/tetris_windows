#include "BlockCreator.hpp"
#include "Block1.hpp"
#include "Block2.hpp"
#include "Block3.hpp"
#include "Block4.hpp"
#include "Block5.hpp"
#include "Block6.hpp"
#include "Block7.hpp"
#include "BlockBoard.hpp"

unique_ptr<BaseBlock> BlockCreator::createRandomBlock(BlockBoard& blockBoardRef_) noexcept
{
	unique_ptr<BaseBlock> createdBlock;
	uint8_t randomNumber;

	random_device rd;
	mt19937 rng(rd());
	uniform_int_distribution<> distrib1(0, 6);
	randomNumber = distrib1(rng);
	switch (randomNumber)
	{
	case 0:
		createdBlock = make_unique<Block1>(blockBoardRef_);
		break;
	case 1:
		createdBlock = make_unique<Block2>(blockBoardRef_);
		break;
	case 2:
		createdBlock = make_unique<Block3>(blockBoardRef_);
		break;
	case 3:
		createdBlock = make_unique<Block4>(blockBoardRef_);
		break;
	case 4:
		createdBlock = make_unique<Block5>(blockBoardRef_);
		break;
	case 5:
		createdBlock = make_unique<Block6>(blockBoardRef_);
		break;
	case 6:
		createdBlock = make_unique<Block7>(blockBoardRef_);
		break;
	}

	uniform_int_distribution<> distrib2(0, 5);
	randomNumber = distrib2(rng);
	switch (randomNumber)
	{
	case 0:
		createdBlock->setColor(Color::Red);
		break;
	case 1:
		createdBlock->setColor(Color::Green);
		break;
	case 2:
		createdBlock->setColor(Color::Blue);
		break;
	case 3:
		createdBlock->setColor(Color::Yellow);
		break;
	case 4:
		createdBlock->setColor(Color::Magenta);
		break;
	case 5:
		createdBlock->setColor(Color::Cyan);
		break;
	}

	return createdBlock;
}
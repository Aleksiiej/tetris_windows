#pragma once

#include <memory>
#include <random>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class BaseBlock;
class BlockBoard;

class BlockCreator
{
public:
	BlockCreator() = delete;
	BlockCreator(const BlockCreator& other) = delete;
	BlockCreator(const BlockCreator&& other) = delete;
	~BlockCreator() = default;

	static unique_ptr<BaseBlock> createRandomBlock(BlockBoard& blockBoardRef_) noexcept;
};


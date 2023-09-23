#pragma once

#include <random>

class BaseBlock;
class BlockBoard;

class BlockCreator
{
public:
	BlockCreator() = delete;
	static std::unique_ptr<BaseBlock> createRandomBlock(BlockBoard& blockBoardRef_, std::random_device& rd) noexcept;
};


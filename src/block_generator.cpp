#include "block_generator.hpp"

#include <stdexcept>

#include "block_shapes.hpp"

BlockGenerator::BlockGenerator() :
	m_mt{std::random_device{}()},
	m_uid{0,BLOCK_COUNT}
{}

auto
BlockGenerator::operator()() -> std::unique_ptr<Block>
{
	return std::make_unique<BlockShape<BlockType::I>>();
	switch(m_uid(m_mt))
	{
		case 0: return std::make_unique<BlockShape<BlockType::I>>();
		//case 1: return std::make_unique<BlockShape<BlockType::O>>();
		//case 2: return std::make_unique<BlockShape<BlockType::T>>();
		//case 3: return std::make_unique<BlockShape<BlockType::S>>();
		//case 4: return std::make_unique<BlockShape<BlockType::Z>>();
		//case 5: return std::make_unique<BlockShape<BlockType::J>>();
		//case 6: return std::make_unique<BlockShape<BlockType::L>>();
	}

	throw new std::runtime_error{"BlockGenerator bad random value"};
}

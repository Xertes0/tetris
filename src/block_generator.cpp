#include <stdexcept>

#include "block_generator.hpp"

BlockGenerator::BlockGenerator() :
	m_mt{std::random_device{}()},
	m_uid{0,BLOCK_COUNT}
{}

auto
BlockGenerator::operator()() -> std::unique_ptr<Block>
{
	switch(m_uid(m_mt))
	{
		case 0: return  std::move(std::make_unique<BlockI>());
		case 1: return  std::move(std::make_unique<BlockO>());
		case 2: return  std::move(std::make_unique<BlockT>());
		case 3: return  std::move(std::make_unique<BlockS>());
		case 4: return  std::move(std::make_unique<BlockZ>());
		case 5: return  std::move(std::make_unique<BlockJ>());
		case 6: return  std::move(std::make_unique<BlockL>());
	}

	throw new std::runtime_error{"BlockGenerator bad random value"};
}

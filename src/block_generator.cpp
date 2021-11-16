#include "block_generator.hpp"

#include <stdexcept>

#include "block_types.hpp"
#include "block_shapes.hpp"

BlockGenerator::BlockGenerator(TexturePtrArray const textures) :
	m_mt{std::random_device{}()},
	m_uid{0,BLOCK_COUNT-1},
	m_textures{textures} {}

auto
BlockGenerator::operator()() -> std::unique_ptr<Block>
{
	//return std::make_unique<BlockShape<BlockType::I>>();
	switch(m_uid(m_mt))
	{
		case 0: return std::make_unique<BlockShape<BlockType::I>>(m_textures);
		case 1: return std::make_unique<BlockShape<BlockType::O>>(m_textures);
		case 2: return std::make_unique<BlockShape<BlockType::T>>(m_textures);
		case 3: return std::make_unique<BlockShape<BlockType::S>>(m_textures);
		case 4: return std::make_unique<BlockShape<BlockType::Z>>(m_textures);
		case 5: return std::make_unique<BlockShape<BlockType::J>>(m_textures);
		case 6: return std::make_unique<BlockShape<BlockType::L>>(m_textures);
	}

	throw new std::runtime_error{"BlockGenerator bad random value"};
}

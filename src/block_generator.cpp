#include "block_generator.hpp"

#include <stdexcept>

#include "block_types.hpp"
#include "block_shapes.hpp"

constexpr size_t BAG_COUNT{3};

BlockGenerator::BlockGenerator(TexturePtrArray const textures) :
	m_mt{std::random_device{}()},
	m_uid{0,(BLOCK_TYPE_COUNT*BAG_COUNT)-1},
	m_textures{textures},
	m_can_generate(BLOCK_TYPE_COUNT*BAG_COUNT)
{
	reset_gen_vector();
}

auto
BlockGenerator::block_from_enum(BlockType const type) -> std::unique_ptr<Block>
{
	switch(type)
	{
		case BlockType::I: return std::make_unique<BlockShape<BlockType::I>>(m_textures);
		case BlockType::O: return std::make_unique<BlockShape<BlockType::O>>(m_textures);
		case BlockType::T: return std::make_unique<BlockShape<BlockType::T>>(m_textures);
		case BlockType::S: return std::make_unique<BlockShape<BlockType::S>>(m_textures);
		case BlockType::Z: return std::make_unique<BlockShape<BlockType::Z>>(m_textures);
		case BlockType::J: return std::make_unique<BlockShape<BlockType::J>>(m_textures);
		case BlockType::L: return std::make_unique<BlockShape<BlockType::L>>(m_textures);
	}

	throw new std::runtime_error{"idk"};
}

auto
BlockGenerator::operator()() -> std::unique_ptr<Block>
{
	if(m_can_generate.empty())
		reset_gen_vector();

	auto const index = m_uid(m_mt)%m_can_generate.size();
	auto to_return = block_from_enum(m_can_generate[index]);

	m_can_generate.erase(std::begin(m_can_generate)+index);

	return to_return;
}

void
BlockGenerator::reset_gen_vector()
{
	m_can_generate = ALL_BLOCK_TYPES;
	for(size_t i=0;i<BAG_COUNT-1;i++) {
		m_can_generate.insert(std::begin(m_can_generate), std::begin(ALL_BLOCK_TYPES), std::end(ALL_BLOCK_TYPES));
	}
}

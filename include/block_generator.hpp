#ifndef BLOCK_GENERATOR_HPP
#define BLOCK_GENERATOR_HPP

#include <array>
#include <memory>
#include <random>

#include <SFML/Graphics/Texture.hpp>

#include "block.hpp"
#include "block_types.hpp"

constexpr size_t QUEUE_SIZE{3};

using TexturePtrArray = std::array<std::shared_ptr<sf::Texture>, BLOCK_TYPE_COUNT>;

class BlockGenerator
{
private:
	std::mt19937 m_mt;
	//std::uniform_int_distribution<size_t> m_uid;

	TexturePtrArray m_textures;

	std::vector<BlockType> m_can_generate;
	std::vector<BlockType> m_block_queue;
	BlockType m_last_gen;

	void
	reset_gen_vector();

	void
	fill_queue();

	auto
	generate_enum() -> BlockType;

	[[nodiscard]] auto
	block_from_enum(BlockType type) -> std::unique_ptr<Block>;

public:
	BlockGenerator(TexturePtrArray const textures);

	[[nodiscard]] auto
	get_queue() const -> std::vector<BlockType> const &;

	auto
	operator()() -> std::unique_ptr<Block>;
};

#endif // BLOCK_GENERATOR_HPP

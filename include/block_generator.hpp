#ifndef BLOCK_GENERATOR_HPP
#define BLOCK_GENERATOR_HPP

#include <array>
#include <memory>
#include <random>

#include <SFML/Graphics/Texture.hpp>

#include "block.hpp"

using TexturePtrArray = std::array<std::shared_ptr<sf::Texture>, BLOCK_COUNT>;

class BlockGenerator
{
private:
	std::mt19937 m_mt;
	std::uniform_int_distribution<size_t> m_uid;

	TexturePtrArray m_textures;

public:
	BlockGenerator(TexturePtrArray const textures);

	auto
	operator()() -> std::unique_ptr<Block>;
};

#endif // BLOCK_GENERATOR_HPP

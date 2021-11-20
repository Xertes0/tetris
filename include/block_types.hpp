#ifndef BLOCK_TYPES_HPP
#define BLOCK_TYPES_HPP

#include <initializer_list>

constexpr std::size_t BLOCK_TYPE_COUNT{7};
enum class BlockType
{
	I, O, T, S, Z, J, L
};

constexpr std::initializer_list<BlockType> ALL_BLOCK_TYPES {
	BlockType::I,
	BlockType::O,
	BlockType::T,
	BlockType::S,
	BlockType::Z,
	BlockType::J,
	BlockType::L
};

#endif // BLOCK_TYPES_HPP

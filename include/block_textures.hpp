#ifndef BLOCK_TEXTURES_HPP
#define BLOCK_TEXTURES_HPP

#include "block_shapes.hpp"

constexpr float TEXTURE_SIZE = 7.f;
constexpr float SCALE_FACTOR = 
	static_cast<float>(FIELD_SIZE)/TEXTURE_SIZE;

template<BlockType block_type>
struct BlockTexture;

template<>
struct BlockTexture<BlockType::I>
{
	static constexpr auto path{"res/blockI.png"};
};

template<>
struct BlockTexture<BlockType::O>
{
	static constexpr auto path{"res/blockO.png"};
};

template<>
struct BlockTexture<BlockType::T>
{
	static constexpr auto path{"res/blockT.png"};
};

template<>
struct BlockTexture<BlockType::S>
{
	static constexpr auto path{"res/blockS.png"};
};

template<>
struct BlockTexture<BlockType::Z>
{
	static constexpr auto path{"res/blockZ.png"};
};

template<>
struct BlockTexture<BlockType::J>
{
	static constexpr auto path{"res/blockJ.png"};
};

template<>
struct BlockTexture<BlockType::L>
{
	static constexpr auto path{"res/blockL.png"};
};

#endif // BLOCK_TEXTURES_HPP

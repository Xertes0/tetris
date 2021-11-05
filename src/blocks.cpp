#include "blocks.hpp"

#include <fmt/printf.h>

template<BlockType block_type>
BlockShape<block_type>::BlockShape()
//	: m_rotation{0}
{
	m_rotation = 0;
}

Block::Block() :
	m_rotation{0},
	m_position{0.f,0.f}
{}

void Block::rotate()
{
	if(++m_rotation == 4)
		m_rotation = 0;
}

BlockShape<BlockType::I>::BlockShape()
{
}

void BlockShape<BlockType::I>::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
}

void BlockShape<BlockType::O>::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	fmt::print("Draw O\n");
}

void BlockShape<BlockType::T>::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	fmt::print("Draw T\n");
}

void BlockShape<BlockType::S>::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	fmt::print("Draw S\n");
}

void BlockShape<BlockType::Z>::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	fmt::print("Draw Z\n");
}

void BlockShape<BlockType::J>::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	fmt::print("Draw J\n");
}

void BlockShape<BlockType::L>::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	fmt::print("Draw L\n");
}

#include "blocks.hpp"

#include <fmt/printf.h>

void BlockShape<BlockType::I>::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	fmt::print("Draw I\n");
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

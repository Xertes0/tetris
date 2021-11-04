#include "blocks.hpp"

#include <fmt/printf.h>

void BlockI::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	fmt::print("Draw I\n");
}

void BlockO::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	fmt::print("Draw O\n");
}

void BlockT::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	fmt::print("Draw T\n");
}

void BlockS::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	fmt::print("Draw S\n");
}

void BlockZ::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	fmt::print("Draw Z\n");
}

void BlockJ::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	fmt::print("Draw J\n");
}

void BlockL::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	fmt::print("Draw L\n");
}

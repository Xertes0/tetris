#ifndef BLOCKS_HPP
#define BLOCKS_HPP

#include <SFML/Graphics.hpp>

constexpr size_t const BLOCK_COUNT = 2;

struct Block : public sf::Drawable
{
	private:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const = 0;
};

struct BlockI : Block
{
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

struct BlockO : Block
{
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

struct BlockT : Block
{
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

struct BlockS : Block
{
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

struct BlockZ : Block
{
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

struct BlockJ : Block
{
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

struct BlockL : Block
{
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

#endif // BLOCKS_HPP

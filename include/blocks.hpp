#ifndef BLOCKS_HPP
#define BLOCKS_HPP

#include <array>

#include <SFML/Graphics.hpp>

constexpr size_t const BLOCK_COUNT = 2;

class Block : public sf::Drawable
{
	public:
	Block();
	void rotate();

	protected:
	int m_rotation;
	sf::Vector2f m_position;
 	std::array<sf::RectangleShape, 4> m_blocks; // TODO - optimalize

	private:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override = 0;
};

enum class BlockType
{
	I, O, T, S, Z, J, L
};

template<BlockType block_type>
class BlockShape : public Block
{
	public:
	BlockShape();

	private:
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override = 0;
};

template<>
class BlockShape<BlockType::I> : public Block
{
	public:
	BlockShape();
	private:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

template<>
class BlockShape<BlockType::O> : public Block
{
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

template<>
class BlockShape<BlockType::T> : public Block
{
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

template<>
class BlockShape<BlockType::S> : public Block
{
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

template<>
class BlockShape<BlockType::Z> : public Block
{
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

template<>
class BlockShape<BlockType::J> : public Block
{
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

template<>
class BlockShape<BlockType::L> : public Block
{
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

#endif // BLOCKS_HPP

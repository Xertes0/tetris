#ifndef BLOCK_SHAPES_HPP
#define BLOCK_SHAPES_HPP

#include "blocks.hpp"

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
	sf::RectangleShape m_rectangle;

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
	virtual void update(TetrisField const & field, bool tick) override;
	virtual std::array<std::tuple<size_t, size_t>, 4>
	get_block_array() const override;
};

//template<>
//class BlockShape<BlockType::O> : public Block
//{
//	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
//	virtual void update() override;
//};
//
//template<>
//class BlockShape<BlockType::T> : public Block
//{
//	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
//	virtual void update() override;
//};
//
//template<>
//class BlockShape<BlockType::S> : public Block
//{
//	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
//	virtual void update() override;
//};
//
//template<>
//class BlockShape<BlockType::Z> : public Block
//{
//	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
//	virtual void update() override;
//};
//
//template<>
//class BlockShape<BlockType::J> : public Block
//{
//	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
//	virtual void update() override;
//};
//
//template<>
//class BlockShape<BlockType::L> : public Block
//{
//	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
//	virtual void update() override;
//};

#endif // BLOCK_SHAPES_HPP

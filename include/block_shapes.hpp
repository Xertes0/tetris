#ifndef BLOCK_SHAPES_HPP
#define BLOCK_SHAPES_HPP

#include "block.hpp"

#include "block_types.hpp"

template<BlockType block_type>
class BlockShape : public Block
{
public:
	BlockShape();

private:
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override = 0;
};

template<BlockType block_type>
struct BlockArrays;

template<>
struct BlockArrays<BlockType::I>
{
	static constexpr std::array value{
		std::array {
			std::tuple(-2,0),
			std::tuple(-1,0),
			std::tuple(0, 0),
			std::tuple(1, 0)
		},
		std::array {
			std::tuple(0,-2),
			std::tuple(0,-1),
			std::tuple(0, 0),
			std::tuple(0, 1)
		},
		std::array {
			std::tuple(-2,0),
			std::tuple(-1,0),
			std::tuple(0, 0),
			std::tuple(1, 0)
		},
		std::array {
			std::tuple(0,-2),
			std::tuple(0,-1),
			std::tuple(0, 0),
			std::tuple(0, 1)
		}
	};
};

template<>
class BlockShape<BlockType::I> : public Block
{
public:
	BlockShape();

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
	virtual void update(TetrisField const & field, bool tick) override;
};

template<>
class BlockShape<BlockType::O> : public Block
{
public:
	BlockShape();

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
	virtual void update(TetrisField const & field, bool tick) override;
};

template<>
class BlockShape<BlockType::T> : public Block
{
public:
	BlockShape();

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
	virtual void update(TetrisField const & field, bool tick) override;
};

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

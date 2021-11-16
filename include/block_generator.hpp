#ifndef BLOCK_GENERATOR_HPP
#define BLOCK_GENERATOR_HPP

#include <memory>
#include <random>
#include <algorithm>

#include "block.hpp"

class BlockGenerator
{
	private:
	std::mt19937 m_mt;
	std::uniform_int_distribution<size_t> m_uid;

	public:
	BlockGenerator();

	auto
	operator()() -> std::unique_ptr<Block>;
};

#endif // BLOCK_GENERATOR_HPP

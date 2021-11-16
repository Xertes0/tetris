#include "block_types.hpp"

#include <array>

template<BlockType block_type>
struct BlockShapeIndex;

template<>
struct BlockShapeIndex<BlockType::I>
{
	static constexpr std::size_t value{0};
};

template<>
struct BlockShapeIndex<BlockType::O>
{
	static constexpr std::size_t value{1};
};

template<>
struct BlockShapeIndex<BlockType::T>
{
	static constexpr std::size_t value{2};
};

template<>
struct BlockShapeIndex<BlockType::S>
{
	static constexpr std::size_t value{3};
};

template<>
struct BlockShapeIndex<BlockType::Z>
{
	static constexpr std::size_t value{4};
};

template<>
struct BlockShapeIndex<BlockType::J>
{
	static constexpr std::size_t value{5};
};

template<>
struct BlockShapeIndex<BlockType::L>
{
	static constexpr std::size_t value{6};
};

template<BlockType block_type>
struct BlockArrayRootOffsets;

template<>
struct BlockArrayRootOffsets<BlockType::I>
{
	static constexpr float x{0.f};
	static constexpr float y{0.f};
};

template<>
struct BlockArrayRootOffsets<BlockType::O>
{
	static constexpr float x{0.f};
	static constexpr float y{0.f};
};

template<>
struct BlockArrayRootOffsets<BlockType::T>
{
	static constexpr float x{-0.5f};
	static constexpr float y{-0.5f};
};

template<>
struct BlockArrayRootOffsets<BlockType::S>
{
	static constexpr float x{-0.5f};
	static constexpr float y{-0.5f};
};

template<>
struct BlockArrayRootOffsets<BlockType::Z>
{
	static constexpr float x{-0.5f};
	static constexpr float y{-0.5f};
};

template<>
struct BlockArrayRootOffsets<BlockType::J>
{
	static constexpr float x{-0.5f};
	static constexpr float y{-0.5f};
};

template<>
struct BlockArrayRootOffsets<BlockType::L>
{
	static constexpr float x{-0.5f};
	static constexpr float y{-0.5f};
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
			std::tuple(-1,-2),
			std::tuple(-1,-1),
			std::tuple(-1, 0),
			std::tuple(-1, 1)
		},
	};
};

template<>
struct BlockArrays<BlockType::O>
{
	static constexpr std::array value{
		std::array {
			std::tuple(-1,-1),
			std::tuple(-1, 0),
			std::tuple(0, -1),
			std::tuple(0,  0)
		},
		std::array {
			std::tuple(-1,-1),
			std::tuple(-1, 0),
			std::tuple(0, -1),
			std::tuple(0,  0)
		},
		std::array {
			std::tuple(-1,-1),
			std::tuple(-1, 0),
			std::tuple(0, -1),
			std::tuple(0,  0)
		},
		std::array {
			std::tuple(-1,-1),
			std::tuple(-1, 0),
			std::tuple(0, -1),
			std::tuple(0,  0)
		}
	};
};

template<>
struct BlockArrays<BlockType::T>
{
	static constexpr std::array value{
		std::array {
			std::tuple(0, -1),
			std::tuple(-1, 0),
			std::tuple(0,  0),
			std::tuple(1,  0)
		},
		std::array {
			std::tuple(0,-1),
			std::tuple(0, 1),
			std::tuple(0, 0),
			std::tuple(1, 0)
		},
		std::array {
			std::tuple(0,  1),
			std::tuple(-1, 0),
			std::tuple(0,  0),
			std::tuple(1,  0)
		},
		std::array {
			std::tuple(0, -1),
			std::tuple(0,  1),
			std::tuple(0,  0),
			std::tuple(-1, 0)
		}
	};
};

template<>
struct BlockArrays<BlockType::S>
{
	static constexpr std::array value{
		std::array {
			std::tuple(-1,0),
			std::tuple(0, 0),
			std::tuple(0,-1),
			std::tuple(1,-1)
		},
		std::array {
			std::tuple(0,-1),
			std::tuple(0, 0),
			std::tuple(1, 0),
			std::tuple(1, 1)
		},
		std::array {
			std::tuple(-1,1),
			std::tuple(0, 1),
			std::tuple(0, 0),
			std::tuple(1, 0)
		},
		std::array {
			std::tuple(-1,-1),
			std::tuple(-1, 0),
			std::tuple(0,  0),
			std::tuple(0,  1)
		}
	};
};

template<>
struct BlockArrays<BlockType::Z>
{
	static constexpr std::array value{
		std::array {
			std::tuple(1,0),
			std::tuple(0, 0),
			std::tuple(0,-1),
			std::tuple(-1,-1)
		},
		std::array {
			std::tuple(0, 1),
			std::tuple(0, 0),
			std::tuple(1, 0),
			std::tuple(1,-1)
		},
		std::array {
			std::tuple(-1,1),
			std::tuple(0, 1),
			std::tuple(0, 0),
			std::tuple(1, 0)
		},
		std::array {
			std::tuple(-1,-1),
			std::tuple(-1, 0),
			std::tuple(0,  0),
			std::tuple(0,  1)
		}
	};
};

template<>
struct BlockArrays<BlockType::J>
{
	static constexpr std::array value{
		std::array {
			std::tuple(-1,-1),
			std::tuple(-1, 0),
			std::tuple(0,  0),
			std::tuple(1,  0)
		},
		std::array {
			std::tuple(1, -1),
			std::tuple(0, -1),
			std::tuple(0, 0),
			std::tuple(0, 1)
		},
		std::array {
			std::tuple(-1,0),
			std::tuple(0, 0),
			std::tuple(1, 0),
			std::tuple(1, 1)
		},
		std::array {
			std::tuple(0, -1),
			std::tuple(0,  0),
			std::tuple(0,  1),
			std::tuple(-1, 1)
		}
	};
};

template<>
struct BlockArrays<BlockType::L>
{
	static constexpr std::array value{
		std::array {
			std::tuple(1, -1),
			std::tuple(-1, 0),
			std::tuple(0,  0),
			std::tuple(1,  0)
		},
		std::array {
			std::tuple(1, 1),
			std::tuple(0, -1),
			std::tuple(0, 0),
			std::tuple(0, 1)
		},
		std::array {
			std::tuple(-1, 0),
			std::tuple(0,  0),
			std::tuple(1,  0),
			std::tuple(-1, 1)
		},
		std::array {
			std::tuple(0, -1),
			std::tuple(0,  0),
			std::tuple(0,  1),
			std::tuple(-1,-1)
		}
	};
};

template<BlockType block_type>
struct BlockGrundCheckOffset;

template<>
struct BlockGrundCheckOffset<BlockType::I>
{
	static constexpr std::array value {-1,-2,-1,-2};
};

template<>
struct BlockGrundCheckOffset<BlockType::O>
{
	static constexpr std::array value {-1,-1,-1,-1};
};

template<>
struct BlockGrundCheckOffset<BlockType::T>
{
	static constexpr std::array value {-1,-1,-1,-1};
};

template<>
struct BlockGrundCheckOffset<BlockType::S>
{
	static constexpr std::array value {-1,-2,-1,-2};
};

template<>
struct BlockGrundCheckOffset<BlockType::Z>
{
	static constexpr std::array value {-1,-2,-1,-2};
};

template<>
struct BlockGrundCheckOffset<BlockType::J>
{
	static constexpr std::array value {-1,-2,-2,-2};
};

template<>
struct BlockGrundCheckOffset<BlockType::L>
{
	static constexpr std::array value {-1,-2,-2,-2};
};

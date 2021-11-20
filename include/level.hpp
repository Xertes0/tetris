#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <array>

constexpr std::array<unsigned int, 30> LEVEL_TIMER {
	48,
	43,
	38,
	33,
	28,
	23,
	18,
	13,
	8,
	6,
	5,
	5,
	5,
	4,
	4,
	4,
	3,
	3,
	3,
	2,
	2,
	2,
	2,
	2,
	2,
	2,
	2,
	2,
	2,
	1,
};

constexpr unsigned int MAX_LEVEL {29};

class Level
{
private:
	unsigned int m_level;
	unsigned int m_score;
	unsigned int m_lines_destroyed;

	[[nodiscard]] constexpr auto
	calc_score(unsigned int destoryed) -> unsigned int;

public:
	constexpr
	Level() = default;

	[[nodiscard]] auto
	get_tick_time() -> unsigned int;

	void
	destoryed(unsigned int line_count);

};

#endif // LEVEL_HPP

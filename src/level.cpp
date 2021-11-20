#include "level.hpp"

#include <fmt/printf.h>

[[nodiscard]] auto
Level::get_tick_time() -> unsigned int
{
	return LEVEL_TIMER[m_level];
}

[[nodiscard]] constexpr auto
Level::calc_score(unsigned int destoryed) -> unsigned int
{
	auto base = 0;
	switch(destoryed) {
		case 1:  base = 40;   break;
		case 2:  base = 100;  break;
		case 3:  base = 300;  break;
		default: base = 1200; break;
	}

	return base * (m_level + 1);
}

void
Level::destoryed(unsigned int line_count)
{
	if(line_count != 0) {
		m_lines_destroyed += line_count;
		m_level = m_lines_destroyed/10;
		m_score += calc_score(line_count);
		fmt::print("ld: {}, lvl: {}, score: {}\n", m_lines_destroyed, m_level, m_score);
	}
}

#include "tetris.hpp"

#include <SFML/Graphics/Rect.hpp>
#include <fmt/printf.h>

#include "block_textures.hpp"

Tetris::Tetris() :
	m_field{},
	m_block_gen{},
	m_timer{0},
	m_timer_end{16},
	m_is_falling(false),
	m_block{}
{
	load_static_textures();
}

void Tetris::load_static_textures()
{
	
	auto i_texture = std::make_shared<sf::Texture>();
	auto o_texture = std::make_shared<sf::Texture>();
	auto t_texture = std::make_shared<sf::Texture>();
	auto s_texture = std::make_shared<sf::Texture>();
	auto z_texture = std::make_shared<sf::Texture>();
	auto j_texture = std::make_shared<sf::Texture>();
	auto l_texture = std::make_shared<sf::Texture>();

	i_texture->loadFromFile(BlockTexture<BlockType::I>::path,
		sf::IntRect{0,0,
			static_cast<int>(TEXTURE_SIZE),
			static_cast<int>(TEXTURE_SIZE)
	});
	o_texture->loadFromFile(BlockTexture<BlockType::O>::path,
		sf::IntRect{0,0,
			static_cast<int>(TEXTURE_SIZE),
			static_cast<int>(TEXTURE_SIZE)
	});
	t_texture->loadFromFile(BlockTexture<BlockType::T>::path,
		sf::IntRect{0,static_cast<int>(TEXTURE_SIZE),
			static_cast<int>(TEXTURE_SIZE),
			static_cast<int>(TEXTURE_SIZE)
	});
	s_texture->loadFromFile(BlockTexture<BlockType::S>::path,
		sf::IntRect{0,static_cast<int>(TEXTURE_SIZE),
			static_cast<int>(TEXTURE_SIZE),
			static_cast<int>(TEXTURE_SIZE)
	});
	z_texture->loadFromFile(BlockTexture<BlockType::Z>::path, 
		sf::IntRect{0,0,
			static_cast<int>(TEXTURE_SIZE),
			static_cast<int>(TEXTURE_SIZE)
	});
	j_texture->loadFromFile(BlockTexture<BlockType::J>::path,
		sf::IntRect{0,0,
			static_cast<int>(TEXTURE_SIZE),
			static_cast<int>(TEXTURE_SIZE)
	});
	l_texture->loadFromFile(BlockTexture<BlockType::L>::path,
		sf::IntRect{0,static_cast<int>(TEXTURE_SIZE),
			static_cast<int>(TEXTURE_SIZE),
			static_cast<int>(TEXTURE_SIZE)
	});

	m_stextures.push_back(i_texture);
	m_stextures.push_back(o_texture);
	m_stextures.push_back(t_texture);
	m_stextures.push_back(s_texture);
	m_stextures.push_back(z_texture);
	m_stextures.push_back(j_texture);
	m_stextures.push_back(l_texture);
}

void Tetris::update()
{
	if(m_timer++ >= m_timer_end) {
		if(!m_is_falling) {
			m_block = m_block_gen();
			m_is_falling = true;
		} else {
			m_block.value()->update(m_field, true);
		}

		m_timer = 0;
	} else {
		if(m_block.has_value())
			m_block.value()->update(m_field, false);
	}

	if(m_block.has_value()) {
		if(m_block.value()->has_fallen) {
			for(auto const &[x,y] : m_block.value()->get_block_array()) {
				m_field.static_blocks[x][y] =
					StaticBlock{.texture =
						m_stextures[m_block.value()->texture_index]};

				//fmt::print("sblock x: {}, y: {}\n", x,y);
			}
			m_is_falling = false;
			m_block.reset();

			m_field.check_score();
		}
	}
}

void Tetris::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	if(m_block.has_value())
		target.draw(**m_block);

	target.draw(m_field);
}

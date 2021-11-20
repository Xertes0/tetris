#include "tetris.hpp"

#include <SFML/Graphics/Rect.hpp>
#include <fmt/printf.h>

#include "block_textures.hpp"

auto
get_stextures() -> TexturePtrArray
{
	TexturePtrArray stextures;
	stextures[0] = std::make_shared<sf::Texture>();
	stextures[0]->loadFromFile(BlockTexture<BlockType::I>::path,
		sf::IntRect{0,0,
			static_cast<int>(TEXTURE_SIZE),
			static_cast<int>(TEXTURE_SIZE)
	});
	stextures[1] = std::make_shared<sf::Texture>();
	stextures[1]->loadFromFile(BlockTexture<BlockType::O>::path,
		sf::IntRect{0,0,
			static_cast<int>(TEXTURE_SIZE),
			static_cast<int>(TEXTURE_SIZE)
	});
	stextures[2] = std::make_shared<sf::Texture>();
	stextures[2]->loadFromFile(BlockTexture<BlockType::T>::path,
		sf::IntRect{0,static_cast<int>(TEXTURE_SIZE),
			static_cast<int>(TEXTURE_SIZE),
			static_cast<int>(TEXTURE_SIZE)
	});
	stextures[3] = std::make_shared<sf::Texture>();
	stextures[3]->loadFromFile(BlockTexture<BlockType::S>::path,
		sf::IntRect{0,static_cast<int>(TEXTURE_SIZE),
			static_cast<int>(TEXTURE_SIZE),
			static_cast<int>(TEXTURE_SIZE)
	});
	stextures[4] = std::make_shared<sf::Texture>();
	stextures[4]->loadFromFile(BlockTexture<BlockType::Z>::path, 
		sf::IntRect{0,0,
			static_cast<int>(TEXTURE_SIZE),
			static_cast<int>(TEXTURE_SIZE)
	});
	stextures[5] = std::make_shared<sf::Texture>();
	stextures[5]->loadFromFile(BlockTexture<BlockType::J>::path,
		sf::IntRect{0,0,
			static_cast<int>(TEXTURE_SIZE),
			static_cast<int>(TEXTURE_SIZE)
	});
	stextures[6] = std::make_shared<sf::Texture>();
	stextures[6]->loadFromFile(BlockTexture<BlockType::L>::path,
		sf::IntRect{0,static_cast<int>(TEXTURE_SIZE),
			static_cast<int>(TEXTURE_SIZE),
			static_cast<int>(TEXTURE_SIZE)
	});

	return stextures;
};

auto
get_textures() -> TexturePtrArray
{
	TexturePtrArray textures;
	textures[0] = std::make_shared<sf::Texture>();
	textures[0]->loadFromFile(BlockTexture<BlockType::I>::path);
	textures[1] = std::make_shared<sf::Texture>();
	textures[1]->loadFromFile(BlockTexture<BlockType::O>::path);
	textures[2] = std::make_shared<sf::Texture>();
	textures[2]->loadFromFile(BlockTexture<BlockType::T>::path);
	textures[3] = std::make_shared<sf::Texture>();
	textures[3]->loadFromFile(BlockTexture<BlockType::S>::path);
	textures[4] = std::make_shared<sf::Texture>();
	textures[4]->loadFromFile(BlockTexture<BlockType::Z>::path);
	textures[5] = std::make_shared<sf::Texture>();
	textures[5]->loadFromFile(BlockTexture<BlockType::J>::path);
	textures[6] = std::make_shared<sf::Texture>();
	textures[6]->loadFromFile(BlockTexture<BlockType::L>::path);

	return textures;
};

Tetris::Tetris() :
	m_stextures{get_stextures()},
	m_textures{get_textures()},
	m_field{},
	m_block_gen{m_textures},
	m_level{},
	m_timer{0},
	m_is_falling(false),
	m_swaped{false},
	m_block{},
	m_block_sbuf{} {}

void
Tetris::update(InputHandler const & input_handler)
{
	if(input_handler.pressed_once<Action::Swap>()) {
		if(m_block != nullptr && !m_swaped) {
			if(m_block_sbuf == nullptr) {
				m_block_sbuf = m_block_gen();
			}
			m_block.swap(m_block_sbuf);
			m_block->reset();
			m_swaped = true;
		}
	}

	if(m_timer++ >= m_level.get_tick_time()) {
		if(!m_is_falling) {
			m_block = m_block_gen();
			if(m_block->is_illegal(m_field)) {
				fmt::print("Loser\n");
			}
			m_is_falling = true;
		} else {
			m_block->update(input_handler, m_field, true);
		}

		m_timer = 0;
	} else {
		if(m_block != nullptr)
			m_block->update(input_handler, m_field, false);
	}

	if(m_block != nullptr) {
		if(m_block->has_fallen) {
			m_timer = 0;
			m_swaped = false;
			for(auto const &[x,y] : m_block->get_block_array()) {
				m_field.static_blocks[x][y] =
					StaticBlock{.texture =
						m_stextures[m_block->texture_index]};

				//fmt::print("sblock x: {}, y: {}\n", x,y);
			}
			m_is_falling = false;
			m_block.reset();

			auto const destoryed = m_field.destory_lines();
			m_level.destoryed(destoryed);
		}
	}
}

void
Tetris::draw(sf::RenderTarget &target, [[maybe_unused]] sf::RenderStates states) const
{
	if(m_block != nullptr)
		target.draw(*m_block);

	target.draw(m_field);

	auto const queue = m_block_gen.get_queue();

	for(int index=QUEUE_SIZE-1; auto const & block : queue) {
		sf::Sprite sprite{};
		sprite.setScale(sf::Vector2f{SCALE_FACTOR,SCALE_FACTOR});
		sprite.setPosition(
			450.f,
			FIELD_OFFSET_Y + 50.f + 100.f*index
		);
		sprite.setTexture(*m_textures[static_cast<size_t>(block)]);
		target.draw(sprite);

		index--;
	}

	if(m_block_sbuf != nullptr) {
		static sf::Sprite swapped{};
		swapped.setTexture(*m_textures[static_cast<size_t>(m_block_sbuf->type)]);
		swapped.setScale(sf::Vector2f{SCALE_FACTOR,SCALE_FACTOR});
		swapped.setPosition(
			450.f,
			static_cast<float>(HEIGHT) - 175.f
		);
		target.draw(swapped);
	}
}

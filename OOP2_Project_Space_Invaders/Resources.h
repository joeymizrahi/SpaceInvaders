#pragma once
#include "Macros.h"
#include "Chronometer.hpp"

enum  MUSIC_ID
{
	SHOOT_M,
	ENEMY_SHOT_1_M,
	ENEMY_SHOT_2_M,
	BOSS_M,
	EXPLOSION_M,
	POWER_UP_M,
	TELEPORT_M,
	MAX_SOUNDS
};

enum class FONT_ID
{
	FONT
};

class Resources
{
public:
	static Resources& get_instance();
	void play(const MUSIC_ID& sound);
	void loadSprites();
	void loadSounds();
	sf::Texture & getGeneralTexture(const GENERAL_TEXTURES c);
	sf::Font& getFont() { return m_font; };
	sf::Music m_gameMusic;
	sftools::Chronometer chrono;

private:
	Resources();
	Resources(const Resources&) = delete;  //copy c-tor
	std::vector<sf::Texture> m_game_textures;
	std::vector<sf::SoundBuffer> m_buffers;
	std::vector<sf::Text> m_texts;
	std::vector<sf::Sound> m_sounds;
	sf::Sound m_sound;
	sf::Font m_font;

	const std::string texturePath = "Sprites/";
	const std::string soundPath = "Sounds/";
};
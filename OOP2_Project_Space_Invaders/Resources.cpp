#include "Resources.h"

//-----------------------------------------------------------------------------
Resources::Resources()
{
	m_game_textures.resize((int)GENERAL_TEXTURES::MAX);
	m_buffers.resize((int)MUSIC_ID::MAX_SOUNDS);
	m_sounds.resize((int)MUSIC_ID::MAX_SOUNDS);

	if(!m_font.loadFromFile("Font/OCRAEXT.ttf"))
		throw(FileException());

	loadSprites();
	loadSounds();
}
//--------------------------------------------------------------
Resources& Resources::get_instance()
{
	static Resources instance;

	return instance;
}
//--------------------------------------------------------------
void Resources::loadSprites()
{
	// loads all game textures to a vector
	for (int i = 0; i < GENERAL_TEXTURES::MAX; i++)
	{
		if (!m_game_textures[i].loadFromFile(texturePath + std::to_string(i) + ".png"))
			throw(FileException());
	}
}
//--------------------------------------------------------------
void Resources::loadSounds()
{
	// loads all game sounds to a vector
	for (int i = 0; i < MUSIC_ID::MAX_SOUNDS; i++)
	{
		if (!m_buffers[i].loadFromFile(soundPath + std::to_string(i) + ".ogg"))
			throw(FileException());

		m_sounds[i].setBuffer(m_buffers[i]);
	}
}
//--------------------------------------------------------------
sf::Texture & Resources::getGeneralTexture(const GENERAL_TEXTURES c)
{
	return m_game_textures[c];
}
//--------------------------------------------------------------
void Resources::play(const MUSIC_ID & sound)
{
	m_sounds[sound].play();
}
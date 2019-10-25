#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include <vector>
#include <list>
#include <memory>
#include <map>
#include <unordered_map>
#include "MyExceptions.h"
#include <algorithm>
#include <random>

enum ENEMY_CHARS
{
	SIMPLE_ENEMY_C = 'a',
	SMART_ENEMY_C = 'b',
	BOSS_ENEMY_C = 'f'
};
enum POWER_UP_CHARS
{
	EXTRA_LIFE_C = 'c',
	WAVE_BULLET_C = 'd',
	SHIELD_C = 'e',
};

static const std::string WAVE_BULLET_STRING = "wave bullet";
static const std::string SIMPLE_ENEMY_BULLET_STRING = "simple enemy bullet";
static const std::string DEFAULT_HERO_BULLET_STRING = "default bullet";
static const int MAX_LEVELS = 3; 
static const sf::Vector2f WINDOW_SIZE = { 1440.f, 900.f };  //size of window
static const float MAX_HEALTH = 100;

struct bullet_pkg
{
	sf::Vector2f initialPos;
	sf::Vector2f driection;
	bool heroBullet;
	float damage;
};

struct enemy_pkg
{
	sf::Vector2f initialPos;
	float yLimit;
};

struct powerUp_pkg
{
	sf::Vector2f initialPos;
	int velocity;
};

enum GENERAL_TEXTURES
{
	GAME_BACKGROUND_T = 0,
	GAMEOVER_BACKGROUND_T,
	LOGO_T,
	START_T,
	EXIT_T,
	HELP_T,
	HIGHSCORE_BUTTON_T,
	RESUME_BUTTON_T,
	PREV_T,
	INSTRUCTIONS_T,
	HIGHSCORE_TITLE_T,
	DEFAULT_HERO_T,
	SIMPLE_ENEMY_T,
	SMART_ENEMY_T,
	SHIP_LEFT_T,
	SHIP_RIGHT_T,
	SIMPLE_ENEMY_BULLET_T,
	HEALTH_BAR_T,
	INNER_HEALTH_BAR_T,
	TELEPORT_T,
	DEFAULT_BULLET_T,
	EXPLOSION_T,
	CLUSTER_BULLET_POWERUP_T,
	SHIELD_SHIP_LEFT_T,
	SHIELD_SHIP_RIGHT_T,
	SHIELD_SHIP_T,
	BOSS_SHEET_T,
	WAVE_BULLET_T,
	MAX
};
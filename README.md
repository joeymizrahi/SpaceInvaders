OOP Semester 2 Final Project 
Space Invaders Clone

Joey Mizrahi 
Avshalom Belger 



Game Explanation:
You the user are a spaceship, you move left and right using the arrow keys,
And shoot using space. Your mortal enemies are weird looking squids and crabs.
The goal in the game is to get to the boss level, the evil squid monster.
The simple enemies move as a group (an army) once in every N seconds the enemy will teleport and be in your face. It will then follow you (the hero) around.
The boss squid has a lot more health and moves in a different way.

Files and classes:
• Main.cpp 
  The main file that runs the start of the GameManager, pushes a menu state.
• Macros.h 
  The file holds all defines and consts, enums, structs as well as usings and includes used throughout the program.

• Resources
 The resources class is in charge of loading and holding all outer files, 
 Such as pictures, music’s and fonts.
 It is a static Singleton class.

• Chronometer:
  A namespace which is an expansion of sf::clock, it has an addition of a pause and resume function which allows us to pause and resume the game clock when we 	                   pass between states.
• Logger
  A singleton static class, the class holds the logger file. The logger file will hold times of major things that happened throughout the program. such as Exceptions, collisions   and more.
If the program has ever failed, the logger file will allow us to know the reason.
•	Bullet, Enemy, PowerUp factories
These classes are each in charge of creating objects.
The class holds a static map which holds a key matching to the proper objects and a pointer to a function which creates the object. Each object is in charge of registering itself to the factory.
	•	Level Manager:
The level manager gets the vector of entities and updates them by using the outer level files. It creates the objects according to the char in the file using the factories.
	•	HighScoreManager:
The manager is in charge of getting the file if it exists and creates a new one if it doesn’t. it adds all the existing high scores to a multimap.
	•	GameManager:
The gameManager runs the main game loop.
It holds a stack of states like menu, help, highscore, pause, play 
Generically it calls a set of functions for the state that’s on the top of the stack.
It has a push and pop function which are called when we want to move between game states.
	•	MyExceptions:
Holds all the exceptions needed throughout the game, the exceptions inherit from std::exception.
	•	State
State is an abstract class that represents possible game states.
	•	Menu state:
The class inherits from state, represents the main menu state.
It is the first state pushed into the stack of states.
It holds a vector of pointers that inherit from command,
Help, start, exit, highscore.
	•	playingState
This state is the playing state, it holds the vectors of entities and is in charge of all playing updates, like movement, shooting, collision, deletion of objects….
	•	PauseState
The state pauses all game clocks…
	•	GameOverState.
The state is in charge of ending the playing state.. cleaning everything getting users name and adding it to the multimap of high scores.
	•	Command:
Abstract class that represents all buttons in games, has an execute function
	•	Exit
Inherits from command, exits the game…. Writes high scores to highscore file.
	•	Help:
Inherits from command, opens a help screen
	•	HighScore:
Inherits from command, loads from multimap, makes sf::Texts and draws them on the window.
	•	NewGame:
Pushes the playingState.

	•	MoveStrategy:
Abstract class that represents the enemy’s movements.
	•	SimpleMove
Inherits from MoveStrategy, is the default move for the simple enemies.
Moves them in an army motion.
	•	TeleportMove.
Inherits from MoveStrategy and continues to move the enemy according to his previous move, until the teleport animation stops. It then puts the enemy’s position in front of the ship. And changes the enemy’s move Strategy to horizontal move.
	23.HorizontalMove
     Inherits from MoveStrategy, this move is given to the enemy that was just 
     teleported in front of the ship.
	•	BossMove
Inherits from MoveStrategy and moves the boss

	•	Entity:
Abstract class which represents a game object.
	•	Bullet:
Abstract class represents a bullet
	•	SimpleEnemyBullet:
Bullet for enemy
	•	DefaultBullet
Default hero bullet
	•	WaveBullet
Bullet for hero gotten after a powerup

	•	Weaponable
Abstract class represents an enemy or hero
	•	Ship
Inherits from weaponable, is the hero class
	•	Enemy.
Inherits from weaponable, is abstract
	•	SimpleEnemy
Inherits from enemy
	•	smartEnemy
Inherits from enemy
	•	BossEnemy
Inherits from enemy
	
	26. PowerUp
	       Abstract class that inherits from entity.
	27. Shield
	28. WaveBullet
	29. Life


	•	DataStructures:

	•	Map:
All factories hold a map
	•	Multimap:
For high score, is multimap because we want it sorted and allow the duplicate keys.
	•	Stack:
GameManager holds stack of game states.
	•	Vectors:
Entities, textures, sounds …… 

	•	Bugs:
No knows bugs.
Link to Video: [AwesomeVid](https://www.youtube.com/watch?v=SLQuXSj7Ak8)


	

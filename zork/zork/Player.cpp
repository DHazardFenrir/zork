#include <iostream>
#include "globals.h"
#include "Room.h"
#include "Exit.h"
#include "Item.h"
#include "Player.h"
#include "Human.h"
#include "Entity.h"
// ----------------------------------------------------
// Constructor that initializes the Player
Player::Player(const std::string& name, const std::string& description, std::shared_ptr<Room> room, Stats stats)
	: Human(name, description, room, 100, 10, 10, 10) // Pass all arguments to Human constructor
{
	// Additional initialization specific to Player, if necessary
}
// ----------------------------------------------------
Player::~Player()
{
}

// ----------------------------------------------------

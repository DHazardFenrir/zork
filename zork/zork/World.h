#ifndef __WORLD_H__
#define __WORLD_H__

#include <string>
#include <vector>
#include <memory>
#include <ctime>

#define TICK_FREQUENCY 0.5f

using namespace std;

class Entity;
class Player;

class World {
public:
    World();
    ~World();

    // Main game loop method
    void GameLoop();
    void Initialize();
    // Process game ticks
    bool Tick(const vector<string>& args);

    void SetPlayer(shared_ptr<Player> newPlayer) {
        player = newPlayer;
    }
private:
   
    // Parse user commands
    bool ParseCommand(const vector<string>& args);

    // Timer for ticks
    clock_t tick_timer;
    
    // List of entities in the world
    vector<shared_ptr<Entity>> entities;
    
    // Shared pointer to the player object
    shared_ptr<Player> player;
};

#endif // __WORLD_H__
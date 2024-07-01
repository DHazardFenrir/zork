#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include "globals.h"
#include "World.h"
#include "Player.h"

using namespace std;

#define BACKSPACE "\033[D\033[K"
#define WHITE_ "\033[1;36m"
#define _WHITE "\033[0m"

// -------------------------------------------------
int main()
{
    char key;
    string player_input;
    vector<string> args;
    args.reserve(10);

    cout << WHITE_ "Welcome to MyZork!\n" _WHITE;
    cout << "----------------\n";

    World my_world;

    // Initialize the world
    my_world.Initialize();

    // Create and set the player
    auto player = make_shared<Player>("Hero", "You are an awesome adventurer!");
    my_world.SetPlayer(player);

    args.push_back("look");

    while (true)
    {
        if (_kbhit() != 0)
        {
            key = _getch();
            if (key == '\b') // Backspace
            {
                if (player_input.length() > 0)
                {
                    player_input.pop_back();
                    cout << BACKSPACE;
                    cout << " ";
                    cout << BACKSPACE;
                }
            }
            else if (key != '\r') // Return
            {
                player_input += key;
                cout << key;
            }
            else
            {
                Tokenize(player_input, args);
                if (args.empty())
                {
                    cout << "\nPlease enter a command.\n";
                }
                else
                {
                    if (my_world.Tick(args) == false)
                        cout << "\nSorry, I do not understand your command.\n";

                    args.clear();
                    player_input = "";
                }
                cout << "> ";
            }
        }
    }

    cout << "\nThanks for playing, Bye!\n";
    return 0;

}
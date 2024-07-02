Zork-like Adventure Game
Overview
Welcome to a copy of Zork! This is a text-based adventure game where you explore various rooms, interact with objects, and battle monsters. Your ultimate goal is to defeat the goblin lurking in the dungeon. Along the way, you may collect items, unlock doors, and manage status ailments inflicted by enemies.

How to Play
You will navigate through different rooms by typing commands into the console. Each room may contain items that you can pick up and use, exits to other rooms, and sometimes even monsters that you will need to defeat.

Available Commands
Movement

north, south, east, west: Move in the specified direction if there is an exit.
Interaction

look at [item name]: Inspect an item in the current room.
pick up: Pick up an item in the current room after selecting it from a list.
unlock [direction]: Unlock a locked exit in the specified direction if you have the corresponding key.

when inputing a command, double tap the key enter, for the program to read and process the input.
Combat

attack: Attack the monster in the current room.
defend: Defend against the monster's next attack.
use item: Use an item from your inventory during combat.
Status and Inventory

stats: View your current health, strength, and defense stats.
inventory: View the items in your inventory.
Objective
Your objective is to navigate through the rooms, collect items, unlock exits, and ultimately defeat the goblin in the dungeon. Be mindful of your health and status ailments, as these can affect your ability to fight and move.

Game Mechanics
Items
Items can be found in various rooms and may include:

Weapons: Increase your attack strength.
Shields: Increase your defense.
Potions: Restore health or cure status ailments.
Keys: Used to unlock locked exits.
Status Ailments
Monsters can inflict status ailments on you during combat:

Burn: Inflicts 5 damage at the start of each turn.
Poison: Inflicts 10 damage at the start of each turn.
Paralyze: Causes you to lose a turn.
Use specific potions to cure these ailments.

Combat
When you encounter a monster, you will enter combat. You can choose to attack, defend, or use an item. Be aware of your status ailments, as they will affect your health and combat performance.

Ending the Game
The game ends when you defeat the goblin in the dungeon. You will be notified of your victory, and the game will exit.

Example Gameplay
vbnet
Copiar código
Welcome to a copy of Zork!, Adventurer!
You are in a grand hall with an echo.
No items to see here.
Available exits: east north
What do you want to do? east

You are in a serene garden with a small pond.
Items in this room:
 - Old Apple: A weird looking apple
 - Box: A wooden box
Available exits: west
What do you want to do? look at Box
You look at the Box: A wooden box
It contains:
- Key
Key added to inventory.
Box added to inventory.
Box has been picked up from the room.

You are in a serene garden with a small pond.
Items in this room:
 - Old Apple: A weird looking apple
Available exits: west
What do you want to do? west

You are in a grand hall with an echo.
No items to see here.
Available exits: east north
What do you want to do? north

You are in a quiet library full of ancient books.
No items to see here.
Available exits: east (locked) south
What do you want to do? unlock east
The east exit has been unlocked.

You are in a quiet library full of ancient books.
No items to see here.
Available exits: east south
What do you want to do? east

You are in a dark dungeon with a foul smell.
A Goblin appears!
Combat! Your Health: 100, Goblin's Health: 50
Choose action: 'attack', 'defend', or 'use item': attack
Adventurer attacks Goblin for 15 damage!
Goblin attacks Adventurer with Rusty Sword for 20 damage!
Adventurer takes 15 damage!
...
You have defeated the Goblin!
Congratulations! You have completed the game by defeating the goblin!
Enjoy your adventure and good luck!

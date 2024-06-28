#pragma once
#ifndef __Stats__
#define __Stats__

using namespace std;

class Stats
{
public:
	Stats(int health = 0, int strength = 0, int defense = 0, int speed = 0);
		//Getters to attributes
		int GetHealth() const;
		int GetStrength() const;
		int GetDefense() const;
		int GetSpeed() const;

		//Setters to attributes
		void SetHealth(int value);
		void SetStrength(int value);
		void SetDefense(int value);
		void SetSpeed(int value);
private:
	int health;
	int strength;
	int defense;
	int speed;

	

};
#endif __Stats__

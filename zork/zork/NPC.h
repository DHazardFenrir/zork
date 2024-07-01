#ifndef __NPC_H__
#define __NPC_H__

#include <iostream>
#include <string>
#include "Entity.h"
#include "Monster.h"
#include "Stats.h"
using namespace std;

class NPC : public Monster {
public:
    NPC(const std::string& name, const std::string& description, std::shared_ptr<Room> room, const Stats& stats, std::shared_ptr<Item> weapon = nullptr);
    ~NPC();

    string GetDialogue() const;
    void SetDialogue(string& dialogue);
    enum EntityType GetType();
private:
    string dialogue;
};

#endif // __NPC_H__
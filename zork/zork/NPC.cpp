#include "NPC.h"
#include "Monster.h"
#include "Stats.h"
NPC::NPC(const std::string& name, const std::string& description, std::shared_ptr<Room> room, const Stats& stats, std::shared_ptr<Item> weapon)
    : Monster(name, description, room, stats.GetHealth(), stats.GetStrength(), stats.GetDefense(), stats.GetSpeed(), weapon) {
    // Constructor body, if needed
}

NPC::~NPC() {}

std::string NPC::GetDialogue() const {
    return dialogue;
}

void NPC::SetDialogue(string& dialg) {
    dialogue = dialg;
}

enum EntityType GetType() {
    return EntityType::NonPlayer;
}
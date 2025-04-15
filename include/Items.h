#ifndef ITEMS_H
#define ITEMS_H

#include "Enums.h"
#include "Structs.h"
#include <vector>

namespace TEM {
std::vector<std::pair<ItemType, ItemInfo>> ALL_ITEMS{
    {ItemType::Usable,
     {"Health Potion", "Restores 25% of your max HP.", .25, 0, 0,
      EquipType::Undefined}},
    {ItemType::Equipable,
     {"Wooden Sword",
      "A simple wooden sword, surprisingly light. Its surface faintly shimmers "
      "upon closer inspection.",
      .0, 10, 0, EquipType::Weapon}},
    {ItemType::Equipable,
     {"Iron Sword",
      "Iron sword? Way better. Fits you nicely. Not the sharpest, but works "
      "fine for smashing things.",
      .0, 25, 0, EquipType::Weapon}},
    {ItemType::Equipable,
     {"Steel Sword",
      "The steel sword: an Imperial military staple. Perfection forged in "
      "steel.",
      .0, 50, 0, EquipType::Weapon}},
    {ItemType::Equipable,
     {"Iron Breastplate",
      "This dented iron armor has seen too many battles. Now it’s barely fit "
      "to turn a butterknife.",
      .0, 0, 8, EquipType::Armor}},
    {ItemType::Equipable,
     {"Steel Breastplate",
      "The cold embrace of steel promises protection—a lie that shatters with "
      "the first blow.",
      .0, 0, 15, EquipType::Armor}},
    {ItemType::Equipable,
     {"Foot soldier's boots",
      "Still warm from the previous owner’s final march.", .0, 0, 2,
      EquipType::Boots}},
    {ItemType::Equipable, {"", "", .0, 0, 6, EquipType::Boots}},
    // {ItemType::Equipable, {"", "", .0, 50, 0, EquipType::Armor}},
};
}

#endif // !ITEMS_H

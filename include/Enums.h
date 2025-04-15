#ifndef ENUMS_H
#define ENUMS_H

namespace TEM {
enum class ItemType : int { Undefined = -1, Equipable = 0, Usable = 1 };
enum class EquipType : int {
  Undefined = -1,
  Armor = 0,
  Weapon = 1,
  Shield = 2,
  Boots = 3,
  Helm = 4
};
enum class Event : int {
  None = 0,
  MoveUp,
  MoveDown,
  MoveLeft,
  MoveRight,
  Attack,
  Inventory,
  Quit,
  NewGame,
  LoadGame,
  ExitToMenu
};
} // namespace TEM

#endif // ENUMS_H

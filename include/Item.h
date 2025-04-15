#ifndef ITEM_H
#define ITEM_H

#include "Enums.h"
#include "Structs.h"

namespace TEM {
class Item {
private:
  unsigned short id;
  ItemType type;
  ItemInfo info;

public:
  Item(ItemType type, ItemInfo info);
};
} // namespace TEM

#endif // !ITEM_H

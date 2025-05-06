#ifndef I_RENDERABLE_H
#define I_RENDERABLE_H

#include <libtcod.h>

class IRenderable {
public:
  ~IRenderable() = default;
  virtual void Render(tcod::Console &console) = 0;
};

#endif // !I_RENDERABLE_H

/* BSD 3-Clause License
 *
 * Copyright © 2008-2025, Jice and the libtcod contributors.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#pragma once
#ifndef TCOD_GUI_VBOX_HPP
#define TCOD_GUI_VBOX_HPP
#ifndef NO_SDL
#ifndef TCOD_NO_UNICODE
#include "container.hpp"

namespace tcod::gui {
class VBox : public Container {
 public:
  VBox(int x, int y, int padding) : Container{x, y, 0, 0}, padding{padding} {}
  void computeSize() override {
    int cursor_y = y;
    w = 0;
    for (auto& wid : content_) {
      if (wid->isVisible()) {
        wid->x = x;
        wid->y = cursor_y;
        wid->computeSize();
        if (wid->w > w) w = wid->w;
        cursor_y += wid->h + padding;
      }
    }
    h = cursor_y - y;
    for (auto& wid : content_) {
      if (wid->isVisible()) {
        wid->expand(w, wid->h);
      }
    }
  }

 protected:
  int padding{};
};
}  // namespace tcod::gui
#endif  // TCOD_NO_UNICODE
#endif  // NO_SDL
#endif /* TCOD_GUI_VBOX_HPP */

/*
 * Copyright (C) 2026 Paul Davis <paul@linuxaudiosystems.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#pragma once

#include "widgets/ardour_icon.h"
#include "canvas/rectangle.h"

namespace ArdourCanvas {

class Canvas;
class Item;

class Icon : public ArdourCanvas::Rectangle
{
  public:
	Icon (Canvas*, ArdourWidgets::ArdourIcon::Icon);
	Icon (Item*, ArdourWidgets::ArdourIcon::Icon);

	void render (Rect const & area, Cairo::RefPtr<Cairo::Context>) const;
	void set_icon (ArdourWidgets::ArdourIcon::Icon);

  private:
	ArdourWidgets::ArdourIcon::Icon _icon;
};

} /* end namespace */


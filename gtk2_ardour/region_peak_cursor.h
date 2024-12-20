/*
 * Copyright (C) 2020 Robin Gareus <robin@gareus.org>
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

#ifndef _gtk_ardour_region_peak_cursor_h_
#define _gtk_ardour_region_peak_cursor_h_

#include "ardour/types.h"
#include "canvas/canvas.h"

namespace ArdourCanvas
{
	class Text;
	class Arrow;
}

class AudioRegionView;

class RegionPeakCursor
{
public:
	RegionPeakCursor (ArdourCanvas::Item*);
	~RegionPeakCursor ();

	void set (AudioRegionView*, samplepos_t, ARDOUR::samplecnt_t);
	void hide ();
	bool visible () const;

private:
	void color_handler ();
	void show ();

	ArdourCanvas::Text*  _canvas_text;
	ArdourCanvas::Arrow* _canvas_line;
};

#endif

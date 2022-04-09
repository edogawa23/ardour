/*
 * Copyright (C) 2022 Robin Gareus <robin@gareus.org>
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

#ifndef _gtkardour_ioplugin_window_h_
#define _gtkardour_ioplugin_window_h_

#include <gtkmm/box.h>

#include "pbd/signals.h"

#include "ardour_window.h"

namespace ARDOUR {
	class IOPlug;
}

class IOPluginWindow : public ArdourWindow
{
public:
	IOPluginWindow ();
	~IOPluginWindow ();

	void set_session (ARDOUR::Session*);

protected:
	void on_show ();
	void on_hide ();

private:
	class IOPlugUI : public Gtk::VBox
	{
	public:
		IOPlugUI (boost::shared_ptr<ARDOUR::IOPlug>);
	private:
		void self_delete ();
		boost::shared_ptr<ARDOUR::IOPlug> _iop;
		PBD::ScopedConnection             _con;
	};

	Gtk::HBox _box_pre;
	Gtk::HBox _box_post;

	void refill ();
};

#endif


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

#include <gtkmm/frame.h>
#include <gtkmm/label.h>
#include <gtkmm/scrolledwindow.h>

#include "ardour/types.h"
#include "ardour/io_plug.h"
#include "ardour/session.h"

#include "gtkmm2ext/utils.h"

#include "io_plugin_window.h"
#include "gui_thread.h"

#include "pbd/i18n.h"

using namespace ARDOUR;
using namespace Gtk;

IOPluginWindow::IOPluginWindow()
	: ArdourWindow (_("I/O Plugins"))
{
	Gtk::VBox* vbox = manage (new Gtk::VBox);
	Gtk::Frame* frame;
	Gtk::ScrolledWindow* scroller;

	frame = manage (new Frame (_("Pre-Process")));
	scroller = manage (new ScrolledWindow);
	scroller->set_policy (Gtk::POLICY_AUTOMATIC, Gtk::POLICY_NEVER);
	frame->add (*scroller);
	scroller->add (_box_pre);
	vbox->pack_start (*frame);

	frame = manage (new Frame (_("Post-Process")));
	scroller = manage (new ScrolledWindow);
	scroller->set_policy (Gtk::POLICY_AUTOMATIC, Gtk::POLICY_NEVER);
	frame->add (*scroller);
	scroller->add (_box_post);
	vbox->pack_start (*frame);

	// TODO "Load plugin" button -- or right-click on blank area.

	add (*vbox);
	show_all ();
}

IOPluginWindow::~IOPluginWindow ()
{
}

void
IOPluginWindow::set_session (Session* s)
{
	printf ("IOPluginWindow::set_session %p\n", s);
	ArdourWindow::set_session (s);
	refill ();
}

void
IOPluginWindow::on_show ()
{
	ArdourWindow::on_show ();
	refill ();
}

void
IOPluginWindow::on_hide ()
{
	ArdourWindow::on_hide ();
}

void
IOPluginWindow::refill ()
{
	Gtkmm2ext::container_clear (_box_pre);
	Gtkmm2ext::container_clear (_box_post);
	if (!_session) {
		return;
	}
	boost::shared_ptr<IOPlugList> iop (_session->get_io_plugs ());
	for (auto & i : *iop) {
		IOPlugUI* iopup = manage (new IOPlugUI (i));
		if (i->is_pre ()) {
			_box_pre.pack_start (*iopup);
		} else {
			_box_post.pack_start (*iopup);
		}
		iopup->show ();
	}
}

/* ****************************************************************************/

IOPluginWindow::IOPlugUI::IOPlugUI (boost::shared_ptr<ARDOUR::IOPlug> iop)
	: _iop (iop)
{
	Gtk::Label* l = manage (new Label (iop->name()));
	pack_start (*l);
	// TODO add I/O connection buttons above/below
	// add a [delete] button and/or capture <backspace>
	// Double-click to show plugin GUI

	_iop->DropReferences.connect (_con, invalidator (*this), boost::bind (&IOPluginWindow::IOPlugUI::self_delete, this), gui_context());
	show_all ();
}

void
IOPluginWindow::IOPlugUI::self_delete ()
{
	get_parent ()->remove (*this);
}

/*
 * Copyright (C) 2007-2012 Carl Hetherington <carl@carlh.net>
 * Copyright (C) 2008-2010 Paul Davis <paul@linuxaudiosystems.com>
 * Copyright (C) 2009-2014 David Robillard <d@drobilla.net>
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

#include <ytkmm/comboboxtext.h>
#include <ytkmm/entry.h>
#include <ytkmm/liststore.h>
#include <ytkmm/treeview.h>

#include "ardour/user_bundle.h"

#include "ardour_dialog.h"
#include "port_matrix.h"

namespace ARDOUR {
	class Session;
	class Bundle;
}

class BundleEditorMatrix : public PortMatrix
{
public:
	BundleEditorMatrix (Gtk::Window *, ARDOUR::Session *, std::shared_ptr<ARDOUR::Bundle>);

	void set_state (ARDOUR::BundleChannel c[2], bool s);
	PortMatrixNode::State get_state (ARDOUR::BundleChannel c[2]) const;

	bool can_add_channels (std::shared_ptr<ARDOUR::Bundle>) const;
	bool can_add_port (std::shared_ptr<ARDOUR::Bundle>, ARDOUR::DataType t) const;

	void add_channel (std::shared_ptr<ARDOUR::Bundle>, ARDOUR::DataType);
	bool can_remove_channels (std::shared_ptr<ARDOUR::Bundle>) const;
	void remove_channel (ARDOUR::BundleChannel);
	bool can_rename_channels (std::shared_ptr<ARDOUR::Bundle>) const;
	void rename_channel (ARDOUR::BundleChannel);
	void setup_ports (int);
	bool list_is_global (int) const;

	std::string disassociation_verb () const;

private:
	enum {
		OTHER = 0,
		OURS = 1
	};

	std::shared_ptr<PortGroup> _port_group;
	std::shared_ptr<ARDOUR::Bundle> _bundle;
};

class BundleEditor : public ArdourDialog
{
public:
	BundleEditor (ARDOUR::Session *, std::shared_ptr<ARDOUR::UserBundle>);

protected:
	void on_map ();

private:
	void name_changed ();
	void input_or_output_changed ();
	void on_show ();

	BundleEditorMatrix _matrix;
	std::shared_ptr<ARDOUR::UserBundle> _bundle;
	Gtk::Entry _name;
	Gtk::ComboBoxText _input_or_output;
};

class BundleManager : public ArdourDialog
{
public:
	BundleManager (ARDOUR::Session *);

private:

	void new_clicked ();
	void edit_clicked ();
	void delete_clicked ();
	void add_bundle (std::shared_ptr<ARDOUR::Bundle>);
	void bundle_changed (ARDOUR::Bundle::Change, std::weak_ptr<ARDOUR::UserBundle>);
	void set_button_sensitivity ();
	void row_activated (Gtk::TreeModel::Path const & p, Gtk::TreeViewColumn* c);

	class ModelColumns : public Gtk::TreeModelColumnRecord
	{
	public:
		ModelColumns () {
			add (name);
			add (bundle);
		}

		Gtk::TreeModelColumn<std::string> name;
		Gtk::TreeModelColumn<std::shared_ptr<ARDOUR::UserBundle> > bundle;
	};

	Gtk::TreeView _tree_view;
	Glib::RefPtr<Gtk::ListStore> _list_model;
	ModelColumns _list_model_columns;
	Gtk::Button edit_button;
	Gtk::Button delete_button;
	PBD::ScopedConnectionList bundle_connections;
};

class NameChannelDialog : public ArdourDialog
{
public:
	NameChannelDialog ();
	NameChannelDialog (std::shared_ptr<ARDOUR::Bundle>, uint32_t);

	std::string get_name () const;

private:

	void setup ();

	std::shared_ptr<ARDOUR::Bundle> _bundle;
	Gtk::Entry _name;
	bool _adding;
};


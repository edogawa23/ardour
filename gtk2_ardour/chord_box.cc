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

#include "widgets/tooltips.h"

#include "gtkmm2ext/actions.h"

#include "editing_context.h"
#include "chord_box.h"
#include "ui_config.h"

#include "pbd/i18n.h"

using namespace ARDOUR;

struct DoubleButton : public Gtk::HBox
{
	DoubleButton (ArdourWidgets::ArdourButton & left, ArdourWidgets::ArdourButton & right);
};

DoubleButton::DoubleButton (ArdourWidgets::ArdourButton & left, ArdourWidgets::ArdourButton & right)
{
	using namespace ArdourWidgets;

	left.set_corner_mask (ArdourButton::LEFT);
	left.set_border_mask (ArdourButton::HIDE_RIGHT);

	right.set_corner_mask (ArdourButton::RIGHT);
	right.set_border_mask (ArdourButton::HIDE_LEFT);

	pack_start (left, true, true);
	pack_start (right, false, false);
	left.show ();
	right.show ();
}


ChordBox::ChordBox (EditingContext& ec)
	: editing_context (ec)
	, triad_label (_("3-Note Chords (Triads)"))
	, tetrad_label (_("4-Note Chords (Tetrads)"))
	, inversion_label (_("Inversions"))
	, drop_label (_("Drop Notes"))
	, _root (0)
	, _culture (WesternEurope12TET)
{
	using namespace Gtk;
	using namespace Menu_Helpers;
	using namespace ArdourWidgets;

	if (tet12_chords.empty()) {
		build_12tet_chords ();
	}

	/* these must match the enum decl order */
	culture_button.add_menu_elem (MenuElem (_("Western 12TET"), [this]() { set_culture (WesternEurope12TET); }));
	culture_button.add_menu_elem (MenuElem (_("Byzantine"), [this]() { set_culture (Byzantine); }));
	culture_button.add_menu_elem (MenuElem (_("Maqams"), [this]() { set_culture (Maqams); }));;
	culture_button.add_menu_elem (MenuElem (_("Hindustani"), [this]() { set_culture (Hindustani); }));;
	culture_button.add_menu_elem (MenuElem (_("Carnatic"), [this]() { set_culture (Carnatic); }));;
	culture_button.add_menu_elem (MenuElem (_("SEAsia"), [this]() { set_culture (SEAsia); }));;
	culture_button.add_menu_elem (MenuElem (_("China"), [this]() { set_culture (China); }));

	pack_start (culture_button, false, false);
	culture_button.show ();
	culture_button.set_active (0);

	set_border_width (12);
	set_spacing (6);
}

ChordBox::~ChordBox ()
{
}

void
ChordBox::set_culture (MusicalModeCulture culture)
{
	if (culture_button.get_active_row_number() != (int) culture) {
		culture_button.set_active ((int) culture);
	}

	_culture = culture;

	switch (_culture) {
	case WesternEurope12TET:
		if (western_vbox.children().empty()) {
			build_western ();
		}
		pack (western_vbox);
		break;
	case Byzantine:
		break;
	case Maqams:
		break;
	case Hindustani:
		break;
	case Carnatic:
		break;
	case SEAsia:
		break;
	case China:
		break;
	}
}


void
ChordBox::pack (Gtk::Widget& widget)
{
	if (western_vbox.get_parent()) {
		remove (western_vbox);
	}
	/* Other culture boxes go here */

	pack_start (widget, false, false);
}

bool
ChordBox::radio_ardour_button_hack (GdkEventButton* ev, ArdourWidgets::ArdourButton* button)
{
	Glib::RefPtr<Gtk::Action> act = button->get_related_action ();
	if (act) {
		Glib::RefPtr<Gtk::RadioAction> ract = Glib::RefPtr<Gtk::RadioAction>::cast_dynamic (act);
		if (ract) {
			if (ract->get_active ()) {
				editing_context.no_chord_action()->activate ();
				return true;
			}
		}
	}
	return false;
}

void
ChordBox::fill_table (Gtk::Table& table, std::vector<std::string> const & names, int chord_size)
{
	using namespace Gtk;
	using namespace Menu_Helpers;
	using namespace ArdourWidgets;

	ArdourButton* butl;
	ArdourButton* butr;
	DoubleButton* dbut;
	int row = 0;
	int col = 0;
	std::vector<std::string>::size_type n = 0;

	for (auto & s : names) {

		butl = manage (new ArdourButton (s));
		butl->signal_clicked.connect ([this,s]() { tet12_replace_chord (s); });

		butr = manage (new ArdourButton);
		butr->set_icon (ArdourIcon::ToolDraw);
		butr->set_elements (ArdourButton::Element (ArdourButton::Body|ArdourButton::Edge|ArdourButton::VectorIcon));
		butr->set_active_color (UIConfiguration::instance().color ("alert:yellow"));
		/* Hack code to catch a click on an already active draw chord
		   button, and deactivate it instead, using the highly-specific
		   EditingContext::no_chord_action() as the new active action.
		*/
		butr->signal_button_release_event().connect (sigc::bind (sigc::mem_fun (*this, &ChordBox::radio_ardour_button_hack), butr), false);

		if (n < names.size()) {

			Glib::RefPtr<RadioAction> ract;
			if (chord_size == 3) {
				ract = editing_context.draw_triad_action (n);
			} else {
				ract = editing_context.draw_tetrad_action (n);
			}

			if (ract) {
				butr->set_related_action (ract);
			}
		}

		dbut = new DoubleButton (*butl, *butr);
		table.attach (*dbut, col, col+1, row, row+1);

		++n;
		++col;
		if (col % 2 == 0) {
			col = 0;
			++row;
		}
	}

	table.set_homogeneous (true);
	table.set_col_spacings (6);
}


void
ChordBox::build_western ()
{
	using namespace Gtk;
	using namespace Menu_Helpers;
	using namespace ArdourWidgets;

	triad_table.resize (3, 2);
	tetrad_table.resize (5, 2);
	inversion_table.resize (1, 2);
	drop_table.resize (2, 2);

	int row = 0;
	int col = 0;

	fill_table (triad_table, editing_context.triad_name_list(), 3);
	fill_table (tetrad_table, editing_context.tetrad_name_list(), 4);

	/* Inversions */

	row = 0;
	col = 0;

	ArdourButton* but;

	but = manage (new ArdourButton);
	but->set_elements (ArdourButton::Element (ArdourButton::Edge|ArdourButton::Body|ArdourButton::Text));
	but->set_text (_("Move Up"));
	but->signal_clicked.connect ([this]() { tet12_invert_chord (true); });
	ArdourWidgets::set_tooltip (*but, _("Move the lowest pitch in the selected chord up by 1 octave"));
	inversion_table.attach (*but, col, col+1, row, row+1);
	col++;
	but = manage (new ArdourButton);
	but->set_elements (ArdourButton::Element (ArdourButton::Edge|ArdourButton::Body|ArdourButton::Text));
	but->set_text (_("Move Down"));
	but->signal_clicked.connect ([this]() { tet12_invert_chord (false); });
	ArdourWidgets::set_tooltip (*but, _("Move the highest pitch in the selected chord down by 1 octave"));
	inversion_table.attach (*but, col, col+1, row, row+1);
	col = 0;
	row++;

	inversion_table.set_homogeneous (true);
	inversion_table.set_col_spacings (6);

	/* Drops */

	row = 0;
	col = 0;

	but = manage (new ArdourButton);
	but->set_elements (ArdourButton::Element (ArdourButton::Edge|ArdourButton::Body|ArdourButton::Text));
	but->set_text (_("Drop 2"));
	ArdourWidgets::set_tooltip (*but, _("Move the 2nd lowest pitch in the selected chord down by 1 octave"));
	but->signal_clicked.connect ([this]() { tet12_drop_chord ({ 1 }); });
	drop_table.attach (*but, col, col+1, row, row+1);
	col++;
	but = manage (new ArdourButton);
	but->set_elements (ArdourButton::Element (ArdourButton::Edge|ArdourButton::Body|ArdourButton::Text));
	but->set_text (_("Drop 3"));
	ArdourWidgets::set_tooltip (*but, _("Move the 3rd lowest pitch in the selected chord down by 1 octave"));
	but->signal_clicked.connect ([this]() { tet12_drop_chord ({ 2 }); });
	drop_table.attach (*but, col, col+1, row, row+1);
	col = 0;
	row++;
	but = manage (new ArdourButton);
	but->set_elements (ArdourButton::Element (ArdourButton::Edge|ArdourButton::Body|ArdourButton::Text));
	but->set_text (_("Drop 2 + 4"));
	ArdourWidgets::set_tooltip (*but, _("Move the 2nd &amp; 4th lowest pitches in the selected chord down by 1 octave (tetrads only)"));
	but->signal_clicked.connect ([this]() { tet12_drop_chord ({ 1, 3 }); });
	drop_table.attach (*but, col, col+2, row, row+1);
	col = 0;
	row++;

	drop_table.set_homogeneous (true);
	drop_table.set_col_spacings (6);


	triad_label.set_alignment (0.0, 0.5);
	tetrad_label.set_alignment (0.0, 0.5);
	inversion_label.set_alignment (0.0, 0.5);
	drop_label.set_alignment (0.0, 0.5);

	name_display.modify_font (UIConfiguration::instance().get_LargeBoldFont());

	western_vbox.pack_start (name_display, false, false);
	western_vbox.pack_start (triad_label, false, false);
	western_vbox.pack_start (triad_table, false, false);
	western_vbox.pack_start (tetrad_label, false, false);
	western_vbox.pack_start (tetrad_table, false, false);
	western_vbox.pack_start (inversion_label, false, false);
	western_vbox.pack_start (inversion_table, false, false);
	western_vbox.pack_start (drop_label, false, false);
	western_vbox.pack_start (drop_table, false, false);

	western_vbox.show_all ();
	western_vbox.set_spacing (6);

	pack_start (western_vbox);
}

void
ChordBox::show_chord (std::string const & name)
{
	name_display.set_text (name);
}

bool
ChordBox::get_midi_chord (int root_pitch, std::vector<int>& pitches) const
{
	std::string const & chord_name = editing_context.draw_chord_name ();
	if (chord_name.empty()) {
		return false;
	}

	auto res = tet12_chords.find (chord_name);

	if (res != tet12_chords.end()) {
		for (auto & interval : res->second) {
			pitches.push_back (root_pitch + interval);
		}
		return true;
	}

	return false;
}

void
ChordBox::tet12_replace_chord (std::string const & name)
{
	auto res = tet12_chords.find (name);

	if (res != tet12_chords.end()) {
		ReplaceChord (res->second); /* EMIT SIGNAL */
	}
}

void
ChordBox::tet12_invert_chord (bool up)
{
	InvertChord (up); /* EMIT SIGNAL */
}

void
ChordBox::tet12_drop_chord (std::vector<int> const & which_notes)
{
	DropChord (which_notes);
}

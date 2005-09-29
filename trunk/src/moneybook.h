/*  MoneyBook, a double bookkeeping program
  *  Copyright (C) 2005  Nathan Samson
  *
  *  This program is free software; you can redistribute it and/or modify
  *  it under the terms of the GNU General Public License as published by
  *  the Free Software Foundation; either version 2 of the License, or
  *   any later version.
  *
  *  This program is distributed in the hope that it will be useful,
  *  but WITHOUT ANY WARRANTY; without even the implied warranty of
  *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  *  GNU General Public License for more details.
  *
  *  You should have received a copy of the GNU General Public License
  *  along with this program; if not, write to the Free Software
  *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/
#ifndef MONEYBOOK_H
#define MONEYBOOK_H
#include <gtkmm.h>
#include <string>

#include "general.h"
class CMoneybookGUI : public Gtk::Window {
	public: 
		CMoneybookGUI ();
		virtual ~CMoneybookGUI ();
	private:
		void addItemsMenu ();

		void on_hide ();
		void onPreferences ();
		void onAbout ();

		Gtk::VBox* vBox;
		Gtk::Widget* menu;
		Gtk::Widget* toolbar;
		Gtk::Statusbar* statusbar;

		Gtk::AboutDialog* aboutDialog; 

		std::list<Glib::ustring> authors;
		Glib::RefPtr<Gtk::UIManager> refUIManager;
		Glib::RefPtr<Gtk::ActionGroup> refActionGroup;
};
#endif

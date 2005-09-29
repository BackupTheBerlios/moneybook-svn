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

#include "general.h"
#include "moneybook.h"

CMoneybookGUI::CMoneybookGUI () {
	vBox = new Gtk::VBox;
	add (*vBox);
	vBox->show ();
	
	statusbar = new Gtk::Statusbar;
	vBox->pack_end (*statusbar,false,false);
	statusbar->show ();

	addItemsMenu ();
	aboutDialog = NULL;

	authors.push_back ("Nathan Samson");
}

CMoneybookGUI::~CMoneybookGUI () {
}

void CMoneybookGUI::addItemsMenu () {
	refActionGroup = Gtk::ActionGroup::create ();

	//File menu:
	refActionGroup->add (Gtk::Action::create ("FileMenu","File"));
	refActionGroup->add (Gtk::Action::create ("FileNew",Gtk::Stock::NEW));
	refActionGroup->add (Gtk::Action::create ("FileSave",Gtk::Stock::SAVE));
	refActionGroup->add (Gtk::Action::create ("FileSaveAs",Gtk::Stock::SAVE_AS));
	refActionGroup->add (Gtk::Action::create ("FileQuit",Gtk::Stock::QUIT),sigc::mem_fun(*this,&CMoneybookGUI::hide));

	//Edit menu:
	refActionGroup->add (Gtk::Action::create ("EditMenu","Edit"));
	refActionGroup->add (Gtk::Action::create ("EditPreferences",Gtk::Stock::PREFERENCES),sigc::mem_fun(*this, &CMoneybookGUI::onPreferences));

	//Help menu:
	refActionGroup->add (Gtk::Action::create ("HelpMenu","Help"));
	refActionGroup->add (Gtk::Action::create ("HelpAbout",Gtk::Stock::HELP),sigc::mem_fun(*this, &CMoneybookGUI::onAbout));

	refUIManager = Gtk::UIManager::create ();
	refUIManager->insert_action_group (refActionGroup);
 
	add_accel_group (refUIManager->get_accel_group ());

	//Layout the actions in a menubar and toolbar:
	try {
		Glib::ustring ui_info = 
			"<ui>"
			"	<menubar name='MenuBar'>"
			"		<menu action='FileMenu'>"
			"			<menuitem action='FileNew'/>"
			"			<menuitem action='FileSave'/>"
			"			<menuitem action='FileSaveAs'/>"
			"			<separator/>"
			"			<menuitem action='FileQuit'/>"
			" 		</menu>"
			"		<menu action='EditMenu'>"
			"			<menuitem action='EditPreferences'/>"
			"		</menu>"
			"		<menu action='HelpMenu'>"
			"			<menuitem action='HelpAbout'/>"
			"		</menu>"
			"	</menubar>"
			"	<toolbar name='ToolBar'>"
			"		<toolitem action='FileNew'/>"
			"		<toolitem action='FileQuit'/>"
			"	</toolbar>"
			"</ui>";

        		refUIManager->add_ui_from_string(ui_info);
	} catch (const Glib::Error& ex) {
		std::cerr << "building menus failed: " <<  ex.what();
	}

	//Get the menubar and toolbar widgets, and add them to a container widget:
	menu = refUIManager->get_widget ("/MenuBar");
	if (menu)
		vBox->pack_start (*menu,Gtk::PACK_SHRINK);

	toolbar = refUIManager->get_widget ("/ToolBar") ;
	if (toolbar)
		vBox->pack_start (*toolbar,Gtk::PACK_SHRINK);

	show_all_children ();
}

void CMoneybookGUI::on_hide () {
	std::cout << "Dit is een andere saving-thing" << std::endl;
}

void CMoneybookGUI::onPreferences () {
}

void CMoneybookGUI::onAbout () {
	if (aboutDialog) {
		aboutDialog->present ();
	} else {
		aboutDialog = new Gtk::AboutDialog ();
		aboutDialog->set_authors (authors);
		aboutDialog->set_comments ("A double bookkeeping program");
		aboutDialog->set_version ("0.1 SVN");
		aboutDialog->set_license ("GPL");
		aboutDialog->set_website ("http://moneybook.berlios.de");
		aboutDialog->set_website_label ("gtkmm website");
		aboutDialog->show ();
	}
}

int main (int argc,char *argv[]) {
	Gtk::Main kit (argc,argv);
	CMoneybookGUI main;
	kit.run (main);

	return 0;
}

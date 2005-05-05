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
#include <wx/wx.h>

#include "moneybook.h"

MyFrame::MyFrame (const wxString& title, const wxPoint& pos, const wxSize& size)
: wxFrame((wxFrame *)NULL, -1, title, pos, size) {
	wxMenu* menuFile = new wxMenu;

	menuFile->Append(ID_About, _T("&About..." ));
	menuFile->AppendSeparator();
	menuFile->Append(ID_Quit, _T("E&xit" ));

	wxMenuBar *menuBar = new wxMenuBar;
	menuBar->Append(menuFile, _T("&File" ));

	SetMenuBar( menuBar );

	CreateStatusBar();
	SetStatusText( _T("Welcome to wxWidgets!" ));
}

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event)) {
	Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& WXUNUSED(event)) {
	wxMessageBox(_T("This is a wxWidgets Hello world sample"),_T("About Hello World"), wxOK | wxICON_INFORMATION, this);
}

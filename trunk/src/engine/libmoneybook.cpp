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
#include <fstream>
#include <string>

#include "../general.h"
#include "libmoneybook.h"

std::string SortPostToString ( SSortPost SortPost ) {
	switch ( SortPost ) {
		case ACTIVE: return "ACTIVE";
			break;
		case PASSIVE: return "PASSIVE";
			break;
		case COST: return "COST";
			break;
		case WINST: return "WINST";
			break;
		default: return "NOTVALID";
	}
} /* std::string SortPostToString ( SSortPost SortPost  */

SSortPost StringToSortPost ( std::string SortPost ) {
	if (SortPost == "ACTIVE") {
		return ACTIVE;
	} else if (SortPost == "PASSIVE") {
		return PASSIVE;
	} else if (SortPost == "COST") {
		return COST;
	} else if (SortPost == "WINST") {
		return WINST;
	} else {
		return NOTVALID;
	}
} /* SSortPost StringToSortPost ( std::string SortPost )  */

/*!
	Constructor CBookKeeping
*/
CBookKeeping::CBookKeeping () {
	FirstPost = 0;
	LastPost = 0;
	
	FirstJournal = 0;
	LastJournal = 0;
} /* Bookkeeping::BookKeeping () */

/*!
	Destructor CBookKeeping
*/
CBookKeeping::~CBookKeeping () {
	cdebug << "Destructor CBookKeeping" << std::endl;
	CJournal* CurJournal = FirstJournal;
	while (CurJournal != 0) {
		FirstJournal = CurJournal->getNext ();
		delete CurJournal;
		CurJournal = FirstJournal;
	}

	CPost* CurPost = FirstPost;
	while (CurPost != 0) {
		FirstPost = CurPost->getNext ();
		delete CurPost;
		CurPost = FirstPost;
	}
} /* CBookKeeping::~CBookKeeping ()  */

/*!
	returns of a number is in a defined rang, if so return true
*/
bool CBookKeeping::searchByNumber (int Minimum,int Maximum,int Number) {
	bool BMinimum,BMaximum;
	BMinimum = false;
	BMaximum = false;
	
	if (Minimum == 0) {
		BMinimum = true;
	} else {
		if (Number >= Minimum) {
			BMinimum = true;
		}
	}
	
	if (Maximum == 0) {
		BMaximum = true;
	} else {
		if (Number <= Maximum) {
			BMaximum = true;
		}
	}
	
	if ((BMinimum == true) && (BMaximum == true)) {
		return true;
	} else {
		return false;
	}
} /* bool CBookKeeping::searchByNumber (int Minimum,int Maximum,int Number) */

/*!
	returns all Journals who are in a range ( 0 is "I don't care" )
*/
SJournal* CBookKeeping::getJournalByNumber (int Minimum,int Maximum) {
	CJournal* CurJournal = FirstJournal;
	SJournal* FirstRJournal = 0;
	SJournal* LastRJournal = 0;
	
	while (CurJournal != 0) {
		if (searchByNumber (Minimum,Maximum,CurJournal->getId ())) {
			SJournal* CurRJournal = new SJournal;
			if (FirstRJournal == 0) {
				FirstRJournal = CurRJournal;
				LastRJournal = FirstRJournal;
			} else {
				LastRJournal->Next = CurRJournal;
			}
			CurRJournal->Journal = CurJournal;
			CurRJournal->Next = 0;
			LastRJournal = CurRJournal;
		}
		CurJournal = CurJournal->getNext ();
	}
	return FirstRJournal;
} /* CJournal* CBookKeeping::getJournalByNumber (int Minimum,int Maximum)  */

/*!
	add a post in the dynamic list
*/
void CBookKeeping::addPost (std::string name,unsigned short id,SSortPost SortPost) {
	CPost* CurPost  = new CPost (name,id,SortPost);
	cdebug << "add posts" << std::endl;
	if (FirstPost == 0) {
		FirstPost = CurPost;
		cdebug << "FirstPost == empty" << std::endl;
	} else {
		LastPost->setNext (CurPost);
		cdebug << "FirstPost != empty" << std::endl;
	}
	LastPost = CurPost;
} /* void CBookKeeping::addPost (std::string name,unsigned short id,SSortPost SortPost) */

/*!
	returns a new CJournalEdit*
*/
CJournalEdit* CBookKeeping::newJournalEdit (bool DebetEdit,CPost* Post,long double Value) {
	CJournalEdit* JournalEdit = new CJournalEdit (DebetEdit,Post,Value);
	return JournalEdit;
} /* CJournalEdit* CBookKeeping::newJournalEdit (bool DebetEdit,CPost* Post,long double Value) */

/*!
	set the next on a given JournalEdit
*/
bool CBookKeeping::setNextOnJournalEdit (CJournalEdit* CurJEdit,CJournalEdit* FirstJEdit,CJournalEdit* LastJEdit) {
	if (FirstJEdit == 0)  {
		FirstJEdit = CurJEdit;
	} else {
		LastJEdit->setNext (CurJEdit);
	}
	LastJEdit = CurJEdit;
	return true;
} /* bool CBookKeeping::setNextOnJournalEdit (CJournalEdit* CurJEdit,CJournalEdit* FirstJEdit,CJournalEdit* LastJEdit) */

/*!
	returns a post whose name matches Name
*/
CPost* CBookKeeping::getPostByName (std::string Name) {
	CPost* CurPost = FirstPost;
	cdebug << "Search Post By: " << Name << std::endl;
	while (CurPost != 0) {
		cdebug << CurPost << std::endl;
		if (CurPost->getName () == Name) {
			cdebug << CurPost->getName () << Name<< std::endl;
			return CurPost;
		}
		CurPost = CurPost->getNext();
	} 
	//cdebug << ""
	cdebug << "empty" << std::endl;
	return 0;
} /* CPost* CBookKeeping::getPostByName (std::string Name) */

/*!
	get the FirstPost
*/
CPost* CBookKeeping::getFirstPost () {
	return FirstPost;
} /* CPost* CBookKeeping::getFirstPost ()  */

/*!
	get the last post
*/
CPost* CBookKeeping::getLastPost () {
	return LastPost;
} /* CPost* CBookKeeping::getLastPost ()  */

/*!
	book a journal, and book with that information also the corresponding posts
*/
bool CBookKeeping::bookJournal (TDate JDate,std::string Document,CJournalEdit* FirstJournalEdit) {
	CJournal* CurJournal; 
	if ( FirstJournal == 0 ) {
		CurJournal = new CJournal (JDate,Document,1,FirstJournalEdit);
		FirstJournal = CurJournal;
	} else {
		CurJournal = new CJournal (JDate,Document,LastJournal->getId () + 1,FirstJournalEdit);
		LastJournal->setNext (CurJournal);
	}
	LastJournal = CurJournal;

	// Now book it on Posts
	CJournalEdit* CurJournalEdit = FirstJournalEdit;
	while (CurJournalEdit != 0) {
		cdebug << "boeken in posts" << std::endl;
		if (CurJournalEdit->getPost() == 0) {cdebug << "empty" << std::endl; }
		CPostEdit* CurPostEdit = new CPostEdit (CurJournalEdit->getDebetEdit (),CurJournalEdit->getValue (),CurJournal->getId ());
		if ( CurJournalEdit->getPost ()->getFirstPostEdit () == 0 ) {
			CurJournalEdit->getPost ()->setFirstPostEdit (CurPostEdit);
		} else {
			CurJournalEdit->getPost ()->getLastPostEdit ()->setNext (CurPostEdit);
		}
		CurJournalEdit->getPost ()->setLastPostEdit (CurPostEdit);

		CurJournalEdit = CurJournalEdit->getNext ();
	}

} /* CBookKeeping::bookJournal (TDate JDate,std::string Document,CJournalEdit* JFirstJournalEdit) */

/*!
	get the current FileName
*/
std::string CBookKeeping::getFileName () {
	return FileName;
} /* std::string CBookKeeping::getFileName () */

/*!
	set the FileName to sFileName
*/
void CBookKeeping::setFileName ( std::string sFileName ) {
	FileName = sFileName;
} /* void CBookKeeping::setFileName ( std::string sFileName ) */

/*!
	save it, if sFileName is empty, use FileName, if that is empty return nothing and end
*/
bool CBookKeeping::save (std::string sFileName) {	
	if ( sFileName == "" ) {
		if ( FileName != "" ) {
			sFileName = FileName;
		} else {
			cdebug << "Error, no filename given, return false" << std::endl;
			return false;
		}
	} else {
		FileName = sFileName;
	}
	std::ofstream File (sFileName.c_str());

	if (File.is_open())
	{
		File << "<?xml version=\"1.0\"?>\n";
		File << "<bookkeeping>\n";
		
		// Save the Posts
		File << "\t<posts>\n";
		CPost* CurPost = FirstPost;
		while (CurPost != 0) {
			File << "\t\t<post name=\"" << CurPost->getName () << "\" id=\"" << CurPost->getId () << "\" ";
			File << "sort=\"" << SortPostToString (CurPost->getSortPost ()) << "\" saldo=\"" << CurPost->getSaldo () << "\" />\n";
			CurPost = CurPost->getNext ();
		}
		File << "\t</posts>\n";

		// Save the Journals
		File << "\t<journals>\n";
		CJournal* CurJournal = FirstJournal;
		while (CurJournal != 0) {
			File << "\t\t<journal id=\" "<< CurJournal->getId () << "\" "; 
			File << "document=\"" << CurJournal->getDocument () << "\" date=\"" << CurJournal->getDate ().date << "\" >\n";

			CJournalEdit* CurJournalEdit = CurJournal->getFirstJournalEdit ();
			while (CurJournalEdit != 0) {
				File << "\t\t\t <journaledit "; 
				File << "postname=\"" << CurJournalEdit->getPost ()->getName () << "\" ";
				File << "value=\"" << CurJournalEdit->getValue () << "\" ";
				File << "debetedit=\"" << CurJournalEdit->getDebetEdit () << "\" ";
				File << "/>\n";
				CurJournalEdit = CurJournalEdit->getNext ();
			} 

			File << "\t\t</journal>\n";
			CurJournal = CurJournal->getNext ();
		}
		File << "\t</journals>\n";

		File << "</bookkeeping>";
	}
	File.close();
	cdebug << "saved as: " << sFileName << std::endl;
	return true;
} /* void CBookKeeping::save (std::string sFileName)  */

/*!
	load a savefile
	if lFileName is empty FileName is used
	if there is already opened a file or already started to work on posts / journals override
	must be true to load a file
*/
bool CBookKeeping::load (std::string LFileName,bool override) {
	if (LFileName != "") {
		if (FileName == "") {
			FileName = LFileName;
		} else {
			cdebug << "There is already assigned a filename" << std::endl;
			if (override == false) {
				return false;
			} else {
				cdebug << "override" << std::endl;
				FileName = LFileName;
			}
		}
	} else {
		if (FileName == "") {
			FileName = LFileName;
		} else {
			cdebug << "There is already assigned a filename" << std::endl;
			if (override == false) {
				return false;
			} else {
				cdebug << "override" << std::endl;
				FileName = LFileName;
			}
		}
	}

	if ( ( FirstJournal == 0 ) and ( FirstPost == 0 ) ) {
		
	} else {
		cdebug << "Already modified" << std::endl;
		if ( override == false ) {
			return false;
		} else {
			cdebug << "override" << std::endl;
		}
	}

	return true;
} /* bool CBookKeeping::load (std::string LFileName,bool override) */ 

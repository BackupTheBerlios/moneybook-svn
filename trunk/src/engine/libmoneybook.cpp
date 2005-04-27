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

#include "libmoneybook.h"

#include <string>
#include <fstream>
#include <iostream>

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
	std::cout << "Destructor CBookKeeping" << std::endl;
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
	if (FirstPost == 0)  {
		FirstPost = CurPost;
	} else {
		LastPost->setNext (CurPost);
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
	while (CurPost != 0) {
		if (CurPost->getName () == Name) {
			return CurPost;
		}
		CurPost = CurPost->getNext();
	}
	// Not found
	/*try {
		throw ();
	}*/
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
	while (CurJournalEdit) {
		std::cout << "boeken in posts" << std::endl;
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
			std::cout << "Error, no filename given, return false" << std::endl;
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
		File << "\t<posts>\n";
		
		// Save the Posts
		CPost* CurPost = FirstPost;
		while (CurPost != 0) {
			File << "\t\t<post name=\"" << CurPost->getName () << "\" id=\"" << CurPost->getId () << "\" />\n";
			CurPost = CurPost->getNext ();
		}
		File << "\t</posts>\n";
		File << "</bookkeeping>";
	}
	File.close();
	std::cout << "saved as: " << sFileName << std::endl;
	return true;
} /* void CBookKeeping::save (std::string sFileName)  */



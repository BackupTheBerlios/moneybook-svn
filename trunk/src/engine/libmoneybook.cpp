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
#include <iostream>
#include <stdlib.h>

CBookKeeping::CBookKeeping () {
	FirstPost = 0;
	LastPost = 0;
	
	FirstJournal = 0;
	LastJournal = 0;
} /* Bookkeeping::BookKeeping () */

CBookKeeping::~CBookKeeping () {
	std::cout << "Destructor CBookKeeping" << std::endl;
	CJournal* CurJournal = FirstJournal;
	do {
		FirstJournal = CurJournal->getNext ();
		delete CurJournal;
		CurJournal = FirstJournal;
	} while ( CurJournal != 0 );
} /* CBookKeeping::~CBookKeeping ()  */

bool CBookKeeping::searchByNumber ( int Minimum,int Maximum,int Number ) {
	bool BMinimum,BMaximum;
	BMinimum = false;
	BMaximum = false;
	
	if ( Minimum == 0 ) {
		BMinimum = true;
	} else {
		if ( Number >= Minimum ) {
			BMinimum = true;
		}
	}
	
	if ( Maximum == 0 ) {
		BMaximum = true;
	} else {
		if ( Number <= Maximum ) {
			BMaximum = true;
		}
	}
	
	if ( ( BMinimum == true ) && ( BMaximum == true ) ) {
		return true;
	} else {
		return false;
	}
} /* bool CBookKeeping::searchByNumber ( int Minimum,int Maximum,int Number ) */

SJournal* CBookKeeping::getJournalByNumber ( int Minimum,int Maximum ) {
	CJournal* CurJournal = FirstJournal;
	SJournal* FirstRJournal = 0;
	SJournal* LastRJournal = 0;
	
	do {
		if ( searchByNumber ( Minimum,Maximum,CurJournal->getId () ) ) {
			SJournal* CurRJournal = new SJournal;
			if ( FirstRJournal == 0 ) {
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
	} while ( CurJournal != 0 );
	return FirstRJournal;
} /* CJournal* CBookKeeping::getJournalByNumber ( int Minimum,int Maximum )  */

bool CBookKeeping::addPost ( std::string name,unsigned int id ) {
	CPost* CurPost  = new CPost ( name,id );
	if ( FirstPost == 0 )  {
		FirstPost = CurPost;
	} else {
		LastPost->setNext ( CurPost );
	}
	LastPost = CurPost;
	return true;
} /*  CBookKeeping::addPost ( std::string name,unsigned int id ) */

CJournalEdit* CBookKeeping::newJournalEdit ( bool DebetEdit,CPost* Post,float Value ) {
	CJournalEdit* JournalEdit = new CJournalEdit ( DebetEdit,Post,Value );
	return JournalEdit;
} /* CJournalEdit* CBookKeeping::newJournalEdit ( bool DebetEdit,CPost* Post,float Value ) */

bool CBookKeeping::setNextOnJournalEdit ( CJournalEdit* CurJEdit,CJournalEdit* FirstJEdit,CJournalEdit* LastJEdit ) {
	if ( FirstJEdit == 0 )  {
		FirstJEdit = CurJEdit;
	} else {
		LastJEdit->setNext ( CurJEdit );
	}
	LastJEdit = CurJEdit;
	return true;
} /* bool CBookKeeping::setNextOnJournalEdit ( CJournalEdit* CurJEdit,CJournalEdit* FirstJEdit,CJournalEdit* LastJEdit ) */

CPost* CBookKeeping::getPostByName ( std::string Name ) {
	CPost* CurPost = FirstPost;
	do {
		if ( CurPost->getName () == Name ) {
			return CurPost;
		}
		CurPost = CurPost->getNext();
	} while ( CurPost != 0 );
	// Not found
	/*try {
		throw ();
	}*/
} /* CPost* CBookKeeping::getPostByName ( std::string Name ) */

bool CBookKeeping::bookJournal ( TDate JDate,std::string Document,CJournalEdit* FirstJournalEdit ) {
	CJournal* CurJournal; 
	if ( FirstJournal == 0 ) {
		CurJournal = new CJournal ( JDate,Document,1,FirstJournalEdit );
		FirstJournal = CurJournal;
	} else {
		CurJournal = new CJournal ( JDate,Document,LastJournal->getId () + 1,FirstJournalEdit );
		LastJournal->setNext ( CurJournal );
	}
	LastJournal = CurJournal;
} /* CBookKeeping::bookJournal ( TDate JDate,CJournalEdit* JFirstJournalEdit ) */

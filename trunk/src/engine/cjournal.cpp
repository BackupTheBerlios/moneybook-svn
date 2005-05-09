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
#include <string>

#include "../general.h"
#include "libmoneybook.h"

/*! 
	Constructor of CJournal 
*/
CJournal::CJournal (TDate JDate,std::string JDocument,unsigned int JId,CJournalEdit* JFirstJournalEdit) {
	Date = JDate;
	Document = JDocument;
	Id = JId;
	FirstJournalEdit = JFirstJournalEdit;
	Next = 0;
} /* CJournal::CJournal (TDate JDate,std::string JDocument,unsigned int JId,CJournalEdit* JFirstJournalEdit) */

/*!
	Copy's an CJournal, except of the Next
*/
CJournal::CJournal (CJournal* Journal) {
	Date = Journal->getDate ();
	Document = Journal->getDocument ();
	Id = Journal->getId ();
	FirstJournalEdit = Journal->getFirstJournalEdit ();
	Next = 0;
} /*CJournal::CJournal (CJournal* Journal) */

/*! 
	Destrucor of CJournal 
*/
CJournal::~CJournal () {
	cdebug << "Destructor CJournal" << std::endl;
	CJournalEdit* CurJournalEdit = FirstJournalEdit;
	while (CurJournalEdit != 0) {
		FirstJournalEdit = CurJournalEdit->getNext ();
		delete CurJournalEdit;
		CurJournalEdit = FirstJournalEdit;
	};
} /* CJournal::~CJournal () */

/* !
	Get the Next in the Dynamic list of CJournal 
*/
CJournal* CJournal::getNext () {
	return Next;
} /* CJournal* CJournal::getNext () */

/* !
	Set the Next in the Dynamic list of CJournal 
*/
void CJournal::setNext (CJournal* JNext) {
	Next = JNext;
} /* void CJournal::setNext (CJournal* Jnext) */

/*!
	Get the id ( each journal has his own Id ) of a CJournal 
*/
unsigned int CJournal::getId () {
	return Id;
} /* unsigned int CJournal::getId () */

/* !
	Get the first JournalEdit 
*/
CJournalEdit* CJournal::getFirstJournalEdit () {
	return FirstJournalEdit;
} /* CJournalEdit* CJournal::getFirstJournalEdit () */

/*!
	Get the date of the Cjournal 
*/
TDate CJournal::getDate () {
	return Date;
} /* TDate CJournal::getDate () */

/* !
	Get the document of the Cjournal 
*/
std::string CJournal::getDocument () {
	return Document;
} /* std::string CJournal::getDocument () */

/*!
	get all journaledits from CJournal who matches DebetEdit,an put it in an new list
*/
CJournalEdit* CJournal::getJournalEditByDebetEdit (bool DebetEdit) {
	CJournalEdit* TmpFirstJournalEdit = 0;
	CJournalEdit* TmpLastJournalEdit = 0;
	CJournalEdit* TmpCurJournalEdit = 0;

	CJournalEdit* CurJournalEdit = FirstJournalEdit;

	while (CurJournalEdit != 0) {
		if (CurJournalEdit->getDebetEdit () == DebetEdit) {
			// Copy this one in an new
			TmpCurJournalEdit = new CJournalEdit (CurJournalEdit);
			if (TmpFirstJournalEdit == 0) {
				TmpFirstJournalEdit = TmpCurJournalEdit;
			} else {
				TmpLastJournalEdit->setNext (TmpCurJournalEdit);
			}
			TmpLastJournalEdit = TmpCurJournalEdit;
		}
		CurJournalEdit = CurJournalEdit->getNext ();
	}
} /* CJournalEdit* CJournal::getJournalEditByDebetEdit (bool DebetEdit) */

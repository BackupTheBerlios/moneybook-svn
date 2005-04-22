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

CJournal::CJournal ( TDate JDate,std::string JDocument,unsigned int JId,CJournalEdit* JFirstJournalEdit ) {
	Date = JDate;
	Document = JDocument;
	Id = JId;
	FirstJournalEdit = JFirstJournalEdit;
	Next = 0;
} /* CJournal::CJournal ( TDate JDate,std::string JDocument,unsigned int JId,CJournalEdit* JFirstJournalEdit ) */

void CJournal::setNext ( CJournal* JNext ) {
	Next = JNext;
} /* void CJournal::setNext ( CJournal* Jnext ) */

CJournal* CJournal::getNext () {
	return Next;
} /* CJournal* CJournal::getNext () */

unsigned int CJournal::getId () {
	return Id;
} /* unsigned int CJournal::getId () */

CJournalEdit* CJournal::getFirstJournalEdit () {
	return FirstJournalEdit;
} /* CJournalEdit* CJournal::getFirstJournalEdit () */

TDate CJournal::getDate () {
	return Date;
} /* TDate CJournal::getDate () */

std::string CJournal::getDocument () {
	return Document;
} /* std::string CJournal::getDocument () */


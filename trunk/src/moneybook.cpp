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
#include <iostream>

#include "general.h"
#include "engine/libmoneybook.h"

int main () {
	CBookKeeping* Test = new CBookKeeping;
	cdebug << "dit is een leuk programma" << std::endl;
	Test = new CBookKeeping;
	try {
		Test->load ("first.xml");
	}
	catch (CException e) {
		cdebug << "Exception occured: " << e.what << std::endl;
	}
	catch (...) {
		cdebug << "Uknown exception occured: " << std::endl;
	}

	SJournal* CurRJournal = Test->getJournalByNumberRange (0,0);
	while (CurRJournal != 0) {
		std::cout << "Id: " << CurRJournal->Journal->getId () << " Date: "  << CurRJournal->Journal->getDate ().date << std::endl;
		SJournalEdit* JournalEdit = CurRJournal->Journal->getJournalEditByDebetEdit (true);
		while (JournalEdit != 0) {
			std::cout << JournalEdit->JournalEdit->getPost ()->getId () << "  ";
			std::cout << JournalEdit->JournalEdit->getPost ()->getName () << "  " ;
			std::cout << JournalEdit->JournalEdit->getValue () << std::endl;
			JournalEdit = JournalEdit->Next;
		};
		std::cout << "                  @" << std::endl;
		JournalEdit = CurRJournal->Journal->getJournalEditByDebetEdit (false);
		while (JournalEdit != 0) {
			std::cout << JournalEdit->JournalEdit->getPost ()->getId () << "  ";
			std::cout << JournalEdit->JournalEdit->getPost ()->getName () << "  ";
			std::cout << "            " << JournalEdit->JournalEdit->getValue () << std::endl;
			JournalEdit = JournalEdit->Next;
		};
		std::cout << std::endl << std::endl;
		CurRJournal = CurRJournal->Next;
	}
	
	CPost* CurPost = Test->getFirstPost ();
	while (CurPost != 0) {
		std::cout << "Id: " << CurPost->getId () << " Name: " << CurPost->getName () << std::endl;
		std::cout << " Saldo: " << CurPost->getSaldo () << std::endl;
		CurPost = CurPost->getNext ();
	};

	delete Test;
}

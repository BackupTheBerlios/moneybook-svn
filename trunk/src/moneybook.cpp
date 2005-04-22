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

#include "engine/libmoneybook.h"

#include <iostream>

int main () {
	std::cout << "dit is een leuk programma" << std::endl;
	CBookKeeping* Test = new CBookKeeping;
	Test->addPost ( "Kapitaal",1000 );
	Test->addPost ( "Bank",5500 );
	
	CJournalEdit* FirstJEdit = Test->newJournalEdit ( true,Test->getPostByName ( "Bank" ),1000 );
	CJournalEdit* LastJEdit = FirstJEdit;
	CJournalEdit* CurJEdit = Test->newJournalEdit ( false,Test->getPostByName ( "Kapitaal" ),1000 );
	Test->setNextOnJournalEdit ( CurJEdit,FirstJEdit,LastJEdit );
	TDate Date;
	Date.date= "Dit is de datum ";
	Test->bookJournal ( Date,"BA 001/1 Fortis",FirstJEdit );
	Test->bookJournal ( Date,"BA 001/2 Fortis",FirstJEdit );
	Test->bookJournal ( Date,"BA 001/3 Fortis",FirstJEdit );
	Test->bookJournal ( Date,"BA 001/4 Fortis",FirstJEdit );
	SJournal* CurRJournal = Test->getJournalByNumber (0,0);
	do {
		std::cout << CurRJournal->Journal->getId () << std::endl;
		SJournalEdit* JournalEdit = CurRJournal->Journal->getJournalEditByDebetEdit (true);
		do {
			std::cout << JournalEdit->JournalEdit->getValue () << std::endl;
			JournalEdit = JournalEdit->Next;
		} while (  JournalEdit != 0 );
		
		JournalEdit = CurRJournal->Journal->getJournalEditByDebetEdit (false);
		do {
			std::cout << JournalEdit->JournalEdit->getValue () << std::endl;
			JournalEdit = JournalEdit->Next;
		} while (  JournalEdit != 0 );
		CurRJournal = CurRJournal->Next;
	} while ( CurRJournal != 0 );
	delete Test;
}

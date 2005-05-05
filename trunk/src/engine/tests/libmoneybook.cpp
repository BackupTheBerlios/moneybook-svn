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
#include <string>

#include <cppunit/TestSuite.h>
#include <cppunit/TestAssert.h>
#include <cppunit/TestCaller.h>

#include "../../general.h"
#include "../libmoneybook.h"
#include "libmoneybook.h"

LibMoneyBookTest::LibMoneyBookTest () {
	BookKeeping = new CBookKeeping;
	
	BookKeeping->addPost ("Kapitaal",1000,PASSIVE);
	BookKeeping->addPost ("Bank RC Fortis",5500,ACTIVE);
}

LibMoneyBookTest::~LibMoneyBookTest () {
	delete BookKeeping;
}


void LibMoneyBookTest::setUp () {
}

void LibMoneyBookTest::tearDown () {
}

void LibMoneyBookTest::testAddPost () {
	CPost* CurPost = BookKeeping->getPostByName ("Kapitaal");
	CPPUNIT_ASSERT_EQUAL (std::string ("Kapitaal"),CurPost->getName ());
	CPPUNIT_ASSERT_EQUAL (SortPostToString(PASSIVE),SortPostToString(CurPost->getSortPost ()));
	CPPUNIT_ASSERT (CurPost->getId () == 1000);
	
	CurPost = BookKeeping->getPostByName ("Bank RC Fortis");
	CPPUNIT_ASSERT_EQUAL (std::string ("Bank RC Fortis"),CurPost->getName ());
	CPPUNIT_ASSERT_EQUAL (SortPostToString(ACTIVE),SortPostToString(CurPost->getSortPost ()));
	CPPUNIT_ASSERT (CurPost->getId () == 5500);
}

void LibMoneyBookTest::testBookJournalGood () {
	CJournalEdit* FirstJEdit = BookKeeping->newJournalEdit (true,BookKeeping->getPostByName ("Bank RC Fortis"),1000.05);
	CJournalEdit* LastJEdit = FirstJEdit;
	CJournalEdit* CurJEdit = BookKeeping->newJournalEdit (false,BookKeeping->getPostByName ("Kapitaal"),1000.05);
	BookKeeping->setNextOnJournalEdit (CurJEdit,FirstJEdit,LastJEdit);
	CJournalEdit* CurJournalEdit = FirstJEdit;
	CPPUNIT_ASSERT (CurJournalEdit->getValue () == 1000.05);
	CPPUNIT_ASSERT (CurJournalEdit->getDebetEdit () == true);
	CPPUNIT_ASSERT_EQUAL (std::string ("Bank RC Fortis"),CurJournalEdit->getPost ()->getName ());
	
	CurJournalEdit = CurJournalEdit->getNext ();
	CPPUNIT_ASSERT (CurJournalEdit->getValue () == 1000.05);
	CPPUNIT_ASSERT (CurJournalEdit->getDebetEdit () == false);
	CPPUNIT_ASSERT_EQUAL (std::string ("Kapitaal"),CurJournalEdit->getPost () ->getName ());

	TDate Date;
	Date.date= "This is the date";
	try {
		BookKeeping->bookJournal (Date,"BA 001/1 Fortis",FirstJEdit);
	}
	catch (...) {
		// Nothing may be thrown
		CPPUNIT_ASSERT_EQUAL (0,1);
	}
	SJournal* CurJournal = BookKeeping->getJournalByNumberRange (1,1);
	CPPUNIT_ASSERT_EQUAL (std::string ("BA 001/1 Fortis"),CurJournal->Journal->getDocument ());
	CPPUNIT_ASSERT_EQUAL (std::string ("This is the date"),CurJournal->Journal->getDate ().date);
	CPPUNIT_ASSERT (CurJournal->Journal->getId () == 1);
	
	CPPUNIT_ASSERT (CurJournal->Journal->getFirstJournalEdit ()->getNext ()->getPost () == BookKeeping->getPostByName ("Kapitaal") );
}

void LibMoneyBookTest::testBookJournalBad () {
	CJournalEdit* FirstJEdit = BookKeeping->newJournalEdit (true,BookKeeping->getPostByName ("Bank RC Fortis"),1000.05);
	CJournalEdit* LastJEdit = FirstJEdit;
	CJournalEdit* CurJEdit = BookKeeping->newJournalEdit (false,BookKeeping->getPostByName ("Kapitaal"),1000.06);
	BookKeeping->setNextOnJournalEdit (CurJEdit,FirstJEdit,LastJEdit);
	CJournalEdit* CurJournalEdit = FirstJEdit;
	TDate Date;
	Date.date= "This is the date";
	try {
		BookKeeping->bookJournal (Date,"BA 001/1 Fortis",FirstJEdit);
	}
	catch (CException e) {
		// see what is trown is good
		CPPUNIT_ASSERT_EQUAL (e.what,std::string("Not in balance"));
	}
	catch (...) {
		// bad thing is trown
		CPPUNIT_ASSERT_EQUAL (0,1);
	}
	CPPUNIT_ASSERT (BookKeeping->getJournalByNumberRange (0,0) == 0);
}

void LibMoneyBookTest::testSave () {
}

void LibMoneyBookTest::testLoad () {
}

CppUnit::Test* LibMoneyBookTest::suite () {
	CppUnit::TestSuite* suiteOfTests = new CppUnit::TestSuite;

	suiteOfTests->addTest(new CppUnit::TestCaller<LibMoneyBookTest>( 
								"Test Adding Posts", 
								&LibMoneyBookTest::testAddPost));
	suiteOfTests->addTest(new CppUnit::TestCaller<LibMoneyBookTest>( 
								"Test Booking Journals", 
								&LibMoneyBookTest::testBookJournalGood));
	suiteOfTests->addTest(new CppUnit::TestCaller<LibMoneyBookTest>( 
								"Test Booking Journals", 
								&LibMoneyBookTest::testBookJournalBad));
	suiteOfTests->addTest(new CppUnit::TestCaller<LibMoneyBookTest>( 
								"Test Booking Journals", 
								&LibMoneyBookTest::testSave));
	suiteOfTests->addTest(new CppUnit::TestCaller<LibMoneyBookTest>( 
								"Test Booking Journals", 
								&LibMoneyBookTest::testLoad));
	return suiteOfTests; 
}

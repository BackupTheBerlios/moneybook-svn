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

#include "../../config.h"
#include "../../general.h"
#include "../libmoneybook.h"
#include "libmoneybook.h"

void LibMoneyBookTest::setUp () {
	BookKeeping = new CBookKeeping;
	
	BookKeeping->addPost ("Kapitaal",1000,PASSIVE);
	BookKeeping->addPost ("Bank RC Fortis",5500,ACTIVE);

	CJournalEdit* FirstJEdit = BookKeeping->newJournalEdit (true,BookKeeping->getPostByName ("Bank RC Fortis"),100005);
	CJournalEdit* LastJEdit = FirstJEdit;
	CJournalEdit* CurJEdit = BookKeeping->newJournalEdit (false,BookKeeping->getPostByName ("Kapitaal"),100005);
	BookKeeping->setNextOnJournalEdit (CurJEdit,FirstJEdit,LastJEdit);
	CJournalEdit* CurJournalEdit = FirstJEdit;

	TDate Date;
	Date.date= "This is the date";
	BookKeeping->bookJournal (Date,"BA 001/1 Fortis",FirstJEdit);
}

void LibMoneyBookTest::tearDown () {
	delete BookKeeping;
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
	SJournal* CurJournal = BookKeeping->getJournalByNumberRange (1,1);
	CPPUNIT_ASSERT_EQUAL (std::string ("BA 001/1 Fortis"),CurJournal->Journal->getDocument ());
	CPPUNIT_ASSERT_EQUAL (std::string ("This is the date"),CurJournal->Journal->getDate ().date);
	CPPUNIT_ASSERT (CurJournal->Journal->getId () == 1);
	
	CPPUNIT_ASSERT (CurJournal->Journal->getFirstJournalEdit ()->getNext ()->getPost () == BookKeeping->getPostByName ("Kapitaal") );

	CJournalEdit* CurJournalEdit = CurJournal->Journal->getFirstJournalEdit ();

	CPPUNIT_ASSERT (CurJournalEdit->getValue () == 100005);
	CPPUNIT_ASSERT (CurJournalEdit->getDebetEdit () == true);
	CPPUNIT_ASSERT_EQUAL (std::string ("Bank RC Fortis"),CurJournalEdit->getPost ()->getName ());
	
	CurJournalEdit = CurJournalEdit->getNext ();
	CPPUNIT_ASSERT (CurJournalEdit->getValue () == 100005);
	CPPUNIT_ASSERT (CurJournalEdit->getDebetEdit () == false);
	CPPUNIT_ASSERT_EQUAL (std::string ("Kapitaal"),CurJournalEdit->getPost () ->getName ());
}

void LibMoneyBookTest::testBookJournalBad () {
	CJournalEdit* FirstJEdit = BookKeeping->newJournalEdit (true,BookKeeping->getPostByName ("Bank RC Fortis"),100005);
	CJournalEdit* LastJEdit = FirstJEdit;
	CJournalEdit* CurJEdit = BookKeeping->newJournalEdit (false,BookKeeping->getPostByName ("Kapitaal"),100006);
	BookKeeping->setNextOnJournalEdit (CurJEdit,FirstJEdit,LastJEdit);
	CJournalEdit* CurJournalEdit = FirstJEdit;
	TDate Date;
	Date.date= "This is the date";
	try {
		//BookKeeping->bookJournal (Date,"BA 001/1 Fortis",FirstJEdit);
	}
	catch (CException e) {
		// see what is trown is good
		CPPUNIT_ASSERT_EQUAL (e.what,std::string("Not in balance"));
	}
	catch (...) {
		// bad thing is trown
		CPPUNIT_ASSERT_EQUAL (0,1);
	}
	CPPUNIT_ASSERT (BookKeeping->getJournalByNumberRange (2,2) == 0);
}

void LibMoneyBookTest::testSave () {
	try {
		BookKeeping->save ();
	}
	catch (CException e) {
		CPPUNIT_ASSERT_EQUAL (e.what,std::string ("Error, no filename given"));
	}
	catch (...) {
		CPPUNIT_ASSERT_EQUAL (0,1);
	}

	try {
		BookKeeping->save ("/tmp/firstsavetest.xml");
	}
	catch (...) {
		CPPUNIT_ASSERT_EQUAL (0,1);
	}
	CPPUNIT_ASSERT_EQUAL (BookKeeping->getFileName (),std::string ("/tmp/firstsavetest.xml"));
	std::ifstream out1 ("/tmp/firstsavetest.xml");
	std::ifstream in1 ("./src/engine/tests/firstsavetest.xml");
	CPPUNIT_ASSERT (streamCompare(out1,in1));

	try {
		BookKeeping->setFileName ("/tmp/secondsavetest.xml");
		BookKeeping->save ();
	}
	catch (...) {
		CPPUNIT_ASSERT_EQUAL (0,1);
	}
	CPPUNIT_ASSERT_EQUAL (BookKeeping->getFileName (),std::string ("/tmp/secondsavetest.xml"));
	std::ifstream out2 ("/tmp/firstsavetest.xml");
	std::ifstream in2 ("./src/engine/tests/secondsavetest.xml");
	CPPUNIT_ASSERT (streamCompare(out2,in2));
}

void LibMoneyBookTest::testLoad () {
	try { 
		BookKeeping->load ();
	}
	catch (CException e) {
		CPPUNIT_ASSERT_EQUAL (e.what,std::string ("No Filename given"));
	}

	try {
		BookKeeping->setFileName ("filenam");
		BookKeeping->load ("another,errr");
	}
	catch (CException e) {
		CPPUNIT_ASSERT_EQUAL (e.what,std::string ("There is already assigned a filename"));
	}
	BookKeeping->setFileName ("");
	try {
		BookKeeping->load ("modified");
	}
	catch (CException e) {
		CPPUNIT_ASSERT_EQUAL (e.what,std::string ("Already modified"));
	}

	try {
		BookKeeping->load ("./src/engine/tests/firstloadtest.xml",true);
	}
	catch (CException e) {
		CPPUNIT_ASSERT_EQUAL (std::string ("Already modified"),e.what);
	}
	cdebug << "Loaded..." << std::endl;
	delete BookKeeping;
	BookKeeping = new CBookKeeping;
	try { 
		BookKeeping->load ("./src/engine/tests/firstloadtest.xml");
	}
	catch (CException e) {
		std::cout << "Exception occured: " << e.what << std::endl;
		CPPUNIT_ASSERT_EQUAL (0,1);
	}
	
	mint test = 900105;
	short unsigned int number = 10000;
	CPPUNIT_ASSERT_EQUAL (BookKeeping->getPostByName ("Kapitaal")->getSaldo (),test);
	CPPUNIT_ASSERT_EQUAL (number,BookKeeping->getPostByName ("Kapitaal")->getId ());
	CPPUNIT_ASSERT_EQUAL (std::string("PASSIVE"),SortPostToString(BookKeeping->getPostByName ("Kapitaal")->getSortPost ()));

	test = 200030;
	number = 57000;
	CPPUNIT_ASSERT_EQUAL (BookKeeping->getPostByName ("Kas")->getSaldo (),test);
	CPPUNIT_ASSERT_EQUAL (number,BookKeeping->getPostByName ("Kas")->getId ());
	CPPUNIT_ASSERT_EQUAL (std::string("ACTIVE"),SortPostToString(BookKeeping->getPostByName ("Kas")->getSortPost ()));

	test = 700075;
	number = 55000;
	CPPUNIT_ASSERT_EQUAL (BookKeeping->getPostByName ("Bank")->getSaldo (),test);
	CPPUNIT_ASSERT_EQUAL (number,BookKeeping->getPostByName ("Bank")->getId ());
	CPPUNIT_ASSERT_EQUAL (std::string("ACTIVE"),SortPostToString(BookKeeping->getPostByName ("Bank")->getSortPost ()));
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
								"Test Saving", 
								&LibMoneyBookTest::testSave));
	suiteOfTests->addTest(new CppUnit::TestCaller<LibMoneyBookTest>( 
								"Test Loading", 
								&LibMoneyBookTest::testLoad));
	return suiteOfTests; 
}

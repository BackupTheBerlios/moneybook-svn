#include "../libmoneybook.h"
#include "libmoneybook.h"

#include <cppunit/TestSuite.h>
#include <cppunit/TestAssert.h>
#include <cppunit/TestCaller.h>
#include <string>
#include <iostream>

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
	BookKeeping->bookJournal (Date,"BA 001/1 Fortis",FirstJEdit);
	SJournal* CurJournal = BookKeeping->getJournalByNumber (1,1);
	CPPUNIT_ASSERT_EQUAL (std::string ("BA 001/1 Fortis"),CurJournal->Journal->getDocument ());
	CPPUNIT_ASSERT_EQUAL (std::string ("This is the date"),CurJournal->Journal->getDate ().date);
	CPPUNIT_ASSERT (CurJournal->Journal->getId () == 1);
	
	CPPUNIT_ASSERT (CurJournal->Journal->getFirstJournalEdit ()->getNext ()->getPost () == BookKeeping->getPostByName ("Kapitaal") );
}

CppUnit::Test* LibMoneyBookTest::suite () {
	CppUnit::TestSuite* suiteOfTests = new CppUnit::TestSuite;

	suiteOfTests->addTest(new CppUnit::TestCaller<LibMoneyBookTest>( 
								"Test Adding Posts", 
								&LibMoneyBookTest::testAddPost));
	suiteOfTests->addTest(new CppUnit::TestCaller<LibMoneyBookTest>( 
								"Test Booking Journals", 
								&LibMoneyBookTest::testBookJournalGood));
	return suiteOfTests; 
}

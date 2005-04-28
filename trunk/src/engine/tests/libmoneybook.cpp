#include "../libmoneybook.h"
#include "libmoneybook.h"

#include <cppunit/TestSuite.h>
#include <cppunit/TestAssert.h>
#include <cppunit/TestCaller.h>
#include <iostream>


void LibMoneyBookTest::setUp () {
	BookKeeping = new CBookKeeping;
}

void LibMoneyBookTest::tearDown () {
	delete BookKeeping;
}

void LibMoneyBookTest::testAddPost () {
	BookKeeping->addPost ("Kapitaal",1000,PASSIVE);
	BookKeeping->addPost ("Bank RC Fortis",5500,ACTIVE);
	
	CPost* CurPost = BookKeeping->getFirstPost ();
	CPPUNIT_ASSERT_EQUAL (std::string ("Kapitaal"),CurPost->getName ());
	CPPUNIT_ASSERT_EQUAL (SortPostToString(PASSIVE),SortPostToString(CurPost->getSortPost ()));
	CPPUNIT_ASSERT_DOUBLES_EQUAL (1000,CurPost->getId (),1); // one precise
	
	CurPost = CurPost->getNext ();
	CPPUNIT_ASSERT_EQUAL (std::string ("Bank RC Fortis"),CurPost->getName ());
	CPPUNIT_ASSERT_EQUAL (SortPostToString(ACTIVE),SortPostToString(CurPost->getSortPost ()));
	CPPUNIT_ASSERT_DOUBLES_EQUAL (5500,CurPost->getId (),1); // one precise
}

CppUnit::Test* LibMoneyBookTest::suite () {
	CppUnit::TestSuite* suiteOfTests = new CppUnit::TestSuite;

	suiteOfTests->addTest(new CppUnit::TestCaller<LibMoneyBookTest>( 
								"Test Adding Posts", 
								&LibMoneyBookTest::testAddPost));
	return suiteOfTests; 
}

#include "../libmoneybook.h"
#include "libmoneybook.h"

#include <cppunit/TestSuite.h>
#include <cppunit/TestAssert.h>
#include <cppunit/TestCaller.h>


void LibMoneyBookTest::setUp () {
	CBookKeeping* BookKeeping = new CBookKeeping;
}

void LibMoneyBookTest::tearDown () {
	delete BookKeeping;
}

void LibMoneyBookTest::testAddPost () {
	BookKeeping->addPost ("Kapitaal",1000,PASSIVE);
	BookKeeping->addPost ("Bank RC Fortis",5500,ACTIVE);
}

CppUnit::Test* LibMoneyBookTest::suite () {
	CppUnit::TestSuite* suiteOfTests = new CppUnit::TestSuite;
	
	suiteOfTests->addTest(new CppUnit::TestCaller<LibMoneyBookTest>( 
								"Test Adding Posts", 
								&LibMoneyBookTest::testAddPost));
	return suiteOfTests; 
}

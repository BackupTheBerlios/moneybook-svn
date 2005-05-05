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

#ifndef TEST_LIBMONEYBOOK_H
#define TEST_LIBMONEYBOOK_H

#include <cppunit/TestFixture.h>
#include <cppunit/Test.h>

#include "../libmoneybook.h"

class LibMoneyBookTest : public CppUnit::TestFixture
{
	private:		
		//CBookKeeping* BookKeeping;
	public:

		LibMoneyBookTest ();
		~LibMoneyBookTest ();
CBookKeeping* BookKeeping;
		void setUp ();
		void tearDown ();

		void testAddPost ();
		void testBookJournalGood ();
		void testBookJournalBad ();
		void testLoad ();
		void testSave ();

		static CppUnit::Test* suite ();
};

#endif /* TEST_LIBMONEYBOOK_H */

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
#include "../general.h"
#include "libmoneybook.h"

/*!
	Normal constructor of CJournalEdit
*/
CJournalEdit::CJournalEdit (bool JDebetEdit,CPost* JPost,mint JValue) {
	DebetEdit = JDebetEdit;
	Post = JPost;
	Value = JValue;
	Next = 0;
} /* CJournalEdit::CJournalEdit (bool JDebetEdit,CPost* JPost,mint JValue) */

/*!
	Copy's an CJournalEdit except the Next, put that one at 0
*/
CJournalEdit::CJournalEdit (CJournalEdit* JournalEdit) {
	DebetEdit = JournalEdit->getDebetEdit ();
	Post = JournalEdit->getPost ();
	Value = JournalEdit->getValue ();
	Next = 0;
} /* CJournalEdit::CJournalEdit (CJournalEdit* JournalEdit) */

/*!
	Destructor of CJournalEdit
*/
CJournalEdit::~CJournalEdit () {
	cdebug << "Destructor CJournalEdit" << std::endl;
} /* CjournalEdit::~CJournalEdit () */

/*!
	returns the next in the CJournalEditList
*/
CJournalEdit* CJournalEdit::getNext () {
	return Next;
} /* CJournalEdit* CJournalEdit::getNext () */

/*!
	set the next in the CJournalEdit List
*/
void CJournalEdit::setNext (CJournalEdit* JNext) {
	Next = JNext;
} /* void CJournalEdit::setNext (CJournalEdit* JNext) */

/*!
	return of CJournalEdit, is on the debetside 
*/
bool CJournalEdit::getDebetEdit () {
	return DebetEdit;
} /* bool CJournalEdit::getDebetEdit () */

/*!
	returns the pointer to the post of this CJournalEdit
*/
CPost* CJournalEdit::getPost () {
	return Post;
} /* CPost* CJournalEdit::getPost () */

/*!
	returns the value of this CJournalEdit
*/
mint CJournalEdit::getValue () {
	return Value;
} /* mint CJournalEdit::getValue () */

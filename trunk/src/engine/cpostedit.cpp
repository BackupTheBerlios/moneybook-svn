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
	Constructor of CPostEdit
*/
CPostEdit::CPostEdit (bool PDebetEdit,long double PValue,unsigned int BookNumber) {
	DebetEdit = PDebetEdit;
	Value = PValue;
	Number = BookNumber;
	Next = 0;
} /* CPostEdit::CPostEdit (bool PDebetEdit,long double PValue,unsigned int BookNumber)*/

/*!
	Destructor of CPostEdit
*/
CPostEdit::~CPostEdit () {
	cdebug << "Destructor CPostEdit " << Number << std::endl;
} /* CpostEdit::~CPostEdit ()  */

/*!
		returns the next in the list
*/
CPostEdit* CPostEdit::getNext () {
	return Next;
} /* CPostEdit* CPostEdit::getNext () */

/*!
	set the Next in the list
*/
void CPostEdit::setNext (CPostEdit* PNext) {
	Next = PNext;
} /* void CPostEdit::setNext (CPostEdit* PNext) */

/*!
	returns the Value of the PostEdit
*/
long double CPostEdit::getValue () {
	return Value;
} /* long double CPostEdit::getValue */

/*!
	returns true if it is an Edit on the DebetSide
*/
bool CPostEdit::getDebetEdit () {
	return DebetEdit;
} /* bool CPostEdit::getDebetEdit () */

/*!
	returns the number of the PostEdit ( the same number on the correspondending Journal )
*/
unsigned int CPostEdit::getNumber () {
	return Number;
} /* unsigned int CPostEdit::getNumber ()  */


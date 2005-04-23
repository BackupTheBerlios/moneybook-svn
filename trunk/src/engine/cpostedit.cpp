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

#include "libmoneybook.h"

#include <iostream>

CPostEdit::CPostEdit ( bool PDebetEdit,long double PValue,unsigned int BookNumber ) {
	DebetEdit = PDebetEdit;
	Value = PValue;
	Number = BookNumber;
} /* CPostEdit::CPostEdit ( bool PDebetEdit,long double PValue,unsigned int BookNumber )*/

CPostEdit::~CPostEdit () {
	std::cout << "Destructor CPostEdit " << Number << std::endl;
} /* CpostEdit::~CPostEdit ()  */

long double CPostEdit::getValue () {
	return Value;
} /* long double CPostEdit::getValue */

CPostEdit* CPostEdit::getNext () {
	return Next;
} /* CPostEdit* CPostEdit::getNext () */

bool CPostEdit::getDebetEdit () {
	return DebetEdit;
} /* bool CPostEdit::getDebetEdit () */

void CPostEdit::setNext ( CPostEdit* PNext ) {
	Next = PNext;
} /* void CPostEdit::setNext ( CPostEdit* PNext ) */

unsigned int CPostEdit::getNumber () {
	return Number;
} /* unsigned int CPostEdit::getNumber ()  */


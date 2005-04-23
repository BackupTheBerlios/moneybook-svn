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

#include <string>
#include <iostream>

CPost::CPost ( std::string PName,unsigned short PId,SSortPost PSortPost ) {
	Next = 0;
	Id = PId;
	Name = PName;
	SortPost = PSortPost;
	FirstPostEdit = 0;
	LastPostEdit = 0;
} /* CPost::CPost ( std::string PName, unsigned short PId,SSortPost PSortPos ) */ 

CPost::~CPost () {
	std::cout << "Destructor CPost" << std::endl;
	CPostEdit* CurPostEdit = FirstPostEdit;
	do {
		FirstPostEdit = CurPostEdit->getNext ();
		delete CurPostEdit;
		CurPostEdit = FirstPostEdit;
	} while ( CurPostEdit != 0 );
} /* CPost::~CPost () */

CPost* CPost::getNext () {
	return Next;
} /* CPost* CPost::getNext () */

std::string CPost::getName () {
	return Name;
} /* std::string CPost::getName () */

unsigned short CPost::getId () {
	return Id;
} /* unsigned short CPost::getNumber */

void CPost::setNext ( CPost* PNext ) {
	Next = PNext;
} /* void CPost::setNext ( CPost* PNext ) */

CPostEdit* CPost::getFirstPostEdit () {
	return FirstPostEdit;
} /* CpostEdit* CPost::getFirstPostEdit () */

CPostEdit* CPost::getLastPostEdit () {
	return LastPostEdit;
} /* CPostEdit* CPost::getLastPostEdit () */

void CPost::setFirstPostEdit ( CPostEdit* PFirstEdit ) {
	FirstPostEdit = PFirstEdit;
} /* void CPost::setFirstPostEdit ( CPostEdit* PFirstEdit ) */

void CPost::setLastPostEdit ( CPostEdit* PLastEdit ) {
	LastPostEdit = PLastEdit;
} /* void CPost::setLastPostEdit ( CPostEdit* PLastEdit ) */

long double CPost::getSaldo () {
	CPostEdit* CurPostEdit = FirstPostEdit;
	long double Saldo = 0;
	do {
		if ( CurPostEdit->getDebetEdit () == true ) {
			Saldo += CurPostEdit->getValue ();
		} else {
			Saldo -= CurPostEdit->getValue ();
		}
		CurPostEdit = CurPostEdit->getNext ();
	} while ( CurPostEdit != 0 );

	if  ( ( SortPost == PASSIVE ) or ( SortPost == WINST ) ) {
		Saldo *= -1;
	}

	return Saldo;
} /* unsigned long CPost::getSaldo () */

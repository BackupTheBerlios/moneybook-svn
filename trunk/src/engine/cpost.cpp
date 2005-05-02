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
#include <string>

#include "../general.h"
#include "libmoneybook.h"

/*!
	Constructor of CPost
*/
CPost::CPost (std::string PName,unsigned short PId,SSortPost PSortPost) {
	Next = 0;
	Id = PId;
	Name = PName;
	SortPost = PSortPost;
	FirstPostEdit = 0;
	LastPostEdit = 0;
} /* CPost::CPost ( std::string PName, unsigned short PId,SSortPost PSortPos ) */ 

/*!
	Destructor of CPost
*/
CPost::~CPost () {
	cdebug << "Destructor CPost" << std::endl;
	CPostEdit* CurPostEdit = FirstPostEdit;
	while (CurPostEdit != 0) {
		FirstPostEdit = CurPostEdit->getNext ();
		delete CurPostEdit;
		CurPostEdit = FirstPostEdit;
	}
} /* CPost::~CPost () */

/*!
	returns the next in the list
*/
CPost* CPost::getNext () {
	return Next;
} /* CPost* CPost::getNext () */

/*!
	set the Next in the list
*/
void CPost::setNext (CPost* PNext) {
	Next = PNext;
} /* void CPost::setNext (CPost* PNext) */

/*!
	returns Name of the Post
*/
std::string CPost::getName () {
	return Name;
} /* std::string CPost::getName () */

/*!
	returns the id ( between 0 and 65535 )
*/
unsigned short CPost::getId () {
	return Id;
} /* unsigned short CPost::getNumber */

/*!
	get the first PostEdit
*/
CPostEdit* CPost::getFirstPostEdit () {
	return FirstPostEdit;
} /* CpostEdit* CPost::getFirstPostEdit () */

/*!
	set the first PostEdit
*/
void CPost::setFirstPostEdit (CPostEdit* PFirstEdit) {
	FirstPostEdit = PFirstEdit;
} /* void CPost::setFirstPostEdit (CPostEdit* PFirstEdit) */

/*!
	get the last PostEdit
*/
CPostEdit* CPost::getLastPostEdit () {
	return LastPostEdit;
} /* CPostEdit* CPost::getLastPostEdit () */

/*! set the last PostEdit
*/
void CPost::setLastPostEdit (CPostEdit* PLastEdit) {
	LastPostEdit = PLastEdit;
} /* void CPost::setLastPostEdit (CPostEdit* PLastEdit) */

/*!
	get the Saldo of the Post
*/
long double CPost::getSaldo () {
	CPostEdit* CurPostEdit = FirstPostEdit;
	long double Saldo = 0;
	while (CurPostEdit != 0)  {
		if ( CurPostEdit->getDebetEdit () == true ) {
			Saldo += CurPostEdit->getValue ();
		} else {
			Saldo -= CurPostEdit->getValue ();
		}
		CurPostEdit = CurPostEdit->getNext ();
	}

	if  ((SortPost == PASSIVE) || (SortPost == TURNOVER)) {
		Saldo *= -1;
	}

	return Saldo;
} /* unsigned long CPost::getSaldo () */

/*!
	returns the Sort of Post
*/
SSortPost CPost::getSortPost () {
	return SortPost;
} /*SSortPost CPost::getSortPost ()*/

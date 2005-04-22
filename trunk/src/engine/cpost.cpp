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

CPost::CPost ( std::string PName,unsigned int PId ) {
	Next = 0;
	Id = PId;
	Name = PName;
} /* CPost::CPost ( std::string PName, unsigned int PId ) */ 

CPost* CPost::getNext () {
	return Next;
} /* CPost* CPost::getNext () */

std::string CPost::getName () {
	return Name;
} /* std::string CPost::getName () */

unsigned int CPost::getId () {
	return Id;
} /* int CPost::getNumber */

void CPost::setNext ( CPost* PNext ) {
	Next = PNext;
} /* void CPost::setNext ( CPost* PNext ) */

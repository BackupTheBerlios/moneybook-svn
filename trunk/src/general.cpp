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

#include <iostream>
#include <cstring>

#include "general.h"

/*!
	returns of a number is in a defined range, if so return true
*/
bool isInIntRange (int Minimum,int Maximum,int Number) {
	bool BMinimum,BMaximum;
	BMinimum = false;
	BMaximum = false;
	
	if (Minimum == 0) {
		BMinimum = true;
	} else {
		if (Number >= Minimum) {
			BMinimum = true;
		}
	}
	
	if (Maximum == 0) {
		BMaximum = true;
	} else {
		if (Number <= Maximum) {
			BMaximum = true;
		}
	}
	
	if ((BMinimum == true) && (BMaximum == true)) {
		return true;
	} else {
		return false;
	}
} /* bool isInIntRange (int Minimum,int Maximum,int Number) */

CException::CException (std::string ewhat) throw () {
	what = ewhat;
} /* CException::CException (std::string ewhat) throw () */

CException::~CException () {
} /* CException::~CException ()  */

std::ofstream cdebug  ("/dev/null");

void debug (bool doDebug) {
	if (doDebug == true) {
		// Open the stream to the console
		cdebug.flush ();
		cdebug.close ();
		cdebug.open ("/dev/tty");
	} else {
		// Close it
		cdebug.flush ();
		cdebug.close ();
		cdebug.open ("/dev/null");
	}
}

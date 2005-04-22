#!/bin/sh

# MoneyBook, a double bookkeeping program
# Copyright (C) 2005  Nathan Samson
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#

if [ $1 = "--clean" ]
then
	echo "removing old shit..."
	rm -R aclocal.m4 autom4te.cache config.* configure Makefile Makefile.in src/Makefile src/Makefile.in src/engine/Makefile.in src/engine/Makefile src/interface/Makefile.in src/interface/Makefile stamp-h1
else
	echo "running aclocal..."
	aclocal
	echo "running autoheader..."
	autoheader
	echo "running autoconf..."
	autoconf
	echo "running automake..."
	automake
fi;

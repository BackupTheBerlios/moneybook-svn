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
	echo "make clean..."
	make clean
	echo "make maintainer-clean..."
	make maintainer-clean
	echo "removing old shit..."
	rm -R aclocal.m4 config.h* autoscan.log configure.scan configure Makefile.in src/Makefile.in src/engine/Makefile.in src/interface/Makefile.in src/interface/Makefile 
else
	echo "Running aclocal... "
	aclocal -I .
	echo "Running autoheader... "
	autoheader
	echo "Runnig libtoolize... "
	libtoolize --automake -c -f
	echo "Running autoconf... "
	autoconf
	echo "Runing automake... "
	automake -c -f
fi;

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


AUTOMAKE_OPTIONS = gnu
INCLUDES = $(PACKAGE_CFLAGS) $(CFLAGS)
bin_PROGRAMS = moneybook
SUBDIRS = engine
moneybook_SOURCES =  moneybook.cpp general.cpp
moneybook_LDADD = $(top_builddir)/src/engine/libmoneybook.a $(PACKAGE_LIBS) $(LIBS) -lxerces-c

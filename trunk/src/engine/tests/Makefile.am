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

check_PROGRAMS = testengine
testengine_SOURCES = main.cpp libmoneybook.cpp ../../general.cpp
testengine_CXXFLAGS = $(CPPUNIT_CFLAGS)
testengine_LDFLAGS = $(CPPUNIT_LIBS) -ldl
testengine_LDADD = $(top_builddir)/src/engine/libmoneybook.a -lxerces-c
testengine_DEPENDENCIES = ../libmoneybook.a

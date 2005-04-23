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

#ifndef BOOKKEEPING_H
#define BOOKKEEPING_H

#include <string>

struct TDate {
	std::string date;
}; /* struct TDate */

class CPostEdit {
	private:
		long double Value;
		CPostEdit* Next;
		bool DebetEdit;
	public:
		CPostEdit ( bool PDebetEdit, long double PValue );
		long double getValue ();
		CPostEdit* getNext ();
		bool getDebetEdit ();
		void setNext ( CPostEdit* PNext );
}; /* class CPostEdit */

class CPost {
	private:
		CPost* Next;
		CPostEdit* FirstPostEdit;
		unsigned short Id;
		std::string Name;
	public:
		CPost ( std::string PName,unsigned short PId );
		CPost* getNext ();
		std::string getName ();
		unsigned short getId ();
		void setNext ( CPost* PNext );
}; /* class CPost */

class CJournalEdit {
	private:
		long double Value;
		CJournalEdit* Next;
		CPost* Post;
		bool DebetEdit;
	public:
		CJournalEdit ( bool JDebetEdit, CPost* JPost, long double JValue );
		~CJournalEdit ();
		bool getDebetEdit ();
		CPost* getPost ();
		long double getValue ();
		CJournalEdit* getNext ();
		void setNext ( CJournalEdit* JNext );
}; /* class CJournalEdit */

struct SJournalEdit {
	CJournalEdit* JournalEdit;
	SJournalEdit* Next;
}; /* struct SJournalEdit */

class CJournal {
	private:
		CJournal* Next;
		CJournalEdit* FirstJournalEdit;
		std::string Document;
		unsigned int Id;
		TDate Date;
	public:
		CJournal ( TDate JDate,std::string JDocument,unsigned int JNumber,CJournalEdit* JFirstJournalEdit );
		~CJournal ();
		void setNext ( CJournal* JNext );
		CJournal* getNext ();
		unsigned int getId ();
		CJournalEdit* getFirstJournalEdit ();
		TDate getDate ();
		std::string getDocument ();
		SJournalEdit* getJournalEditByDebetEdit ( bool DebetEdit );
}; /* class CJournal */

struct SJournal {
	CJournal* Journal;
	SJournal* Next;
}; /* struct SJournal */

class CBookKeeping {
	private:
		CPost* LastPost;
		CPost* FirstPost;
		CJournal* FirstJournal;
		CJournal* LastJournal;
		bool searchByNumber ( int Minimum,int Maximum,int Number );
	public:
		//CBalance* Balance;
		//CProveSaldiBalance* ProveSaldiBalance;
		CBookKeeping ();
		~CBookKeeping (); 
		SJournal* getJournalByNumber ( int Minimum,int Maximum );
		bool bookJournal ( TDate JDate,std::string Document,CJournalEdit* JFirstJournalEdit );
		bool addPost ( std::string name,unsigned short id );
		CJournalEdit* newJournalEdit ( bool DebetEdit,CPost* Post,long double Value );
		bool setNextOnJournalEdit ( CJournalEdit* CurJEdit,CJournalEdit* FirstJEdit,CJournalEdit* LastJEdit );
		CPost* getPostByName ( std::string Name );
}; /* class CBookKeeping */

#endif /* BOOKKEEPING_H  */

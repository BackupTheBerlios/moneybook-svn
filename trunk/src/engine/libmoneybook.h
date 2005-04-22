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
		float Value;
		CPostEdit* Next;
		bool DebetEdit;
	public:
		CPostEdit ( bool PDebetEdit, float PValue );
		float getValue ();
		CPostEdit* getNext ();
		bool getDebetEdit ();
		void setNext ( CPostEdit* PNext );
}; /* class CPostEdit */

class CPost {
	private:
		CPost* Next;
		CPostEdit* FirstPostEdit;
		unsigned int Id;
		std::string Name;
	public:
		CPost ( std::string PName,unsigned int PId );
		CPost* getNext ();
		std::string getName ();
		unsigned int getId ();
		void setNext ( CPost* PNext );
}; /* class CPost */

class CJournalEdit {
	private:
		float Value;
		CJournalEdit* Next;
		CPost* Post;
		bool DebetEdit;
	public:
		CJournalEdit ( bool JDebetEdit, CPost* JPost, float JValue );
		bool getDebetEdit ();
		CPost* getPost ();
		float getValue ();
		CJournalEdit* getNext ();
		void setNext ( CJournalEdit* JNext );
}; /* class CJournalEdit */

class CJournal {
	private:
		CJournal* Next;
		CJournalEdit* FirstJournalEdit;
		std::string Document;
		unsigned int Id;
		TDate Date;
	public:
		CJournal ( TDate JDate,std::string JDocument,unsigned int JNumber,CJournalEdit* JFirstJournalEdit );
		void setNext ( CJournal* JNext );
		CJournal* getNext ();
		unsigned int getId ();
		CJournalEdit* getFirstJournalEdit ();
		TDate getDate ();
		std::string getDocument ();
}; /* class CJournal */

struct SJournal {
	CJournal* Journal;
	SJournal* Next;
}; /* struct SJournal */

class CBookKeeping {
	private:
		bool searchByNumber ( int Minimum,int Maximum,int Number );
	public:
		//CBalance* Balance;
		//CProveSaldiBalance* ProveSaldiBalance;
		CPost* LastPost;
		CPost* FirstPost;
		CJournal* FirstJournal;
		CJournal* LastJournal;
		CBookKeeping ();
		~CBookKeeping (); 
		SJournal* getJournalByNumber ( int Minimum,int Maximum );
		bool bookJournal ( TDate JDate,std::string Document,CJournalEdit* JFirstJournalEdit );
		bool addPost ( std::string name,unsigned int id );
		CJournalEdit* newJournalEdit ( bool DebetEdit,CPost* Post,float Value );
		bool setNextOnJournalEdit ( CJournalEdit* CurJEdit,CJournalEdit* FirstJEdit,CJournalEdit* LastJEdit );
		CPost* getPostByName ( std::string Name );
}; /* class CBookKeeping */

#endif /* BOOKKEEPING_H  */

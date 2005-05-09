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

#include <xercesc/dom/DOMAttr.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMError.hpp>
#include <xercesc/dom/DOMException.hpp>
#include <xercesc/dom/DOMNamedNodeMap.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/util/OutOfMemoryException.hpp>

XERCES_CPP_NAMESPACE_USE;

// this is an int, but the 2 last digits represents the precision after the comma
// floats are not precise enough
typedef long int mint;

/*!
	Date, can store dates ( in all types and formats )
*/
struct TDate {
	std::string date;
}; /* struct TDate */

/*!
	SSortPost, stores with types of posts you have
*/
enum SSortPost { ACTIVE,PASSIVE,COST,TURNOVER };
std::string SortPostToString ( SSortPost SortPost );
SSortPost StringToSortPost ( std::string SortPost );

/*!
	CPostEdit, Dynamic list, for holding all PostEdits
*/
class CPostEdit {
	private:
		mint Value;
		bool DebetEdit;
		unsigned int Number;

		CPostEdit* Next;
	public:
		CPostEdit (bool PDebetEdit,mint PValue,unsigned int BookNumber);
		~CPostEdit ();
		CPostEdit* getNext ();
		void setNext (CPostEdit* PNext);
		mint getValue ();
		bool getDebetEdit ();
		unsigned int getNumber ();
}; /* class CPostEdit */

/*!
	CPost, Dynamic list, for holding all Posts
*/
class CPost {
	private:
		CPostEdit* FirstPostEdit;
		CPostEdit* LastPostEdit;

		unsigned short Id;
		std::string Name;
		SSortPost SortPost;

		CPost* Next;
	public:
		CPost (std::string PName,unsigned short PId,SSortPost PSortPost);
		CPost (CPost* Post);
		~CPost ();
		CPost* getNext ();
		void setNext (CPost* PNext);
		std::string getName ();
		unsigned short getId ();
		CPostEdit* getFirstPostEdit ();
		void setFirstPostEdit (CPostEdit* PFirstEdit);
		CPostEdit* getLastPostEdit ();
		void setLastPostEdit (CPostEdit* PLastEdit);
		mint getSaldo ();
		SSortPost getSortPost ();
}; /* class CPost */

/*!
	CJournalEdit, Dynamic list, for holding all CJournalEdit
*/
class CJournalEdit {
	private:
		mint Value;
		CPost* Post;
		bool DebetEdit;

		CJournalEdit* Next;
	public:
		CJournalEdit (bool JDebetEdit, CPost* JPost,mint JValue);
		CJournalEdit (CJournalEdit* JournalEdit);
		~CJournalEdit ();
		CJournalEdit* getNext ();
		void setNext (CJournalEdit* JNext);
		bool getDebetEdit ();
		CPost* getPost ();
		mint getValue ();
}; /* class CJournalEdit */

/*!
	CJournal, dynamic list, keeps a Journal
*/
class CJournal {
	private:
		CJournalEdit* FirstJournalEdit;
		std::string Document;
		unsigned int Id;
		TDate Date;

		CJournal* Next;
	public:
		CJournal (TDate JDate,std::string JDocument,unsigned int JNumber,CJournalEdit* JFirstJournalEdit);
		CJournal (CJournal* Journal);
		~CJournal ();
		CJournal* getNext ();
		void setNext (CJournal* JNext);
		unsigned int getId ();
		CJournalEdit* getFirstJournalEdit ();
		TDate getDate ();
		std::string getDocument ();
		CJournalEdit* getJournalEditByDebetEdit (bool DebetEdit);
}; /* class CJournal */

/*!
	Main API, most functionality is in this Class
*/
class CBookKeeping {
	private:
		CPost* LastPost;
		CPost* FirstPost;
		CJournal* FirstJournal;
		CJournal* LastJournal;
		std::string FileName;

		void loadFromParser (DOMNode* n);
	public:
		CBookKeeping ();
		~CBookKeeping (); 
		CJournal* getJournalByNumberRange (int Minimum,int Maximum);
		void bookJournal (TDate JDate,std::string Document,CJournalEdit* JFirstJournalEdit);
		void addPost (std::string name,unsigned short id,SSortPost SortPost);
		CJournalEdit* newJournalEdit (bool DebetEdit,CPost* Post,mint Value);
		void setNextOnJournalEdit (CJournalEdit* CurJEdit,CJournalEdit* FirstJEdit,CJournalEdit* LastJEdit);
		CPost* getPostByName (std::string Name);
		CPost* getFirstPost ();
		CPost* getLastPost ();
		std::string getFileName ();
		void setFileName (std::string sFileName);
		void save (std::string sFileName = "");
		bool load (std::string LFileName = "",bool override = false);
		CPost* getPostById (int Minimum,int Maximum);
		
}; /* class CBookKeeping */

#endif /* BOOKKEEPING_H  */

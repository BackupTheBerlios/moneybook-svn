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
#include <cassert>
#include <fstream>
#include <string>

#include <xercesc/dom/DOMAttr.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMError.hpp>
#include <xercesc/dom/DOMException.hpp>
#include <xercesc/dom/DOMNamedNodeMap.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/util/OutOfMemoryException.hpp>

#include "../general.h"
#include "libmoneybook.h"

XERCES_CPP_NAMESPACE_USE;

std::string SortPostToString (SSortPost SortPost) {
	switch ( SortPost ) {
		case ACTIVE: return "ACTIVE";
			break;
		case PASSIVE: return "PASSIVE";
			break;
		case COST: return "COST";
			break;
		case TURNOVER: return "TURNOVER";
			break;
		default: throw CException ("Not a valid SPost");
	}
} /* std::string SortPostToString (SSortPost SortPost)  */

SSortPost StringToSortPost (std::string SortPost) {
	if (SortPost == "ACTIVE") {
		return ACTIVE;
	} else if (SortPost == "PASSIVE") {
		return PASSIVE;
	} else if (SortPost == "COST") {
		return COST;
	} else if (SortPost == "TURNOVER") {
		return TURNOVER;
	} else {
		throw CException ("Not a valid SPost");
	}
} /* SSortPost StringToSortPost (std::string SortPost)  */

std::string getAttributeByName (DOMNode* node, std::string attrName) {
	cdebug << "getAttr " << attrName << std::endl;
	assert (node->getNodeType () == DOMNode::ELEMENT_NODE);
	
	std::string value = "";
	
	if (node->hasAttributes()) {
		DOMNamedNodeMap *pAttributes = node->getAttributes ();
		
		for (unsigned int i = 0; i < pAttributes->getLength (); i++) {
			DOMAttr* pAttributeNode = (DOMAttr*) pAttributes->item(i);
			char* name = XMLString::transcode(pAttributeNode->getName());
			if (name == attrName) {
				char* tmpValue = XMLString::transcode(pAttributeNode->getValue());
				value = tmpValue;
				XMLString::release(&tmpValue);
			}
			XMLString::release(&name);
		}
	} else {
		cdebug << "Error in file to parse" << std::endl;
		throw ("Error in file to parse attributes");
	}
	cdebug << value << std::endl;
	return value;
} /* std::string getAttributeByName (DOMNode* node, std::string attrName) */

DOMNode* getTagByName (DOMNode* node, std::string tagName) {
	assert (node->getNodeType () == DOMNode::ELEMENT_NODE);
	
	DOMNode* tag = 0;
	DOMNode* CurNode = node->getFirstChild ();
	while (CurNode != 0) {
		if (std::string (XMLString::transcode (CurNode->getNodeName())) == tagName) {
			cdebug << "Found..." << XMLString::transcode (CurNode->getNodeName()) << std::endl;
			return CurNode;
		}
		CurNode = CurNode->getNextSibling ();
	}
	throw ("Not found");
} /* DOMNode* getTagByName (DOMNode* node, std::string tagName) */

/*!
	Constructor CBookKeeping
*/
CBookKeeping::CBookKeeping () {
	FirstPost = 0;
	LastPost = 0;
	
	FirstJournal = 0;
	LastJournal = 0;
} /* Bookkeeping::BookKeeping () */

/*!
	Destructor CBookKeeping
*/
CBookKeeping::~CBookKeeping () {
	cdebug << "Destructor CBookKeeping" << std::endl;
	CJournal* CurJournal = FirstJournal;
	while (CurJournal != 0) {
		FirstJournal = CurJournal->getNext ();
		delete CurJournal;
		CurJournal = FirstJournal;
	}

	CPost* CurPost = FirstPost;
	while (CurPost != 0) {
		FirstPost = CurPost->getNext ();
		delete CurPost;
		CurPost = FirstPost;
	}
} /* CBookKeeping::~CBookKeeping ()  */

/*!
	returns all Journals who are in a range ( 0 is "I don't care" )
*/
SJournal* CBookKeeping::getJournalByNumberRange (int Minimum,int Maximum) {
	CJournal* CurJournal = FirstJournal;
	SJournal* FirstRJournal = 0;
	SJournal* LastRJournal = 0;
	
	while (CurJournal != 0) {
		if (isInIntRange (Minimum,Maximum,CurJournal->getId ())) {
			SJournal* CurRJournal = new SJournal;
			if (FirstRJournal == 0) {
				FirstRJournal = CurRJournal;
				LastRJournal = FirstRJournal;
			} else {
				LastRJournal->Next = CurRJournal;
			}
			CurRJournal->Journal = CurJournal;
			CurRJournal->Next = 0;
			LastRJournal = CurRJournal;
		}
		CurJournal = CurJournal->getNext ();
	}
	return FirstRJournal;
} /* SJournal* CBookKeeping::getJournalByNumberRange (int Minimum,int Maximum)  */

/*!
	add a post in the dynamic list
*/
void CBookKeeping::addPost (std::string name,unsigned short id,SSortPost SortPost) {
	CPost* CurPost  = new CPost (name,id,SortPost);
	if ((getPostById (id,id) == 0) && (getPostByName(name) == 0)) {
		cdebug << "add posts" << std::endl;
		if (FirstPost == 0) {
			FirstPost = CurPost;
		} else {
			LastPost->setNext (CurPost);
		}
		LastPost = CurPost;
	} else {
		cdebug << "Name and/or id already used in another post" << std::endl;
		throw CException ("Name and/or id already used in another post");
	}
} /* void CBookKeeping::addPost (std::string name,unsigned short id,SSortPost SortPost) */

/*!
	returns a new CJournalEdit*
*/
CJournalEdit* CBookKeeping::newJournalEdit (bool DebetEdit,CPost* Post,long double Value) {
	return new CJournalEdit (DebetEdit,Post,Value);;
} /* CJournalEdit* CBookKeeping::newJournalEdit (bool DebetEdit,CPost* Post,long double Value) */

/*!
	!!!I think i'm not going to use this anymore!!!
	set the next on a given JournalEdit
*/
void CBookKeeping::setNextOnJournalEdit (CJournalEdit* CurJEdit,CJournalEdit* FirstJEdit,CJournalEdit* LastJEdit) {
	if (FirstJEdit == 0)  {
		FirstJEdit = CurJEdit;
	} else {
		LastJEdit->setNext (CurJEdit);
	}
	LastJEdit = CurJEdit;
} /* void CBookKeeping::setNextOnJournalEdit (CJournalEdit* CurJEdit,CJournalEdit* FirstJEdit,CJournalEdit* LastJEdit) */

/*!
	returns a post whose name matches Name
*/
CPost* CBookKeeping::getPostByName (std::string Name) {
	CPost* CurPost = FirstPost;
	cdebug << "Search Post By: " << Name << std::endl;
	while (CurPost != 0) {
		cdebug << CurPost << std::endl;
		if (CurPost->getName () == Name) {
			cdebug << CurPost->getName () << CurPost<< std::endl;
			return CurPost;
		}
		CurPost = CurPost->getNext();
	}
	return 0;
} /* CPost* CBookKeeping::getPostByName (std::string Name) */

/*!
	get the FirstPost
*/
CPost* CBookKeeping::getFirstPost () {
	return FirstPost;
} /* CPost* CBookKeeping::getFirstPost ()  */

/*!
	get the last post
*/
CPost* CBookKeeping::getLastPost () {
	return LastPost;
} /* CPost* CBookKeeping::getLastPost ()  */

/*!
	book a journal, and book with that information also the corresponding posts
*/
void CBookKeeping::bookJournal (TDate JDate,std::string Document,CJournalEdit* FirstJournalEdit) {
	cdebug << "Check balance" << std::endl;
	CJournalEdit* CurJournalEdit = FirstJournalEdit;
	long double balance = 0;
	while (CurJournalEdit != 0) {
		if (CurJournalEdit->getDebetEdit () == true) {
			balance += CurJournalEdit->getValue ();
		} else {
			balance -= CurJournalEdit->getValue ();
		}
		CurJournalEdit = CurJournalEdit->getNext ();
	}
	cdebug << "Balance: " << balance << std::endl;

	if (balance == 0) {
		// Book it in the journals
		CJournal* CurJournal; 
		if ( FirstJournal == 0 ) {
			CurJournal = new CJournal (JDate,Document,1,FirstJournalEdit);
			FirstJournal = CurJournal;
		} else {
			CurJournal = new CJournal (JDate,Document,LastJournal->getId () + 1,FirstJournalEdit);
			LastJournal->setNext (CurJournal);
		}
		LastJournal = CurJournal;
	
		// Now book it on Posts
		CJournalEdit* CurJournalEdit = FirstJournalEdit;
		while (CurJournalEdit != 0) {
			CPostEdit* CurPostEdit = new CPostEdit (CurJournalEdit->getDebetEdit (),CurJournalEdit->getValue (),CurJournal->getId ());
			if ( CurJournalEdit->getPost ()->getFirstPostEdit () == 0 ) {
				cdebug << "FirstPostEdit == 0" << std::endl;
				CurJournalEdit->getPost ()->setFirstPostEdit (CurPostEdit);
			} else {
				cdebug << "FirstPostEdit != 0" << std::endl;
				CurJournalEdit->getPost ()->getLastPostEdit ()->setNext (CurPostEdit);
			}
			CurJournalEdit->getPost ()->setLastPostEdit (CurPostEdit);
	
			CurJournalEdit = CurJournalEdit->getNext ();
		}
	} else {
		throw CException ("Not in balance");
	}
} /* void CBookKeeping::bookJournal (TDate JDate,std::string Document,CJournalEdit* JFirstJournalEdit) throw() */

/*!
	get the current FileName
*/
std::string CBookKeeping::getFileName () {
	return FileName;
} /* std::string CBookKeeping::getFileName () */

/*!
	set the FileName to sFileName
*/
void CBookKeeping::setFileName ( std::string sFileName ) {
	FileName = sFileName;
} /* void CBookKeeping::setFileName ( std::string sFileName ) */

/*!
	save it, if sFileName is empty, use FileName, if that is empty return nothing and end
*/
void CBookKeeping::save (std::string sFileName) {	
	if (sFileName == "") {
		if (FileName != "") {
			sFileName = FileName;
		} else {
			cdebug << "Error, no filename given" << std::endl;
			throw CException ("Error, no filename given");
		}
	} else {
		FileName = sFileName;
	}
	std::ofstream File (sFileName.c_str());

	if (File.is_open())
	{
		cdebug << "Saving as: " << FileName << "..." << std::endl;
		// Header
		File << "<?xml version=\"1.0\"?>\n";
		File << "<bookkeeping>\n";
		
		// Save the Posts
		File << "\t<posts>\n";
		CPost* CurPost = FirstPost;
		while (CurPost != 0) {
			File << "\t\t<post name=\"" << CurPost->getName () << "\" id=\"" << CurPost->getId () << "\" ";
			File << "sort=\"" << SortPostToString (CurPost->getSortPost ()) << "\" saldo=\"" << CurPost->getSaldo () << "\" />\n";
			CurPost = CurPost->getNext ();
		}
		File << "\t</posts>\n";

		// Save the Journals
		File << "\t<journals>\n";
		CJournal* CurJournal = FirstJournal;
		while (CurJournal != 0) {
			File << "\t\t<journal id=\" "<< CurJournal->getId () << "\" "; 
			File << "document=\"" << CurJournal->getDocument () << "\" date=\"" << CurJournal->getDate ().date << "\" >\n";

			CJournalEdit* CurJournalEdit = CurJournal->getFirstJournalEdit ();
			while (CurJournalEdit != 0) {
				File << "\t\t\t <journaledit "; 
				File << "postname=\"" << CurJournalEdit->getPost ()->getName () << "\" ";
				File << "value=\"" << CurJournalEdit->getValue () << "\" ";
				File << "debetedit=\"" << CurJournalEdit->getDebetEdit () << "\" ";
				File << "/>\n";
				CurJournalEdit = CurJournalEdit->getNext ();
			} 

			File << "\t\t</journal>\n";
			CurJournal = CurJournal->getNext ();
		}
		File << "\t</journals>\n";

		File << "</bookkeeping>";
		File.close();
	} else {
		throw CException ("Can not save, can not open file");
	}
} /* void CBookKeeping::save (std::string sFileName)  */

/*!
	load a savefile
	if lFileName is empty FileName is used
	if there is already opened a file or already started to work on posts / journals override
	must be true to load a file
*/
bool CBookKeeping::load (std::string LFileName,bool override) {
	bool load = false;
	if (LFileName != "") {
		if (FileName == "") {
			FileName = LFileName;
		} else {
			cdebug << "There is already assigned a filename" << std::endl;
			if (override == false) {
				throw CException ("There is already assigned a filename");
			} else {
				cdebug << "override" << std::endl;
				FileName = LFileName;
			}
		}
	} else {
		if (FileName == "") {
			throw CException ("No Filename given");
		}
	}

	if ((FirstJournal != 0) and (FirstPost != 0)) {
		cdebug << "Already modified" << std::endl;
		throw CException ("Already modified");
	}
	// now the file is ready to load
	cdebug << "Loading..." << std::endl;
	// Initialize the XML4C2 system
	XMLPlatformUtils::Initialize();

	// Create our parser, then attach an error handler to the parser.
	// The parser will call back to methods of the ErrorHandler if it
	// discovers errors during the course of parsing the XML document.
	XercesDOMParser* parser = new XercesDOMParser;
	parser->setDoNamespaces (false);
	parser->setDoSchema (false);
	parser->setCreateEntityReferenceNodes (false);
	try {
		parser->parse (FileName.c_str());
	} catch (XMLException& e) {
		std::cerr << "Error occured during parsing" << std::endl;
		throw CException ("XML Error occured during parsing");
	} catch (DOMException& e) {
		std::cerr << "Error occured during parsing" << std::endl;
		throw CException ("Dom Error occured during parsing");
	} catch (...) {
		cdebug << "Unknown error occured during parsing" << std::endl;
		throw CException ("Unknown error occured during parsing");
	}

	DOMDocument* doc = 0;
	doc = parser->getDocument ();
	loadFromParser ((DOMNode*)doc->getDocumentElement ());

	delete parser;
	// And call the termination method
	XMLPlatformUtils::Terminate ();
	cdebug << "Opened bookkeeping document \""<< FileName <<"\"" << std::endl;
} /* bool CBookKeeping::load (std::string LFileName,bool override) */ 

/*
	returns SPost with all Posts in in range Minimum->Maximum
*/
SPost* CBookKeeping::getPostById (int Minimum,int Maximum) {
	CPost* CurPost = FirstPost;
	SPost* FirstSPost = 0;
	SPost* LastSPost = 0;
	
	while (CurPost != 0) {
		if (isInIntRange (Minimum,Maximum,CurPost->getId ())) {
			SPost* CurSPost = new SPost;
			if (FirstSPost == 0) {
				FirstSPost = CurSPost;
				LastSPost = CurSPost;
			} else {
				LastSPost->Next = CurSPost;
			}
			CurSPost->Post = CurPost;
			CurSPost->Next = 0;
			LastSPost = CurSPost;
		}
		CurPost = CurPost->getNext ();
	}
	return FirstSPost;
} /* SPost* CBookKeeping::getPostById (int Minimum,int Maximum) */

void CBookKeeping::loadFromParser (DOMNode *n) {
	DOMNode* tagpost = 0;
	DOMNode* tagjournal = 0;
	try {
		DOMNode* tagposts = getTagByName (n,"posts");
		tagpost = tagposts->getFirstChild ();

		DOMNode* tagjournals = getTagByName (n,"journals");
		tagjournal = tagjournals->getFirstChild ();
	}
	catch (CException e) {
		cdebug << "Exception occured" << e.what << std::endl;
	}
	catch (...) {
		cdebug << "Uknown exception occured" << std::endl;
	}

	while (tagpost != 0) {
		if (std::string(XMLString::transcode (tagpost->getNodeName())) == "post") {
			cdebug << "Post found" << std::endl;
			std::string name = getAttributeByName (tagpost,"name");
			unsigned short id = atoi (getAttributeByName (tagpost,"id").c_str());
			SSortPost sortpost = StringToSortPost (getAttributeByName (tagpost,"sort"));
			try {
				cdebug << "Adding post" << name << " " << id;
				addPost (name,id,sortpost);
			}
			catch (CException e) {
				cdebug << "Exception occured: " << e.what << std::endl;
			}
		} else {
			cdebug << "Not a usuable tag: " << XMLString::transcode (tagpost->getNodeName()) << std::endl;
		}
		tagpost = tagpost->getNextSibling ();
	}

	while (tagjournal != 0) {
		if (std::string(XMLString::transcode (tagjournal->getNodeName())) == "journal") {
			cdebug << "Journal found" << std::endl;

			CJournalEdit* FirstJournalEdit = 0;
			CJournalEdit* LastJournalEdit = 0;
			CJournalEdit* CurJournalEdit = 0;

			// check for journaledit
			DOMNode* tagjournaledit = tagjournal->getFirstChild ();
			while (tagjournaledit != 0) {
				if (std::string(XMLString::transcode (tagjournaledit->getNodeName())) == "journaledit") {
					cdebug << "Journaledit found" << std::endl;
					CPost* post = getPostByName(getAttributeByName (tagjournaledit,"postname"));
					cdebug << post << std::endl;
					long double value = atof (getAttributeByName (tagjournaledit,"value").c_str());
					// it is a number (0 or 1) but it is an bool
					bool debetedit = atoi (getAttributeByName (tagjournaledit,"debetedit").c_str ());
					try {
						cdebug << "ADD JOURNALEDIT" << std::endl;
						CurJournalEdit = new CJournalEdit (debetedit,post,value);
					}
					catch (CException e) {
						cdebug << "Exception occured: " << e.what;
					}
					if (FirstJournalEdit == 0) {
						FirstJournalEdit = CurJournalEdit;
					} else {
						LastJournalEdit->setNext (CurJournalEdit);
					}
					LastJournalEdit = CurJournalEdit;
				} else {
					cdebug << "Not a usable tag: " << XMLString::transcode (tagjournaledit->getNodeName()) << std::endl;
				}
				tagjournaledit = tagjournaledit->getNextSibling ();
			}

			try {
				std::string document = getAttributeByName (tagjournal,"document");
				TDate date;
				date.date = "Dit is de zelfgemaakte datum";
				cdebug << "BookJournal" << std::endl;
				bookJournal (date,document,FirstJournalEdit);
			}
			catch (CException e) {
				cdebug << "Exception occured" << e.what << std::endl;
				throw e;
			}
			cdebug << "ADD Journal" << std::endl;
		} else {
			cdebug << "Not a usable tag: " << XMLString::transcode (tagjournal->getNodeName()) << std::endl;
		}
		tagjournal = tagjournal->getNextSibling ();
	}
} /* void CBookKeeping::loadFromParser (DOMNode *n) */ 

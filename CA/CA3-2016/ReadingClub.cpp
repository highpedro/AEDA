/*
 * ReadingClub.cpp
 *
 *  Created on: 11/12/2016
 *      Author: RRossetti
 */

#include "ReadingClub.h"

ReadingClub::ReadingClub() :
		catalogItems(BookCatalogItem("", "", 0)) {
	//do nothing!
}

ReadingClub::ReadingClub(vector<Book*> books) :
		catalogItems(BookCatalogItem("", "", 0)) {
	this->books = books;
}

void ReadingClub::addBook(Book* book) {
	this->books.push_back(book);
}

void ReadingClub::addBooks(vector<Book*> books) {
	this->books = books;
}

vector<Book*> ReadingClub::getBooks() const {
	return this->books;
}

BookCatalogItem ReadingClub::getCatalogItem(string title, string author) {
	BookCatalogItem itemNotFound("", "", 0);
	BSTItrIn<BookCatalogItem> it(catalogItems);
	while (!it.isAtEnd()) {
		if (it.retrieve().getTitle() == title
				&& it.retrieve().getAuthor() == author) {
			BookCatalogItem bci(it.retrieve().getTitle(),
					it.retrieve().getAuthor(), 0);
			bci.setItems(it.retrieve().getItems());
			return bci;
		}
		it.advance();
	}
	return itemNotFound;
}

void ReadingClub::addCatalogItem(Book* book) {
	BookCatalogItem itemNotFound("", "", 0);
	BookCatalogItem bci(book->getTitle(), book->getAuthor(), book->getYear());
	BookCatalogItem bciX = catalogItems.find(bci);
	if (bciX == itemNotFound) {
		bci.addItems(book);
		this->catalogItems.insert(bci);
	} else {
		this->catalogItems.remove(bciX);
		bciX.addItems(book);
		this->catalogItems.insert(bciX);
	}
	books.push_back(book);
}

BST<BookCatalogItem> ReadingClub::getCatalogItems() const {
	return this->catalogItems;
}

vector<UserRecord> ReadingClub::getUserRecords() const {
	vector<UserRecord> records;
	HashTabUserRecord::const_iterator it1 = this->userRecords.begin();
	HashTabUserRecord::const_iterator it2 = this->userRecords.end();
	for (; it1 != it2; it1++) {
		records.push_back(*it1);
	}
	return records;
}

void ReadingClub::setUserRecords(vector<UserRecord>& urs) {
	for (int i = 0; i < urs.size(); i++)
		userRecords.insert(urs[i]);
}

priority_queue<User> ReadingClub::getBestReaderCandidates() const {
	return readerCandidates;
}
void ReadingClub::setBestReaderCandidates(priority_queue<User>& candidates) {
	readerCandidates = candidates;
}

//
// TODO: Part I   - BST
//

void ReadingClub::generateCatalog() {

	BookCatalogItem notFound("", "", 0);

	for (auto it = this->books.begin(); it != this->books.end(); it++) {

		BookCatalogItem new_one((*it)->getTitle(), (*it)->getAuthor(),
				(*it)->getYear());

		BookCatalogItem temp = this->catalogItems.find(new_one);

		if (temp == notFound) {

			new_one.addItems((*it));

			this->catalogItems.insert(new_one);

		} else {

			this->catalogItems.remove(temp);

			temp.addItems((*it));

			this->catalogItems.insert(temp);

		}

	}

}

vector<Book*> ReadingClub::getAvailableItems(Book* book) const {
	vector<Book*> temp;

	BookCatalogItem notFound("", "", 0);

	BookCatalogItem tryTo(book->getTitle(), book->getAuthor(), 0);

	BookCatalogItem findBook = this->catalogItems.find(tryTo);

	if (!(findBook == notFound)) {

		for (size_t t = 0; t < findBook.getItems().size(); t++) {

			if (findBook.getItems().at(t)->getReader() == NULL)
				temp.push_back(findBook.getItems().at(t));

		}
	}

	return temp;
}

bool ReadingClub::borrowBookFromCatalog(Book* book, User* reader) {

	BookCatalogItem notFound("", "", 0);

	BookCatalogItem tryTo(book->getTitle(), book->getAuthor(), 0);

	BookCatalogItem findBook = this->catalogItems.find(tryTo);

	if (findBook == notFound)
		return false;
	else {

		for (size_t t = 0; t < findBook.getItems().size(); t++) {

			if (findBook.getItems().at(t)->getReader() == NULL) {
				reader->addReading(findBook.getItems().at(t)->getTitle(),
						findBook.getItems().at(t)->getAuthor());
				findBook.getItems().at(t)->setReader(reader);
				return true;
			}

		}

	}

	return false;
}

//
// TODO: Part II  - Hash Table
//

void ReadingClub::addUserRecord(User* user) {

	this->userRecords.insert(UserRecord(user));

}

void ReadingClub::changeUserEMail(User* user, string newEMail) {

	UserRecord temp(user);

	auto it = this->userRecords.find(temp);

	if (it == this->userRecords.end())
		return;
	else {

		this->userRecords.erase(it);

		user->setEMail(newEMail);

		this->userRecords.insert(UserRecord(user));

	}

}

//
// TODO: Part III - Priority Queue
//

void ReadingClub::addBestReaderCandidates(const vector<User>& candidates,
		int min) {

	for (size_t t = 0; t < candidates.size(); t++) {

		User temp = candidates.at(t);

		int tempNumber = 0;

		tempNumber += temp.getReadings().size();

		if (temp.getReading().first != "" && temp.getReading().second != "")
			tempNumber++;

		if (tempNumber >= min)
			this->readerCandidates.push(temp);

	}

}

int ReadingClub::awardReaderChampion(User& champion) {

	int candidates = 0;

	priority_queue<User> temp = this->readerCandidates;

	if (temp.empty())
		return 0;

	User uno = temp.top();
	temp.pop();

	candidates++;

	int numberUno = uno.numReadings();

	User other = temp.top();
	candidates++;

	int numberOther = other.numReadings();

	if (numberUno > numberOther) {

		champion = uno;

		return temp.size() + 1;

	}

	return 0;
}


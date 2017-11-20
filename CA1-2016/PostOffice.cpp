/*
 * PostOffice.cpp
 */

#include "PostOffice.h"
#include <string>

PostOffice::PostOffice(string firstZCode, string lastZCode):
								firstZipCode(firstZCode), lastZipCode(lastZCode)
{}
PostOffice::PostOffice() {}

void PostOffice::addMailToSend(Mail *m) {
	mailToSend.push_back(m);
}

void PostOffice::addMailToDeliver(Mail *m) {
	mailToDeliver.push_back(m);
}

void PostOffice::addPostman(const Postman &p){
	postmen.push_back(p);
}

vector<Mail *> PostOffice::getMailToSend() const {
	return mailToSend;
}

vector<Mail *> PostOffice::getMailToDeliver() const {
	return mailToDeliver;
}

vector<Postman> PostOffice::getPostman() const {
	return postmen;
}

vector<Mail *> PostOffice::removePostman(string name){
	vector <Mail* > result;

	auto it = this->postmen.begin();

	for (it; it < this->postmen.end(); it++){
		if (it->getName() == name){
			result = it->getMail();
			this->postmen.erase(it);
		}

	}

	return result;
}
vector<Mail *> PostOffice::endOfDay(unsigned int & balance){

	balance = 0;

	auto it = this->mailToSend.begin();

	vector<Mail *> otherStation;

	for (; it < this->mailToSend.end(); it++){
		balance += (*it)->getPrice();
	}

	for (size_t t = 0; t < this->mailToSend.size(); t++){

		if(this->mailToSend.at(t)->getZipCode() >= this->firstZipCode && this->mailToSend.at(t)->getZipCode() <= this->lastZipCode)
			this->addMailToDeliver(this->mailToSend.at(t));
		else
			otherStation.push_back(this->mailToSend.at(t));

	}

	this->mailToSend.clear();

	return otherStation;

}

Postman PostOffice::addMailToPostman(Mail * m, string name){

	for (size_t t = 0; t < this->postmen.size(); t++){
		if (this->postmen.at(t).getName() == name){
			this->postmen.at(t).addMail(m);
			return this->postmen.at(t);
		}

	}

	throw(NoPostmanException(name));

}

/*
 * Postman.cpp
 */
#include "Postman.h"
#include <iostream>


unsigned int Postman::id_provider = 0;

Postman::Postman(): id(0) {}

Postman::Postman(string name) : id(++id_provider){
	this->name = name;
}

void Postman::setName(string nm){
	name = nm;
}

string Postman::getName() const{
	return name;
}

vector<Mail *> Postman::getMail() const {
	return myMail;
}

void Postman::addMail(Mail *m) {
	myMail.push_back(m);
}

void Postman::addMail(vector<Mail *> mails) {
	myMail.insert(myMail.end(),mails.begin(),mails.end());
}

unsigned int Postman::getID() const{
	return id;
}

bool Postman::operator< (const Postman & lhs) {

	unsigned int p1, p2;

	p1 = numberDifferent(this->myMail);

	p2 = numberDifferent(lhs.myMail);

	return p1 < p2;

}






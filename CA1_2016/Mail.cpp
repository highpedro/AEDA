/*
 * Mail.cpp
 */

#include "Mail.h"

Mail::Mail(string send, string rec, string zcode):
			sender(send),receiver(rec), zipCode(zcode)
{ }

Mail::~Mail()
{ }

string Mail::getZipCode() const {
	return zipCode;
}

RegularMail::RegularMail(string send, string rec, string zcode, unsigned int w):
			Mail(send, rec, zcode), weight(w)
{ }

GreenMail::GreenMail(string send, string rec, string zcode, string t):
			Mail(send, rec, zcode), type(t)
{ }

unsigned int RegularMail::getPrice () const{

	if (this->weight <= 20)
		return 50;
	else if(this->weight > 20 && this->weight <= 100)
		return 75;
	else if (this->weight  > 100 && this->weight <= 500)
		return 140;
	else
		return 325;

}

unsigned int GreenMail::getPrice() const{

	if (this->type == "envelope")
		return 80;
	else if(this->type == "bag")
		return 200;
	else
		return 240;


}

bool Mail::operator== (const Mail & lhs) const{

	return this->zipCode == lhs.zipCode;
}






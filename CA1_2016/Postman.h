/*
 * Postman.h
 */

#ifndef SRC_POSTMAN_H_
#define SRC_POSTMAN_H_

#include "Mail.h"
#include <string>
#include <vector>
#include <algorithm>

class Postman {
	unsigned int id;
	string name;
	vector<Mail *> myMail;
	static unsigned int id_provider;
public:
	Postman();
	Postman(string name);
	void setName(string nm);
	void addMail(Mail *m);
	void addMail(vector<Mail *> mails);
	string getName() const;
	vector<Mail *> getMail() const;
	unsigned int getID() const;
	bool operator< (const Postman& lhs);

};




template<class T>
unsigned int numberDifferent(const vector<T> & v1) {

	if (v1.size() == 0)
		return 0;

	vector<T> temp_copy;

	temp_copy.push_back(v1.at(0));

	for (size_t t = 1; t < v1.size(); t++) {

		if (find(temp_copy.begin(), temp_copy.end(), v1.at(t))
				== temp_copy.end())
			temp_copy.push_back(v1.at(t));

	}

	return temp_copy.size();
}

template<class T>
unsigned int numberDifferent(const vector<T *> & v1) {

	if (v1.size() == 0)
		return 0;

	vector<T> temp_copy;

	temp_copy.push_back((*v1.at(0)));

	for (size_t t = 1; t < v1.size(); t++) {

		if (find(temp_copy.begin(), temp_copy.end(), (*v1.at(t)))
				== temp_copy.end())
			temp_copy.push_back((*v1.at(t)));

	}

	return temp_copy.size();
}


#endif /* SRC_POSTMAN_H_ */

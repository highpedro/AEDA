/*
 * Cinema.cpp
 */
#include "Cinema.h"

Cinema::Cinema(string nm, unsigned d, unsigned nr) :
		name(nm), distance(d), numberOfRooms(nr), timetable(
				FilmTime(0, NULL, 0)) {
}

Cinema::Cinema(string nm, unsigned d, unsigned nr, list<string> ls) :
		name(nm), distance(d), numberOfRooms(nr), services(ls), timetable(
				FilmTime(0, NULL, 0)) {
}

Cinema::~Cinema() {
}

string Cinema::getName() const {
	return name;
}

unsigned Cinema::getDistance() const {
	return distance;
}

list<string> Cinema::getServices() const {
	return services;
}

BST<FilmTime> Cinema::getTimetable() const {
	return timetable;
}

void Cinema::addService(string service1) {
	services.push_back(service1);
}

void Cinema::addFilmTime(const FilmTime &ft1) {
	timetable.insert(ft1);
}

// TODO

bool Cinema::operator<(const Cinema & cr) const {
	if (this->distance != cr.distance)
		return this->distance > cr.distance;

	return this->services.size() > cr.services.size();
}

//a1
Film *Cinema::filmAtHour(unsigned &h1) const {
	Film *res = NULL;

	BSTItrIn<FilmTime> it(this->timetable);

	unsigned tempHour = 0;

	while (!it.isAtEnd()) {

		if (it.retrieve().getHour() == h1) {

			res = it.retrieve().getFilm();
			return res;

		}

		if (it.retrieve().getHour() < h1) {
			res = it.retrieve().getFilm();
			tempHour = it.retrieve().getHour();
		}

		if (it.retrieve().getHour() > h1)
			break;

		it.advance();

	}

	if (tempHour != 0)
		h1 = tempHour;

	return res;
}

//a2
bool Cinema::modifyHour(unsigned h1, unsigned room1, unsigned h2) {
	bool res;

	BSTItrIn<FilmTime> it(this->timetable);

	Film * toChange = NULL;

	bool occupied = false;

	while (!it.isAtEnd()) {

		if (it.retrieve().getRoomID() == room1
				&& it.retrieve().getHour() == h1) {

			toChange = it.retrieve().getFilm();

		}

		if (it.retrieve().getHour() == h2)
			occupied = true;

		it.advance();

	}

	if (occupied == true || toChange == NULL)
		return false;

	if (occupied == false && toChange != NULL) {

		BSTItrIn<FilmTime> aux(this->timetable);

		while (!aux.isAtEnd()) {

			if (aux.retrieve().getRoomID() == room1
					&& aux.retrieve().getHour() == h1) {

				FilmTime temp = aux.retrieve();

				this->timetable.remove(aux.retrieve());

				temp.setHour(h2);

				this->timetable.insert(temp);

				break;

			}

			aux.advance();

		}

		res = true;
	}

	return res;
}

//a3
unsigned Cinema::addFilm(Film *f1, unsigned h1) {
	unsigned roomToUse = 0;

	unsigned counter = 1;

	BSTItrIn<FilmTime> it(this->timetable);

	while (!it.isAtEnd()) {

		if (it.retrieve().getHour() == h1) {
			counter++;
		}

		it.advance();

	}

	if (counter <= this->numberOfRooms) {

		FilmTime toInsert(h1, f1, counter);
		this->timetable.insert(toInsert);
		roomToUse = counter;
	}

	return roomToUse;
}


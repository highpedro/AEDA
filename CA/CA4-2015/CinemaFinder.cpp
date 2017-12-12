/*
 * CinemaFinder.cpp
 */

#include "CinemaFinder.h"
#include "Cinema.h"
#include "Film.h"
#include <algorithm>

CinemaFinder::CinemaFinder() {
}

CinemaFinder::~CinemaFinder() {
}

void CinemaFinder::addFilm(Film *f1) {
	FilmPtr fp1;
	fp1.film = f1;
	films.insert(fp1);
}

void CinemaFinder::addCinema(const Cinema &c1) {
	cinemas.push(c1);
}

tabHFilm CinemaFinder::getFilms() const {
	return films;
}

priority_queue<Cinema> CinemaFinder::getCinemas() const {
	return cinemas;
}

// TODO

//b1
list<string> CinemaFinder::filmsWithActor(string actorName) const {
	list<string> res;

	for (auto it = this->films.begin(); it != this->films.end(); it++) {

		list<string> temp = it->film->getActors();

		if (find(temp.begin(), temp.end(), actorName) != temp.end())
			res.push_back(it->film->getTitle());

	}

	return res;
}

//b2
void CinemaFinder::addActor(string filmTitle, string actorName) {

	for (auto it = this->films.begin(); it != this->films.end(); it++) {

		if (it->film->getTitle() == filmTitle) {
			it->film->addActor(actorName);
			return;
		}

	}

	Film * newOne = new Film(filmTitle);

	newOne->addActor(actorName);

	FilmPtr watFace;
	watFace.film = newOne;

	this->films.insert(watFace);

}

//c1
string CinemaFinder::nearestCinema(string service1) const {
	string cName = "";

	priority_queue<Cinema> temp = this->cinemas;

	while (!temp.empty()) {

		Cinema needsmorejpeg = temp.top();

		list<string> thereugo = needsmorejpeg.getServices();

		if (find(thereugo.begin(), thereugo.end(), service1)
				!= thereugo.end()) {
			cName = needsmorejpeg.getName();
			return cName;
		}

		temp.pop();
	}

	return cName;
}

//c2
void CinemaFinder::addServiceToNearestCinema(string service1,
		unsigned maxDistance) {

	priority_queue<Cinema> temp;

	if (this->cinemas.empty())
		throw CinemaNotFound();

	bool added = false;

	while (!this->cinemas.empty()) {

		Cinema tempCin = this->cinemas.top();

		if (added == false) {
			if (tempCin.getDistance() <= maxDistance) {

				tempCin.addService(service1);
				added = true; //ain't adding to no one else boi
			}
		}

		temp.push(tempCin);
		this->cinemas.pop();

	}

	while (!temp.empty()) {
		this->cinemas.push(temp.top());
		temp.pop();
	}

	if (added == false) //didnt add boi
		throw CinemaNotFound();

}

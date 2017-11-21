/*
 * Restaurant.cpp
 *
 *  Created on: 17/11/2015
 *      Author: hlc
 */

#include "Restaurant.h"
#include <iostream>
#include <string>

using namespace std;

Restaurant::Restaurant() { }

Restaurant::Restaurant(vector< stack<Dish*> >* cl, queue<Dish*>* di, list<Dish*>* dr) {
	if(cl != NULL) clean = *cl;
	if(di != NULL) dirty = *di;
	if(dr != NULL) drying = *dr;
}

void Restaurant::addTable(unsigned int n_places) {
	tables.push_back(Table(n_places));
}

void Restaurant::addTable(Table& t) {
	tables.push_back(t);
}

const Table& Restaurant::getTable(vector<Table>::size_type idx) const {
	return tables[idx];
}

/**
 * Gets the clean dishes stack for a given collection and type.
 * If there is none, adds and returns an empty stack.
 */
stack<Dish*>& Restaurant::getCleanDishStack(string collection, TypeOfDish type) {

	for(vector< stack<Dish*> >::iterator it = clean.begin(); it != clean.end(); ++it) {
		if((*it).empty() || ((*it).top()->getCollection() == collection && (*it).top()->getType() == type)) {
			return *it;
		}
	}

	stack<Dish*> st;
	clean.push_back(st);
	return clean.back();
}

const queue<Dish*>& Restaurant::getDirty() const {
	return dirty;
}

const list<Dish*>& Restaurant::getDrying() const {
	return drying;
}

/**
 * Adds a number of dishes of a collection/type to the respective clean stack.
 */
void Restaurant::addDishes(unsigned int n, string collection, TypeOfDish type) {

	unsigned int counter = 0;

	while(counter < n){
		this->getCleanDishStack(collection,type).push(new Dish(collection,type));
		counter++;
	}

}

/**
 * Washes a dish, getting if from the dirty queue and putting it in the wet list.
 * Returns the washed dish.
 */
Dish* Restaurant::washDish() {
	Dish* d;

	d = this->dirty.front();
	this->dirty.pop();
	this->drying.push_back(d);

	return d;
}

/**
 * Clears a table, placing all dishes that are on it in the dirty queue.
 */
void Restaurant::clearTable(vector<Table>::size_type idx) {

	if (idx >= this->tables.size() || this->tables.empty())
		return;

	vector<Dish *> dirty_lil_bitch;

	dirty_lil_bitch = this->tables.at(idx).clear();

	for(size_t t = 0; t < dirty_lil_bitch.size(); t++){
		this->dirty.push(dirty_lil_bitch.at(t));
	}

}

/**
 * Stores in the respective clean stack all drying dishes of a given collection and type.
 */
void Restaurant::storeDryDishes(string collection, TypeOfDish type) {

	/*
	 stack<Dish *> & clean = this->getCleanDishStack(collection, type);

	 for (auto it = this->drying.begin(); it != this->drying.end(); it++) {
	 if ((*it)->getCollection() == collection && (*it)->getType() == type) {
	 clean.push((*it));

	 it = this->drying.erase(it);

	 it--;


	 }
	 }
	 */

	//some of that sweet lambda magic

	stack<Dish *> & clean = this->getCleanDishStack(collection, type);

	this->drying.remove_if(
			[&clean,collection,type](Dish * dish) {
				if(dish->getCollection() == collection && dish->getType() == type) {
					clean.push(dish);
					return true;
				}
				else
				return false;

			});

}

/**
 * Puts Plates of a given collection in a table.
 * Throws TableNotReadyException when the table is not empty.
 * Throws NotEnoughDishesException when there are not enough clean plates of the collection.
 */
void Restaurant::setupTable(vector<Table>::size_type idx, string collection) {

	if (idx >= this->tables.size() || this->tables.empty())
			return;

	if(!this->tables.at(idx).empty())
		throw TableNotReadyException();

	stack<Dish *> & clean = this->getCleanDishStack(collection,Plate);

	if (clean.size() < this->tables.at(idx).size())
		throw NotEnoughDishesException();

	vector <Dish *> yolo;

	for(unsigned int t = 0; t < this->tables.at(idx).size(); t++){
		yolo.push_back(clean.top());
		clean.pop();
	}

	this->tables.at(idx).putOn(yolo);
}

/**
 * Picks the dry dishes and groups them.
 * Returns the grouped dishes.
 */
list<Dish*> Restaurant::pickupAndGroupDryDishes() {
	list<Dish*> dry_grouped;

	auto it = this->drying.begin();

	while (!this->drying.empty()) {

		 it = this->drying.begin();

		dry_grouped.push_back((*it));

		it = this->drying.erase(it);

		for (; it != this->drying.end(); it++) {

			if ((*it)->getCollection() == dry_grouped.back()->getCollection()
					&& (*it)->getType() == dry_grouped.back()->getType()) {
				dry_grouped.push_back((*it));
				this->drying.erase(it);
				it--;
			}


		}
	}

	return dry_grouped;
}

/**
 * Stores grouped dishes in the respective clean stacks.
 * Returns the number of stacks that have been updated.
 */
int Restaurant::storeGroupedDishes(list<Dish*> grouped_dishes) {
	auto it = grouped_dishes.begin();
	string collection = (*it)->getCollection();
	TypeOfDish type = (*it)->getType();

	//spaghetti code master

	int counter = 0;
	counter++;

	for (; it != grouped_dishes.end(); it++) {

		this->getCleanDishStack((*it)->getCollection(), (*it)->getType()).push((*it));

		if ((*it)->getCollection() != collection || (*it)->getType() != type)
			counter++;
		collection = (*it)->getCollection();
		type = (*it)->getType();

	}

	return counter;
}


/*
 * Purchase.cpp
 *
 *  Created on: Nov 16, 2016
 *      Author: hlc
 */

#include "Purchase.h"

using namespace std;

Purchase::Purchase(long cli) : client (cli) {
}

long Purchase::getClient() const {
	return client;
}

list< stack<Article*> > Purchase::getBags() const {
	return bags;
}

/**
 * Create an Article associated with the client of this purchase.
 */
Article* Purchase::createArticle(long barCode, bool present, bool deliverHome) {

	Article * newArt = new Article(this->client, barCode);
	newArt->setPresent(present);
	newArt->setDeliverHome(deliverHome);

	return newArt;

}

/**
 * Add an Article to the bags of this purchase. A new bag is added when the last bag is full.
 */
void Purchase::putInBag(Article* article) {



	if ( this->bags.back().size() < this->BAG_SIZE){
		this->bags.back().push(article);
		return;
	}
	else{
		stack<Article *> last_one;
		last_one.push(article);
		this->bags.push_back(last_one);
		return;
	}
	return;
}

/**
 * Pop from the bags all articles that are presents.
 * All other articles are pushed back into the bags where they were, maintaining order.
 */
vector<Article*> Purchase::popPresents() {

	vector<Article*> presents;

	for (auto it = this->bags.begin(); it != this->bags.end(); it++) {

		stack<Article *> temp;

		while(!(*it).empty()) {
			if ((*it).top()->getPresent() == true) {  //it is a present
				presents.push_back((*it).top());
			} else {   //not a present
				temp.push((*it).top());
			}
			(*it).pop();
		}


		while(!temp.empty()){
			(*it).push(temp.top());
			temp.pop();
		}



	}

	return presents;

}


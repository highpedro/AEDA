/*
 * Jogo.cpp
 *
 */

#include "Jogo.h"
#include <sstream>
#include <algorithm>
#include <iostream>
#include <random>
using namespace std;

unsigned Jogo::numPalavras(string frase) {
	if (frase.length() == 0)
		return 0;
	int n = 1;
	int pos = frase.find(' ');
	while (pos != string::npos) {
		frase = frase.substr(pos + 1);
		pos = frase.find(' ');
		n++;
	}
	return n;
}

Jogo::Jogo() :
		criancas() {

}

Jogo::Jogo(list<Crianca>& lc2) :
		criancas(lc2) {

}

void Jogo::insereCrianca(const Crianca &c1) {
	this->criancas.insert(this->criancas.end(), c1);
}

list<Crianca> Jogo::getCriancasJogo() const {
	list<Crianca> res = this->criancas;

	return res;
}

string Jogo::escreve() const {
	string res;

	for_each(this->criancas.begin(), this->criancas.end(),
			[&res](const Crianca & c1) {res += c1.escreve() + '\n';});

	return res;
}

Crianca& Jogo::perdeJogo(string frase) {

	int palavras = this->numPalavras(frase);

	palavras = palavras % this->criancas.size();

	auto it = this->criancas.begin();

	while (palavras) {
		it++;
		palavras--;
	}

	string nome = it->getNome();
	unsigned age = it->getIdade();

	Crianca * c1 = new Crianca(nome, age);

	return *c1;
}

list<Crianca>& Jogo::inverte() {
	/*
	 auto it = this->criancas.end();

	 it--;

	 list<Crianca> reversed;

	 while( it != this->criancas.begin()){

	 reversed.push_back(*it);
	 it--;
	 }

	 reversed.push_back(*it);

	 this->criancas = reversed;
	 */

	this->criancas.reverse();

	return criancas;
}

list<Crianca> Jogo::divide(unsigned id) {
	list<Crianca> res;

	this->criancas.remove_if([&res, id](Crianca & c1) {
		if(c1.getIdade() > id) {
			res.push_back(c1);
			return true;
		}
		else
		return false;
	});

	return res;
}

void Jogo::setCriancasJogo(const list<Crianca>& l1) {
	this->criancas = l1;
}

bool Jogo::operator==(Jogo& j2) {
	if (this->criancas.size() != j2.criancas.size())
		return false;

	auto j1it = this->criancas.begin();
	auto j2it = j2.criancas.begin();

	for (; j1it != this->criancas.end(); ++j1it, ++j2it) {

		if (!(*j1it == *j2it))
			return false;
	}

	return true;
}

list<Crianca> Jogo::baralha() const {
	list<Crianca> res;

	list<Crianca> temp = this->criancas;

	unsigned long index;

	while (!temp.empty()) {

		auto it = temp.begin();
		index = rand() % temp.size();
		advance(it, index);
		res.push_back(*it);
		temp.erase(it);

	}

	return res;
}

/*
 * Caixa.cpp
 */

#include "Caixa.h"


Objeto::Objeto(unsigned idObj, unsigned pesoObj): id(idObj), peso(pesoObj)
{}

unsigned Objeto::getID() const {
	return id;
}

unsigned Objeto::getPeso() const {
	return peso;
}

Caixa::Caixa(unsigned cap): id(ultimoId++), capacidade(cap), cargaLivre(cap)
{}

unsigned Caixa::getID() const {
	return id;
}

unsigned Caixa::getCargaLivre() const {
	return cargaLivre;
}

void Caixa::addObjeto(Objeto& obj) {
	cargaLivre -= obj.getPeso();
	objetos.push(obj);
}

void Caixa::resetID(){
	ultimoId = 1;
}

unsigned Caixa::getSize() const {
	return objetos.size();
}


ostream& operator<<(ostream& os, Objeto obj) {
	os << "O" << obj.getID() << ": " << obj.getPeso();
	return os;
}

unsigned Caixa::ultimoId = 1;


/* a implementar pelos estudantes */

bool Objeto::operator<(const Objeto& o1) const {

	return this->peso < o1.peso;

}

bool Caixa::operator<(const Caixa& c1) const {
	return this->cargaLivre > c1.cargaLivre;
}


string Caixa::imprimeConteudo() const {
	// TODO
	return "";
}



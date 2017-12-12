/*
 * Empacotador.cpp
 */

#include "MaquinaEmpacotar.h"

MaquinaEmpacotar::MaquinaEmpacotar(int capCaixas) :
		capacidadeCaixas(capCaixas) {
}

unsigned MaquinaEmpacotar::numCaixasUsadas() {
	return caixas.size();
}

unsigned MaquinaEmpacotar::addCaixa(Caixa& cx) {
	caixas.push(cx);
	return caixas.size();
}

HEAP_OBJS MaquinaEmpacotar::getObjetos() const {
	return this->objetos;
}

HEAP_CAIXAS MaquinaEmpacotar::getCaixas() const {
	return this->caixas;
}

/* a implementar pelos estudantes */

unsigned MaquinaEmpacotar::carregaPaletaObjetos(vector<Objeto> &objs) {

	//unsigned maxFreeCapacity = this->caixas.top().getCargaLivre();

	unsigned maxFreeCapacity = this->capacidadeCaixas;

	unsigned counter = 0;

	for (auto it = objs.begin(); it != objs.end(); it++) {

		if ((*it).getPeso() < maxFreeCapacity) {

			this->objetos.push((*it));
			counter++;
			it = objs.erase(it);
			it--;
		}

	}

	return counter;
}

Caixa MaquinaEmpacotar::procuraCaixa(Objeto& obj) {
	Caixa cx;

	priority_queue<Caixa> temp;

	int FoundBox = 0;

	while (!caixas.empty()) {

		cx = caixas.top();

		if (cx.getCargaLivre() >= obj.getPeso()) {
			caixas.pop();
			FoundBox = 1;
			break;
		}

		temp.push(caixas.top());
		caixas.pop();

	}

	while(!temp.empty()){
		caixas.push(temp.top());
		temp.pop();
	}

	if(FoundBox == 0){
		cx = Caixa(this->capacidadeCaixas);
	}


	return cx;
}

unsigned MaquinaEmpacotar::empacotaObjetos() {


	unsigned counter = 0;




	return counter;
}

string MaquinaEmpacotar::imprimeObjetosPorEmpacotar() const {
// TODO
	return "";
}

Caixa MaquinaEmpacotar::caixaMaisObjetos() const {
// TODO
	Caixa cx;
	return cx;
}


#include "Jogador.h"

void Jogador::adicionaAposta(const Aposta & ap) {
	this->apostas.insert(ap);
}

unsigned Jogador::apostasNoNumero(unsigned num) const {
	unsigned count = 0;

	auto it = this->apostas.begin();

	while (it != this->apostas.end()) {

		if ((*it).contem(num))
			count++;

		it++;

	}

	return count;
}

tabHAposta Jogador::apostasPremiadas(const tabHInt & sorteio) const {
	tabHAposta money;

	auto it = this->apostas.begin();

	while (it != this->apostas.end()) {

		if ((*it).calculaCertos(sorteio) > 3) {

			money.insert((*it));
		}

		it++;
	}

	return money;
}

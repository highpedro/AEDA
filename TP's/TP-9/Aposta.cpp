#include "Aposta.h"
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

bool Aposta::contem(unsigned num) const {

	auto it = this->numeros.begin();

	while (it != this->numeros.end()) {

		int x = *it;

		if (x == num)
			return true;

		it++;
	}

	return false;
}

void Aposta::geraAposta(const vector<unsigned> & valores, unsigned n) {
	vector<unsigned> nao_repetidos;
	int counter = 0;

	for (auto e : valores) {
		if (find(nao_repetidos.begin(), nao_repetidos.end(), e)
				== nao_repetidos.end() && counter < n) {
			nao_repetidos.push_back(e);
			counter++;
		}
	}

	for (auto e : nao_repetidos) {
		this->numeros.insert(e);
	}

}

unsigned Aposta::calculaCertos(const tabHInt & sorteio) const {
	unsigned certos = 0;

	auto itSorteio = sorteio.begin();

	auto itAposta = this->numeros.begin();

	while (itSorteio != sorteio.end()) {

		while (itAposta != this->numeros.end()) {

			int x = *itAposta;
			int y = *itSorteio;

			if (x == y)
				certos++;

			itAposta++;

		}

		itAposta = this->numeros.begin();
		itSorteio++;
	}

	return certos;
}


#ifndef JOGADOR_H_
#define JOGADOR_H_

#include "Aposta.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

//A ALTERAR!!
struct apostaHash {
	int operator()(const Aposta & ap) const {
		int i = 0;

		auto it = ap.getNumeros().begin();

		while (it != ap.getNumeros().end()) {

			int x = *it;

			i += (x * x) % 47;
			it++;
		}

		return i;

	}

	bool operator()(const Aposta & ap1, const Aposta & ap2) const {

		vector<int> AP1(ap1.getNumeros().begin(), ap1.getNumeros().end());
		vector<int> AP2(ap2.getNumeros().begin(), ap2.getNumeros().end());

		for (auto e : AP1) {
			if (find(AP2.begin(), AP2.end(), e) != AP2.end()){
				cout << "falso"<< endl;
				return false;
			}

		}

		cout << "true" << endl;
		return true;

	}
};

typedef unordered_set<Aposta, apostaHash, apostaHash> tabHAposta;

class Jogador {
	tabHAposta apostas;
	string nome;
public:
	Jogador(string nm = "anonimo") {
		nome = nm;
	}
	void adicionaAposta(const Aposta & ap);
	unsigned apostasNoNumero(unsigned num) const;
	tabHAposta apostasPremiadas(const tabHInt & sorteio) const;
	unsigned getNumApostas() const {
		return apostas.size();
	}
};

#endif /*JOGADOR1_H_*/

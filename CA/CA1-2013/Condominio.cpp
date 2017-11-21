/*
 * Condominio.cpp
 */

#include "Condominio.h"
#include <algorithm>




Imovel::Imovel(int areaH, string prop, int id) :
		areaHabitacao(areaH), proprietario(prop), ID(id) {
}

int Imovel::getID() const {
	return ID;
}

void Imovel::setID(int id) {
	ID = id;
}

int Imovel::getAreaHabitacao() const {
	return areaHabitacao;
}

string Imovel::getProprietario() const {
	return proprietario;
}

float Imovel::mensalidade() const {

	return 50 + 0.2 * this->areaHabitacao;

}

int Imovel::areaTotal() const {
	return this->areaHabitacao;
}

Apartamento::Apartamento(int areaH, int anda, string prop, int id) :
		Imovel(areaH, prop, id), andar(anda) {
}

float Apartamento::mensalidade() const {

	return Imovel::mensalidade() + 1 * this->andar;

}

int Apartamento::areaTotal() const {
	return Imovel::areaTotal();
}

Vivenda::Vivenda(int areaH, int areaExt, bool pisc, string prop, int id) :
		Imovel(areaH, prop, id), areaExterior(areaExt), piscina(pisc) {
}

float Vivenda::mensalidade() const {

	return Imovel::mensalidade() + 0.1 * this->areaExterior + 10 * this->piscina;

}

int Vivenda::areaTotal() const {

	return Imovel::areaTotal() + this->areaExterior;
}

Urbanizacao::Urbanizacao(string nm, int id) :
		nome(nm), ID(id) {
}

void Urbanizacao::adicionaImovel(Imovel *im1) {
	im1->setID(++imovel_id);
	imoveis.push_back(im1);
}

vector<Imovel *> Urbanizacao::getImoveis() const {
	return imoveis;
}

string Urbanizacao::getNome() const {
	return nome;
}

int Urbanizacao::getID() const {
	return ID;
}

vector<Imovel *> Urbanizacao::areaSuperiorA(int area1) const {

	vector<Imovel *> superior;

	for (size_t t = 0; t < this->imoveis.size(); t++) {

		if (this->imoveis.at(t)->areaTotal() > area1)
			superior.push_back(this->imoveis.at(t));

	}

	return superior;
}

bool Urbanizacao::operator >(const Urbanizacao & lhs) {

	vector<string> v1, v2;

	//nr de habitacoes
	unsigned int hab1 = this->imoveis.size();
	unsigned int hab2 = lhs.getImoveis().size();

	if (hab1 == 0)
		return false;
	if (hab2 == 0)
		return true;

	v1.push_back(this->imoveis.at(0)->getProprietario());

	for (size_t t = 1; t < this->imoveis.size(); t++) {
		if (find(v1.begin(), v1.end(), this->imoveis.at(t)->getProprietario())
				== v1.end())
			v1.push_back(this->imoveis.at(t)->getProprietario());
	}

	v2.push_back(lhs.getImoveis().at(0)->getProprietario());

	for (size_t t = 1; t < lhs.getImoveis().size(); t++) {
		if (find(v2.begin(), v2.end(),
				lhs.getImoveis().at(t)->getProprietario()) == v2.end())
			v2.push_back(lhs.getImoveis().at(t)->getProprietario());
	}

	unsigned int prop1, prop2;

	//nr de props yo to ma peepz represent ggez
	prop1 = v1.size();
	prop2 = v2.size();

	float reason1 = hab1 / prop1;
	float reason2 = hab2 / prop2;

	return reason1 < reason2;

}

void ECondominio::adicionaUrbanizacao(Urbanizacao urb1) {
	urbanizacoes.push_back(urb1);
}

vector<Urbanizacao> ECondominio::getUrbanizacoes() const {
	return urbanizacoes;
}

float ECondominio::mensalidadeDe(string nomeProp) const {

	float sum = 0;

	for (size_t t = 0; t < this->urbanizacoes.size(); t++) {
		for (size_t k = 0; k < this->urbanizacoes.at(t).getImoveis().size();
				k++) {
			if (this->urbanizacoes.at(t).getImoveis().at(k)->getProprietario()
					== nomeProp)
				sum +=
						this->urbanizacoes.at(t).getImoveis().at(k)->mensalidade();
		}
	}
	return sum;
}

vector<Urbanizacao> ECondominio::removeUrbanizacaoDe(string nomeProp) {

	vector<Urbanizacao> deleted;

	bool remove = false;

	auto it = this->urbanizacoes.begin();

	for (it; it < this->urbanizacoes.end(); it++) {

		remove = false;

		for (size_t t = 0; t < it->getImoveis().size(); t++) {
			if (it->getImoveis().at(t)->getProprietario() == nomeProp) {
				remove = true;
				break;
			}
		}

		if (remove == true) {
			deleted.push_back(*it);
			this->urbanizacoes.erase(it);
			it--;
		}

	}

	return deleted;

}

vector<Imovel *> ECondominio::operator ()(string name) {

	vector<Imovel *> result;

	for (size_t t = 0; t < this->urbanizacoes.size(); t++) {
		if (this->urbanizacoes.at(t).getNome() == name)
			result = this->urbanizacoes.at(t).getImoveis();
	}

	return result;

}


int Urbanizacao::id_provider = 0;

Urbanizacao::Urbanizacao(string nm) : ID(++id_provider){
	this->nome = nm;
}



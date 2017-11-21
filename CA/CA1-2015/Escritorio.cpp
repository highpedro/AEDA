#include "Escritorio.h"
#include <iostream>

//Documento
Documento::Documento(int nPag, float pP, float pA) :
		numPaginas(nPag), pPreto(pP), pAmarelo(pA) {
}
Documento::~Documento() {
}

int Documento::getNumPaginas() const {
	return numPaginas;
}

float Documento::getPercentagemPreto() const {
	return pPreto;
}

float Documento::getPercentagemAmarelo() const {
	return pAmarelo;
}

Documento & Documento::operator +(const Documento & lhs) {

	int npag = this->numPaginas + lhs.numPaginas;

	float pP = (this->pPreto * this->numPaginas + lhs.pPreto * lhs.numPaginas)
			/ (this->numPaginas + lhs.numPaginas);
	float pA = (this->pAmarelo * this->numPaginas
			+ lhs.pAmarelo * lhs.numPaginas)
			/ (this->numPaginas + lhs.numPaginas);

	Documento * doc = new Documento(npag, pP, pA);

	return (*doc);

}

//Impressora
Impressora::Impressora(string cod, int a) :
		codigo(cod), ano(a) {
}
Impressora::~Impressora() {
}

string Impressora::getCodigo() const {
	return codigo;
}

int Impressora::getAno() const {
	return ano;
}

vector<Documento> Impressora::getDocumentosImpressos() const {
	return docsImpressos;
}

//ImpressoraPB
ImpressoraPB::ImpressoraPB(string cod, int a, int toner) :
		Impressora(cod, a), numPagImprimir(toner) {
}

int ImpressoraPB::getNumPaginasImprimir() const {
	return numPagImprimir;
}

bool ImpressoraPB::imprime(Documento doc1) {
	if (this->numPagImprimir >= doc1.getNumPaginas()) {
		this->numPagImprimir -= doc1.getNumPaginas();

		this->docsImpressos.push_back(doc1);

		return true;
	}

	return false;
}

bool ImpressoraPB::tonerBaixo() {

	if (this->numPagImprimir < 30)
		return true;

	return false;
}

//ImpressoraCores
ImpressoraCores::ImpressoraCores(string cod, int a, int toner) :
		Impressora(cod, a), numPagImprimirPreto(toner), numPagImprimirAmarelo(
				toner) {
}

int ImpressoraCores::getNumPaginasImprimir() const {
	if (numPagImprimirPreto < numPagImprimirAmarelo)
		return (int) numPagImprimirPreto;
	return (int) numPagImprimirAmarelo;
}

bool ImpressoraCores::imprime(Documento doc1) {

	if (this->numPagImprimirPreto
			>= (doc1.getNumPaginas() * doc1.getPercentagemPreto())
			&& this->numPagImprimirAmarelo
					>= (doc1.getNumPaginas() * doc1.getPercentagemAmarelo())) {

		this->numPagImprimirAmarelo -= doc1.getNumPaginas()
				* doc1.getPercentagemAmarelo();
		this->numPagImprimirPreto -= (doc1.getNumPaginas()
				* doc1.getPercentagemPreto());

		this->docsImpressos.push_back(doc1);

		return true;
	}

	return false;
}

bool ImpressoraCores::tonerBaixo() {

	if (this->numPagImprimirAmarelo < 20 || this->numPagImprimirPreto < 20)
		return true;

	return false;

}

//Funcionario
Funcionario::Funcionario(string cod) :
		codigo(cod) {
}
Funcionario::~Funcionario() {
}

void Funcionario::adicionaImpressora(Impressora *i1) {
	impressoras.push_back(i1);
}

vector<Impressora *> Funcionario::getImpressoras() const {
	return impressoras;
}

string Funcionario::getCodigo() const {
	return codigo;
}

//Escritorio
Escritorio::Escritorio() {
}
Escritorio::~Escritorio() {
}

void Escritorio::adicionaImpressora(Impressora *i1) {
	impressoras.push_back(i1);
}

void Escritorio::adicionaFuncionario(Funcionario f1) {
	funcionarios.push_back(f1);
}

vector<Impressora *> Escritorio::getImpressoras() const {
	return impressoras;
}

int Escritorio::numImpressorasSemResponsavel() const {

	unsigned int comResp = 0;

	for (size_t t = 0; t < this->funcionarios.size(); t++) {
		comResp += this->funcionarios.at(t).getImpressoras().size();
	}

	return this->impressoras.size() - comResp;

}

vector<Impressora *> Escritorio::retiraImpressoras(int ano1) {

	vector<Impressora *> result;

	if (this->impressoras.size() == 0)
		return result;

	auto it = this->impressoras.begin();

	for (it; it < this->impressoras.end(); it++) {
		if ((*it)->getAno() < ano1) {
			result.push_back(*it);
			it = this->impressoras.erase(it);
			it--;
		}

	}

	return result;

}

Impressora * Escritorio::imprimeDoc(Documento doc1) const {

	for (size_t t = 0; t < this->impressoras.size(); t++) {

		if (this->impressoras.at(t)->imprime(doc1))
			return this->impressoras.at(t);
	}

	return (new ImpressoraPB("inexistente", 0, 0));
}

vector<Impressora *> Escritorio::tonerBaixo() const {

	vector<Impressora *> down;

	for (size_t t = 0; t < this->impressoras.size(); t++) {

		if (this->impressoras.at(t)->tonerBaixo())
			down.push_back(this->impressoras.at(t));
	}

	return down;

}

string Escritorio::operator ()(string cod) {

	string null = "nulo";

	bool cena = false;

	for (size_t t = 0; t < this->impressoras.size(); t++) {
		if (this->impressoras.at(t)->getCodigo() == cod){
			cena = true;
			break;
		}

	}

	if (cena == false)
		return null;

	for (size_t t = 0; t < this->funcionarios.size(); t++) {
		for (size_t k = 0; k < this->funcionarios.at(t).getImpressoras().size();
				k++)
			if (this->funcionarios.at(t).getImpressoras().at(k)->getCodigo()
					== cod)
				return (this->funcionarios.at(t).getCodigo());
	}

	return null;
}

/*
 * Agencia.cpp
 */

#include "Agencia.h"


//Conta
Conta::Conta(int nConta, float sd, int nTrans): numConta(nConta), saldo(sd), numTransacoes(nTrans), titular2(nullptr)
{ }

Conta::Conta(const Conta & lhs){
	this->numConta = lhs.numConta;
	this->saldo = lhs.saldo;
	this->numTransacoes = lhs.numTransacoes;
	this->titular2 = lhs.titular2;
}


Conta::~Conta(){}

Normal::~Normal(){}

DeOperacao::~DeOperacao(){}

int Conta::getNumConta() const
{ return numConta; }

float Conta::getSaldo() const
{ return saldo; }

int Conta::getNumTransacoes() const
{ return numTransacoes; }


void Conta::setTitular2(Cliente *cli2)
{ titular2=cli2; }

Cliente * Conta::getTitular2() const
{ return titular2; }



Normal::Normal(int nConta, float sd, int nTrans): Conta(nConta, sd, nTrans)
{}

bool Normal::levantamento(float valor){

	if (valor <= this->saldo){
		this->saldo -= valor;
		this->numTransacoes++;
		return true;
	}

	return false;
}

void Normal::deposito(float valor){

	this->saldo += valor;
}

DeOperacao::DeOperacao(int nConta, float tx, float sd, int nTrans): Conta(nConta, sd, nTrans), taxa(tx)
{}


bool DeOperacao::levantamento(float valor){

	if (valor <= this->saldo){
		if (valor > 30)
			this->saldo = this->saldo - valor - this->taxa;
		else
			this->saldo -= valor;
		this->numTransacoes++;
		return true;
	}

	return false;
}

void DeOperacao::deposito(float valor){

	this->saldo += valor;
}


//Cliente
Cliente::Cliente (string nm): nome(nm)
{}

string Cliente::getNome() const
{ return nome; }

vector<Conta *> Cliente::getContas() const
{ return contas; }

void Cliente::adicionaConta(Conta *c1)
{ contas.push_back(c1); }


//Agencia
Agencia::Agencia(string desig): designacao(desig)
{}

string Agencia::getDesignacao() const
{ return designacao; }

vector<Cliente *> Agencia::getClientes() const
{ return clientes; }

vector<Gerente> Agencia::getGerentes() const
{ return gerentes; }

void Agencia::adicionaCliente(Cliente *cli1)
{ clientes.push_back(cli1); }

Conta * Agencia::levantamento(string nomeCli, float valor){

	for (size_t t = 0; t < this->clientes.size(); t++){
		if (this->clientes.at(t)->getNome() == nomeCli){
			for(size_t k = 0; k < this->clientes.at(t)->getContas().size(); k++){
				if (this->clientes.at(t)->getContas().at(k)->levantamento(valor))
					return this->clientes.at(t)->getContas().at(k);
			}
		}
	}

	Conta * erro = new Normal(-1, 0, 0);

	return erro;


}

float Agencia::fimMes() const {

	float sum = 0;

	for (size_t t = 0; t < this->clientes.size(); t++) {

		for (size_t k = 0; k < this->clientes.at(t)->getContas().size(); k++) {
			if (this->clientes.at(t)->getContas().at(k)->isNormal()) {
				this->clientes.at(t)->getContas().at(k)->levantamento(1.5);

			}
			sum += this->clientes.at(t)->getContas().at(k)->getSaldo();
		}

	}
	return sum;

}

vector<Conta *> Agencia::removeCliente(string nomeCli) {

	vector<Conta *> leftovers;
	bool exists = false;
	size_t t = 0;
	for (t; t < this->clientes.size(); t++) {

		if (this->clientes.at(t)->getNome() == nomeCli) {
			exists = true;
			break;
		}

	}

	if (exists) {
		//removing 2nd titular
		for (size_t t = 0; t < this->clientes.size(); t++) {

			for (size_t k = 0; k < this->clientes.at(t)->getContas().size();
					k++)

				if (this->clientes.at(t)->getContas().at(k)->getTitular2()
						!= nullptr)

					if (this->clientes.at(t)->getContas().at(k)->getTitular2()->getNome()
							== nomeCli)

						this->clientes.at(t)->getContas().at(k)->setTitular2(
								nullptr);

		}

		for (size_t i = 0; i < this->clientes.at(t)->getContas().size(); i++) {

			if (this->clientes.at(t)->getContas().at(i)->getTitular2()
					== nullptr) {
				leftovers.push_back(this->clientes.at(t)->getContas().at(i));

			}

			else
				this->clientes.at(t)->getContas().at(i)->getTitular2()->adicionaConta(
						this->clientes.at(t)->getContas().at(i));

			//
			//

		}

	}

	this->clientes.at(t)->getContas().clear();
	this->clientes.erase(this->clientes.begin() + t);

	return leftovers;
}


bool Agencia::operator <(const Agencia & lhs){

	float moneis1 = 0;
	float moneis2 = 0;
	float peepz1 = this->clientes.size();
	float peepz2 = lhs.clientes.size();

	if(peepz1 == 0)
		return true;
	if(peepz2 == 0)
		return false;


	for(size_t t = 0; t < this->clientes.size(); t++){
		for (size_t k = 0; k < this->clientes.at(t)->getContas().size(); k++){
			moneis1 += this->clientes.at(t)->getContas().at(k)->getSaldo();
		}
	}

	for(size_t t = 0; t < lhs.clientes.size(); t++){
			for (size_t k = 0; k < lhs.clientes.at(t)->getContas().size(); k++){
				moneis2 += lhs.clientes.at(t)->getContas().at(k)->getSaldo();
			}
		}

	float ratio1 = moneis1/peepz1;
	float ratio2 = moneis2/peepz2;

	return ratio1 < ratio2;
}


float Agencia::operator() (string nomeCli){

	float sum = 0;
	bool exists = false;

	for (size_t t = 0; t < this->clientes.size(); t++){

		if(this->clientes.at(t)->getNome() == nomeCli){
			exists = true;
			for (size_t k = 0; k < this->clientes.at(t)->getContas().size(); k++){
				sum += this->clientes.at(t)->getContas().at(k)->getSaldo();
			}
			break;
		}

	}

	if (exists == false)
		return -1;

	return sum;

}


void Agencia::setGerenteID(int IDinicio){
	Gerente::setID_PROVIDER(IDinicio);
}

void Agencia::adicionaGerente(string nomeGer){

	Gerente * new_one = new Gerente(nomeGer);

	this->gerentes.push_back(*new_one);

}

//Gerente

int Gerente::id_provider = 0;
int Gerente::getID() const
{ return ID; }

string Gerente::getNome() const
{ return nome; }

void Gerente::setID_PROVIDER(int ID){
	Gerente::id_provider = ID;
}

Gerente::Gerente(string nm) : ID(id_provider++), nome(nm){};

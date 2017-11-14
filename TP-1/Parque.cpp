#include "Parque.h"
#include <vector>
#include <algorithm>

using namespace std;

ParqueEstacionamento::ParqueEstacionamento(unsigned int lot,
		unsigned int nMaxCli) : lotacao {lot}, numMaximoClientes {nMaxCli} {
			this-> vagas = lot;
		}
unsigned int ParqueEstacionamento::getNumLugares() const{
					return this->lotacao;
				}
				unsigned int ParqueEstacionamento::getNumMaximoClientes() const{
					return this->numMaximoClientes;
				}

int ParqueEstacionamento::posicaoCliente(const string & nome) const{
					for(unsigned int i = 0; i < this->clientes.size(); i++)
						if(clientes.at(i).nome == nome)
							return i;
					return -1;
				}
bool ParqueEstacionamento::adicionaCliente(const string & nome){
			if (this->clientes.size() < this->numMaximoClientes){
				InfoCartao p1;
				p1.nome = nome;
				p1.presente = false;
				this->clientes.push_back(p1);
				return true;
			}
		return false;
}


bool ParqueEstacionamento::entrar(const string & nome){
	for (unsigned int i = 0; i < this->clientes.size(); i++){
		if (clientes.at(i).nome == nome){
			if (clientes.at(i).presente == true)
				return false;
			else{
				if (vagas > 0){
					--vagas;
					clientes.at(i).presente = true;
					return true;
				}
			}
		}
	}
	return false;
}


bool operator== (const InfoCartao & p1, const InfoCartao & p2){
	if (p1.nome == p2.nome && p1.presente == p2.presente)
		return true;
	return false;
}

bool ParqueEstacionamento::retiraCliente(const string & nome){
	for (unsigned int i = 0; i < this->clientes.size(); i++){
		if (clientes.at(i).nome == nome){
			if (clientes.at(i).presente == true)
				return false;
			else{
				clientes.erase(remove(clientes.begin(), clientes.end(), clientes.at(i)), clientes.end());
				return true;
			}

	}
	}
	return false;
}

bool ParqueEstacionamento::sair(const string & nome){
	for (unsigned int i = 0; i < this->clientes.size(); i++){
		if (clientes.at(i).nome == nome && clientes.at(i).presente == true){
			clientes.at(i).presente = false;
			++vagas;
			return true;
		}
	}
	return false;
}


unsigned int ParqueEstacionamento::getNumLugaresOcupados() const{
	int counter = 0;
	for (unsigned int i = 0; i < this->clientes.size(); i++){
		if(clientes.at(i).presente == true)
			counter++;

	}
	return counter;
}

unsigned int ParqueEstacionamento::getNumClientesAtuais() const{
	return this->clientes.size();
}

const ParqueEstacionamento & ParqueEstacionamento::operator += (const
 ParqueEstacionamento & p2){

	for (unsigned int i = 0; i < p2.clientes.size(); i++){


	if (this->clientes.size() < this->numMaximoClientes){
		this->clientes.push_back(p2.clientes.at(i));

	}
	}

	return (*this);
}

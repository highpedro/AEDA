#include <queue>
#include <cstdlib>
#include "Balcao.h"
#include "exceptions.h"

using namespace std;


Cliente::Cliente() {
	numPresentes = (rand() % 5) +1;
}


int Cliente::getNumPresentes() const {
	return numPresentes;
}

queue<Cliente> Balcao::getClientes() const{
	return clientes;
}

Balcao::Balcao(int te): tempo_embrulho(te) {
	this->tempo_atual = 0;
	this->prox_chegada = (rand() % 20) +1;
	this->prox_saida = 0;
	this->clientes_atendidos = 0;
}      


void Balcao:: proximoEvento()
{
	if (this->clientes.empty()){
		tempo_atual = this->prox_chegada;
		Balcao::chegada();
		return;
	}


	if (this->prox_chegada <= this->prox_saida){
		tempo_atual = this->prox_chegada;
		Balcao::chegada();
	}
	else{
		tempo_atual = this->prox_saida;
		Balcao::saida();
	}

}


void Balcao::chegada()
{
	Cliente * newCli = new Cliente();

	if (this->clientes.empty())
		this->prox_saida = this->tempo_atual + newCli->getNumPresentes() * this->tempo_embrulho;

	this->clientes.push(*newCli);

	this->prox_chegada = rand() % 20 +1;

	cout << "tempo= " << this->tempo_atual << "\nchegou novo cliente com " << newCli->getNumPresentes() << " presentes\n";


}   


void Balcao::saida()
{
	Cliente proxCli;
	try{
	 proxCli = Balcao::getProxCliente();
	}
	catch(const FilaVazia & e){
		cout << e.getMsg() << endl;
	}

	this->clientes.pop();

	this->prox_saida = this->tempo_atual + proxCli.getNumPresentes()*this->tempo_embrulho;

	cout << "tempo= " << tempo_atual << endl << "saiu cliente com " << proxCli.getNumPresentes() << " presentes\n";

	++this->clientes_atendidos;
}


int Balcao::getTempoAtual() const { return tempo_atual; }


int Balcao::getProxChegada() const { return prox_chegada; }


ostream & operator << (ostream & out, const Balcao & b1)
{
	out << "Nr de clientes atendidos: " << b1.getClientesAtendidos() << endl;
	out << "Nr de clientes em espera: " << b1.getClientes().size() << endl;
	return out;
}


int Balcao::getTempoEmbrulho() const {
	return this->tempo_embrulho;
}


int Balcao::getProxSaida() const {
	return this->prox_saida;
}


int Balcao::getClientesAtendidos() const {
	return this->clientes_atendidos;
}


Cliente & Balcao::getProxCliente() {
	if(this->clientes.empty())
		throw FilaVazia();
	return this->clientes.front();
}

      

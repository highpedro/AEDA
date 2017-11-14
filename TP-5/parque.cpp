#include "parque.h"
#include "insertionSort.h"
#include "sequentialSearch.h"
#include <vector>

using namespace std;

bool InfoCartao::operator ==(const InfoCartao & ic1) const{

	return this->nome == ic1.nome;

}

bool InfoCartao::operator <(const InfoCartao & ic1) const{
	if (this->frequencia == ic1.frequencia)
		return this->nome < ic1.nome;
	else
		return this->frequencia > ic1.frequencia;
}

ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli):
	lotacao(lot), numMaximoClientes(nMaxCli) {
    numClientes = 0;
    vagas=lot; 
}

ParqueEstacionamento::~ParqueEstacionamento() {}

vector<InfoCartao> ParqueEstacionamento::getClientes() const { return clientes; }


bool ParqueEstacionamento::adicionaCliente(const string & nome)
{
 	if ( numClientes == numMaximoClientes ) return false;
	if ( posicaoCliente(nome) != -1 ) return false;
	InfoCartao info;
	info.nome = nome;
    info.presente = false;
    info.frequencia = 0;  // a fazer
	clientes.push_back(info);
	numClientes++;
	return true;
}
 
bool ParqueEstacionamento::retiraCliente(const string & nome)
{
	for (vector<InfoCartao>::iterator it = clientes.begin(); it != clientes.end(); it++)
		if ( it->nome == nome ) {
			if ( it->presente == false ) {
				clientes.erase(it);
				numClientes--;
				return true;
			}
			else return false;
		}
	return false;
}
  
unsigned int ParqueEstacionamento::getNumLugares() const
{
	return lotacao;
}
                   
unsigned int ParqueEstacionamento::getNumLugaresOcupados() const
{
	return lotacao-vagas;
}

bool ParqueEstacionamento::entrar(const string & nome)
{
	if ( vagas == 0 ) return false;
	int pos = posicaoCliente(nome);
	if ( pos == -1 ) return false;
	if ( clientes[pos].presente == true ) return false;
	clientes[pos].presente = true;
	clientes.at(pos).frequencia++;
	vagas--;
	return true;
}

bool ParqueEstacionamento::sair(const string & nome)
{
	int pos = posicaoCliente(nome);
	if ( pos == -1 ) return false;
	if ( clientes[pos].presente == false ) return false;
	clientes[pos].presente = false;
	vagas++;
	return true;
}

// a alterar
int ParqueEstacionamento::posicaoCliente(const string & nome) const {
	InfoCartao inf1;

	inf1.nome = nome;

	return sequentialSearch(this->clientes,inf1);

}

int ParqueEstacionamento::getFrequencia(const string &nome) const{

	InfoCartao inf1;

	inf1.nome = nome;

	int indice = sequentialSearch(this->clientes, inf1);

	if (indice == -1)
		throw ClienteNaoExistente(nome);

	return clientes.at(indice).frequencia;


}

void ParqueEstacionamento::ordenaClientesPorFrequencia(){
	insertionSort(this->clientes);
}

vector<string> ParqueEstacionamento::clientesGamaUso(int n1, int n2){
	vector<string> result;

	insertionSort(this->clientes);


	for(size_t t = 0; t < this->clientes.size(); t++){
		if (this->clientes.at(t).frequencia >= n1 && this->clientes.at(t).frequencia <= n2)
			result.push_back(this->clientes.at(t).nome);
	}



	return result;


}

void ParqueEstacionamento::ordenaClientesPorNome() {
	for (unsigned int p = 1; p < this->clientes.size(); p++)
	    {
	    	InfoCartao tmp = this->clientes[p];
	    	int j;
	    	for (j = p; j > 0 && tmp.nome < this->clientes[j-1].nome; j--)
	    		this->clientes[j] = this->clientes[j-1];
	    	this->clientes[j] = tmp;
	    }
}

ostream & operator <<(ostream & os, const ParqueEstacionamento & pe){
	vector<InfoCartao> clientes = pe.getClientes();
	for (size_t t = 0; t < clientes.size(); t++){
		os << clientes.at(t).nome << '\t' << clientes.at(t).presente << '\t' << clientes.at(t).frequencia << endl;
	}

	return os;
}


InfoCartao ParqueEstacionamento::getClienteAtPos(vector<InfoCartao>::size_type p) const{

	if (p < 0 || p >= this->clientes.size())
		throw PosicaoNaoExistente(p);

	return clientes.at(p);

}


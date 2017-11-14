/*
 * Agencia.h
 */

#ifndef AGENCIA_H_
#define AGENCIA_H_

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Cliente;

class Conta {
protected:
  int numConta;
  float saldo;
  int numTransacoes;
  Cliente *titular2;
public:
	Conta(int nConta, float sd=0, int nTrans=0);
	Conta(const Conta & lhs);
	virtual ~Conta();
	int getNumConta() const;
	float getSaldo() const;
	int getNumTransacoes() const;
	Cliente *getTitular2() const;
	void setTitular2(Cliente *cli2);
	virtual bool levantamento(float valor) = 0;
	virtual void deposito(float valor) = 0;
	virtual bool isNormal() = 0;

};

class Normal: public Conta {
public:
   Normal(int nConta, float sd=0, int nTrans=0);
   bool levantamento(float valor);
   void deposito(float valor);
   bool isNormal() {return true;};
   ~Normal();

};


class DeOperacao: public Conta {
  float taxa;
public:
  DeOperacao(int nConta, float tx, float sd=0, int nTrans=0);
  bool levantamento(float valor);
  void deposito(float valor);
  bool isNormal() {return false;};
  ~DeOperacao();
};


class Cliente {
  string nome;
  vector<Conta *> contas;
public:
  Cliente(string nm);
  string getNome() const;
  vector<Conta *> getContas() const;
  void adicionaConta(Conta *c1);

};


class Gerente {
  int ID;
  string nome;
  vector<Cliente *> meusClientes;
  static int id_provider;
public:
  Gerente(string nm);
  int getID() const;
  string getNome() const;
  static void setID_PROVIDER(int ID);

};


class Agencia {
  string designacao;
  vector<Cliente *> clientes;
  vector<Gerente> gerentes;
public:
  Agencia(string desig);
  string getDesignacao() const;
  vector<Cliente *> getClientes() const;
  vector<Gerente> getGerentes() const;
  void adicionaCliente(Cliente *cli1);
  Conta * levantamento (string nomeCli, float valor);
  float fimMes() const;
  vector <Conta *> removeCliente(string nomeCli);
  bool operator< (const Agencia & lhs);
  float operator() (string nomeCli);
  void setGerenteID(int IDinicio);
  void adicionaGerente(string nomeGer);

};



#endif /* AGENCIA_H_ */

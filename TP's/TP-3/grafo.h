#include <iostream>
#include <vector>
#include <string>

using namespace std;

/**
 * Versao da classe generica Grafo usando a classe vector
 */

template <class N, class A> class Aresta;

template <class N> class NoRepetido;
template <class N> class NoInexistente;
template <class N> class ArestaRepetida;

template <class N, class A>
class No {
public:
	N info;
	vector< Aresta<N,A> > arestas;
	No(N inf) {
		info = inf;
	}
};

template <class N, class A>
class Aresta {
public:
	A valor;
	No<N,A> *destino;
	Aresta(No<N,A> *dest, A val) {
		valor = val;
		destino = dest;
	}
};

template <class N, class A> 
class Grafo { 
	vector< No<N,A> *> nos;
  public: 
    Grafo();
    ~Grafo(); 
    Grafo & inserirNo(const N &dados);
    Grafo & inserirAresta(const N &inicio, const N &fim, const A &val);
    Grafo & eliminarAresta(const N &inicio, const N &fim);
    A & valorAresta(const N &inicio, const N &fim);
    int numArestas(void) const;
    int numNos(void) const;
    void imprimir(std::ostream &os) const; 
};

//IMPLEMENTATIONS================================
template <class N, class A>
Grafo<N, A>::Grafo(){};

template <class N, class A>
Grafo<N,A>::~Grafo(){
	for(auto it = this->nos.begin(); it != this->nos.end(); it++){
		delete (*it);
	}
	this->nos.clear();
}

template<class N, class A>
int Grafo<N,A>::numNos() const{
	return (int)this->nos.size();
}


template<class N, class A>
int Grafo<N,A>::numArestas() const{
	int numA = 0;

	for (auto it = this->nos.begin(); it != this->nos.end(); it++){
		numA += (*it)->arestas.size();
	}

	return numA;
}

template <class N, class A>
Grafo<N,A> & Grafo<N,A>::inserirNo(const N & dados){


	for (auto it = this->nos.begin(); it != this->nos.end(); it++){

		if (   (*it)->info == dados)
			throw NoRepetido<N>(dados);
	}

	No<N, A> * new_No = new No<N,A>(dados);

	this->nos.push_back(new_No);

	return *this;
}

template <class N, class A>
Grafo<N,A> & Grafo<N,A>::inserirAresta(const N &inicio, const N &fim, const A &val){
	No<N,A> * startNo = nullptr;
	No<N,A> * endNo = nullptr;
	for (auto it = this->nos.begin(); it != this->nos.end(); it++){
		if ((*it)->info == inicio)
			startNo = (*it);
		if ((*it)->info == fim)
			endNo = (*it);
	}

	if(startNo == nullptr) //the starting node was not found
		throw NoInexistente<N> (inicio);
	if(endNo == nullptr) //the ending node was not found, thus the aresta does not exist
		throw NoInexistente<N> (fim);


	for(auto it = startNo->arestas.begin(); it != startNo->arestas.end(); it++){
		if( it->destino == endNo)
			throw ArestaRepetida<N>(inicio, fim);
	}


	//startNo->arestas.em


	return *this;
}





//=============================================

template <class N, class A> 
std::ostream & operator<<(std::ostream &out, const Grafo<N,A> &g);

// excecao  NoRepetido
template <class N>
class NoRepetido
{
public:
   N info;
   NoRepetido(N inf) { info=inf; }
};



template <class N>
std::ostream & operator<<(std::ostream &out, const NoRepetido<N> &no)
{ out << "No repetido: " << no.info; return out; }


// excecao NoInexistente
template <class N>
class NoInexistente {
public:
	N info;
	NoInexistente(N inf) {
		info = inf;
	}
};



template <class N>
std::ostream & operator<<(std::ostream &out, const NoInexistente<N> &ni)
{ out << "No inexistente: " << ni.info; return out; }


template <class N>
class ArestaRepetida{
public:
	N start;
	N end;
	ArestaRepetida(N start, N end) : start(start), end(end){};

};

template <class N>
ostream & operator<<(ostream & out, const ArestaRepetida<N> &ar)
{
	out << "Aresta Repetida: " << ar.start << ", " << ar.end;
	return out;
}








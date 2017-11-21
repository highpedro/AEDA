/*
 * zoo.h
 */

#ifndef ZOO_H_
#define ZOO_H_

#include <string>
#include <vector>
#include <iostream>
#include <climits>

using namespace std;

class Animal;


class Veterinario {
	string nome;
	long codOrdem;
	bool hasAnimal;
	vector <Animal *> vetAnimals;
public:
	Veterinario(string nome, long cod);
	string getNome() const;
	long getCod() const;
	void addAnimal(Animal *a1);
	bool hasAnimals() const;
	void ChangeAnimalsTo(Veterinario * v2);
};

class Animal {
protected:
	string nome;
	int idade;
	Veterinario *vet;
	static int maisJovem;
public:
	Animal(string nome, int idade);
	virtual ~Animal(){};
	string getNome() const;
	int getIdade() const;
	virtual bool eJovem() const = 0;
	virtual string getInformacao() const =0;
	static int getMaisJovem();
	void setVet(Veterinario *v1);

};



class Cao: public Animal {
	string raca;
public:
	Cao(string nome, int idade, string raca);
	bool eJovem() const;
	string getInformacao() const;

};



class Voador {
	int velocidade_max;
	int altura_max;
public:
	Voador(int vmax, int amax);
	virtual ~Voador(){};
	int getVMax() const;
	int getAMax() const;

};



class Morcego: public Animal, public Voador {
public:
	Morcego(string nome, int idade, int vmax, int amax);
	bool eJovem() const;
	string getInformacao() const;


};


class Zoo {
	vector<Animal *> animais;
	vector<Veterinario *> veterinarios;
public:
	int numAnimais() const;
	int numVeterinarios() const;
	void adicionaAnimal(Animal *a1);
	string getInformacao() const;
	bool animalJovem(string nomeA);
	void alocaVeterinarios(istream &isV);

	bool removeVeterinario(string nomeV);
	//bool operator < (Zoo& zoo2) const;
};


#endif /* ZOO_H_ */

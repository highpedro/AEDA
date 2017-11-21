#include "zoo.h"
#include <sstream>
#include <algorithm>


string Animal::getNome() const {
	return nome;
}

int Animal::getIdade() const{
	return idade;
}


string Veterinario::getNome() const {
	return nome;
}

long Veterinario::getCod() const{
	return this->codOrdem;
}


int Zoo::numAnimais() const {
	return animais.size();
}

int Zoo::numVeterinarios() const {
	return veterinarios.size();
}

//=======VET

Veterinario::Veterinario(string nome, long cod) {
	this->nome = nome;
	this->codOrdem = cod;
}

void Veterinario::addAnimal(Animal * a1){
	this->vetAnimals.push_back(a1);
}

bool Veterinario::hasAnimals() const  {

	if(this->vetAnimals.size())
		return true;

	return false;

}

void Veterinario::ChangeAnimalsTo(Veterinario *v2){

	vector<Animal *>::iterator it;

	for( it = this->vetAnimals.begin(); it != this->vetAnimals.end(); it++ ){
			(*it)->setVet(v2);
			v2->addAnimal(*it);
	}
}


//=======ANIMAL

int Animal::maisJovem = INT_MAX;

Animal::Animal(string nome, int idade) {
	this->nome = nome;
	this->idade = idade;

	if(this->idade < Animal::maisJovem)
		Animal::maisJovem = this->idade;

	this->vet = nullptr;


}

int Animal::getMaisJovem() {
	return Animal::maisJovem;
}

void Animal::setVet(Veterinario *v1){
	this->vet = v1;
}

//======CAO

Cao::Cao(string nome, int idade, string raca) : Animal(nome, idade) {
	this->raca = raca;
}

bool Cao::eJovem() const {
	if (this->idade < 5)
		return  true;
	return false;
}

string Cao::getInformacao() const{
	string info;
	if(this->vet == nullptr)
		info = this->nome + ", " + to_string(this->idade) + ", " + this->raca;
	else
		info = this->nome + ", "+ to_string(this->idade) + ", " + this->vet->getNome() + ", " + to_string(this->vet->getCod()) + ", " + this->raca;

	return info;
}

//======VOADOR

Voador::Voador(int vmax, int amax) {
	this->velocidade_max = vmax;
	this->altura_max = amax;
}


//=======MORCEGO

Morcego::Morcego(string nome, int idade, int vmax, int amax) : Animal(nome, idade), Voador(vmax, amax) {
	;
}


bool Morcego::eJovem() const{
	if(this->idade < 4)
		return true;
	return false;
}



string Morcego::getInformacao() const{
	string info;
	info = this->nome +", " + to_string(this->idade) + ", " + to_string(this->getVMax()) + ", " + to_string(this->getAMax());
	return info;
}

//======VOADOR

int Voador::getAMax() const{
	return this->altura_max;
}

int Voador::getVMax() const{
	return this->velocidade_max;
}

//======ZOO
void Zoo::adicionaAnimal(Animal *a1){
	this->animais.push_back(a1);
}


bool Zoo::animalJovem(string nomeA){
	for (size_t t = 0; t < this->animais.size(); t++){
		if(this->animais.at(t)->getNome() == nomeA && this->animais.at(t)->eJovem())
			return true;
	}
	return false;
}

string Zoo::getInformacao() const{
	string info;
	for (size_t t = 0; t < this->animais.size(); t++){
		info += animais.at(t)->getInformacao() + '\n';
	}

	return info;
}


void Zoo::alocaVeterinarios(istream &isV){
	while(!isV.eof()){
		string nome;
		getline(isV, nome);
		string tmp_cod;
		getline(isV, tmp_cod);
		long cod = stol(tmp_cod);
		Veterinario *v1 = new Veterinario { nome, cod };

		this->veterinarios.push_back(v1);
	}

	int AnimalSize = this->animais.size();
	int VetSize = this->veterinarios.size();

	if (VetSize >= AnimalSize){
		for(size_t t = 0; t < this->animais.size(); t++){
			this->animais.at(t)->setVet(this->veterinarios.at(t));
			this->veterinarios.at(t)->addAnimal(this->animais.at(t));
		}
	}
	else
		for (size_t t = 0; t < this->animais.size(); t++){
			this->animais.at(t)->setVet(this->veterinarios.at(t % this->veterinarios.size()));
			this->veterinarios.at(t % this->veterinarios.size())->addAnimal(this->animais.at(t));
		}


}


bool Zoo::removeVeterinario(string nomeV){

		auto it = find_if(this->veterinarios.begin(), this->veterinarios.end(), [nomeV](Veterinario * obj)
				{return obj->getNome() == nomeV; } );

		if (it != this->veterinarios.end() ){

			if((*it)->hasAnimals()){
				auto last = prev(this->veterinarios.end());
				vector<Veterinario *>::iterator nextVet;
				if(it != last){
					nextVet = it + 1;
				}
				else{
					nextVet = this->veterinarios.begin();
				}

				(*it)->ChangeAnimalsTo(*nextVet);
			}


		this->veterinarios.erase(it);
		return true;
		}

		return false;
}





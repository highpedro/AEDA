#include "ClubeVideo.h"
#include <iostream>
using namespace std;
#include <sstream>

ostream& operator<<(ostream& os, const Filme& umFilme) {
	os << umFilme.getTitulo() << " " << umFilme.getEmprestimos();
	return os;
}

ostream& operator<<(ostream& os, const PedidoCliente& pc) {
	os << "Cliente " << pc.getNomeCliente() << " em espera para "
			<< pc.getTituloFilme() << endl;
	return os;
}

ostream& operator<<(ostream& os, const Cliente& c1) {
	os << c1.getNome() << " tem " << c1.getFilmesEmprestados().size()
			<< " filmes!\n";
	return os;
}

//
// Incluir abaixo a implementa��o das suas fun��es
//

bool ClubeVideo::existeCliente(string umNome) const {

	for (auto it = this->clientes.begin(); it != this->clientes.end(); it++) {
		if ((*it).getNome() == umNome)
			return true;
	}

	return false;
}

bool ClubeVideo::existeFilme(string umTitulo) const {

	for (auto it = this->filmes.begin(); it != this->filmes.end(); it++) {
		if ((*it).getTitulo() == umTitulo)
			return true;
	}

	for (auto it = this->clientes.begin(); it != this->clientes.end(); it++) {

		if (!(*it).getFilmesEmprestados().empty()) {

			stack<Filme> tempFilm = (*it).getFilmesEmprestados();

			while (!tempFilm.empty()) {
				if (tempFilm.top().getTitulo() == umTitulo)
					return true;
				tempFilm.pop();
			}

		}

	}

	return false;
}

string ClubeVideo::imprimirFilmes() const {

	string toReturn = "";

	stringstream info(toReturn);

	for (auto it = this->filmes.begin(); it != this->filmes.end(); it++) {
		info << (*it) << endl;
	}

	for (auto it = this->clientes.begin(); it != this->clientes.end(); it++) {

		if (!(*it).getFilmesEmprestados().empty()) {

			stack<Filme> tempFilm = (*it).getFilmesEmprestados();

			while (!tempFilm.empty()) {

				info << (tempFilm.top()) << endl;

				tempFilm.pop();
			}

		}

	}

	toReturn = info.str();

	return toReturn;

}

bool cmpTitle(const Filme & rhs, const Filme & lhs) {

	return rhs.getTitulo() < lhs.getTitulo();
}

list<string> ClubeVideo::titulosDisponiveis() const {

	list<string> result;

	if (this->filmes.empty())
		return result;

	auto it = this->filmes.begin();

	//placing the first movie there
	result.push_back((*it).getTitulo());

	it++; //going to the next movie and entering the cicle

	if (it == this->filmes.end()) //if the list has only one element
		return result;

	for (; it != this->filmes.end(); it++) {

		if (find(result.begin(), result.end(), (*it).getTitulo())
				== result.end())
			result.push_back((*it).getTitulo());

	}

	result.sort(cmpTitle);

	return result;

}

bool ClubeVideo::tituloDisponivel(string umTitulo) const {

	for (auto it = this->filmes.begin(); it != this->filmes.end(); it++) {

		if ((*it).getTitulo() == umTitulo)
			return true;

	}

	return false;
}

string ClubeVideo::imprimirListaDeEspera() const {

	vector<string> organize;

	string toReturn = "";

	queue<PedidoCliente> temp = this->pedidos;

	while (!temp.empty()) {

		organize.push_back(temp.front().getTituloFilme());
		temp.pop();
	}

	sort(organize.begin(), organize.end());

	for (size_t t = 0; t < organize.size(); t++) {
		toReturn += organize.at(t) + "\n";
	}

	return toReturn;
}

void ClubeVideo::alugar(string umNome, string umTitulo) {

	if (!this->existeFilme(umTitulo))
		throw FilmeInexistente(umTitulo);
	else {

		if (!this->existeCliente(umNome))
			this->clientes.emplace_back(umNome);

		auto itCli = find_if(this->clientes.begin(), this->clientes.end(),
				[umNome](Cliente cli)
				{	if(cli.getNome() == umNome)
					return true;
					else
					return false;

				});
		auto itFil = find_if(this->filmes.begin(), this->filmes.end(),
				[umTitulo](Filme film)
				{
					if (film.getTitulo() == umTitulo)
					return true;
					else
					return false;
				});

		if (itFil != this->filmes.end()) {

			(*itFil).addEmprestimos();
			(*itCli).addFilme((*itFil));
			this->filmes.erase(itFil);
		}
		//the film ain't available ma boi, too bad
		else {

			PedidoCliente fodeu(umNome, umTitulo);

			this->pedidos.push(fodeu);

		}

	}
}

void ClubeVideo::devolver(string umNome, string umTitulo) {

	auto itCli = find_if(this->clientes.begin(), this->clientes.end(),
			[umNome](Cliente cli)
			{	if(cli.getNome() == umNome)
				return true;
				else
				return false;

			});

	Filme voltou = (*itCli).devolver(umTitulo);



	queue<PedidoCliente> temp;

	bool someoneIsWaiting = false;

	string cliName;

	if(this->pedidos.empty()){
		this->filmes.push_back(voltou);
		return;
	}

	queue<PedidoCliente> nemsei = this->pedidos;

	while (!this->pedidos.empty()) {

		if (this->pedidos.front().getTituloFilme() == umTitulo) {
			someoneIsWaiting = true;
			cliName = this->pedidos.front().getNomeCliente();
		} else {
			temp.push(this->pedidos.front());
		}

		this->pedidos.pop();

	}



	while (!temp.empty()) {
		this->pedidos.push(temp.front());
		temp.pop();
	}

	if (someoneIsWaiting) {

		auto it = find_if(this->clientes.begin(), this->clientes.end(),
				[cliName](Cliente cli)
				{	if(cli.getNome() == cliName)
					return true;
					else
					return false;

				});

		voltou.addEmprestimos();

		(*it).addFilme(voltou);

	} else {
		this->filmes.push_back(voltou);
	}



}

#include <cstddef>
//FAUTE manque cstddef
#include <ostream>
//FAUTE manque ostream
#include <string>
//FAUTE manque string
#include "List.h"
//FAUTE manque "List.h"

namespace pr {

// ******************* Chainon
Chainon::Chainon (const std::string & data, Chainon * next):data(data),next(next) {};

size_t Chainon::length() {
	size_t len = 1;
	if (next != nullptr) {
		len += next->length();

	}
	return len;
}
//FAUTE manque const probleme de signature 
void Chainon::print (std::ostream & os) const{
	os << data ;
	if (next != nullptr) {
		os << ", ";
		next->print(os);
	}
	
}

// ******************  List
const std::string & List::operator[] (size_t index) const  {
	Chainon * it = tete;
	for (size_t i=0; i < index ; i++) {
		if (it->next == nullptr){
			break;
		}else{
		it = it->next;
		}
	}
	return it->data;
}

void List::push_back (const std::string& val) {
	if (tete == nullptr) {
		tete = new Chainon(val);
	} else {
		Chainon * fin = tete;
		while (fin->next) {
			fin = fin->next;
		}
		fin->next = new Chainon(val);
	}
}
//FAUTE linker definition déja defini
void List::push_front (const std::string& val) {
	tete = new Chainon(val,tete);
}
//FAUTE manque List:: probleme de signature 
bool List::empty() {
	return tete == nullptr;
}

size_t List::size() const {
	if (tete == nullptr) {
		return 0;
	} else {
		return tete->length();
	}
}

} // namespace pr
//FAUTE pas inclut dans le namespace pr
namespace pr {
std::ostream & operator<< (std::ostream & os, const pr::List & vec)
{
	os << "[";
	if (vec.tete != nullptr) {
		vec.tete->print (os) ;
	}
	os << "]" << std::endl;
	return os;
}}


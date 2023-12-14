#include "List.h"
#include <string>
#include <iostream>
#include <cstring>

int main () {

	std::string abc = "abc";
	char * str = new char [3];
	str[0] = 'a';
	str[1] = 'b';
	str[2] = 'c';
	size_t i = 0;
	//Fuite memoire car on compare plus que l'on devrait
	if (!std::strncmp (str, abc.c_str(),3)) {
		std::cout << "Equal !";
	}

	pr::List list;
	list.push_front(abc);
	list.push_front(abc);

	std::cout << "Liste : " << list << std::endl;
	std::cout << "Taille : " << list.size() << std::endl;

	// Affiche à l'envers
	for (i= list.size() ; i > 0 ; --i) {
		std::cout << "elt " << i-1 << ": " << list[i-1] << std::endl;
	}

	//FAUTE car on essaie de supprimé un char** alors que c'est un char*
	/* liberer les char de la chaine
	for (char *cp = str ; *cp ; cp++) {
		//delete cp;
	}*/
	// et la chaine elle meme
	abc.erase();
	//Fuite memoire car on supprime que str et pas son contenu
	//delete str;
	delete[] str;

}

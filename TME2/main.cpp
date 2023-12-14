#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <vector>
#include "HashMap.hpp"

int main () {
	using namespace std;
	using namespace std::chrono;
	using namespace pr;

	ifstream input = ifstream("WarAndPeace.txt");

	auto start = steady_clock::now();
	cout << "Parsing War and Peace" << endl;

	size_t nombre_lu = 0;
	HashMap<string,size_t> hp(100); 
	//vector<HashMap<const string,size_t>> hp;

	//vector<pair<string,size_t>> nombre_rec;
	//nombre_rec.push_back(make_pair("war",0));
	//nombre_rec.push_back(make_pair("peace",0));
	//nombre_rec.push_back(make_pair("toto",0));
	//hp.put("war",0);
	//hp.put("peace",0);
	//hp.put("toto",0);
	bool unique = true;

	//prochain mot lu
	string word;
	// une regex qui reconnait les caractères anormaux (négation des lettres)
	regex re( R"([^a-zA-Z])");
	while (input >> word) {
		// élimine la ponctuation et les caractères spéciaux
		word = regex_replace ( word, re, "");
		// passe en lowercase
		transform(word.begin(),word.end(),word.begin(),::tolower);

		//Sans HashMap
		/*for (auto & mot : nombre_rec){
			if (mot.first == word){
				mot.second++;
				//unique = false;
			}
		}*/

		//Avec HashMap
		for (auto & listHP : hp.buckets){
			for (auto & key_hp : listHP){
				if (key_hp.key == word){
					key_hp.value++;
					unique = false;
					break;
				}
			}
		}
		if (unique){
			hp.put(word,1);
		}
		unique = true;
		// word est maintenant "tout propre"
		/*if (nombre_lu % 100 == 0)
			// on affiche un mot "propre" sur 100
			cout << nombre_lu << ": "<< word << endl;
		*/
		nombre_lu++;
	}
	input.close();

	cout << "Finished Parsing War and Peace" << endl;

	auto end = steady_clock::now();
    cout << "Parsing took "
              << duration_cast<milliseconds>(end - start).count()
              << "ms.\n";

    /*cout << "Found a total of " << nombre_rec.size() << " differents words." << endl;
	for (const auto & mot : nombre_rec){
		cout << mot.first << " = " << mot.second << " ";
	}*/
	cout << "Taille de HashMap = " << hp.size();
	cout << endl;
    return 0;
}



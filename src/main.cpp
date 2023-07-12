#include "Jeu.h"
#include <cassert>


// LE QUART DE SIGNE !!
/*
 /* Le jeu utilise la structure joueur_donnees pour g�rer les joueurs et effectuer toutes les op�rations sur eux en utilisant get_data() et update_data()  garde la structure de joueur dans un tableau, une fois qu'une infos_joueur est ajout� au jeu, le jeu initialisera une structure de joueur dans un emplacement de m�moire sp�cifi�,
 -toutes les communications se font  travers la structure infos_joueur.
 - Ainsi, nous pouvons garder la structure de joueur utilis�e par le jeu, et la fonction principale ne passe qu'une structure de type infos_joueur.
 - le mot struct est un conteneur pour toutes les methodes dont nous avons besoin pour manipuler les cha�nes de caract�res.
- On peut lutiliser par exemple pour creer un simple cache pour le jeu ou  stocker une cha�ne pour un certain temps*/

//////////////////////////////////////////
 /** nous utilisons visual studio community pour developper ce jeu :
 * 1- ouvrir jeu_singe.sln avec visual studio
 * 2- nettoyer la solution et construire le projet vous pouvez utiliser f5 pour commencer la construction, (avec debug ou release)
 * 3- et allez a l'emplacement du dossier excutable
 * 4- verifiez que le dictionnaire est present
 * 5-lancer le jeu avec cmd monkey_game.exe avec les arguments du joueur H R H R ,exemple :
 * monkey_game.exe H R H R
 */


 ////Nommer le joueur :(numero + type
void namer(joueur_donnees&);

//pour tester, retirer // dans main pour voir les resultats.
void test();



int main(int argc, char** argv) try {
	//test();
	if (argc - 1 < 2) {
		throw std::exception("Veuillez entrer au moins deux joueurs.");
	}
	
	size_t playersCount = argc - 1;

	//init le jeu 
	jue monkeys_game(playersCount, "ods4.txt");

	for (int i = 1; i <= playersCount; ++i) {
		joueur_donnees data;
		data.number = i - 1;

		memset(data.type, 0, 2);

		data.type[0] = toupper(argv[i][0]);

		if (data.type[0] != 'H' and data.type[0] != 'R') {
			throw std::exception("invalid user type.");
		}
		//nommer le joueur
		namer(data);
		data.monkeys = .0;
		data.isLastRoundLoose = false;
		monkeys_game.add_new_player(data, i - 1);
	}

	//boucle du jeu
	monkeys_game.play();

	std::cin.get();

	return 0;
}
catch (std::exception& ex) {
	std::cerr << ex.what() << "\n";
}



void namer(joueur_donnees& data) {
	//Le buffer va permettre ti stocker le nom du joueur
	vecteur tmpWord;
	char umTostr[BUFFER_SIZE]; 
	memset(umTostr, 0, BUFFER_SIZE);
	snprintf(umTostr, BUFFER_SIZE, "%d", data.number + 1); 
	tmpWord.add_new_word(umTostr);
	tmpWord.add_new_word(data.type); //Rajouter la nature du joueur R ou H
	auto name = tmpWord.get();
	strcpy_s(data.PlayerName, sizeof data.PlayerName, name);//Stocker le nom final
}



//afin de voir les resultats des test , retirer // de main 
void test() {
	
	size_t playersCount = 10, casheSize = 512;
	jue testgame(playersCount, "ods4.txt");
	assert(testgame.playersCount == playersCount);
	assert(testgame.dict == "ods4.txt");
	assert(testgame.excludeCache.size() == 0);//embty cashe
	std::cout << "monkey_game init test: " << std::boolalpha << true << "\n";

	//tester la fonction qui permet de nommer les joueurs
	joueur_donnees data;
	data.number = 0;
	data.monkeys = 0.;
	data.isLastRoundLoose = false;
	memset(data.type, 0, 2);
	data.type[0] = 'H';
	namer(data);
	assert(strcmp(data.PlayerName, "1H") == 0);
	std::cout << "namer() test: " << std::boolalpha << true << "\n";

	//tester la fonction qui permet d'ajouter de nouveaux joueurs
	try {
		testgame.add_new_player(data, 20);
		std::cout << "add_new_player() test: " << std::boolalpha << false << "\n";
	}
	catch (...) {
		std::cout << "add_new_player() test: " << std::boolalpha << true << "\n";
	}

	//Tester la fonction is_word_found
	const char* wrd = "ISONIAZIDES";
	assert(testgame.is_word_found(wrd));
	assert(testgame.is_word_found("arandomword") == false);
	std::cout << "is_word_found() test: " << std::boolalpha << true << "\n";
	
	//tester testgame.excludeCache.is_word_exists
	assert(testgame.excludeCache.is_word_exists(wrd));
	std::cout << "testgame.excludeCache.is_word_exists() test: " << std::boolalpha << true << "\n";
	//test testgame.excludeCache.is_strig_equal
	assert(testgame.excludeCache.is_strig_equal(wrd, wrd));
	std::cout << "testgame.excludeCache.is_strig_equal() test: " << std::boolalpha << true << "\n";


	//tester testgame.excludeCache.is_word_exists
	assert(testgame.excludeCache.is_word_exists("ISON"));
	std::cout << "testgame.excludeCache.is_word_exists() test: " << std::boolalpha << true << "\n";
	std::cout << "word test: " << std::boolalpha << true << "\n";
	//Tester la fonction player
	joueur testPayer(data);
	assert(strcmp(testPayer.get_data().PlayerName, "1H") == 0);
	//tester la fonction qui renvoie les nouvelles informations:
	memset(data.PlayerName, 0, BUFFER_SIZE);
	strcpy_s(data.PlayerName, sizeof data.PlayerName, "2R");
	testPayer.update_data(data);
	assert(strcmp(testPayer.get_data().PlayerName, "2R") == 0);
	std::cout << "player test: " << std::boolalpha << true << "\n";

	//tster game.word_to_upper
	char* result = testgame.word_to_upper("abcd");
	assert(strcmp(result, "ABCD") == 0);
	delete result;
	result = nullptr;
	std::cout << "testgame.word_to_upper() test: " << std::boolalpha << true << "\n";

	//tester testgame.get_robot_word_in_mind
	testgame.curr_word.add_new_word("ABA");//the robot word in mind must be ABACA according to the dict ods4.txt
	char* rWord = testgame.get_robot_word_in_mind();
	assert(strcmp(rWord, "ABACA") == 0);
	delete rWord;
	rWord = nullptr;
	std::cout << "testgame.get_robot_word_in_mind() test: " << std::boolalpha << true << "\n";

	//testgame.is_word_found 
	assert(testgame.is_word_found("MAQUEREAUTE"));
	testgame.excludeCache.add_new_word("BOULOCHES");//this must be excluded now
	assert(testgame.is_word_found("BOULOCHES") == false);
	std::cout << "testgame.is_word_found() test: " << std::boolalpha << true << "\n";

	//testgame.is_word_real 
	testgame.curr_word.clear();
	testgame.curr_word.add_new_word("ABA");
	assert(testgame.is_word_real("ABACU"));
	assert(testgame.is_word_real("DBACU") == false);
	std::cout << "testgame.is_word_real() test: " << std::boolalpha << true << "\n";

	//testgame.get_last_round_looser 
	data.number = 2;
	data.isLastRoundLoose = true;
	testgame.add_new_player(data, data.number);
	assert(testgame.get_last_round_looser() == data.number);
	delete testgame.joueurs[data.number];
	testgame.joueurs[data.number] = nullptr;

	assert(testgame.get_last_round_looser() == -1);
	std::cout << "testgame.get_last_round_looser() test: " << std::boolalpha << true << "\n";

	std::cout << "integration test: " << std::boolalpha << true << "\n";
}


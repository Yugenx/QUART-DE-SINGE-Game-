#include "Jeu.h"

jue::jue(size_t playersCount, const char* dict) {
	joueurs = new joueur * [playersCount];
	this->playersCount = playersCount;
	this->dict = dict;
	//initialiser le tableau de joueurs
	init_all_players();
	//afin d'étendre la taille de la memoire cache !
	excludeCache.change_buffer_size(480); 
}


//fixer tout les joueurs sur nullptr
void jue::init_all_players() {
	for (int i = 0; i < playersCount; ++i) {
		joueurs[i] = nullptr;
	}
}


void jue::add_new_player(joueur_donnees playerData, int index) {
	if (index >= playersCount) {
		throw std::out_of_range("Index des joueurs hors plage");
	}
	joueurs[index] = new joueur(playerData);
}

char* jue::word_to_upper(const char* word) {
	char* tmp = new char[32];
	memset(tmp, 0, 32);
	for (int i = 0; i < strlen(word); ++i) {
		tmp[i] = toupper(word[i]);
	}
	return tmp;
}

//pour faire un print d'un message permettant au joueur de faire la saisie ex: 1H, (ABAC) >
void jue::print_input_ask_msg(joueur_donnees& pdata) {
	vecteur tmpWord;
	tmpWord.change_buffer_size(96); //32 the dafault size + 96 = 128
	tmpWord.add_new_word(pdata.PlayerName);
	tmpWord.add_new_word(",(");
	//pour ajouer le mot actuel formé par le joueur
	tmpWord.add_new_word(get_current_word());
	tmpWord.add_new_word(")>");
	printf("%s", tmpWord.get());
	tmpWord.destroy();
}

//faire une update du statut des quarts de singe
void jue::set_last_round_looser(joueur_donnees& pdata) {

	for (int i = 0; i < playersCount; ++i) {
		joueur_donnees tempData = joueurs[i]->get_data();
		if (pdata.number != tempData.number) {
			tempData.isLastRoundLoose = false;
			joueurs[i]->update_data(tempData);
		}
	}
	
	pdata.isLastRoundLoose = true;
	int lastLooserIndex = pdata.number;
	joueurs[lastLooserIndex]->update_data(pdata);
}

//récuperer la lettre du robot
char* jue::get_robot_letter() {
	FILE* db;
	errno_t err;

	if ((err = fopen_s(&db, this->dict, "r")) != 0) {
		throw std::exception("Can't read the dict.");
	}
	char line[32];
	bool isletterFound = false;
	char* Theletter = new char[2];
	char currWrd[32];
	memset(currWrd, 0, 32);
	while (fgets(line, sizeof line, db) != NULL) {
		//retirer \n de la ligne courrante
		line[strcspn(line, "\n")] = 0;

		//s'il s'agit du premier robot , celui-ci choisirait la lettre dans la ligne
		//sinon , il prendra une lettre du dictionnaire
		(get_current_word() == "") ? currWrd[0] = line[0] : strcpy_s(currWrd, 31, get_current_word());

		//excludeCache.is_word_exists:  verifie si le mot du dictionnaire n'a pas deja ete traité
		if (excludeCache.is_word_exists(line) == false
			and strlen(line) > 2 and strstr(line, currWrd) != NULL) {
			
			for (int i = 0; i < strlen(line); ++i) {
				if (isletterFound) break;

				for (int y = 0; y < strlen(currWrd); ++y) {

					if (line[i] != currWrd[i]) {
						Theletter[0] = line[i];
						isletterFound = true;
						break;
					}
					else continue;

				}
			}

			break; //break de la boucle while
		}
	}
	fclose(db);
	if (!isletterFound) {
		Theletter[0] = '?';
	}
	return Theletter;
}


char* jue::get_robot_word_in_mind() {
	FILE* db;
	errno_t err;

	if ((err = fopen_s(&db, this->dict, "r")) != 0) {
		throw std::exception("Can't read the dict.");
	}

	char line[32];
	bool isWordFound = false;
	char* TheWord = new char[32];
	//recuperrer le mot formé par le robot
	const char* currWrd = get_current_word();

	while (fgets(line, sizeof line, db) != NULL) {
		//retirer \n de la ligne cournate
		line[strcspn(line, "\n")] = 0;
		//excludeCache.is_word_exists: verifie si le mot du dictionnaire n'a pas deja ete traité
		if (excludeCache.is_word_exists(line) == false
			and strlen(line) > 2 and strstr(line, currWrd) != NULL) {
			
			strcpy_s(TheWord, 31, line);
			isWordFound = true;
			break; //break de la boucle while
		}
	}
	fclose(db);
	if (!isWordFound) {
		strcpy_s(TheWord, 31, "Idontknow");
	}
	return TheWord;
}





//mot dans le dictionnaire ou pas
bool jue::is_word_found(const char* wrd) {
	char* upperWord = word_to_upper(wrd);
	FILE* db;
	errno_t err;

	if ((err = fopen_s(&db, this->dict, "r")) != 0) {
		throw std::exception("Can't read the dict.");
	}

	char line[32];
	bool isWordFound = false;

	while (fgets(line, sizeof line, db) != NULL) {
		//retire \n 
		line[strcspn(line, "\n")] = 0;
		//excludeCache.is_word_exists: verifie si le mot du dictionnaire n'a pas deja ete traité
		if (excludeCache.is_word_exists(line) == false
			and strlen(line) > 2 and excludeCache.is_strig_equal(line, upperWord)) {

			//ajout du mot au cache
			excludeCache.add_new_word(line);
			isWordFound = true;
			delete upperWord;
			upperWord = nullptr;
			break;
		}
	}
	delete upperWord;
	upperWord = nullptr;
	fclose(db);
	return isWordFound;
}

const char* jue::get_current_word() {
	return curr_word.get();
}


//print la barre d'info , par exemple
//1H : 0.5; 2R : 0; 3H : 0.25; 4R : 0
void jue::print_the_info_bar() {
	vecteur info;
	info.change_buffer_size(512);
	for (int i = 0; i < playersCount; ++i) {
		joueur_donnees pdata = joueurs[i]->get_data();
		info.add_new_word(pdata.PlayerName);
		info.add_new_word(":");
		char umTostr[16];
		memset(umTostr, 0, 16);
		snprintf(umTostr, 16, "%f", pdata.monkeys);
		info.add_new_word(umTostr);
		info.add_new_word("; ");
	}
	std::cout << info.get() << "\n";
}


//evaluer la saisie d'un joueur
void jue::evaluate_player_guess(joueur_donnees& pdata) {

	char* upperWord = word_to_upper(pdata.guess);
	curr_word.add_new_word(upperWord);
	delete upperWord;
	upperWord = nullptr;

		//voir si �a complete le mot du dictionnaire 
	if (is_word_found(get_current_word())) {
		//un message montrant le dernier joueur ayant siasie la derniere lettre compl�tant un mot
		std::cout << "Le mot " << get_current_word() << " existe, " << pdata.PlayerName << " prend un quart de singe\n";
		pdata.monkeys += .25;
		joueurs[pdata.number]->update_data(pdata);
		set_last_round_looser(pdata);
		print_the_info_bar();
		//La partie est finie
		if (pdata.monkeys >= 1.) {
			throw std::exception("La partie est finie");
		}
		curr_word.clear();
		//start from 0
		int lastLooser = get_last_round_looser();
		if (lastLooser == playersCount - 1) {
			default_play(lastLooser);
			default_play(0);
		}
		else {
			default_play(lastLooser);
		}


	}
	else {
		//mot pas trouvé!
		
		set_last_round_looser(pdata);
	}

}


bool jue::is_word_real(const char* wrd) {
	const char* currWrd = get_current_word();
	size_t sz = curr_word.size();
	bool isReal = true;
	for (int i = 0; i < sz; ++i) {
		if (currWrd[i] != wrd[i]) {
			isReal = false;
			break;
		}
	}
	return isReal;
}


//evaluer la communication entre 2 joueurs , si l'in demande au precedent de deviner le mot
void jue::evaluate_tow_players_comm(joueur_donnees& pdata, joueur_donnees& prevPlayerData) {
	char* upperWord = word_to_upper(pdata.guess);
	
	if (!is_word_real(upperWord)) {
		std::cout << "le mot " << pdata.guess << " ne commence pas par les lettres attendues, le joueur " << prevPlayerData.PlayerName << "  prend un quart de singe\n";
		prevPlayerData.monkeys += .25;
		set_last_round_looser(prevPlayerData);//set the cuurent user to last round user and all other player to not loosers
		print_the_info_bar();
		// La partie est finie
		if (prevPlayerData.monkeys >= 1.) {
			throw std::exception("La partie est finie\n");
		}
		int lastLooser = get_last_round_looser();
		if (lastLooser == playersCount - 1) {
			wellcome_user_to_play(lastLooser);
			//default_play(0);
		}
		else {
			wellcome_user_to_play(lastLooser);//commencer de perdant de la derniere manche
		}


	}

	else if (is_word_found(upperWord)) {
		//message du jeu montrant le nom du dernier joueur ayant complete un mot
		std::cout << "Le mot " << upperWord << " existe, " << pdata.PlayerName << " prend un quart de singe\n";
		pdata.monkeys += .25;
		int index = pdata.number;
		joueurs[index]->update_data(pdata);
		set_last_round_looser(pdata);
		print_the_info_bar();
		if (pdata.monkeys >= 1.) {
			throw std::exception("La partie est finie\n");
		}
		curr_word.clear();
		int lastLooser = get_last_round_looser();
		if (lastLooser == playersCount - 1) {
			wellcome_user_to_play(lastLooser);
			//default_play(0);
		}
		else {
			wellcome_user_to_play(lastLooser);
		}
	}
	else {
		//si le joueur donner un faux mot
		std::cout << "le mot " << upperWord << " n'existe pas, le joueur " << prevPlayerData.PlayerName << " prend un quart de singe\n";
		prevPlayerData.monkeys += .25;
		set_last_round_looser(prevPlayerData);
	}

	delete upperWord;
	upperWord = nullptr;

}




//commencer le jeu
void jue::wellcome_user_to_play(int currPlayerIndex) {
	joueur_donnees pdata = joueurs[currPlayerIndex]->get_data();

	print_input_ask_msg(pdata);

	if (joueurs[currPlayerIndex]->is_robot()) {
		//le reobot va donner une lettre
		char* robotGuess = get_robot_letter();
		//std::cout << "robotGuess " << robotGuess << "\n";
		memset(pdata.guess, 0, 32);
		size_t len = strlen(pdata.guess);
		pdata.guess[len] = robotGuess[0];
		delete robotGuess;
		robotGuess = nullptr;
		//print de la saisie du robot
		std::cout << pdata.guess << "\n";

	}
	else {
		//demander au joueur humain de deviner une lettre
		joueurs[currPlayerIndex]->my_answer();
		pdata = joueurs[currPlayerIndex]->get_data();
	}


	
	if (excludeCache.is_strig_equal(pdata.guess, "?")) {
		//std::cout << "user want to ask previous player\n";
		int prevPlayerIndex = (pdata.number - 1);
		if (prevPlayerIndex < 0) {


			//prevPlayerIndex = get_last_round_looser();
			do {//no prev player , the curr player must enter the word in mind.
				std::cout << "Il n'y a pas de joueurs precedents.\n";
				if (!joueurs[currPlayerIndex]->is_robot()) {
					//demander au meme joueur de repondre
					print_input_ask_msg(pdata);
					joueurs[currPlayerIndex]->my_answer();
					pdata = joueurs[currPlayerIndex]->get_data();
				}
				else {
					
			
					char* robotGuess = get_robot_word_in_mind();
					memset(pdata.guess, 0, 32);
					strcpy_s(pdata.guess, sizeof pdata.guess, robotGuess);
					delete robotGuess;
					robotGuess = nullptr;
					//print the robot guess
					std::cout << pdata.guess << "\n";
				}

			} while (excludeCache.is_strig_equal(pdata.guess, "?"));

		}
		else {

			//recuperer les infos du dernier joueur
			joueur_donnees prevPlayerData = joueurs[prevPlayerIndex]->get_data();

			if (joueurs[prevPlayerIndex]->is_robot()) {
				
				char* robotWordInMind = get_robot_word_in_mind();
				std::cout << prevPlayerData.PlayerName << ", saisir le mot > " << robotWordInMind << "\n";
				
				memset(pdata.guess, 0, 32);
				strcpy_s(pdata.guess, 31, robotWordInMind);
				delete robotWordInMind;
				robotWordInMind = nullptr;

				
				evaluate_tow_players_comm(pdata, prevPlayerData);
			}
			else {
				print_input_ask_msg(prevPlayerData);
				joueurs[prevPlayerIndex]->my_answer();
				prevPlayerData = joueurs[prevPlayerIndex]->get_data();
				memset(pdata.guess, 0, 32);
				strcpy_s(pdata.guess, 31, prevPlayerData.guess);
			
				std::cout << prevPlayerData.PlayerName << " saisir le mot > " << pdata.guess << "\n";
				
				evaluate_tow_players_comm(pdata, prevPlayerData);

			}
		}

	}
	//si l'input est ! le joueur abandonne la manche
	else if (excludeCache.is_strig_equal(pdata.guess, "!")) {
		pdata.monkeys += .25;
		std::cout << "le joueur " << pdata.PlayerName << " abandonne la manche et prend un quart de singe\n";
		joueurs[currPlayerIndex]->update_data(pdata);
		set_last_round_looser(pdata);
		//default_play(get_last_round_looser());
	}
	else if (strlen(pdata.guess) >= size_t(1)) {
		evaluate_player_guess(pdata);
		joueurs[currPlayerIndex]->update_data(pdata);
	}
	else {
		//input non valid , le joueur prend un quart de singe
		std::cout << "Entr�es invalides, le joueur " << pdata.PlayerName << " prend un quart de singe\n";
		pdata.monkeys += .25;
		joueurs[currPlayerIndex]->update_data(pdata);
		set_last_round_looser(pdata);

	}


}



//returns the last round looser index
int jue::get_last_round_looser() {
	int index{ -1 };
	for (int i = 0; i < playersCount; ++i) {
		if (joueurs[i] == nullptr) {
			continue;
		}
		if (joueurs[i]->get_data().isLastRoundLoose) {
			index = i;
			break;
		}
	}
	return index;
}


//start the game with the default mode
inline void jue::default_play(int index) {
	for (int i = index; i < playersCount; ++i) {
		if (joueurs[i] != nullptr) {
			wellcome_user_to_play(i);
		}
	}
}




//
void jue::play() {
	default_play(0);

	while (get_last_round_looser() != -1) {
		int lastLooser = get_last_round_looser();
		//si le perdant de la derniere manche est un robot on recommance de 0
		if (joueurs[lastLooser]->is_robot() and (lastLooser == playersCount - 1) {
			default_play(0);
		}
		//else
		else if (!joueurs[lastLooser]->is_robot()) {
			default_play(lastLooser);
		}
	}
	/*
	int lastLooser = get_last_round_looser();
		if (lastLooser == playersCount - 1) {
			default_play(lastLooser);
			default_play(0);
		}
		else {
			default_play(lastLooser);
		}

	*/
}


//Detruire
void jue::destroy_players() {
	for (int i = 0; i < playersCount; ++i) {
		if (joueurs[i] != nullptr) {
			delete joueurs[i];
			joueurs[i] = nullptr;
			//std::cout << "Ok.\n";
		}
	}
	delete joueurs;
	joueurs = nullptr;
}


jue::~jue() {
	destroy_players();
}

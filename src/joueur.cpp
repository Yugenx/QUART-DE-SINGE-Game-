#include "joueur.h"

joueur::joueur(joueur_donnees data) {
	//stocker les informations du joueur
	this->data = data;
}


//cas robot
bool joueur::is_robot() {
	return data.type[0] == 'R' or data.type[0] == 'r';
}


//pour les saisies de l'humain
void joueur::my_answer() {
	char in[BUFFER_SIZE];//stocker les siasies du joueur humain
	memset(in, 0, BUFFER_SIZE);
	fgets(in, sizeof in, stdin);//lire sa siasie
	memset(data.guess, 0, BUFFER_SIZE);
	in[strcspn(in, "\n")] = 0;//retirer le \n de sa saisie
	strcpy_s(data.guess, sizeof data.guess, in); 
	if (strlen(data.guess) == 0) {
		throw std::exception("entr�e invalide");
	}

}

joueur_donnees joueur::get_data() {//return des infomations du joueur
	return data;
}

void joueur::update_data(joueur_donnees data) {//apres modifications
	this->data = data;
}

joueur::~joueur() {
	//std::cout << data.PlayerName << " leave.\n";
}



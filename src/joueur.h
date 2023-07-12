#ifndef __MONKEY__PLAYER__
#define __MONKEY__PLAYER__

#include <iostream>

#define BUFFER_SIZE 32

struct joueur_donnees {
	int number;
	//on peut lui changer de taille selon le besoin
	char PlayerName[BUFFER_SIZE];
	char type[2]; //humain ou robot
	char WordInMind[BUFFER_SIZE];
	char guess[BUFFER_SIZE];
	double monkeys; //( le quart de singe ) ex : 0.25 quart de singe
	bool isLastRoundLoose; // perdant(ou pas) de la derniere manche
};


struct joueur {
	joueur_donnees data; //les informations des joueurs
	joueur() = default;
	joueur(joueur_donnees data);
	joueur_donnees get_data(); //Récuperer les informations des joueurs
	void update_data(joueur_donnees data);//faire une update de ces informations
	bool is_robot();
	void my_answer()noexcept(false); //Pour que le joueur humain puisse entrer sa proposition
	~joueur();
};


#endif // ! __MONKEY__PLAYER__ INCLUDED
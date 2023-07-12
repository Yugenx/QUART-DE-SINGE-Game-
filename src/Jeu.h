#ifndef  __MONKEY_GAME__
#define __MONKEY_GAME__

#include "joueur.h"
#include "vecteur.h"

struct jue {
	//pour stocker les joueurs
	joueur** joueurs;

	size_t playersCount;

	//les mots du dictionnaire dict *.txt
	const char* dict;

	//conteneur pour stocker ce qui est formé du mot
	vecteur curr_word;

	//un cache qui va stocker les mots à ne plus utiliser
	vecteur excludeCache;

	//initer le jeu
	jue(size_t playersCount, const char* dict);

	//ajout dun nouveau joueur
	void add_new_player(joueur_donnees playerData, int index)noexcept(false);

	//fixer tout les joueurs sur nullptr
	void init_all_players();

	//recuperer tout ce qui a été saisie pr les joueurs
	const char* get_current_word();

	
	bool is_word_real(const char* wrd);


	char* word_to_upper(const char* word);

	//voir s'il est dans le dic
	bool is_word_found(const char* wrd)noexcept(false);

	//recuperer le mot siasie par le robot
	char* get_robot_letter();

	char* get_robot_word_in_mind();

	//pour daire un print du message demandant la saisie par ex: 1H, (ABAC) >
	void print_input_ask_msg(joueur_donnees& pdata);

	//fxer le perdant de la derniere manche
	void set_last_round_looser(joueur_donnees& pdata);


	//evaluer la saisie des joueurs
	void evaluate_player_guess(joueur_donnees& pdata);


	void evaluate_tow_players_comm(joueur_donnees& pdata, joueur_donnees& prevPlayerData);


	//un print de la barre d'informations
	//1H : 0.5; 2R : 0; 3H : 0.25; 4R : 0
	void print_the_info_bar();

	//fait un return de m'index du dernier perdant
	int get_last_round_looser();

	//Commencr le jeu
	void wellcome_user_to_play(int currPlayerIndex);

	//commencer le jeu par defzut
	void default_play(int index);

	//commencer la boucle du jeu
	void play();

	//detruire tout les joueurs
	void destroy_players();

	~jue();
};



#endif // ! __MONKEY_GAME__ INCLUDED

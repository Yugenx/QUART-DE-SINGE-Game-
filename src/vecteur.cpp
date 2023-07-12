#include "vecteur.h"

vecteur::vecteur() {
	buff = new char[MAX_WORD_SIZE];
	curr_max_size = MAX_WORD_SIZE;
	clear();
}

size_t vecteur::get_curr_max_size() {
	return curr_max_size;
}


//voir si la longeur du mot peut etre stockée
bool vecteur::is_good_size(const char* wrd) {
	return strlen(wrd) <= get_curr_max_size() - 1;
}

void vecteur::clear() {//vider le buffer
	for (int i = 0; i < get_curr_max_size() - 1; ++i) {
		buff[i] = '\0';
	}
	sz = 0;
}

inline void vecteur::put_char(char val) {
	if (sz >= get_curr_max_size() - 1) {
		throw std::exception("Can't put a new char: max word size reached.");
	}
	buff[sz] = val;
	sz += 1;
}

//le remplir avec les nouveaux mots
void  vecteur::update(const char* val) {
	if (!is_good_size(val)) {
		throw std::exception("Can't update : word too large.");
	}

	clear();

	for (int i = 0; i < strlen(val); ++i) {
		put_char(val[i]);
	}

}

void vecteur::print() {
	std::cout << buff << "\n";
}

inline size_t vecteur::size() {
	return sz;
}

//comparer les mots
//faire un return des indexs des differents char
//faire un return de la taille des mots s'ils sont égaux
int vecteur::compare(const char* wrd) {
	int i{ 0 };
	if (size() == 0) throw std::exception("No word exists.");
	while (buff[i] == wrd[i] and i <= sz) {
		++i;
	}
	return i;
}

//augmenter la taille du buffer
void vecteur::change_buffer_size(size_t sz) {
	destroy();
	curr_max_size = (MAX_WORD_SIZE + sz);
	buff = new char[curr_max_size];
	clear();
}


void vecteur::add_new_word(const char* newWord) {
	for (int i = 0; i < strlen(newWord); ++i) {
		put_char(newWord[i]);
	}
}

char* vecteur::get() {
	if (sz == 0) return (char*)"";
	else return buff;
}


// voir si les chaines de caracter sont égales
bool vecteur::is_strig_equal(const char* str1, const char* str2) {
	if (strlen(str1) != strlen(str2)) return false;
	bool is_equal = true;
	int i{ 0 };
	while (i < strlen(str1)) {
		if (str1[i] != str2[i]) {
			is_equal = false;
			break;
		}
		++i;
	}
	return is_equal;
}


//si le mot existe dans le buffer
bool vecteur::is_word_exists(const char* wrd) {
	char* res = strstr(buff, wrd);
	return res != NULL;
}

void vecteur::destroy() {
	delete[]buff;
	buff = nullptr;
}


vecteur::~vecteur() {
	destroy();
}
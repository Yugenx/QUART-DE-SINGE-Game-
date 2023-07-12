#ifndef  __MQ_JEU__VECTEUR__
#define  __MQ_JEU__VECTEUR__

#include <iostream>

#define MAX_WORD_SIZE 32

struct vecteur {
	//cons
	vecteur();

	char* buff; //pour stocker les valeurs des chaines de caracteres
	size_t sz;
	size_t curr_max_size; //sa taille max

	//si la taille du mot stockée est convenable
	bool is_good_size(const char* wrd);


	inline size_t size();

	//recuperer la taille maximale
	size_t get_curr_max_size();

	//le vider
	void clear();

	
	void change_buffer_size(size_t sz);

	//y mettre un nouveau caractere
	inline void put_char(char val)noexcept(false);

	//le vider et y stocker un nouveau mot
	void update(const char* val)noexcept(false);

	
	void add_new_word(const char* newWord);

	//print
	void print();

	
	int compare(const char* wrd)noexcept(false);

	
	char* get();

	bool is_strig_equal(const char* str1, const char* str2);

	
	bool is_word_exists(const char* wrd);

	
	void destroy();

	~vecteur();
};


#endif // ! __MQ_JEU__VECTEUR__ INCLUDED

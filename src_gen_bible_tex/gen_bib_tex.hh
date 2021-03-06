
#ifndef GB_GEN_BIB_TEX_H
#define GB_GEN_BIB_TEX_H

#include <assert.h>
#include <stdio.h>

#include <string>
#include <iostream>
#include <sstream>

#define GB_CRONO_BIBLE_NM "crono_bible"

#define GB_VERSES_PTH "REINA_VALERA.txt"
#define GB_REFS_PTH "REFS.txt"
#define GB_SUBTITU_PTH "SUBTITU.txt"

#define GB_PREF_BOOK "book"
#define GB_SUFI_BOOK ".tex"

#define GB_BOOK_ABRV_IDX 1
#define GB_BOOK_NAME_IDX 2
#define GB_BOOK_TRANSLIT_IDX 3
#define GB_BOOK_MEANING_IDX 4
#define GB_BOOK_HEBREW_NM_IDX 5

#define GB_OFFSET_STR_END 2

#define GB_KEY_SEP '+'
#define GB_REF_SEP '|'
#define GB_RNG_SEP '-'
#define GB_KRF_SEP '.'

#define GB_STR_END '\0'

#define MARK_USED(X)  ((void)(&(X)))

#define MAX_VERSE_SZ 4100
#define MAX_REFS_SZ 400
#define MAX_SUBTITU_SZ 100

#define gb_cstr(the_str) (const_cast<char *>(the_str))

#define gb_out std::cout
#define gb_err std::cerr


#ifdef __cplusplus
extern "C"{
#endif

bool 
gb_call_assert(bool vv_ck, const char* file, int line, const char* ck_str, const char* msg);

#define gb_assert(vv, msg) gb_call_assert(vv, __FILE__, __LINE__, #vv, msg)

#define GB_CK(vv) gb_assert(vv, NULL)
#define GB_CK_PRT(vv, msg) gb_assert(vv, msg)

inline 
int
cmp_int(int const & n1, int const & n2){ 
	if(n1 == n2){ return 0; }
	if(n1 < n2){ return -1; }
	return 1;
}

extern const char* GB_BOOKS_NAMES[][6];

typedef std::ostream gb_ostream;
typedef std::string gb_string;

class verse_key {
public:
	int book;
	int chapter;
	int verse;

	verse_key(){
		init_verse_key();
	}

	~verse_key(){}

	void init_verse_key(){
		book = -1;
		chapter = -1;
		verse = -1;
	}

};

int cmp_verse_key(verse_key& vk1, verse_key& vk2);

class tex_gen {
public:
	gb_string	help_str;
	gb_string	version_str;

	bool		op_with_images;
	int			op_dbg_prt;
	bool		op_gen_tex;
	bool		op_gen_crn;

	FILE* 		verses;
	FILE* 		subtitles;
	FILE* 		references;

	FILE* 		tex_output;

	char* verse_line;
	char* ref_line;
	char* subtitu_line;

	size_t verse_sz;
	size_t ref_sz;
	size_t subtitu_sz;

	verse_key 	verse_prv_vk;
	verse_key 	verse_vk;
	verse_key 	ref_vk;
	verse_key 	subtitu_vk;

	char* 		verse_val;
	char* 		ref_val;
	char* 		subtitu_val;

	char 		the_subtitu_kind;

	char* 		the_verse;
	char* 		the_refs;
	char* 		the_subtitu;

	tex_gen(){
		init_tex_gen();
	}

	~tex_gen();

	void 	init_tex_gen();

	bool	get_args(int argc, char** argv);
	FILE*	open_file(gb_string& nm, const char* mode = "r");

	//char*	get_line(FILE* ff);
	char*	get_line(FILE* ff, char*& line, size_t& sz);
	char*	get_key(char* line, verse_key& vk, char sep = GB_KEY_SEP);
	bool	get_ref(char*& value, verse_key& vk);

	void	print_file(FILE* ff);
	void	test_print_file();
	char*	get_subtitle_kind(char* value, char& kind);
	void	set_content_end(char* line, int line_sz);
	void	reset_content_end(char* line, int line_sz);

	void	gen_start_crono_bible();
	void	gen_start_book(int num_book);
	void	gen_verse();
	void	gen_crono_verse();
	void	gen_refs();
	void	gen_end_book();

	void	get_verse_line();
	void	get_ref_line();
	void	get_subtitu_line(bool is_sorted = true);

	void	gen_bible();
	void	gen_crono_bible();
};


#ifdef __cplusplus
}
#endif


#endif // GB_GEN_BIB_TEX_H

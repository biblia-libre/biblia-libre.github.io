
#ifndef GB_GEN_BIB_TEX_H
#define GB_GEN_BIB_TEX_H

#include <stdio.h>

#include <string>
#include <iostream>
#include <sstream>

#define GB_KEY_SEP '+'
#define GB_REF_SEP '|'

#define MARK_USED(X)  ((void)(&(X)))

#define MAX_VERSE_SZ 4100
#define MAX_REFS_SZ 400
#define MAX_SUBTITU_SZ 100

#define gb_cstr(the_str) (const_cast<char *>(the_str))

#define gb_out std::cout


#ifdef __cplusplus
extern "C"{
#endif

enum file_pth_t {
	gb_verses_pth = 0,
	gb_refs_pth = 1,
	gb_subtitu_pth = 2,
	gb_invalid_pth = 100
};

const char* INPUT_PATHS[] = {
	"REINA_VALERA.txt",
	"REFS.txt",
	"SUBTITU.txt"
};


typedef std::ostream gb_ostream;
typedef std::string gb_string;

class prog_args {
public:
	gb_string	help_str;
	gb_string	version_str;

	bool		op_with_images;
	gb_string 	op_pth_verses;

	FILE* 		verses;
	FILE* 		subtitles;
	FILE* 		references;
	FILE* 		format;

	char* verse_line;
	char* ref_line;
	char* subtitu_line;

	size_t verse_sz;
	size_t ref_sz;
	size_t subtitu_sz;

	prog_args(){
		init_prog_args();
	}

	~prog_args();

	void 	init_prog_args();
	void 	print_paths();

	bool	get_args(int argc, char** argv);
	FILE*	open_file(file_pth_t id);

	bool	get_line(FILE* ff);
	char*	get_key(char* line, int& book, int& chapter, int& verse);
	bool	get_ref(char* value, int& book, int& chapter, int& verse);
};

#ifdef __cplusplus
}
#endif


#endif // GB_GEN_BIB_TEX_H

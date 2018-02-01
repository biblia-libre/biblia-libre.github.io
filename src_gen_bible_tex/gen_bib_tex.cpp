

#include <stdlib.h>
#include <string.h>

#include "gen_bib_tex.hh"

#define GB_BUFF_SZ 1000
char GB_BUFF[GB_BUFF_SZ];

#define GB_FMT_BookNameMeaning "\\blSetBookNameMeaning{%s}\n"
#define GB_FMT_BookNumber "\\blSetBookNumber{%d}\n"
#define GB_FMT_HebrewBookName "\\blSetHebrewBookName{%s}\n"
#define GB_FMT_BookName "\\blSetBookName{%s}\n"
#define GB_FMT_BookNameTranslit "\\blSetBookNameTranslit{%s}\n"
#define GB_FMT_StartBook "\\blStartBook\n"

#define GB_FMT_ChapterNumber "\\blSetChapterNumber{%d}\n"
#define GB_FMT_SubTitle "\\blSubTitle{%s}\n"
#define GB_FMT_StartChapterN "\\lettrine{%d}{}\n"

#define GB_FMT_StartVerse "\\blGetVerse{%d}"
#define GB_FMT_StartVerseX "\\blGetVerseX{%d}"

#define GB_FMT_EndBook "\\blEndBook\n"

const char* GB_BOOKS_NAMES[][6] = {
{"BAD_COD_NM", "BAD_NM_ABREV", "BAD_PRT_NM", "BAD_TRNSLIT_NM", "BAD_TRADUC", "BAD_HEBREW_NM"},
{"genesis", "Gen", "Génesis", "Bereshit", "En el principio", "בראשית"},
{"exodo", "Exo", "Exodo", "Shemot", "Nombres", "שמות"},
{"levitico", "Lev", "Levítico", "Vayikra", "EL llamo", "ויקרא"},
{"numeros", "Num", "Números", "Bamidbar", "En el desierto", "במדבר"},
{"deuteronomio", "Deu", "Deuteronomio", "Devarim", "Palabreas", "דברים"},
{"josue", "Jos", "Josué", "Yehoshua", "", "יהושע"},
{"jueces", "Jue", "Jueces", "Shoftim", "", "שופטים"},
{"rut", "Rut", "Rut", "Rut", "", "רות"},
{"1samuel", "1Sa", "1 Samuel", "Alef Shmuel", "", "א שמואל"},
{"2samuel", "2Sa", "2 Samuel", "Bet Shmuel", "", "ב שמואל"},
{"1reyes", "1Re", "1 Reyes", "Alef Melajim", "", "א מלכים"},
{"2reyes", "2Re", "2 Reyes", "Bet Melajim", "", "ב מלכים"},
{"1cronicas", "1Cr", "1 Crónicas", "Alef Divre Hayamim", "", "א דברי הימים"},
{"2cronicas", "2Cr", "2 Crónicas", "Bet Divre Hayamim", "", "ב דברי הימים"},
{"esdras", "Esd", "Esdras", "Ezra", "", "עזרא"},
{"nehemias", "Neh", "Nehemías", "Nehemia", "", "נחמיה"},
{"ester", "Est", "Ester", "Ester", "", "אסתר"},
{"job", "Job", "Job", "Yob", "", "איוב"},
{"salmos", "Sal", "Salmos", "Tehilim", "", "תהלים"},
{"proverbios", "Pro", "Proverbios", "Mishle", "", "משלי"},
{"eclesiastes", "Ecl", "Eclesiastés", "Kohelet", "Recolector", "קהלת"},
{"cantares", "Can", "Cantares", "Shir Heshirim", "", "שיר השירים"},
{"isaias", "Isa", "Isaías", "Yeshayahu", "", "ישעיה"},
{"jeremias", "Jer", "Jeremías", "Yirmiyahu", "", "ירמיה"},
{"lamentaciones", "Lam", "Lamentaciones", "Eja", "", "איכה"},
{"ezequiel", "Eze", "Ezequiel", "Yejezkel", "", "יחזקאל"},
{"daniel", "Dan", "Daniel", "Daniyel", "", "דניאל"},
{"oseas", "Ose", "Oseas", "Hoshea", "", "הושע"},
{"joel", "Joe", "Joel", "Yoel", "", "יואל"},
{"amos", "Amo", "Amós", "Amos", "", "עמוס"},
{"abdias", "Abd", "Abdías", "Ovadia", "", "עובדיה"},
{"jonas", "Jon", "Jonás", "Yona", "", "יונה"},
{"miqueas", "Miq", "Miqueas", "Mija", "", "מיכה"},
{"nahum", "Nah", "Nahúm", "Najum", "", "נחום"},
{"habacuc", "Hab", "Habacuc", "Jabacuc", "", "חבקוק"},
{"sofonias", "Sof", "Sofonías", "Tzfania", "", "צפניה"},
{"hageo", "Hag", "Hageo", "Jagai", "", "חגי"},
{"zacarias", "Zac", "Zacarías", "Zejaria", "", "זחריה"},
{"malaquias", "Mal", "Malaquías", "Malaji", "", "מלאכי"},
{"mateo", "Mat", "Mateo", "Mati", "", "מתי"},
{"marcos", "Mar", "Marcos", "Marcos", "", "מרקוס"},
{"lucas", "Luc", "Lucas", "Lucas", "", "לוקס"},
{"juan", "Jua", "Juan", "Yojanan", "", "יוחנן"},
{"hechos", "Hch", "Hechos", "Maase Hashalijim", "", "מעשי השליחים"},
{"romanos", "Rom", "Romanos", "Romiim", "", "רומיים"},
{"1corintios", "1Co", "1 Corintios", "Alef Corrintiim", "", "א קורנתיים"},
{"2corintios", "2Co", "2 Corintios", "Bet Corrintiim", "", "ב קורנתיים"},
{"galatas", "Gal", "Gálatas", "Galatiim", "", "גלטיים"},
{"efesios", "Efe", "Efesios", "Efesiim", "", "אפסיים"},
{"filipenses", "Fil", "Filipenses", "Filipiim", "", "פילפיים"},
{"colosenses", "Col", "Colosenses", "Colosim", "", "קולסים"},
{"1tesalonicenses", "1Te", "1 Tesalonicenses", "Alef Tesalonikim", "", "א תסלוניקים"},
{"2tesalonicenses", "2Te", "2 tesalonicenses", "Bet Tesalonikim", "", "ב תסלוניקים"},
{"1timoteo", "1Ti", "1 Timoteo", "Alef Timotios", "", "א טימותיוס"},
{"2timoteo", "2Ti", "2 Timoteo", "Bet Timotios", "", "ב טימותיוס"},
{"tito", "Tit", "Tito", "Titus", "", "טיטוס"},
{"filemon", "Fil", "Filemon", "Filimon", "", "פילימון"},
{"hebreos", "Heb", "Hebreos", "Ivrim", "", "עברים"},
{"santiago", "Stg", "Santiago", "Yaakov", "", "יעקב"},
{"1pedro", "1Pe", "1 Pedro", "Alef Petros", "", "א פטרוס"},
{"2pedro", "2Pe", "2 Pedro", "Bet Petros", "", "ב פטרוס"},
{"1juan", "1Ju", "1 Juan", "Alef Yojanan", "", "א יוחנן"},
{"2juan", "2Ju", "2 Juan", "Bet Yojanan", "", "ב יוחנן"},
{"3juan", "3Ju", "3 Juan", "Gimel Yojanan", "", "ג יוחנן"},
{"judas", "Jud", "Judas", "Yahuda", "", "יהודה"},
{"apocalipsis", "Rev", "Revelación", "Jazon Yojanan", "", "חזון יוחנן"}
};

bool 
gb_call_assert(bool vv_ck, const char* file, int line, const char* ck_str, const char* msg)
{	
	if(! vv_ck){
		fprintf(stderr, "ASSERT '%s' FAILED\nFILE= %s\nLINE=%d \n", ck_str, file, line);
		if(msg != NULL){
			fprintf(stderr, "MSG=%s\n", msg);
		}
		fprintf(stderr, "------------------------------------------------------------------\n");
	}
	assert(vv_ck);
	return vv_ck;
}

void 
gb_abort_func(long val, const char* msg){
	fprintf(stderr, "\nABORTING_WITH_ERR=%ld %s\n", val, msg);
	
	exit(EXIT_FAILURE);
}


FILE*
tex_gen::open_file(gb_string& nm, const char* mode){
	FILE* fpth = fopen(nm.c_str(), mode);
	if(fpth == NULL){
		fprintf(stderr, "ERROR. Can NOT open file %s\n", nm.c_str());
		exit(1);;
	}
	return fpth;
}

void
tex_gen::init_tex_gen(){

	help_str =
		"[ -h | -v | -p | -tex ] "
		"[ -ver <verses_path> "
		"| -ref <refs_path> "
		"| -sub <subtitles_path> "
		"]"
		"\n"
		"-h : print help.\n"
		"-v : print version.\n"
		"-p : print paths to use.\n"
		"-tex : generate all bible books LaTeX files (xelatex).\n"
		"-ver : set the verses path to <verses_path>.\n"
		"-ref : set the references path to <refs_path>.\n"
		"-sub : set the subtitles path to <subtitles_path>.\n"
		"\n"
		;

	version_str =
		"v0.1\n"
		"(c) 2018. QUIROGA BELTRAN, Jose Luis. c.c. 79523732. Bogota - Colombia.\n"
		;
		
	op_with_images = false;
	op_dbg_prt = -1;
	op_gen_tex = false;

	verses = NULL;
	subtitles = NULL;
	references = NULL;

	tex_output = NULL;

	verse_line = NULL;
	ref_line = NULL;
	subtitu_line = NULL;

	verse_sz = 0;
	ref_sz = 0;
	subtitu_sz = 0;

	verse_prv_vk.init_verse_key();
	verse_vk.init_verse_key();
	ref_vk.init_verse_key();
	subtitu_vk.init_verse_key();

	verse_val = NULL;
	ref_val = NULL;
	subtitu_val = NULL;

	the_subtitu_kind = 'N';

	the_subtitu = NULL;
	the_refs = NULL;
	the_verse = NULL;
};

bool
tex_gen::get_args(int argc, char** argv)
{
	gb_ostream& os = gb_err;
	MARK_USED(os);

	bool prt_help = false;
	bool prt_version = false;
	bool prt_paths = false;

	gb_string verses_pth = GB_VERSES_PTH;
	gb_string refs_pth = GB_REFS_PTH;
	gb_string subtitu_pth = GB_SUBTITU_PTH;
	
	for(long ii = 1; ii < argc; ii++){
		gb_string the_arg = argv[ii];
		if(the_arg == "-h"){
			prt_help = true;
		} else if(the_arg == "-v"){
			prt_version = true;
		} else if(the_arg == "-p"){
			prt_paths = true;
		} else if(the_arg == "-with_images"){
			op_with_images = true;
		} else if(the_arg == "-tex"){
			op_gen_tex = true;
		} else if((the_arg == "-ver") && ((ii + 1) < argc)){
			int kk_idx = ii + 1;
			ii++;

			verses_pth = argv[kk_idx];
		} else if((the_arg == "-ref") && ((ii + 1) < argc)){
			int kk_idx = ii + 1;
			ii++;

			refs_pth = argv[kk_idx];
		} else if((the_arg == "-sub") && ((ii + 1) < argc)){
			int kk_idx = ii + 1;
			ii++;

			subtitu_pth = argv[kk_idx];
		} else if((the_arg == "-dbg") && ((ii + 1) < argc)){
			int kk_idx = ii + 1;
			ii++;

			op_dbg_prt = atoi(argv[kk_idx]);
		}
	}

	if(argc <= 1){
		prt_help = true;
	}
	
	if(prt_help){
		os << argv[0] << " " << help_str << "\n";
		return false;
	}
	if(prt_version){
		os << argv[0] << " " << version_str << "\n";
		return false;
	}
	os << "pth_verses = " << verses_pth << "\n";
	os << "refs_pth = " << refs_pth << "\n";
	os << "subtitu_pth = " << subtitu_pth << "\n";

	verses = open_file(verses_pth);
	subtitles = open_file(subtitu_pth);
	references = open_file(refs_pth);

	return true;
}

tex_gen::~tex_gen(){
	if(verses != NULL){ fclose(verses); }
	if(subtitles != NULL){ fclose(subtitles); }
	if(references != NULL){ fclose(references); }

	if(tex_output != NULL){ fclose(tex_output); }

	if(verse_line != NULL){ free(verse_line); }
	if(ref_line != NULL){ free(ref_line); }
	if(subtitu_line != NULL){ free(subtitu_line); }
}


int main(int argc, char **argv){
	gb_ostream& os = gb_out;
	tex_gen txg;

	bool args_ok = txg.get_args(argc, argv);
	if(args_ok){
		gb_err << "ARGS_OK\n";
	}

	//txg.test_print_file();
	if(txg.op_gen_tex){
		txg.gen_bible();
	}

	return 0;
}

char*
tex_gen::get_line(FILE* ff, char*& line, size_t& sz){
	size_t read_sz = getline(&line, &sz, ff);
	sz = read_sz;
	if((read_sz == -1) && (line != NULL)){ 
		free(line);
		line = NULL;
	}
	return line;
}

char*
tex_gen::get_key(char* line, verse_key& vk, char the_sep){
	vk.init_verse_key();
	if(line == NULL){
		return NULL;
	}
	char* pt_str = line;
	char* pt_sep = NULL;
	for(int aa = 0; aa < 3; aa++){
		pt_sep = strchr(pt_str, the_sep);
		if(pt_sep == NULL){ 
			fprintf(stderr, "ERROR. Cannot find separator '%c' in line:\n%s\n\n", the_sep, line);
			exit(1);;
		}
		*pt_sep = GB_STR_END;
		switch(aa){
		case 0:
			vk.book = atoi(pt_str);
			break;
		case 1:
			vk.chapter = atoi(pt_str);
			break;
		case 2:
			vk.verse = atoi(pt_str);
			break;
		}
		*pt_sep = the_sep;
		pt_str = pt_sep + 1;
	}
	return pt_str;
}

bool
tex_gen::get_ref(char*& value, verse_key& vk){
	if((*value != GB_REF_SEP) && (*value != GB_RNG_SEP)){
		fprintf(stderr, "ERROR. Cannot find separator '%c' in value:\n%s\n\n", GB_REF_SEP, value);
		exit(1);;
	}
	value++;
	if(*value == GB_KEY_SEP){
		return false;
	}
	value = get_key(value, vk, GB_KRF_SEP);
	return true;
}

int cmp_verse_key(verse_key& vk1, verse_key& vk2){
	int c1 = 0;
	c1 = cmp_int(vk1.book, vk2.book);
	if(c1 != 0){ return c1; }
	c1 = cmp_int(vk1.chapter, vk2.chapter);
	if(c1 != 0){ return c1; }
	c1 = cmp_int(vk1.verse, vk2.verse);
	if(c1 != 0){ return c1; }
	return 0;
}

void
tex_gen::print_file(FILE* ff){
	char* line = NULL;
	size_t line_sz = 0;

	char* ln = NULL;
	char* val = NULL;
	verse_key vk;
	verse_key prv_vk;
	verse_key ref;
	char kk;
	while((ln = get_line(ff, line, line_sz)) != NULL){
		printf("%s", ln);
		val = get_key(ln, vk);
		printf("KEY= %d %d %d \n\tVAL=%s", vk.book, vk.chapter, vk.verse, val);
	}
}

void
tex_gen::test_print_file(){
	switch(op_dbg_prt){
	case 1:
		print_file(verses);
		break;
	case 2:
		print_file(subtitles);
		break;
	case 3:
		print_file(references);
		break;
	};
}

char*
tex_gen::get_subtitle_kind(char* value, char& kind){
	if(value == NULL){
		return NULL;
	}
	if(*value != GB_REF_SEP){
		fprintf(stderr, "ERROR_1. Cannot find separator '%c' in subtitle:\n%s\n\n", GB_REF_SEP, value);
		exit(1);;
	}
	value++;
	kind = *value;
	value++;
	if(*value != GB_REF_SEP){
		fprintf(stderr, "ERROR_2. Cannot find separator '%c' in subtitle:\n%s\n\n", GB_REF_SEP, value);
		exit(1);;
	}
	value++;
	return value;
}

void
tex_gen::set_content_end(char* line, int line_sz){
	if(line == NULL){ return; }
	int idx = line_sz - GB_OFFSET_STR_END;
	if(line[idx] != GB_KEY_SEP){
		fprintf(stderr, "ERROR_1. Cannot find end_of_line '%c' in line:\n%s\n%d(%c)\n", GB_KEY_SEP, line,
				idx, line[idx]);
		exit(1);;
	}
	line[idx] = GB_STR_END;
}

void
tex_gen::reset_content_end(char* line, int line_sz){
	int idx = line_sz - GB_OFFSET_STR_END;
	if(line[idx] != GB_STR_END){
		fprintf(stderr, "ERROR_2. Cannot find end_of_line '%c' in line:\n%s\n%d(%c)\n", GB_STR_END, line,
				idx, line[idx]);
		exit(1);;
	}
	line[idx] = GB_KEY_SEP;
}

void
tex_gen::gen_start_book(int num_book){
	if(tex_output != NULL){ fclose(tex_output); }

	snprintf(GB_BUFF, GB_BUFF_SZ, "%s%d%s", GB_PREF_BOOK, num_book, GB_SUFI_BOOK);
	gb_string nm = GB_BUFF;
	tex_output = open_file(nm, "w+");

	const char** book_dat = GB_BOOKS_NAMES[num_book];

	fprintf(tex_output, GB_FMT_BookName, book_dat[GB_BOOK_NAME_IDX]);
	fprintf(tex_output, GB_FMT_BookNameTranslit, book_dat[GB_BOOK_TRANSLIT_IDX]);
	fprintf(tex_output, GB_FMT_BookNameMeaning, book_dat[GB_BOOK_MEANING_IDX]);
	fprintf(tex_output, GB_FMT_HebrewBookName, book_dat[GB_BOOK_HEBREW_NM_IDX]);
	fprintf(tex_output, GB_FMT_BookNumber, num_book);
	fprintf(tex_output, GB_FMT_StartBook);
}

void
tex_gen::gen_verse(){
	bool new_book = verse_vk.book > verse_prv_vk.book;
	if(new_book){
		if(tex_output != NULL){
			gen_end_book();
		}
		gen_start_book(verse_vk.book);
	}

	bool new_chap = verse_vk.chapter > verse_prv_vk.chapter;
	if(new_chap){
		fprintf(tex_output, "%% =================================================\n\n");
		fprintf(tex_output, GB_FMT_ChapterNumber, verse_vk.chapter);
		fprintf(tex_output, "\n");
	}

	if(cmp_verse_key(verse_vk, subtitu_vk) == 0){
		GB_CK(the_subtitu != NULL);
		fprintf(tex_output, "\n\n");
		fprintf(tex_output, GB_FMT_SubTitle, the_subtitu);
		fprintf(tex_output, "\n");
		get_subtitu_line();
	}
	if(new_chap){
		switch(the_subtitu_kind){
		case 'N':
		default:
			fprintf(tex_output, GB_FMT_StartChapterN, verse_vk.chapter);
			break;
		};
	}
	if(cmp_verse_key(verse_vk, ref_vk) == 0){
		GB_CK(the_refs != NULL);
		fprintf(tex_output, GB_FMT_StartVerseX, verse_vk.verse);
		fprintf(tex_output, "{");
		gen_refs();
		fprintf(tex_output, "}");
		//fprintf(tex_output, "nota %d}", verse_vk.verse);
		get_ref_line();

		//fprintf(tex_output, GB_FMT_StartVerse, verse_vk.verse);
	} else {
		fprintf(tex_output, GB_FMT_StartVerse, verse_vk.verse);
	}
	fprintf(tex_output, "%s", the_verse);
	fprintf(tex_output, " \n");
}

void
tex_gen::gen_refs(){
	verse_key ref;
	while(get_ref(the_refs, ref)){
		char sep = ' ';
		if(*the_refs == '-'){ sep = '-'; }
		fprintf(tex_output, "%s %d:%d%c", GB_BOOKS_NAMES[ref.book][GB_BOOK_ABRV_IDX], 
				ref.chapter, ref.verse, sep);
	}
}

void
tex_gen::gen_end_book(){
	//fprintf(tex_output, "\n\n");
	fprintf(tex_output, "\\nopagebreak\n\n");
	fprintf(tex_output, GB_FMT_EndBook);
	fprintf(tex_output, "\n\n");
}

void
tex_gen::get_verse_line(){
	verse_prv_vk = verse_vk;
	get_line(verses, verse_line, verse_sz);
	verse_val = get_key(verse_line, verse_vk);
	set_content_end(verse_line, verse_sz);
	the_verse = verse_val;
}

void
tex_gen::get_ref_line(){
	get_line(references, ref_line, ref_sz);
	verse_key pvk = ref_vk;
	ref_val = get_key(ref_line, ref_vk);
	GB_CK((ref_line == NULL) || cmp_verse_key(pvk, ref_vk) == -1);
	the_refs = ref_val;
}

void
tex_gen::get_subtitu_line(){
	get_line(subtitles, subtitu_line, subtitu_sz);
	verse_key pvk = subtitu_vk;
	subtitu_val = get_key(subtitu_line, subtitu_vk);
	GB_CK((subtitu_line == NULL) || cmp_verse_key(pvk, subtitu_vk) == -1);

	the_subtitu = get_subtitle_kind(subtitu_val, the_subtitu_kind);
	set_content_end(subtitu_line, subtitu_sz);
}

void
tex_gen::gen_bible(){
	get_verse_line();
	get_ref_line();
	get_subtitu_line();

	while(verse_line != NULL){
		gen_verse();
		get_verse_line();
	}

	gen_end_book();
}

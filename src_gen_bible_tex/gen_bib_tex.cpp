

#include <stdlib.h>
#include <string.h>

#include "gen_bib_tex.hh"

const char* BOOKS_NAMES[][6] = {
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
tex_gen::open_file(gb_string& nm){
	FILE* fpth = fopen(nm.c_str(), "r");
	if(fpth == NULL){
		fprintf(stderr, "ERROR. Can NOT open file %s\n", nm.c_str());
		exit(1);;
	}
	return fpth;
}

void
tex_gen::init_tex_gen(){

	help_str =
		"[ -h | -v | -tex ]\n"
		"\t[ -pth_verses <verses_path> "
		"| -pth_refs <refs_path> "
		"| -pth_subtitu <subtitles_path> "
		"]"
		"\n"
		"-h : print help.\n"
		"-v : print version.\n"
		"-tex : generate tex files.\n"
		"-pth_verses : set the verses path to <verses_path>.\n"
		"-pth_refs : set the references path to <refs_path>.\n"
		"-pth_subtitu : set the subtitles path to <subtitles_path>.\n"
		"\n"
		;

	version_str =
		"v0.1\n"
		"(c) 2018. QUIROGA BELTRAN, Jose Luis. c.c. 79523732. Bogota - Colombia.\n"
		;
		
	op_with_images = false;
	op_dbg_prt = -1;

	verses = NULL;
	subtitles = NULL;
	references = NULL;
	format = NULL;

	verse_line = NULL;
	ref_line = NULL;
	subtitu_line = NULL;

	verse_sz = 0;
	ref_sz = 0;
	subtitu_sz = 0;
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
		} else if(the_arg == "-paths"){
			prt_paths = true;
		} else if(the_arg == "-with_images"){
			op_with_images = true;
		} else if((the_arg == "-pth_verses") && ((ii + 1) < argc)){
			int kk_idx = ii + 1;
			ii++;

			verses_pth = argv[kk_idx];
		} else if((the_arg == "-pth_refs") && ((ii + 1) < argc)){
			int kk_idx = ii + 1;
			ii++;

			refs_pth = argv[kk_idx];
		} else if((the_arg == "-pth_subtitu") && ((ii + 1) < argc)){
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
	subtitles = open_file(refs_pth);
	references = open_file(subtitu_pth);

	return true;
}

tex_gen::~tex_gen(){
	if(verses != NULL){ fclose(verses); }
	if(subtitles != NULL){ fclose(subtitles); }
	if(references != NULL){ fclose(references); }

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

	txg.test_print_file();

	return 0;
}

char*
tex_gen::get_line(FILE* ff){
	size_t read_sz;
	char* resp = NULL;
	if(ff == verses){
		read_sz = getline(&verse_line, &verse_sz, verses);
		resp = verse_line;
	}
	else if(ff == subtitles){
		read_sz = getline(&subtitu_line, &subtitu_sz, subtitles);
		resp = subtitu_line;
	}
	else if(ff == references){
		read_sz = getline(&ref_line, &ref_sz, references);
		resp = ref_line;
	} 
	else {
		return NULL;
	}

	if(read_sz == -1){ return NULL; }
	return resp;
}

char*
tex_gen::get_key(char* line, verse_key& vk, char the_sep){
	vk.init_verse_key();
	char* pt_str = line;
	char* pt_sep = NULL;
	for(int aa = 0; aa < 3; aa++){
		pt_sep = strchr(pt_str, the_sep);
		if(pt_sep == NULL){ 
			fprintf(stderr, "ERROR. Cannot find separator '%c' in line:\n%s\n\n", the_sep, line);
			exit(1);;
		}
		*pt_sep = '\0';
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
	value = get_key(value, vk, GB_KRF_SEP);
	if(*value == GB_KEY_SEP){
		return false;
	}
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
	char* ln = NULL;
	char* val = NULL;
	verse_key vk;
	verse_key prv_vk;
	while((ln = get_line(ff)) != NULL){
		printf("%s", ln);
		/*
		val = get_key(ln, vk);
		printf("PRV_KEY= %d %d %d ", prv_vk.book, prv_vk.chapter, prv_vk.verse);
		printf("KEY= %d %d %d \n\tVAL= %s", vk.book, vk.chapter, vk.verse, val);
		GB_CK(cmp_verse_key(prv_vk, vk) == -1);
		prv_vk = vk;
		*/
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

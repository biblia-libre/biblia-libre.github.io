

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

FILE*
prog_args::open_file(file_pth_t id){
	FILE* fpth = fopen(INPUT_PATHS[id], "r");
	if(fpth == NULL){
		fprintf(stderr, "ERROR. Can NOT open file %s\n", INPUT_PATHS[id]);
		exit(1);;
	}
	return fpth;
}

void
prog_args::init_prog_args(){

	help_str =
		"[-h | -v | -paths] "
		"-pth_verses <verses_path> \n"
		"\n"
		"-h : print help.\n"
		"-v : print version.\n"
		"-paths : print the paths to be used.\n"
		"-pth_verses : set the verses path to <verses_path>.\n"
		"\n"
		;

	version_str =
		"v0.1\n"
		"(c) 2018. QUIROGA BELTRAN, Jose Luis. c.c. 79523732. Bogota - Colombia.\n"
		;
		
	op_with_images = false;
	op_pth_verses = "./ALL_VERSES.txt";

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

void 
prog_args::print_paths(){
	gb_ostream& os = gb_out;
	
	os << "pth_verses = " << op_pth_verses << "\n";
}

bool
prog_args::get_args(int argc, char** argv)
{
	gb_ostream& os = gb_out;
	MARK_USED(os);

	bool prt_help = false;
	bool prt_version = false;
	bool prt_paths = false;
	
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

			op_pth_verses = argv[kk_idx];
		}
	}
	
	if(prt_help){
		os << argv[0] << " " << help_str << "\n";
		return false;
	}
	if(prt_version){
		os << argv[0] << " " << version_str << "\n";
		return false;
	}
	if(prt_paths){
		print_paths();
		return false;
	}

	verses = open_file(gb_verses_pth);
	subtitles = open_file(gb_refs_pth);
	references = open_file(gb_subtitu_pth);

	return true;
}

prog_args::~prog_args(){
	if(verses != NULL){ fclose(verses); }
	if(subtitles != NULL){ fclose(subtitles); }
	if(references != NULL){ fclose(references); }
}


int main(int argc, char **argv){
	gb_ostream& os = gb_out;
	prog_args the_args;

	bool args_ok = the_args.get_args(argc, argv);
	if(args_ok){
		os << "ARGS_OK\n";
	}

	return 0;
}

bool
prog_args::get_line(FILE* ff){
	size_t read_sz;

	if(ff == verses){
		if(verse_line != NULL){ free(verse_line); }
		verse_line = NULL;
		verse_sz = 0;
		read_sz = getline(&verse_line, &verse_sz, verses);
		if(read_sz == -1){ free(verse_line); verse_line = NULL; return false; }
	}
	else if(ff == subtitles){
		if(subtitu_line != NULL){ free(subtitu_line); }
		subtitu_line = NULL;
		subtitu_sz = 0;
		read_sz = getline(&subtitu_line, &subtitu_sz, subtitles);
		if(read_sz == -1){ free(subtitu_line); subtitu_line = NULL; return false; }
	}
	else if(ff == references){
		if(ref_line != NULL){ free(ref_line); }
		ref_line = NULL;
		ref_sz = 0;
		read_sz = getline(&ref_line, &ref_sz, references);
		if(read_sz == -1){ free(ref_line); ref_line = NULL; return false; }
	} 
	else {
		return false;
	}
	return true;
}

char*
prog_args::get_key(char* line, int& book, int& chapter, int& verse){
	book = -1;
	chapter = -1;
	verse = -1;
	char* pt_str = line;
	char* pt_sep = NULL;
	for(int aa = 0; aa < 3; aa++){
		pt_sep = strchr(pt_str, GB_KEY_SEP);
		if(pt_sep == NULL){ 
			fprintf(stderr, "ERROR. Cannot find separator '%c' in line:\n%s\n\n", GB_KEY_SEP, line);
			exit(1);;
		}
		*pt_sep = '\0';
		switch(aa){
		case 0:
			book = atoi(pt_str);
		break;
		case 1:
			chapter = atoi(pt_str);
		break;
		case 2:
			verse = atoi(pt_str);
		break;
		}
		*pt_sep = GB_KEY_SEP;
		pt_str = pt_sep + 1;
	}
	return pt_str;
}

bool
prog_args::get_ref(char* value, int& book, int& chapter, int& verse){
	book = -1;
	chapter = -1;
	verse = -1;
	char* pt_str = value;
	char* pt_sep = NULL;
	if(*pt_str != GB_REF_SEP){
		fprintf(stderr, "ERROR. Cannot find separator '%c' in value:\n%s\n\n", GB_REF_SEP, value);
		exit(1);;
	}
	pt_sep = strchr(pt_str, GB_KEY_SEP);
	
}


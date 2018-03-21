
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//include <regex.h> 

int parse_seps(int argc, char **argv){
	FILE *stream;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	assert(sizeof(char) == 1);

	if( argc < 2 ){
		fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
		return(1);
	}

	stream = fopen(argv[1], "r");
	if(stream == NULL){
		exit(EXIT_FAILURE);
	}

	while ((read = getline(&line, &len, stream)) != -1) {
		char* pt_ln = line;
		char* pt_oeln = (line + read);
		char* eo_book = strchr(line, ' ');
		char* book = strndup(line, (eo_book - line));

		char* nxt_sep = strchr(pt_ln, ';');
		while((nxt_sep != NULL) && (pt_ln < pt_oeln)){
			assert(*nxt_sep == ';');
			*nxt_sep = '\0';
			printf("%s\n%s", pt_ln, book);
			*nxt_sep = ';';

			pt_ln = nxt_sep + 1;
			nxt_sep = strchr(pt_ln, ';');
		}
		if(pt_ln < pt_oeln){
			printf("%s", pt_ln);
		}

		//printf("%s", line);
		//printf("---------\n");

		free(book);
	}

	free(line);
	fclose(stream);
	exit(EXIT_SUCCESS);
}

int parse_ranges(int argc, char **argv){
	FILE *stream;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	assert(sizeof(char) == 1);

	if( argc < 2 ){
		fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
		return(1);
	}

	stream = fopen(argv[1], "r");
	if(stream == NULL){
		exit(EXIT_FAILURE);
	}

	while ((read = getline(&line, &len, stream)) != -1) {
		char* pt_ln = line;
		char* pt_oeln = (line + read);
		char* eo_book = strchr(line, ' ');
		char* book = strndup(line, (eo_book - line));

		char* fst_rng = strchr(line, '-');
		if(fst_rng != NULL){
			assert(*fst_rng == '-');
			*fst_rng = '\0';

			assert((fst_rng + 1) < pt_oeln);
			if(strchr(fst_rng + 1, '-') != NULL){
				printf("ERROR ======================================\n");
			} else {
				char* sec_rng = strchr(fst_rng + 1, ':');
				if(sec_rng != NULL){
					pt_ln = fst_rng + 1;
					printf("%s > %s ", line, book);
				}
			}
			*fst_rng = '-';
		}
		if(pt_ln < pt_oeln){
			printf("%s", pt_ln);
		}

		//printf("%s", line);
		//printf("---------\n");

		free(book);
	}

	free(line);
	fclose(stream);
	exit(EXIT_SUCCESS);
}

int parse_commas(int argc, char **argv){
	FILE *stream;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	assert(sizeof(char) == 1);

	if( argc < 2 ){
		fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
		return(1);
	}

	stream = fopen(argv[1], "r");
	if(stream == NULL){
		exit(EXIT_FAILURE);
	}

	while ((read = getline(&line, &len, stream)) != -1) {
		char* pt_ln = line;
		char* pt_oeln = (line + read);
		char* eo_book = strchr(line, ':');
		char* chapt = strndup(line, (eo_book - line + 1));

		char* nxt_sep = strchr(pt_ln, ',');
		while((nxt_sep != NULL) && (pt_ln < pt_oeln)){
			assert(*nxt_sep == ',');
			*nxt_sep = '\0';
			printf("%s\n%s", pt_ln, chapt);
			*nxt_sep = ',';

			pt_ln = nxt_sep + 1;
			nxt_sep = strchr(pt_ln, ',');
		}
		if(pt_ln < pt_oeln){
			printf("%s", pt_ln);
		}

		//printf("%s", line);
		//printf("---------\n");

		free(chapt);
	}

	free(line);
	fclose(stream);
	exit(EXIT_SUCCESS);
}

char* first_non_digit(char* pt_str, bool side){
	while(isdigit(*pt_str)){
		if(side){ pt_str++; } 
		else { pt_str--; }
	}
	return pt_str;
}

int parse_verse_ranges(int argc, char **argv){
	FILE *stream;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	assert(sizeof(char) == 1);

	if( argc < 2 ){
		fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
		return(1);
	}

	stream = fopen(argv[1], "r");
	if(stream == NULL){
		exit(EXIT_FAILURE);
	}

	while ((read = getline(&line, &len, stream)) != -1) {
		char* pt_ln = line;
		char* pt_oeln = (line + read);
		char* eo_chapt = strchr(line, ':');
		char* chapt = strndup(line, (eo_chapt - line + 1));

		char* fst_rng = strchr(line, '-');
		if(fst_rng != NULL){
			assert(*fst_rng == '-');
			*fst_rng = '\0';

			assert((fst_rng + 1) < pt_oeln);
			assert((fst_rng - 1) > line);

			char* rgt = first_non_digit(fst_rng + 1, true);
			char* lft = first_non_digit(fst_rng - 1, false);

			assert(rgt < pt_oeln);
			assert((lft + 1) > line);

			if(strchr(fst_rng + 1, '-') != NULL){
				printf("ERROR ======================================\n");
			} else {
				char* str_max = strndup(fst_rng + 1, (rgt - fst_rng - 1));
				char* str_min = strndup(lft + 1, (fst_rng - lft + 1));
				int val_min = atoi(str_min);
				int val_max = atoi(str_max);

				assert(val_min < val_max);
		
				pt_ln = NULL;

				for(int aa = val_min; aa <= val_max; aa++){
					printf("%s%d\n", chapt, aa);
				}
			}

			*fst_rng = '-';
		}
		if(pt_ln != NULL){
			printf("%s", pt_ln);
		}

		//printf("%s", line);
		//printf("---------\n");

		free(chapt);
	}

	free(line);
	fclose(stream);
	exit(EXIT_SUCCESS);
}

FILE *all_verses = NULL;

void
fill_verses(ssize_t fst_sz, char* first, char* last){
	assert(first != NULL);
	assert(all_verses != NULL);

	rewind(all_verses);

	char *verse = NULL;
	size_t vlen = 0;
	ssize_t vread;

	bool ok1 = false;
	bool ok2 = false;
	bool prt_vrse = false;
	bool is_last = false;
	while ((vread = getline(&verse, &vlen, all_verses)) != -1) {
		if(strncmp(verse, first, fst_sz) == 0){
			ok1 = true;
			prt_vrse = true;
		} else {
			if(prt_vrse && (last == NULL)){
				ok2 = true;
				break; 
			}
		}
		if((last != NULL) && (strncmp(verse, last, vread) == 0)){
			ok2 = true;
			is_last = true;
		}
		if(prt_vrse){
			printf("%s", verse);
		}
		if(is_last){ break; }
	}
	assert(ok1);
	assert(ok2);

	free(verse);
}

int complete_ranges(int argc, char **argv){
	FILE *stream;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	char *line2 = NULL;
	size_t len2 = 0;
	ssize_t read2;

	assert(sizeof(char) == 1);

	if( argc < 2 ){
		fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
		return(1);
	}

	all_verses = fopen("VERSES", "r");
	if(all_verses == NULL){
		fprintf(stderr, "Cannot find file 'VERSES'\n");
		exit(EXIT_FAILURE);
	}

	stream = fopen(argv[1], "r");
	if(stream == NULL){
		exit(EXIT_FAILURE);
	}

	while ((read = getline(&line, &len, stream)) != -1) {
		char* pt_ln = line;
		char* pt_oeln = (line + read);

		char* fst_rng = strchr(line, '>');
		if(fst_rng != NULL){
			if((read2 = getline(&line2, &len2, stream)) == -1) {
				printf("ERROR ======================================\n");
				exit(EXIT_FAILURE);
			}
			assert(*fst_rng == '>');
			*fst_rng = '\0';

			fill_verses((fst_rng - line), line, line2);

			pt_ln = NULL;

			*fst_rng = '>';
		}
		if(pt_ln != NULL){
			printf("%s", pt_ln);
		}

		//printf("%s", line);
		//printf("---------\n");
	}

	free(line);
	free(line2);
	fclose(all_verses);
	fclose(stream);
	exit(EXIT_SUCCESS);
}

int complete_psalms(int argc, char **argv){
	FILE *stream;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	assert(sizeof(char) == 1);

	if( argc < 2 ){
		fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
		return(1);
	}

	all_verses = fopen("VERSES", "r");
	if(all_verses == NULL){
		fprintf(stderr, "Cannot find file 'VERSES'\n");
		exit(EXIT_FAILURE);
	}

	stream = fopen(argv[1], "r");
	if(stream == NULL){
		exit(EXIT_FAILURE);
	}

	while ((read = getline(&line, &len, stream)) != -1) {
		char* pt_ln = line;

		if(strncmp(line, "19+", 3) != 0){
			printf("%s", pt_ln);
			continue;
		}

		//printf("%s", pt_ln);
		fill_verses(read - 1, line, NULL);
	}

	free(line);
	fclose(all_verses);
	fclose(stream);
	exit(EXIT_SUCCESS);
}

int main(int argc, char **argv){
	return complete_ranges(argc, argv);
}


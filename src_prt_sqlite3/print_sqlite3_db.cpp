

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

char* the_sep = NULL;

static int callback(void *the_prm, int argc, char **argv, char **azColName){
	int i;
	for(i=0; i<argc; i++){
		if(the_sep == NULL){
			printf("%s = %s\n", azColName[i], (argv[i] ? argv[i] : "NULL"));
		} else {
			printf("%s%s", (argv[i] ? argv[i] : "NULL"), the_sep);
		}
	}
	printf("\n");
	return 0;
}

int main(int argc, char **argv){
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;

	if( argc < 3 ){
		fprintf(stderr, "Usage: %s <DATABASE> <SQL-STATEMENT> [<separator>] \n", argv[0]);
		return(1);
	}
	rc = sqlite3_open(argv[1], &db);
	if( rc ){
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return(1);
	}

	if(argc > 3){
		the_sep = strdup(argv[3]);
	}

	rc = sqlite3_exec(db, argv[2], callback, 0, &zErrMsg);
	if( rc!=SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	sqlite3_close(db);

	if(the_sep != NULL){
		free(the_sep);
	}

	return 0;
}

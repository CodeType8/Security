#include <crypt.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define SHDW_LINE_LEN 256
#define WORD_LEN 80
#define HASH 256
#define ID 100
#define SALT 20

typedef struct store {
	char id[ID];
	char hash[HASH];
	char salt[SALT];
} Store;

int main(){

	FILE *shadow;
	FILE *dict;
	Store data[10];

	shadow = fopen("shadow", "r");
	if(shadow == NULL){
		fprintf(stderr, "Cannot open shadow file \n");
		exit(1);
	}

	dict = fopen("words.txt", "r");
	if(dict == NULL){
		fprintf(stderr, "Cannot open dict file\n");
		exit(1);
	}

	char shdw_line[SHDW_LINE_LEN];
	int num_accounts = 0;
	while(fgets(shdw_line, SHDW_LINE_LEN, shadow)!=NULL){
		char *token = strtok(shdw_line, ":");
		strcpy(data[num_accounts].id, token);
		printf("ID: %s\n", token);
		char *shdw_hash = strtok(NULL, ":");
		if(strcmp(shdw_hash, "*")!=0 && strcmp(shdw_hash, "!")!=0){
			token = strtok(shdw_hash, "$");
			token = strtok(NULL, "$");
			strcpy(data[num_accounts].salt, "$6$");
			strcat(data[num_accounts].salt, token);
			printf("  salt: %s\n", token);
			token = strtok(NULL, "$");
			strcpy(data[num_accounts].hash, token);
			printf("  hash: %s\n", token);
			num_accounts++;
			//////////////////////
			// Part A: 
			//  These values need to 
			//  be stored in an array
			//////////////////////
		}
	}

	char word[WORD_LEN];
	char *hash;
	int checker;

	printf("\n\n\n==================Cracking Start==================\n\n");

	while(fgets(word, WORD_LEN, dict)!=NULL){
		word[strlen(word)-1] = 0;

		for(int i=0; i<num_accounts; i++){
			hash = crypt(word, data[i].salt);
			checker = strcmp(data[i].hash, hash + 12);
			
			if (checker == 0)
			{
				printf("ID: %s\nPassword: %s\n\n", data[i].id, word);
			}

			//////////////////////
			// Part B: 
			//  For each account, compute
			//  the hash for that dictionary
			//  word and the users known salt
			//  as shown below:
			//     hash = crypt("password", "$6$_____");
			//  then check if the password is 
			//  the same as that users entry 
			//  from  /etc/shadow, if so
			//  you've successfully cracked it,
			//  print the password and userid
			//////////////////////

			//$ gcc -o passwd_cracker passwd_cracker.c -lcrypt
		}
	}
}

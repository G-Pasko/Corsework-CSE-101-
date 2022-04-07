#include <stdio.h>
#include <string.h>
//#include <unistd.h>
#include <stdlib.h>
#include "List.h"

extern char *strdup(const char *);

int main(int argc, char* argv[]){
	if(argc != 3){
		fprintf(stderr, "Incorrect number of files provided\n");
		return 0;
	}
	char buff[512];
	int lines = 0;
	FILE *input = fopen(argv[1], "r");
	FILE *output = fopen(argv[2], "w");
	while((fgets(buff, 512, input) != NULL)){
		lines ++;
	}
	rewind(input);
	char** words = (char **)calloc(lines, sizeof(char*));
	int i = 0;
	char buff2[512];
	while((fgets(buff2, 512, input) != NULL)){
		words[i] = strdup(buff2);
		i++;
	}
	//printf("%s\n", words[0]);
	int length = i;
	/*
	for(i = 0; i < length; i++){
		printf("%s", words[i]);
	}*/
	List new = newList();
	append(new, 0);

	//printf("%d\n", length);

	for(int j = 1; j < length; j++){
		moveFront(new);	
		//printf("For loop cycle: %d\n", j);
		while(index(new) >= 0){
			if(strcmp(words[j], words[get(new)]) <= 0){
				insertBefore(new, j);
				//append(new, j);
				//printf("New number added before: %d\n", j);
				break;
			}
			else{
				moveNext(new);
			}
		}
		if(index(new) < 0){
			append(new, j);
		}

		//printf("New number added before: %d\n", j);
	}

	//printList(stdout, new);

	//printf("\nWords have been sorted\n");
	moveFront(new);
	for(i = 0; i < length; i++){
		//printf("%d\n", i);
		fprintf(output, "%s", words[get(new)]);
		moveNext(new);
	}

	freeList(&new);

	for(i = 0; i < length; i++){
		free(words[i]);
	}
	free(words);
	fclose(input);
	fclose(output);
	return 0;
}
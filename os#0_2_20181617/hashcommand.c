#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "hashcommand.h"
#include "main.h"

void hashcommand(char* input){
	//printf("hashcommand function\n");

	char arr[4][10]={'\0',};
	int i=0;
	char*ptr=strtok(input, " _");
	while(ptr!=NULL){
		strcpy(arr[i], ptr);
		ptr=strtok(NULL, " _");
		i++;
	}
	struct hashlink* temp;
	if(!strcmp(arr[1], "insert")){
		//printf("hash insert\n");
		temp=hash_namefind(arr[2]);
		struct hash_elem2 *new=(struct hash_elem2*)malloc(sizeof(struct hash_elem2));
		new->data=atoi(arr[3]);
		hash_insert(temp->hash, &new->hash_elem);
	}
	else if(!strcmp(arr[1], "apply")){
		//printf("hash apply\n");
		temp=hash_namefind(arr[2]);
		if(!strcmp(arr[3], "square"))
			hash_apply(temp->hash, hash_action_square);
		else if(!strcmp(arr[3], "triple"))
			hash_apply(temp->hash, hash_action_triple);
		
	}
	else if(!strcmp(arr[1], "delete")){
		//printf("hash delete\n");
		temp=hash_namefind(arr[2]);
		struct hash_elem2* del=(struct hash_elem2*)malloc(sizeof(struct hash_elem2));
		del->data=atoi(arr[3]);

		hash_delete(temp->hash, &del->hash_elem);
	}
	else if(!strcmp(arr[1], "empty")){
		//printf("hash empty\n");
		temp=hash_namefind(arr[2]);
		if(hash_empty(temp->hash)==true)
			printf("true\n");
		else
			printf("false\n");
	}
	else if(!strcmp(arr[1], "size")){
		//printf("hash size\n");
		temp=hash_namefind(arr[2]);
		printf("%zu\n", hash_size(temp->hash));

	}
	else if(!strcmp(arr[1], "clear")){
		//printf("hash clear\n");
		temp=hash_namefind(arr[2]);
		hash_clear(temp->hash, NULL);
	}
	else if(!strcmp(arr[1], "find")){
		//printf("hash find\n");
		temp=hash_namefind(arr[2]);
		struct hash_elem2* elem2=(struct hash_elem2*)malloc(sizeof(struct hash_elem2));
		elem2->data=atoi(arr[3]);

		if(hash_find(temp->hash, &elem2->hash_elem))
			printf("%d\n", elem2->data);
	}
	else if(!strcmp(arr[1], "replace")){
		//printf("hash replace\n");
		temp=hash_namefind(arr[2]);
		struct hash_elem2* elem2=(struct hash_elem2*)malloc(sizeof(struct hash_elem2));
		elem2->data=atoi(arr[3]);

		hash_replace(temp->hash, &elem2->hash_elem);
	}

}

struct hashlink*  hash_namefind(char* name){
	struct hashlink* temp=hashlink_head;
	while(1){
		if(!strcmp(temp->name, name)){
			return temp;
		}
		else
			temp=temp->next;
	}
}

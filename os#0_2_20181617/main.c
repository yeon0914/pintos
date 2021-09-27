#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bitmap.h"
#include "hash.h"
#include "list.h"
#include "limits.h"
#include "bitmapcommand.h"
#include "hashcommand.h"
#include "listcommand.h"
#include "main.h"

int main(){
	char input[50];
	bitmaplink_head=NULL;
	hashlink_head=NULL;
	listlink_head=NULL;


	while(1){
		fgets(input, 50, stdin);
		input[strlen(input)-1]='\0';

		//printf("input command : %s\n", input);

		if(!strncmp(input, "quit", 4)){				//quit
			exit(1);
		}
		else if(!strncmp(input, "create", 6)){		//create ...
			createcommand(input);
		}
		else if(!strncmp(input, "dumpdata", 8)){
			dumpcommand(input);
		}
		else if(!strncmp(input, "delete", 6)){
			deletecommand(input);
		}
		else if(!strncmp(input, "bitmap", 6)){
			bitmapcommand(input);
		}
		else if(!strncmp(input, "hash", 4)){
			hashcommand(input);
		}
		else if(!strncmp(input, "list", 4)){
			listcommand(input);
		}









	}
}

void createcommand(char *input){
	//printf("createcommand function input : %s\n", input);

	char arr[4][10]={'\0', };
	int i=0;
	char *ptr = strtok(input, " ");
	while(ptr!=NULL){
		strcpy(arr[i],ptr);
		ptr=strtok(NULL, " ");
		//printf("arr[%d] = %s\n", i, arr[i]);
		i++;
	}


	if(!strcmp(arr[1], "bitmap")){
		//bitmap create command
		struct bitmaplink * new;
		new = (struct bitmaplink*)malloc(sizeof(struct bitmaplink));
		strcpy(new->name,arr[2]);
		new->bitmap = bitmap_create(atoi(arr[3]));
		new->next=NULL;
		if(bitmaplink_head==NULL)
			bitmaplink_head=new;
		else{
			struct bitmaplink* temp=bitmaplink_head;
			while(temp->next!=NULL)
				temp=temp->next;
			temp->next=new;
		}
		
		//printf("bitmapcreate done\n");
	}
	else if(!strcmp(arr[1], "hashtable")){
		struct hashlink* new;
		new = (struct hashlink*)malloc(sizeof(struct hashlink));
		new->hash=(struct hash*)malloc(sizeof(struct hash));
		strcpy(new->name,arr[2]);
		hash_init(new->hash, hash_function, hash_less, NULL);
		new->next=NULL;

		if(hashlink_head==NULL)
			hashlink_head=new;
		else{
			struct hashlink* temp=hashlink_head;
			while(temp->next!=NULL)
				temp = temp->next;
			temp->next=new;
		}

		//printf("hashtablecreate done\n");
	}
	else if(!strcmp(arr[1], "list")){
		struct listlink* new;
		new = (struct listlink*)malloc(sizeof(struct listlink));
		new->list=(struct list*)malloc(sizeof(struct list));
		strcpy(new->name, arr[2]);
		list_init(new->list);
		new->next=NULL;

		if(listlink_head==NULL)
			listlink_head=new;
		else{
			struct listlink * temp =listlink_head;
			while(temp->next!=NULL)
				temp=temp->next;
			temp->next=new;
		}
		//printf("listcreate done\n");
	}
	return;
}

void dumpcommand(char * input){
	//printf("dump command function input : %s\n", input);

	char arr[2][10]={'\0', };
	int i=0;
	char * ptr=strtok(input, " ");
	while(ptr!=NULL){
		strcpy(arr[i], ptr);
		ptr=strtok(NULL, " ");
		//printf("arr[%d]= %s\n", i, arr[i]);
		i++;
	}

	struct bitmaplink* temp1=bitmaplink_head;
	struct hashlink* temp2=hashlink_head;
	struct listlink* temp3 = listlink_head;

	while(1){
		if(temp1==NULL)
			break;
		if(!strcmp(temp1->name, arr[1])){
			//printf("dump bitmap\n");
			bitmap_dump2(temp1->bitmap);
			return;
		}
		else
			temp1=temp1->next;
		
	}
	//printf("**");
	while(1){
		if(temp2==NULL)
			break;
		if(!strcmp(temp2->name, arr[1])){
			//printf("dump hashtable\n");
			hash_dump(temp2->hash);
			return;
		}
		else
			temp2=temp2->next;
	}

	while(1){
		if(temp3==NULL)
			break;
		if(!strcmp(temp3->name, arr[1])){
			//printf("dump linkedlist\n");
			list_dump(temp3->list);
			return;
		}
		else
			temp3=temp3->next;
	}


}

void deletecommand(char* input){
	//printf("delte command function input : %s\n", input);
	
	char arr[2][10]={'\0', };
	int i=0;
	char *ptr = strtok(input, " ");
	while(ptr!=NULL){
		strcpy(arr[i], ptr);
		ptr=strtok(NULL, " ");
		i++;
	}

	struct bitmaplink* temp1=bitmaplink_head;
	struct hashlink* temp2=hashlink_head;
	struct listlink* temp3=listlink_head;

	while(1){
		if(temp1==NULL)
			break;
		if(!strcmp(temp1->name, arr[1])){
			//printf("delete bitmap\n");
			bitmap_destroy(temp1->bitmap);
			struct bitmaplink* temp=bitmaplink_head;
			if(temp1==bitmaplink_head){
				bitmaplink_head=NULL;
				free(temp1);
				return;
			}
			while(temp->next!=temp1)
				temp=temp->next;
			temp->next=temp->next->next;
			free(temp1);
			return;
		}
		else 
			temp1=temp1->next;
	}

	while(1){
		if(temp2==NULL)
			break;
		if(!strcmp(temp2->name, arr[1])){
			//printf("delete hashtable\n");
			hash_destroy(temp2->hash, hash_free);
			struct hashlink* temp=hashlink_head;
			if(temp2==hashlink_head){
				free(temp2);
				hashlink_head=NULL;
				return;
			}
			while(temp->next!=temp2)
				temp=temp->next;
			temp->next=temp->next->next;
			free(temp2);
			return;
		}
		else
			temp2=temp2->next;
	}

	while(1){
		if(temp3==NULL)
			break;
		if(!strcmp(temp3->name, arr[1])){
			//printf("delete linkedlist\n");
			struct list_elem * listtemp=list_begin(temp3->list);
			while(list_empty(temp3->list)==false){
				listtemp=list_pop_front(temp3->list);
				struct list_item* item= list_entry(listtemp, struct list_item, elem);
				free(item);

				listtemp=list_begin(temp3->list);
			}
			struct listlink* temp=listlink_head;
			if(temp3==listlink_head){
				free(temp3);
				listlink_head=NULL;
				return;
			}
			while(temp->next!=temp3)
				temp=temp->next;
			temp->next=temp->next->next;
			free(temp3);

			return;
		}
		else
			temp3=temp3->next;
	}

}

void bitmap_dump2(struct bitmap* bitmap){
	int i=0;
	for(i=0; i<bitmap_size(bitmap); i++){
		if(bitmap_test(bitmap, i)==true)
			printf("1");
		else
			printf("0");
	}
	printf("\n");
	return;
}

void hash_dump(struct hash* hash){
	if(hash_empty(hash)==1)
		return;
	struct hash_iterator  temp;
	hash_first(&temp, hash);
	hash_next(&temp);

	while(1){
		struct hash_elem2 * elem2=hash_entry(hash_cur(&temp), struct hash_elem2, hash_elem);
		printf("%d ", elem2->data);

		if(!hash_next(&temp))
			break;
	}
	printf("\n");
	return;
}

void list_dump(struct list* list){
	if(list_empty(list))
		return;
	struct list_elem* elem=list_begin(list);
	while(list_end(list)!=elem){
		struct list_item* item = list_entry(elem, struct list_item, elem);

		printf("%d ", item->data);

		elem=list_next(elem);
	}
	printf("\n");
	return;
}

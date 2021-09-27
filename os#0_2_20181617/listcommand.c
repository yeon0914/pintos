#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "listcommand.h"
#include "main.h"

void listcommand(char*input){
	//printf("listcommand function\n");

	char arr[7][10]={'\0',};
	int i=0;
	char*ptr=strtok(input, " _");
	while(ptr!=NULL){
		strcpy(arr[i], ptr);
		ptr=strtok(NULL, " _");
		i++;
	}
	struct listlink* temp;
	if(!strcmp(arr[1], "push")&&!strcmp(arr[2], "back")){
		//printf("list push back\n");
		temp=list_find(arr[3]);
		struct list_item* new=(struct list_item*)malloc(sizeof(struct list_item));
		new->data=atoi(arr[4]);
		list_push_back(temp->list, &new->elem);
	}
	else if(!strcmp(arr[1], "push")&&!strcmp(arr[2], "front")){
		//printf("list push front\n");
		temp=list_find(arr[3]);
		struct list_item* new=(struct list_item*)malloc(sizeof(struct list_item));
		new->data=atoi(arr[4]);
		list_push_front(temp->list, &new->elem);
	}
	else if(!strcmp(arr[1], "front")){
		//printf("list front\n");
		temp=list_find(arr[2]);
		struct list_item* new;
		struct list_elem* new2;
		new2=list_front(temp->list);
		new=list_entry(new2, struct list_item, elem);

		printf("%d\n", new->data);

	}
	else if(!strcmp(arr[1], "back")){
		//printf("list back\n");
		temp=list_find(arr[2]);
		struct list_item*new;
		struct list_elem* new2;
		new2=list_back(temp->list);
		new=list_entry(new2, struct list_item, elem);

		printf("%d\n", new->data);
	}
	else if(!strcmp(arr[1], "pop")&& !strcmp(arr[2], "back")){
		//printf("list pop back\n");
		temp=list_find(arr[3]);
		list_pop_back(temp->list);

	}
	else if(!strcmp(arr[1], "pop")&&!strcmp(arr[2],"front")){
		//printf("list pop front\n");
		temp=list_find(arr[3]);
		list_pop_front(temp->list);
	}
	else if(!strcmp(arr[1], "insert")&&!(strcmp(arr[2], "ordered"))){
		//printf("list insert ordered\n");
		temp=list_find(arr[3]);
		struct list_item*new=(struct list_item*)malloc(sizeof(struct list_item));
		new->data=atoi(arr[4]);

		list_insert_ordered(temp->list, &new->elem, list_less, NULL);
	}
	else if(!strcmp(arr[1], "insert")){
		//printf("list insert\n");
		temp=list_find(arr[2]);
		struct list_item * new=(struct list_item*)malloc(sizeof(struct list_item));
		new->data=atoi(arr[4]);
		int count=0;
		struct list_elem *before=list_head(temp->list);
		while(count<=atoi(arr[3])){
			before=before->next;
			count++;
		}

		list_insert(before, &new->elem);
	}
	else if(!strcmp(arr[1], "empty")){
		//printf("list empty\n");
		temp=list_find(arr[2]);
		if(list_empty(temp->list)==true)
			printf("true\n");
		else
			printf("false\n");
	}
	else if(!strcmp(arr[1], "size")){
		//printf("list size\n");
		temp=list_find(arr[2]);

		printf("%zu\n", list_size(temp->list));
	}
	else if(!strcmp(arr[1], "max")){
		//printf("list max\n");
		temp=list_find(arr[2]);

		struct list_elem* ptr1=(struct list_elem*)malloc(sizeof(struct list_elem));
		ptr1=list_max(temp->list, list_less, NULL);
		struct list_item* ptr2=(struct list_item*)malloc(sizeof(struct list_item));
		ptr2=list_entry(ptr1, struct list_item, elem);

		printf("%d\n", ptr2->data);

	}
	else if(!strcmp(arr[1], "min")){
		//printf("list min\n");
		temp=list_find(arr[2]);

		struct list_elem* ptr1=(struct list_elem*)malloc(sizeof(struct list_elem));
		ptr1=list_min(temp->list, list_less, NULL);
		struct list_item* ptr2=(struct list_item*)malloc(sizeof(struct list_item));
		ptr2=list_entry(ptr1, struct list_item, elem);

		printf("%d\n", ptr2->data);
	}
	else if(!strcmp(arr[1], "remove")){
		//printf("list remove\n");
		temp=list_find(arr[2]);

		struct list_elem* ptr=list_head(temp->list);
		int count=0;
		while(count<=atoi(arr[3])){
			ptr=ptr->next;
			count++;
		}
		list_remove(ptr);
	}
	else if(!strcmp(arr[1], "reverse")){
		//printf("list reverse\n");
		temp=list_find(arr[2]);

		list_reverse(temp->list);
	}
	else if(!strcmp(arr[1], "shuffle")){
		//printf("list shuffle\n");
		temp=list_find(arr[2]);

		list_shuffle(temp->list);
	}
	else if(!strcmp(arr[1], "swap")){
		//printf("list swap\n");
		temp=list_find(arr[2]);
		
		struct list_elem* a=list_head(temp->list);
		struct list_elem* b=list_head(temp->list);
		int count=0;
		while(count<=atoi(arr[3])){
			a=a->next;
			count++;
		}
		count=0;
		while(count<=atoi(arr[4])){
			b=b->next;
			count++;
		}

		list_swap(a, b);
	}
	else if(!strcmp(arr[1], "sort")){
		//printf("list sort\n");
		temp=list_find(arr[2]);

		list_sort(temp->list, list_less, NULL);
	}
	else if(!strcmp(arr[1], "splice")){
		//printf("list splice\n");
		temp=list_find(arr[2]);
		struct listlink* temp2=list_find(arr[4]);
		int count=0;

		struct list_elem* before = list_head(temp->list);
		while(count<=atoi(arr[3])){
			before=before->next;
			count++;
		}
		struct list_elem* first=list_head(temp2->list);
		struct list_elem* last=list_head(temp2->list);
		count=0;
		while(count<=atoi(arr[6])){
			last=last->next;
			count++;
		}

		count=0;
		while(count<=atoi(arr[5])){
			first=first->next;
			count++;
		}

		list_splice(before, first, last);
	}
	else if(!strcmp(arr[1], "unique")){
		//printf("list unique\n");
		temp=list_find(arr[2]);
		if(arr[3][0]=='\0'){
			list_unique(temp->list, NULL, list_less, NULL);
		}
		else{
			struct listlink* temp2=list_find(arr[3]);
			list_unique(temp->list, temp2->list, list_less, NULL);
		}
	}
}

struct listlink* list_find(char* name){
	struct listlink* temp=listlink_head;
	while(1){
		if(!strcmp(temp->name, name))
			return temp;
		else
			temp=temp->next;
		if(temp==NULL)
			return NULL;
	}
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bitmap.h"
#include "bitmapcommand.h"
#include "main.h"

void bitmapcommand(char* input){
	//printf("bitmapcommand function input : %s\n", input);
	
	char arr[8][10]={'\0', };
	int i=0;
	char *ptr = strtok(input, " _");
	while(ptr!=NULL){
		strcpy(arr[i],ptr);
		ptr=strtok(NULL, " _");
		//printf("arr[%d] = %s\n", i, arr[i]);
		i++;
	}
	struct bitmaplink* temp;
	if(!strcmp(arr[1],"mark")){
		//printf("bitmap mark\n");
		temp = bitmap_find(arr[2]);
		bitmap_mark(temp->bitmap, atoi(arr[3]));
		//bitmap_dump2(temp->bitmap);
	}
	else if(!strcmp(arr[1], "all")){
		//printf("bitmap all\n");
		temp=bitmap_find(arr[2]);
		if(bitmap_all(temp->bitmap, atoi(arr[3]), atoi(arr[4]))==true)
			printf("true\n");
		else
			printf("false\n");
		
	}
	else if(!strcmp(arr[1], "any")){
		//printf("bitmap any\n");
		temp=bitmap_find(arr[2]);
		if(bitmap_any(temp->bitmap, atoi(arr[3]), atoi(arr[4]))==true)
			printf("true\n");
		else
			printf("false\n");
	}
	else if(!strcmp(arr[1], "contains")){
		//printf("bitmap contains\n");
		temp=bitmap_find(arr[2]);
		bool value;
		if(!strcmp(arr[5],"true"))
			value = true;
		else
			value = false;
		if(bitmap_contains(temp->bitmap, atoi(arr[3]),atoi(arr[4]), value)==true)
			printf("true\n");
		else
			printf("false\n");
	}
	else if(!strcmp(arr[1], "count")){
		//printf("bitmap count\n");
		temp=bitmap_find(arr[2]);
		bool value;
		if(!strcmp(arr[5], "true"))
			value =true;
		else
			value=false;
		printf("%zu\n", bitmap_count(temp->bitmap, atoi(arr[3]), atoi(arr[4]),value));
	}
	else if (!strcmp(arr[1], "dump")){
		//printf("bitmap dump\n");
		temp=bitmap_find(arr[2]);
		bitmap_dump(temp->bitmap);
	}
	else if(!strcmp(arr[1], "expand")){
		//printf("bitmap expand\n");
		temp=bitmap_find(arr[2]);
		temp->bitmap=bitmap_expand(temp->bitmap, atoi(arr[3]));
	}
	else if( !strcmp(arr[1],"set")&& !(strcmp(arr[2], "all"))){
		//printf("bitmap set all\n");
		temp=bitmap_find(arr[3]);
		bool value;
		if(!strcmp(arr[4],"true"))
			value = true;
		else 
			value = false;
		bitmap_set_all(temp->bitmap, value);
	}
	else if(!strcmp(arr[1], "set")&& !(strcmp(arr[2], "multiple"))){
		//printf("bitmap set multiple\n");
		temp = bitmap_find(arr[3]);
		bool value;
		if(!strcmp(arr[6], "true"))
			value = true;
		else
			value = false;
		bitmap_set_multiple(temp->bitmap, atoi(arr[4]), atoi(arr[5]), value);
	}
	else if(!strcmp(arr[1], "set")){
		//printf("bitmap set\n");
		temp=bitmap_find(arr[2]);
		bool value;
		if(!strcmp(arr[4], "true"))
			value = true;
		else 
			value = false;
		bitmap_set(temp->bitmap, atoi(arr[3]), value);
	}
	else if(!strcmp(arr[1], "flip")){
		//printf("bitmap flip\n");
		temp=bitmap_find(arr[2]);
		bitmap_flip(temp->bitmap, atoi(arr[3]));
	}
	else if(!strcmp(arr[1], "none")){
		//printf("bitmap none\n");
		temp=bitmap_find(arr[2]);
		if(bitmap_none(temp->bitmap, atoi(arr[3]), atoi(arr[4]))==true)
			printf("true\n");
		else
			printf("false\n");
	}
	else if(!strcmp(arr[1], "reset")){
		//printf("bitmap reset\n");
		temp=bitmap_find(arr[2]);
		bitmap_reset(temp->bitmap, atoi(arr[3]));
	}
	else if(!strcmp(arr[1], "scan") && !(strcmp(arr[2], "and"))){
		//printf("bitmap scan and flip\n");
		temp = bitmap_find(arr[4]);
		bool value;
		if(!strcmp(arr[7],"true"))
			value = true;
		else
			value = false;
		printf("%zu\n", bitmap_scan_and_flip(temp->bitmap, atoi(arr[5]), atoi(arr[6]), value));
	}
	else if(!strcmp(arr[1], "scan")){
		//printf("bitmap scan\n");
		temp=bitmap_find(arr[2]);
		bool value;
		if(!strcmp(arr[5],"true"))
			value = true;
		else
			value = false;
		printf("%zu\n",bitmap_scan(temp->bitmap, atoi(arr[3]), atoi(arr[4]),value));
	}
	else if(!strcmp(arr[1], "size")){
		//printf("bitmap size\n");
		temp=bitmap_find(arr[2]);
		printf("%zu\n", bitmap_size(temp->bitmap));
	}
	else if(!strcmp(arr[1], "test")){
		//printf("bitmap test\n");
		temp = bitmap_find(arr[2]);
		if(bitmap_test(temp->bitmap, atoi(arr[3]))==true)
			printf("true\n");
		else
			printf("false\n");
	}

}



struct bitmaplink*  bitmap_find(char* name){
	struct bitmaplink*temp=bitmaplink_head;

	while(1){
		if(!strcmp(temp->name, name)){
			return temp; 
		}
		else
			temp=temp->next;

	}
}

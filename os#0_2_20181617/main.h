#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bitmap.h"
#include "list.h"
#include "hash.h"
#include "limits.h"

struct bitmaplink{
	char name[10];
	struct bitmap *bitmap;
	struct bitmaplink *next;
};
struct bitmaplink* bitmaplink_head;

struct hashlink{
	char name[10];
	struct hash* hash;
	struct hashlink * next;
};
struct hashlink* hashlink_head;

struct listlink{
	char name[10];
	struct list* list;
	struct listlink* next;
};
struct listlink* listlink_head;

void createcommand (char* );
void dumpcommand(char*);
void deletecommand(char*);
void bitmap_dump2(struct bitmap*);
void hash_dump(struct hash*);
void list_dump(struct list*);


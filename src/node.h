
#pragma once

#define true 1
#define false 0

struct node {
    char* key;
    void* value;
    struct node *next, *prev;
}; typedef struct node node;


void add_node(char*, void*);
void pop_node(char*);

void* get_node(char*);
void mod_node(char*, void*);
int has_node(char*);

node* map_get(char*);
node* map_end();

char** map_keys();
void** map_values();
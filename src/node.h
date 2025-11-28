
#pragma once

#define true 1
#define false 0

struct node {
    char* key;
    void* value;
    struct node *next, *prev;
}; typedef struct node node;


void add_node(char*, void*);
void rem_node(char*);

int has_node(char*);
void* get_node(char*);
void edt_node(char*, void*);

node* traverse_tree(char*, node*);
node* traverse_end(node*);
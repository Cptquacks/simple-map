#include <stdlib.h>
#include "node.h"

node *entry_node = NULL, *current_node = NULL;

void add_node(char *key, void *value) {
    /*
        This adds a node only if key and value aren't null
    */


    if (key == NULL || value == NULL) 
        return;

    node *new_node = (node*)malloc(sizeof(node)); // initialize the node after checking


    new_node->key = key;
    new_node->value = value;
    new_node->prev = NULL;
    new_node->next = NULL;


    if (entry_node == NULL) {
        entry_node = new_node; // If entry point is null then set entry point
        current_node = entry_node;
        return; 
    }

    new_node->prev = current_node;
    current_node->next = new_node;
    current_node = new_node;
    return;
}

void rem_node(char *key) {
    if (has_node(key) == false)
        return;

    node *target_node = traverse_tree(key, entry_node);

    if (target_node->next != NULL) {

        if (target_node->prev == NULL) 
            entry_node = target_node->next;
        
        else if (target_node->prev != NULL) {
            node* temporal_node = target_node->prev;
            temporal_node->next = target_node->next;
            free(temporal_node);
        }


    }

    else if(target_node->prev != NULL) {
        target_node->prev->next = NULL;
    }

    else if(entry_node->next == NULL) {
        entry_node = NULL;
    }

    free(target_node);
    current_node = traverse_end(entry_node);
    return;
}

int has_node(char *key) {
    return ( (traverse_tree(key, entry_node) == NULL) ? false : true);
}

void* get_node(char *key) {
    if (has_node(key) == false) 
        return NULL;
    
    return traverse_tree(key, entry_node)->value;
}

void edt_node(char *key, void *value) {
    if (value == NULL) 
        return;

    if (has_node(key) == false) 
        return;
    
    node* target_node = traverse_tree(key, entry_node);
    target_node->value = value;

    return;
}

node* traverse_tree(char *key, node *current_node) {
    if (*current_node->key == *key)
        return current_node;

    if (current_node->next == NULL)
        return NULL;
    
    return traverse_tree(key, current_node->next);
}

node* traverse_end(node* current_node) {

    if (current_node->next == NULL)
        return current_node;
    
    return traverse_end(current_node->next);
}
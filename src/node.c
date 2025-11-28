#include <stdlib.h>
#include <string.h>
#include "node.h"

node *entry_node = NULL, *current_node = NULL;

void add_node(char *key, void *value) {
    /*
        This adds a node only if key and value aren't null
    */


    if (key == NULL || value == NULL) 
        return;
    
    if (has_node(key)) {
        mod_node(key, value);
        return;
    }

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

void pop_node(char *key) {
    if (has_node(key) == false)
        return;

    node *target_node = map_get(key);

    if (target_node->next != NULL) {

        if (target_node->prev == NULL) 
            entry_node = target_node->next;
        
        else if (target_node->prev != NULL) {
            target_node->next->prev = target_node->next;
            target_node->next->prev = target_node->prev;
        }


    }

    else if(target_node->prev != NULL) {
        target_node->prev->next = NULL;
    }

    else if(entry_node->next == NULL) {
        entry_node = NULL;
    }

    free(target_node);
    current_node = map_end();
    return;
}

void* get_node(char *key) {
    if (has_node(key) == false) 
        return NULL;
    
    return map_get(key)->value;
}

void mod_node(char *key, void *value) {
    if (value == NULL) 
        return;

    if (has_node(key) == false) 
        return;
    
    node* target_node = map_get(key);
    target_node->value = value;

    return;
}

int has_node(char *key) {
    node* target_node = entry_node;

    while (target_node != NULL) {
        if (strcmp(target_node->key, key) == 0) {
            return true;
        }
        target_node = target_node->next;
    }
    return false;
}

node* map_get(char* key) {
    node* target_node = entry_node;
    while (strcmp(target_node->key, key) != 0) {
        target_node = target_node->next;
    }
    return target_node;
}

node* map_end() {
    node* target_node = entry_node;
    while (target_node->next != NULL) {
        target_node = target_node->next;
    }
    return target_node;
}

char** map_keys() {
    if (entry_node == NULL)
        return NULL;
    
    int size = 16, len = 0;
    char** new_array = malloc(size * sizeof(char*)); if (new_array == NULL) return NULL;
    node *target_node = entry_node;

    while (target_node != NULL) {

        if (len >= size) {
            size *= 2;
            new_array = realloc(new_array, size * sizeof(char*));
            
            if (new_array == NULL) {
                return NULL;
            }
        }

        new_array[len++] = target_node->key;
        target_node = target_node->next;

    }
    new_array[len] = NULL;

    char** short_array = new_array;
    short_array = realloc(short_array, len * sizeof(char*));

    if (short_array != NULL) {
        return short_array;
    }

    return new_array;
}

void** map_values() {
    if (entry_node == NULL)
        return NULL;
    
    int size = 16, len = 0;
    void** new_array = malloc(size * sizeof(void*)); if (new_array == NULL) return NULL;
    node *target_node = entry_node;

    while (target_node != NULL) {

        if (len >= size) {
            size *= 2;
            new_array = realloc(new_array, size * sizeof(void*));
            
            if (new_array == NULL) {
                return NULL;
            }
        }

        new_array[len++] = target_node->value;
        target_node = target_node->next;

    }
    new_array[len] = NULL;

    void** short_array = new_array;
    short_array = realloc(short_array, len * sizeof(void*));

    if (short_array != NULL) {
        return short_array;
    }

    return new_array;
}
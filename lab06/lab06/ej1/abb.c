#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "abb.h"

struct _s_abb {
    abb_elem elem;
    struct _s_abb *left;
    struct _s_abb *right;
};   
/*
static bool elem_eq(abb_elem a, abb_elem b) {
    return a == b;
}*/

static bool elem_less(abb_elem a, abb_elem b) {
    bool c= a < b;
    return c;
}

static bool invrep(abb tree) {
    bool inv= true;
    if (tree != NULL){
        if (tree->left != NULL){
            inv = inv && elem_less (tree->left->elem,tree->elem);
        }
        if (tree->right != NULL){
            inv = inv && elem_less (tree->elem,tree->right->elem);
        }

        inv = inv && invrep(tree->left) && invrep (tree->right);
    }

    return inv;
}

abb abb_empty(void) {
    abb tree= NULL;

    assert(invrep(tree) && abb_is_empty(tree));
    return tree;
}

abb abb_add(abb tree, abb_elem e) {
    assert(invrep(tree));

    if ( tree == NULL){
        abb new_node = malloc (sizeof (struct _s_abb));
        new_node->elem=e;
        new_node->left=NULL;
        new_node->right= NULL;
        tree=new_node;
    }
    else if (elem_less(e,tree->elem)){
        tree->left = abb_add (tree->left,e);
    }
    else{
        tree->right = abb_add (tree->right,e);
    }

    assert(invrep(tree) && abb_exists(tree, e));
    return tree;
}

bool abb_is_empty(abb tree) {
    assert(invrep(tree));
    return tree ==NULL;
}



bool abb_exists(abb tree, abb_elem e) {
    bool exists=false;
    assert(invrep(tree));
 
    if (tree != NULL){

        if (tree->elem == e){
            exists=true;
        }
        else{
            exists = abb_exists(tree->left,e) || abb_exists (tree->right,e);
        }
    }


    return exists   ;
}


unsigned int abb_length(abb tree) {
    unsigned int length=0;
    assert(invrep(tree));

    if ( tree == NULL) {
        length=0;
    }
    else{
        length += abb_length (tree->left) + abb_length (tree->right) +1;

    }


    assert(invrep(tree) && (abb_is_empty(tree) || length > 0));
    return length;
}



abb abb_remove(abb tree, abb_elem e) {

    assert(invrep(tree));
    if(tree != NULL){
        if(elem_less(e,tree->elem)){
            tree->left = abb_remove(tree->left,e);
        } else if(elem_less(tree->elem,e)){
            tree->right = abb_remove(tree->right,e);
        } else {
                abb temp = NULL;
            if (tree->left == NULL) {
                temp = tree;
                tree = tree->right;
                free(temp);
            } else if (tree->right == NULL) {
                temp = tree;
                tree = tree->left;
                free(temp);
            } else {
                temp = tree->right;
                while(temp && temp->left != NULL){
                    temp = temp->left;
                }

                tree->elem = temp->elem;
                tree->right = abb_remove(tree->right,temp->elem);
            }
        }
    }
    assert(invrep(tree) && !abb_exists(tree, e));
    return tree;
}


abb_elem abb_root(abb tree) {
    assert(invrep(tree) && !abb_is_empty(tree));

    abb_elem root = tree->elem;

    assert(abb_exists(tree, root));
    return root;
}



abb_elem abb_max(abb tree) {
    abb_elem max_e;
    
    abb aux = tree;

    while ( aux->right != NULL){
        aux = aux->right;
    }

    max_e = aux->elem;
    
    assert(invrep(tree) && abb_exists(tree, max_e));
    return max_e;
}



abb_elem abb_min(abb tree) {
    abb_elem min_e;

    abb aux = tree;

    while (aux->left != NULL){
        aux = aux->left;

    }

    min_e = aux->elem;


    assert(invrep(tree) && abb_exists(tree, min_e));
    return min_e;
}

void abb_dump(abb tree) {
    assert(invrep(tree));
    if (tree != NULL) {
        printf("%d ", tree->elem);
        abb_dump(tree->left);
        abb_dump(tree->right);
    }
}

abb abb_destroy(abb tree) {
    assert(invrep(tree));

    if (! abb_is_empty(tree)){
        abb_destroy(tree->right);
        abb_destroy(tree->left);
        free(tree);
   }

    tree=NULL;

    assert(tree == NULL);
    return tree;
}


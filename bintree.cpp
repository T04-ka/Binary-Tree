#define DEBUG

#include <stdlib.h>

#include "bintree.h"
#include "myformat.cpp"



//---------------------------------------------------------------------------------------------------------------------------------

tree_node_t* tree_node_create(tree_node_elem_t value) {

    tree_node_t* created_node_ptr = (tree_node_t*) calloc(1, sizeof(tree_node_t));

    created_node_ptr->value     = value;
    created_node_ptr->left      = NULL;
    created_node_ptr->right     = NULL;
    created_node_ptr->parent    = NULL;
    created_node_ptr->rank      = 0;

    return created_node_ptr;
}

//---------------------------------------------------------------------------------------------------------------------------------

void tree_node_destroy(tree_node_t* node_ptr) {

    if (node_ptr == NULL) {

        $err(RED FAT "NULL was passed as pointer to node in function %s %s:%d.\n" DEF,  __FUNCTION__, __FILE__, __LINE__);
        return;
    }

    free(node_ptr);
}

//---------------------------------------------------------------------------------------------------------------------------------

void tree_node_force_link(tree_node_t* parent_node_ptr, tree_node_t* daughter_node_ptr, tree_node_side_t side) {


    daughter_node_ptr->parent = parent_node_ptr;

    if (side == TREE_NODE_SIDE_LEFT) {

        parent_node_ptr->left = daughter_node_ptr;
    }
    else {

        parent_node_ptr->right = daughter_node_ptr;
    }

}

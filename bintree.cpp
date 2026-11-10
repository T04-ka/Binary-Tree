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

    return created_node_ptr;
}

//---------------------------------------------------------------------------------------------------------------------------------

void tree_node_destroy(tree_node_t* node_ptr) {

    ASSERT(node_ptr != NULL);

    free(node_ptr);
}

//---------------------------------------------------------------------------------------------------------------------------------

void tree_node_link(tree_node_t* parent_node_ptr, tree_node_t* daughter_node_ptr, tree_node_side_t side) {

    ASSERT(parent_node_ptr != 0);
    ASSERT(daughter_node_ptr != 0);

    WARNING(daughter_node_ptr->parent == NULL);
    daughter_node_ptr->parent = parent_node_ptr;

    if (side == TREE_NODE_SIDE_LEFT) {

        WARNING(parent_node_ptr->left == NULL);
        parent_node_ptr->left = daughter_node_ptr;
    }
    else {

        WARNING(parent_node_ptr->right == NULL);
        parent_node_ptr->right = daughter_node_ptr;
    }
}

//---------------------------------------------------------------------------------------------------------------------------------

void tree_node_detach(tree_node_t* node_to_detach_ptr) {

    ASSERT(node_to_detach_ptr != NULL);

    ASSERT(node_to_detach_ptr->parent != NULL);
    tree_node_t* parent_node_ptr = node_to_detach_ptr->parent;

    WARNING(parent_node_ptr->left == node_to_detach_ptr || parent_node_ptr->right == node_to_detach_ptr);
    if (parent_node_ptr->left == node_to_detach_ptr) {

        parent_node_ptr->left = NULL;
    }
    else if (parent_node_ptr->right == node_to_detach_ptr) {

        parent_node_ptr->right = NULL;
    }
}

//---------------------------------------------------------------------------------------------------------------------------------

void tree_node_value_change(tree_node_t* tree_node_ptr, tree_node_elem_t new_value) {

    ASSERT(tree_node_ptr);

    tree_node_ptr->value = new_value;
}

//---------------------------------------------------------------------------------------------------------------------------------

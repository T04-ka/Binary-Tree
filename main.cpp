
#include "bintree.h"
#define DEBUG

#include "myformat.cpp"

int main(){

    tree_node_t* NODES[10] = {};

    NODES[0] = tree_node_create(50);
    NODES[1] = tree_node_create(50);

    tree_node_destroy(NODES[0]);

    return 0;
}

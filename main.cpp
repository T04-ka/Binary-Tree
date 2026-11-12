
#include "bintree.h"
#define DEBUG

#include "myformat.cpp"

int main(){

    tree_node_t* NODES[10] = {};

    NODES[0] = tree_node_create(50);
    NODES[1] = tree_node_create(100);
    NODES[2] = tree_node_create(25);

    tree_node_link(NODES[0], NODES[1], TREE_NODE_SIDE_LEFT, __FILE__, __LINE__, __PRETTY_FUNCTION__);
    tree_node_link(NODES[0], NODES[2], TREE_NODE_SIDE_RIGHT, __FILE__, __LINE__, __PRETTY_FUNCTION__);

    unsigned depth = tree_depth_search(NODES[2], 0 PASS_CURRENT_LOCATION);

    $du(depth);

    tree_dump_dot_file_generate(NODES[0], "hui.dot" PASS_CURRENT_LOCATION);
    tree_dump_in_png(NODES[0], "hui.png" PASS_CURRENT_LOCATION);

    tree_node_destroy(NODES[0], __FILE__, __LINE__, __PRETTY_FUNCTION__);
    tree_node_destroy(NODES[1], __FILE__, __LINE__, __PRETTY_FUNCTION__);
    tree_node_destroy(NODES[2], __FILE__, __LINE__, __PRETTY_FUNCTION__);

    return 0;
}

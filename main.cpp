
#include "bintree.h"
#define DEBUG

#include "myformat.cpp"

int main(){

    tree_node_t* NODES[10] = {};

    NODES[0] = tree_node_create(50);
    NODES[1] = tree_node_create(100);
    NODES[2] = tree_node_create(25);
    NODES[3] = tree_node_create(60);
    NODES[4] = tree_node_create(40);
    NODES[5] = tree_node_create(60);
    NODES[6] = tree_node_create(60);

    tree_node_link(NODES[0], NODES[1], TREE_NODE_SIDE_LEFT PASS_CURRENT_LOCATION);
    tree_node_link(NODES[0], NODES[2], TREE_NODE_SIDE_RIGHT PASS_CURRENT_LOCATION);
    tree_node_link(NODES[1], NODES[3], TREE_NODE_SIDE_RIGHT PASS_CURRENT_LOCATION);
    tree_node_link(NODES[1], NODES[4], TREE_NODE_SIDE_LEFT PASS_CURRENT_LOCATION);
    tree_node_link(NODES[2], NODES[5], TREE_NODE_SIDE_LEFT PASS_CURRENT_LOCATION);
    tree_node_link(NODES[2], NODES[6], TREE_NODE_SIDE_RIGHT PASS_CURRENT_LOCATION);

//     unsigned depth = tree_depth_search(NODES[0], 0 PASS_CURRENT_LOCATION);
//
//     $du(depth);
//
//     tree_dump_dot_file_generate(NODES[0], "hui.dot", NODES[1] PASS_CURRENT_LOCATION);
//
//     FILE* html_file = fopen("tree_dump.html", "w");
//
//     tree_dump_in_html(NODES[0], html_file, "1", NODES[2] PASS_CURRENT_LOCATION);
//
//     fclose(html_file);
//
//

    FILE* preorder = fopen("preorder.txt", "w");

    tree_write_preorder(preorder, NODES[0] PASS_CURRENT_LOCATION);

    fclose(preorder);
    // tree_dump_dot_file_generate(NODES[0], "hui.dot" PASS_CURRENT_LOCATION);
    // tree_dump_in_png(NODES[0], "hui.png" PASS_CURRENT_LOCATION);

    tree_node_destroy(NODES[0], true PASS_CURRENT_LOCATION);



    return 0;
}

#ifndef BINTREE_H
#define BINTREE_H

#define DEBUG

#include "myformat.cpp"

//---------------------------------------------------------------------------------------------------------------------------------

#ifndef tree_node_elem_t
typedef int tree_node_elem_t;
#endif

//---------------------------------------------------------------------------------------------------------------------------------

struct tree_node_t
{
    tree_node_elem_t value;
    tree_node_t* left;
    tree_node_t* right;
    tree_node_t* parent;
};

//---------------------------------------------------------------------------------------------------------------------------------

enum tree_node_side_t
{
    TREE_NODE_SIDE_LEFT = 0,
    TREE_NODE_SIDE_RIGHT = 1,
};

//---------------------------------------------------------------------------------------------------------------------------------

#define MAX_FILENAME_LEN 100

//---------------------------------------------------------------------------------------------------------------------------------

tree_node_t* tree_node_create(tree_node_elem_t value);

//---------------------------------------------------------------------------------------------------------------------------------

void tree_node_destroy(tree_node_t* tree_node_ptr, bool do_recursively ONDEBUG(, const char*, int, const char*));

//---------------------------------------------------------------------------------------------------------------------------------

void tree_node_link(tree_node_t* parent_node_ptr, tree_node_t* daughter_node_ptr, tree_node_side_t side ONDEBUG(, const char*, int, const char*));

//---------------------------------------------------------------------------------------------------------------------------------

void tree_node_detach(tree_node_t* node_to_detach_ptr ONDEBUG(, const char*, int, const char*));

//---------------------------------------------------------------------------------------------------------------------------------

void tree_node_value_change(tree_node_t* tree_node_ptr, tree_node_elem_t new_value ONDEBUG(, const char*, int, const char*));

//---------------------------------------------------------------------------------------------------------------------------------

unsigned tree_depth_search(tree_node_t* tree_node_ptr, unsigned current_rank PASS_PREV_DATA);

//---------------------------------------------------------------------------------------------------------------------------------

void tree_dump_in_html(tree_node_t* tree_root_ptr, FILE* html_file PASS_PREV_DATA);

//---------------------------------------------------------------------------------------------------------------------------------

void tree_dump_dot_file_generate(tree_node_t* tree_root_ptr, const char* dot_file_name PASS_PREV_DATA);

//---------------------------------------------------------------------------------------------------------------------------------

void tree_dump_in_png(tree_node_t* tree_root_ptr, const char* png_name PASS_PREV_DATA);

//---------------------------------------------------------------------------------------------------------------------------------

#endif

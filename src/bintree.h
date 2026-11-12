#ifndef BINTREE_H
#define BINTREE_H

#define DEBUG

#include "myformat.cpp"

//---------------------------------------------------------------------------------------------------------------------------------

#ifndef tree_node_elem_t
typedef int tree_node_elem_t;
#endif

#define __TREE_TYPE_PERC__ "%d"
#define __TREE_TYPE_INIT__ 0

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

enum tree_read_t
{
    TREE_PREORDER  = 1,
    TREE_INORDER   = 2,
    TREE_POSTORDER = 3,
};

//---------------------------------------------------------------------------------------------------------------------------------

#define MAX_FILENAME_LEN 100

//---------------------------------------------------------------------------------------------------------------------------------

tree_node_t* tree_node_create(tree_node_elem_t value);

//---------------------------------------------------------------------------------------------------------------------------------

void tree_node_destroy(tree_node_t* tree_node_ptr, bool do_recursively PASS_PREV_DATA);

//---------------------------------------------------------------------------------------------------------------------------------

void tree_node_link(tree_node_t* parent_node_ptr, tree_node_t* daughter_node_ptr, tree_node_side_t side PASS_PREV_DATA);

//---------------------------------------------------------------------------------------------------------------------------------

void tree_node_detach(tree_node_t* node_to_detach_ptr PASS_PREV_DATA);

//---------------------------------------------------------------------------------------------------------------------------------

void tree_node_value_change(tree_node_t* tree_node_ptr, tree_node_elem_t new_value PASS_PREV_DATA);

//---------------------------------------------------------------------------------------------------------------------------------

unsigned tree_depth_search(tree_node_t* tree_node_ptr, unsigned current_rank PASS_PREV_DATA);

//---------------------------------------------------------------------------------------------------------------------------------

void tree_dump_in_html(tree_node_t* tree_root_ptr, FILE* html_file, const char* png_name, tree_node_t* highlighted_node_ptr PASS_PREV_DATA);

//---------------------------------------------------------------------------------------------------------------------------------

void tree_dump_dot_file_generate(tree_node_t* tree_root_ptr, const char* dot_file_name, tree_node_t* highlighted_node_ptr PASS_PREV_DATA);

//---------------------------------------------------------------------------------------------------------------------------------

void tree_dump_in_png(tree_node_t* tree_root_ptr, const char* png_name, tree_node_t* highlighted_node_ptr PASS_PREV_DATA);

//---------------------------------------------------------------------------------------------------------------------------------

void tree_write_preorder(FILE* write_file, tree_node_t* tree_node_ptr PASS_PREV_DATA);

//---------------------------------------------------------------------------------------------------------------------------------

void tree_write_inorder(FILE* write_file, tree_node_t* tree_node_ptr PASS_PREV_DATA);

//---------------------------------------------------------------------------------------------------------------------------------

void tree_write_postorder(FILE* write_file, tree_node_t* tree_node_ptr PASS_PREV_DATA);

//---------------------------------------------------------------------------------------------------------------------------------

tree_node_t* parse_preorder(char* source_data PASS_PREV_DATA);

//---------------------------------------------------------------------------------------------------------------------------------

tree_node_t* read_tree(FILE* preorder_data, tree_read_t read_t PASS_PREV_DATA);

//---------------------------------------------------------------------------------------------------------------------------------

tree_node_t* parse_inorder(char* inorder_data PASS_PREV_DATA);

//---------------------------------------------------------------------------------------------------------------------------------

#endif

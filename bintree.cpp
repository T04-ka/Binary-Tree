#include <stdlib.h>
#include <string.h>

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

void tree_node_destroy(tree_node_t* node_ptr PASS_PREV_DATA) {

    ASSERT(node_ptr != NULL);

    free(node_ptr);
}

//---------------------------------------------------------------------------------------------------------------------------------

void tree_node_link(tree_node_t* parent_node_ptr, tree_node_t* daughter_node_ptr, tree_node_side_t side PASS_PREV_DATA) {

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

void tree_node_detach(tree_node_t* node_to_detach_ptr PASS_PREV_DATA) {

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

void tree_node_value_change(tree_node_t* tree_node_ptr, tree_node_elem_t new_value PASS_PREV_DATA) {

    ASSERT(tree_node_ptr);

    tree_node_ptr->value = new_value;
}

//---------------------------------------------------------------------------------------------------------------------------------

unsigned tree_depth_search(tree_node_t* tree_node_ptr, unsigned current_rank PASS_PREV_DATA) {

    ASSERT(tree_node_ptr);

    unsigned right_max_rank = current_rank;
    unsigned left_max_rank  = current_rank;

    if (tree_node_ptr->left != NULL) {

        left_max_rank = tree_depth_search(tree_node_ptr->left, current_rank + 1 PASS_CURRENT_LOCATION);
    }

    if (tree_node_ptr->right != NULL) {

        right_max_rank = tree_depth_search(tree_node_ptr->right, current_rank + 1 PASS_CURRENT_LOCATION);
    }

    return MAX(right_max_rank, left_max_rank);
}

//---------------------------------------------------------------------------------------------------------------------------------

void tree_dump_in_html(tree_node_t* tree_root_ptr, FILE* html_file PASS_PREV_DATA) {

    fprintf(html_file, "<!DOCTYPE html>\n");
    fprintf(html_file, "<html>\n");
    fprintf(html_file, "<head>\n");
    fprintf(html_file, "    <meta charset=\"US-ASCII\">\n");
    fprintf(html_file, "    <title>LIST DUMP</title>\n");
    fprintf(html_file, "</head>\n");
    fprintf(html_file, "<body>\n");
    fprintf(html_file, "    <p style=\"font-family: monospace;\">\n        ");

    tree_dump_in_png(tree_root_ptr, "dump4html.png" PASS_CURRENT_LOCATION);

    fprintf(html_file, " DED_LOH\n");
    fprintf(html_file, "    < -- Image insert -->\n");
    fprintf(html_file, "    <img src=\"dump4html.png\" alt=\"graph.png\" style=\"max-width: 100%%; height: auto;\"><br>\n");

    fprintf(html_file, "\n    </p>\n");
    fprintf(html_file, "</body>\n");
    fprintf(html_file, "</html>\n");

    printf("HTML dump was writed succesfully.\n");

    return 0;
}

// TODO: сделать подкраску указываемых индексов
void tree_dump_dot_file_generate(tree_node_t* tree_root_ptr, const char* dot_file_name PASS_PREV_DATA) {

    unsigned depth = tree_depth_search(tree_root_ptr, 0 PASS_CURRENT_LOCATION);

}

void tree_dump_in_png(tree_node_t* tree_root_ptr, const char* png_name PASS_PREV_DATA) {

    ASSERT(tree_root_ptr != NULL);

    FILE* png_f = fopen(png_name, "w");

    tree_dump_dot_file_generate(tree_root_ptr, "yashapidor.dot" PASS_CURRENT_LOCATION);

    char system_command[MAX_FILENAME_LEN * 2] = "dot -Tpng yashapidor.dot -o ";
    strncat(system_command, png_name, MAX_FILENAME_LEN);
    strcat(system_command, " ; rm yashapidor.dot");

    int errn = system(system_command);
    fclose(png_f);

    if (errn == -1) {

        fprintf(stderr, RED FAT "ERROR: running dot script fault.\n" DEF);
        return;
    }

    printf("PNG dump was created successfully.\n");

    return;
}

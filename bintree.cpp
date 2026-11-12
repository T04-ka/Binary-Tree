
#include "bintree.h"

//---------------------------------------------------------------------------------------------------------------------------------

long long read_file_size(FILE* file);

long long read_file_size(FILE* file){

    struct stat statdata = {};
    int err = fstat(fileno(file), &statdata);

    return (!err) ? statdata.st_size : -2;
}

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

void tree_node_destroy(tree_node_t* tree_node_ptr, bool do_recursively PASS_PREV_DATA) {

    ASSERT(tree_node_ptr != NULL);

    if (do_recursively) {

        if (tree_node_ptr->left != NULL) {

            tree_node_destroy(tree_node_ptr->left, true PASS_CURRENT_LOCATION);
        }

        if (tree_node_ptr->right != NULL) {

            tree_node_destroy(tree_node_ptr->right, true PASS_CURRENT_LOCATION);
        }
    }

    free(tree_node_ptr);
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

void tree_dump_in_html(tree_node_t* tree_root_ptr, FILE* html_file, const char* png_name, tree_node_t* highlighted_node_ptr PASS_PREV_DATA) {

    ASSERT(tree_root_ptr != NULL);
    WARNING(tree_root_ptr->parent == NULL);

    fprintf(html_file, "<!DOCTYPE html>\n");
    fprintf(html_file, "<html>\n");
    fprintf(html_file, "<head>\n");
    fprintf(html_file, "    <meta charset=\"US-ASCII\">\n");
    fprintf(html_file, "    <title>LIST DUMP</title>\n");
    fprintf(html_file, "</head>\n");
    fprintf(html_file, "<body>\n");
    fprintf(html_file, "    <p style=\"font-family: monospace;\">\n        ");

    tree_dump_in_png(tree_root_ptr, png_name, highlighted_node_ptr PASS_CURRENT_LOCATION);

    fprintf(html_file, " DED_LOH\n");
    fprintf(html_file, "    < -- Image insert -- >\n");
    fprintf(html_file, "    <img src=\"%s\" alt=\"graph.png\" style=\"max-width: 100%%; height: auto;\"><br>\n", png_name);

    fprintf(html_file, "\n    </p>\n");
    fprintf(html_file, "</body>\n");
    fprintf(html_file, "</html>\n");

    printf("HTML dump has written succesfully.\n");
}

//---------------------------------------------------------------------------------------------------------------------------------

void tree_nodes_dot_link_recursively(FILE* dot_file, tree_node_t* tree_node_ptr PASS_PREV_DATA);
void tree_nodes_dot_init_recursively(FILE* dot_file, tree_node_t* tree_node_ptr, unsigned rank, tree_node_t* highlighted_node_ptr PASS_PREV_DATA);

//---------------------------------------------------------------------------------------------------------------------------------

// TODO: сделать подкраску указываемых индексов

#define WRITE_DOT(FORMAT, ...) fprintf(dot_file, FORMAT, ##__VA_ARGS__)

void tree_dump_dot_file_generate(tree_node_t* tree_root_ptr, const char* dot_file_name, tree_node_t* highlighted_node_ptr PASS_PREV_DATA) {

    ASSERT(tree_root_ptr != NULL);
    WARNING(tree_root_ptr->parent == NULL);

    unsigned depth = tree_depth_search(tree_root_ptr, 0 PASS_CURRENT_LOCATION);

    FILE* dot_file = fopen(dot_file_name, "w");

    WRITE_DOT("digraph G {\n\trankdir=TB\n\tnodesep=0.4\n\tranksep=0.4;\n\tsplines=true;\n\n\tnode [shape=record, style=filled, fillcolor=\"#F4F4F4\", width=3.1, height=1.2, fixedsize=true, fontname=\"Arial\"];\
        \n\n\tsubgraph levels {\n\t\tnode [shape=plaintext, width=0.8, style=filled, fillcolor=none, fontname=\"Arial\", fontcolor=\"#777777\"];\n\n");

    for (unsigned i = 0; i <= depth; i++) {

        WRITE_DOT("\t\tL_%u [label=\"%u\"];\n", i, i);
    }

    WRITE_DOT("\n\t\tL_0 ");
    for (unsigned i = 1; i <= depth; i++) {

        WRITE_DOT("-> L_%u ", i);
    }

    WRITE_DOT("[style=invis];\n\t}\n\n");

    tree_nodes_dot_init_recursively(dot_file, tree_root_ptr, 0, highlighted_node_ptr PASS_CURRENT_LOCATION);

    tree_nodes_dot_link_recursively(dot_file, tree_root_ptr PASS_CURRENT_LOCATION);

    WRITE_DOT("}\n");

    fclose(dot_file);

    printf("DOT file \"%s\" was created succeffully.\n", dot_file_name);
}

//---------------------------------------------------------------------------------------------------------------------------------

void tree_nodes_dot_init_recursively(FILE* dot_file, tree_node_t* tree_node_ptr, unsigned rank, tree_node_t* highlighted_node_ptr PASS_PREV_DATA) {

    ASSERT(tree_node_ptr != NULL);

// TODO ВОТ ЗДЕСЬ                 v ПОПРОБОВАТЬ СДЕЛАТЬ ВСТАВКУ МАКРОСОМ, КОТОРЫЙ В ЗАВИСИМОСИ ОТ ТАЙПДЕФА РАСКРЫВАЕТСЯ В d p lg и тд
    WRITE_DOT("\tnode_%p[", tree_node_ptr);
    if (tree_node_ptr == highlighted_node_ptr) {

        WRITE_DOT("style=filled, fillcolor=<yellow>, ");
    }
    WRITE_DOT("label=<{ {%p} | {<b>" __TREE_TYPE_PERC__ "</b>} | {%p} | { %p | %p} }>];\n", \
             tree_node_ptr->parent, tree_node_ptr->value, tree_node_ptr, tree_node_ptr->left, tree_node_ptr->right);

    WRITE_DOT("\t{ rank=same; node_%p; L_%u };\n\n", tree_node_ptr, rank);

    if (tree_node_ptr->left != NULL) {

        tree_nodes_dot_init_recursively(dot_file, tree_node_ptr->left, rank + 1, highlighted_node_ptr PASS_CURRENT_LOCATION);
    }

    if (tree_node_ptr->right != NULL) {

        tree_nodes_dot_init_recursively(dot_file, tree_node_ptr->right, rank + 1, highlighted_node_ptr PASS_CURRENT_LOCATION);
    }
}

//---------------------------------------------------------------------------------------------------------------------------------

void tree_nodes_dot_link_recursively(FILE* dot_file, tree_node_t* tree_node_ptr PASS_PREV_DATA) {

    ASSERT(tree_node_ptr != NULL);

    if (tree_node_ptr->left != NULL) {

        WRITE_DOT("\tnode_%p -> node_%p;\n", tree_node_ptr, tree_node_ptr->left);
        tree_nodes_dot_link_recursively(dot_file, tree_node_ptr->left PASS_CURRENT_LOCATION);
    }

    if (tree_node_ptr->right != NULL) {

        WRITE_DOT("\tnode_%p -> node_%p;\n", tree_node_ptr, tree_node_ptr->right);
        tree_nodes_dot_link_recursively(dot_file, tree_node_ptr->right PASS_CURRENT_LOCATION);
    }
}

//---------------------------------------------------------------------------------------------------------------------------------

#undef WRITE_DOT

//---------------------------------------------------------------------------------------------------------------------------------

void tree_dump_in_png(tree_node_t* tree_root_ptr, const char* png_name, tree_node_t* highlighted_node_ptr PASS_PREV_DATA) {

    ASSERT(tree_root_ptr != NULL);

    FILE* png_f = fopen(png_name, "w");

    tree_dump_dot_file_generate(tree_root_ptr, "yashapidor.dot", highlighted_node_ptr PASS_CURRENT_LOCATION);

    char system_command[MAX_FILENAME_LEN * 2] = "dot -Tpng yashapidor.dot -o ";
    strncat(system_command, png_name, MAX_FILENAME_LEN);
    strcat(system_command, " ; rm yashapidor.dot");

    int errn = system(system_command);
    fclose(png_f);

    if (errn == -1) {

        fprintf(stderr, RED FAT "ERROR: running dot script fault.\n" DEF);
        return;
    }

    printf("PNG dump \"%s\" was created successfully.\n", png_name);

    return;
}

//---------------------------------------------------------------------------------------------------------------------------------

#define WRITE(FORMAT, ...) fprintf(write_file, FORMAT, ##__VA_ARGS__)

void tree_write_preorder(FILE* write_file, tree_node_t* tree_node_ptr PASS_PREV_DATA) {

    ASSERT(write_file != NULL);
    ASSERT(tree_node_ptr != NULL);

    WRITE("(");

    WRITE("\"" __TREE_TYPE_PERC__ "\"", tree_node_ptr->value);

    if (tree_node_ptr->left != NULL) {

        tree_write_preorder(write_file, tree_node_ptr->left PASS_CURRENT_LOCATION);
    }

    if (tree_node_ptr->right != NULL) {

        tree_write_preorder(write_file, tree_node_ptr->right PASS_CURRENT_LOCATION);
    }

    WRITE(")");
}

//---------------------------------------------------------------------------------------------------------------------------------

void tree_write_inorder(FILE* write_file, tree_node_t* tree_node_ptr PASS_PREV_DATA) {

    ASSERT(write_file != NULL);
    ASSERT(tree_node_ptr != NULL);

    WRITE("(");

    if (tree_node_ptr->left != NULL) {

        tree_write_inorder(write_file, tree_node_ptr->left PASS_CURRENT_LOCATION);
    }

    WRITE("\"" __TREE_TYPE_PERC__ "\"", tree_node_ptr->value);

    if (tree_node_ptr->right != NULL) {

        tree_write_inorder(write_file, tree_node_ptr->right PASS_CURRENT_LOCATION);
    }

    WRITE(")");
}

//---------------------------------------------------------------------------------------------------------------------------------

void tree_write_postorder(FILE* write_file, tree_node_t* tree_node_ptr PASS_PREV_DATA) {

    ASSERT(write_file != NULL);
    ASSERT(tree_node_ptr != NULL);

    WRITE("(");

    if (tree_node_ptr->left != NULL) {

        tree_write_postorder(write_file, tree_node_ptr->left PASS_CURRENT_LOCATION);
    }

    if (tree_node_ptr->right != NULL) {

        tree_write_postorder(write_file, tree_node_ptr->right PASS_CURRENT_LOCATION);
    }

    WRITE("\"" __TREE_TYPE_PERC__ "\"", tree_node_ptr->value);

    WRITE(")");
}

#undef WRITE

//---------------------------------------------------------------------------------------------------------------------------------

tree_node_t* read_preorder(FILE* preorder_data PASS_PREV_DATA) {

    ASSERT(preorder_data != NULL);

    long long preorder_size = read_file_size(preorder_data);
    ASSERT(preorder_size != -1);

    char* source_data = (char*) calloc(preorder_size + 1, sizeof(char));
    fread(source_data, sizeof(char), preorder_size, preorder_data);

    tree_node_t* parsed_preorder_tree = parse_preorder(source_data PASS_CURRENT_LOCATION);
    WARNING(parsed_preorder_tree != NULL);

    free(source_data);

    return parsed_preorder_tree;
}

//---------------------------------------------------------------------------------------------------------------------------------
#define __TREE_TYPE_INIT__ 0
tree_node_t* parse_preorder(char* preorder_data PASS_PREV_DATA) {

    ASSERT(preorder_data != NULL);
    // -----recurs
    // read char, shift(1) if "("
    // node* node_ptr = NULL;
    // if char == "(": {
    //      node_ptr = calloc(tree_node_t)
    //      val = scanf("")
    //      shift(scanfed)
    //      node_ptr->val = val;
    //      node_ptr->left = recurs
    //      node_ptr->right = recurs
    //      shift(")")
    // }
    //
    // return node_ptr
    // -----

    char current_char = *preorder_data;

    tree_node_t* current_tree_node = NULL;

    if (current_char == '(') {

        preorder_data++;

        current_tree_node = (tree_node_t*) calloc(1, sizeof(tree_node_t));

        tree_node_elem_t value = __TREE_TYPE_INIT__;
        int nread = 1;
        $d(value);
        $s(preorder_data);
        sscanf(preorder_data, "\" %d%n[^\"] ", &value, &nread);
        $d(value);
        $d(nread);
        preorder_data += nread + 1;

        current_tree_node->value = value;
        $s(preorder_data);
        current_tree_node->left = parse_preorder(preorder_data PASS_CURRENT_LOCATION); //SUDA: if left != NULL: left->parent = current
        current_tree_node->right = parse_preorder(preorder_data PASS_CURRENT_LOCATION);

        preorder_data++; //VOT SUDA PROVERKA NA ")"
    }

    return current_tree_node;
}

// file tree.hpp

#pragma once

#include "scanner.hpp"

enum type_data {
	TYPE_UNKNOWN = 0,
	TYPE_INT = 1,
	TYPE_SHORT = 2,
	TYPE_LONG = 3,
	TYPE__INT64 = 4,
	TYPE_CHAR = 5,
	TYPE_VOID = 6
};

enum type_object {
	OBJECT_UNKNOWN = 0,
	OBJECT_VARIABLE = 1,
	OBJECT_ARRAY = 2,
	OBJECT_FUNCTION = 3
};

union type_value {
	int data_as_int;
	short data_as_short;
	long data_as_long;
	__int64 data_as__int64;
	char data_as_char;

	int* array_as_int;
	short* array_as_short;
	long* array_as_long;
	__int64* array_as__int64;
	char* array_as_char;
};

struct TData {
	type_data type;
	type_value value;
	TData() {
		type = TYPE_UNKNOWN;
		value.data_as_char = 0;
		value.data_as_short = 0;
		value.data_as_int = 0;
		value.data_as_long = 0;
		value.data_as__int64 = 0;
	}
};

class Tree;

struct Node {
	Tree* pointer;
	type_lex lex;
	type_object object;
	TData data;
	int init;
	int array_size;
	int addr;
};

class Tree {
private:
	TScaner* scaner;
	Node* node;
	Tree* parent;
	Tree* left;
	Tree* right;
public:
	static bool flag_interp;
	Tree* current;
	Tree(TScaner*, Tree* parent, Tree* left, Tree* right, Node* node);
	Tree(TScaner*);
	~Tree();
	void set_left(Node*);
	void set_right(Node*);
	Tree* find_up(Tree*, type_lex);
	Tree* find_up(type_lex);
	Tree* find_up_at_level(Tree*, type_lex);
	Tree* find_right_left(Tree*, type_lex);
	Tree* find_right_left(type_lex);
	void print();
	Node* get_current_node();
	void set_current_node(Node* node);
	Node* get_node();
	void set_node(Node* node);
	Tree* semantic_include(type_lex, type_object, type_data);
	void set_current(Tree* tree);
	Tree* get_current();
	void semantic_set_type(Tree*, type_data);
	Tree* semantic_get_type(type_lex, type_object);
	void semantic_set_object(Tree*, type_object);
	Tree* semantic_get_object(type_lex);
	void semantic_set_init(Tree*, int);
	Tree* semantic_get_init(type_lex);
	void semantic_set_array_size(Tree*, int);
	Tree* semantic_get_array_size(type_lex);

	int is_exists(Tree* tree, type_lex lex);
};
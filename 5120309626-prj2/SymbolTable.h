////////////////////////////////////////////////////////////////////////
/*
  File Name: SymbolTable.h
  I have implemented all the things required for implementing a 
  SymbolTable in this file. For each StatementBlock SymbolTable,
  it has a variable name symbol table and a struct type information
  symbol table.
*/
////////////////////////////////////////////////////////////////////////

#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include "Info.h"
#include <string>
#include <vector>
#include <map>
using namespace std;

struct SymbolTable;

enum DefinitionType{
	type_function,
	type_global_int,
	type_global_array,
	type_global_struct,
	type_global_struct_virtual,
	type_parameter,
	type_local_int,
	type_local_array,
	type_local_struct,
	type_local_struct_virtual
};

struct Definition{
	DefinitionType definition_type;


	// Variable initialize
	int variable_init_value;
	int stackOffsite;

	// Struct initialize
	string struct_type;
	SymbolTable* table;

	// Array initialize
	int array_item_num;
	vector<int> array_init_list;
	int array_subscript_num;
	vector<int> array_subscript_list;

	// Function initialize
	int parameter_number;
};

struct StructType{
	map<string, int> Struct_Offsites;
	vector<string> Struct_List;

	int size(){
		return Struct_Offsites.size();
	}

	int count(string str){
		return Struct_Offsites.count(str);
	}
};

struct SymbolTable{
	SymbolTable* parent;


	map<string, Definition*> symbol_map;

	map<string, StructType*> struct_map;

	vector<SymbolTable*> sub_symbol_tables;

	int count(string str){
		return symbol_map.count(str);
	}

	int countStruct(string str){
		return struct_map.count(str);
	}

	Definition* getItem(string str){
		return symbol_map[str];
	}
	SymbolTable(){};
	~SymbolTable(){};
};



#endif
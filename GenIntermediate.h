////////////////////////////////////////////////////////////////////////
/*
  File Name: GenIntermediate.h
  This file is the header file of GenIntermediate.cpp
*/
////////////////////////////////////////////////////////////////////////

#ifndef GEN_INTERMEDIATE_H
#define GEN_INTERMEDIATE_H

#include "Info.h"
#include "SymbolTable.h"
#include "Intermediate.h"
#include "MIPS32.h"
#include <set>

struct SymbolTable;
struct Intermediates;

extern SymbolTable* global_table;
extern vector<Intermediate*>* global_intermediates;
extern set<Register> remainingRegisters;
extern set<Register> registersInUse;
extern map<Node*, Register> intermediate;
extern string label;		
extern string currentLoopContinueLabel;
extern string currentLoopBreakLabel;
extern int stackSize;

SymbolTable* pushScope(SymbolTable* table);

SymbolTable* popScope(SymbolTable* table);

Definition* getDefinition(string name, SymbolTable* table, int linenum);

Register getVarAddress(Node* cur, SymbolTable* table, int linenum);

Register getStructMemberAddress(Node* cur, SymbolTable* table, int linenum);

Register getArraySubscriptAddress(Node* cur, SymbolTable* table, int linenum);

void reclainRegisters();

void returnRegister(Register r);

Register getFreeRegister();

bool generate_intermediates(SymbolTable* symbol_table, vector<Inter*>* intermediates, Node* program_out, vector<Instruction*>* instrs);

bool check(Node* cur, SymbolTable* table);

bool Define_Global_Var_Array(Variable_ArrayDeclarationInfo* info, SymbolTable* table, int linenum);

bool Define_Global_Struct(string structname, vector<string>* structMembers, vector<string>* structDeclarations, SymbolTable* table, int linenum);

bool Define_Function(Node* cur, SymbolTable* table, int linenum);

bool Define_Local_Var_Array(Variable_ArrayDeclarationInfo* info, SymbolTable* table, int linenum);

bool Define_Local_Struct(string structname, vector<string>* structMembers, vector<string>* structDeclarations, SymbolTable* table, int linenum);

bool Define_If_Statement(Node* cur, SymbolTable* table, int linenum);

bool Define_IfElse_Statement(Node* cur, SymbolTable* table, int linenum);

bool Define_For_Statement(Node* cur, SymbolTable* table, int linenum);

bool Define_Break_Statement(Node* cur, SymbolTable* table, int linenum);

bool Define_Continue_Statement(Node* cur, SymbolTable* table, int linenum);

bool Define_Return_Statement(Node* cur, SymbolTable* table, int linenum);

bool Define_Assign_Expression(Node* cur, SymbolTable* table, int linenum);

bool Define_UnaryAssign_Expression(Node* cur, SymbolTable* table, int linenum);

bool Define_Int_Expression(Node* cur, SymbolTable* table, int linenum);

bool Define_BinaryOp_Expression(Node* cur, SymbolTable* table, int linenum);

bool Define_UnaryOp_Expression(Node* cur, SymbolTable* table, int linenum);

bool Define_Variable_Expression(Node* cur, SymbolTable* table, int linenum);

bool Define_Array_Expression(Node* cur, SymbolTable* table, int linenum);

bool Define_FunctionCall_Expression(Node* cur, SymbolTable* table, int linenum);

bool Define_StructMember_Expression(Node* cur, SymbolTable* table, int linenum);

bool Define_Read_Statement(Node* cur, SymbolTable* table, int linenum);

bool Define_Write_Statement(Node* cur, SymbolTable* table, int linenum);
#endif
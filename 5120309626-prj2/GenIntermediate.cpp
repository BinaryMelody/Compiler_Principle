////////////////////////////////////////////////////////////////////////
/*
  File Name: GenIntermediate.cpp
  This file is the core file of semantic checking, generating intermediate
  code and also generating the final MIPS code! The "check" function will
  be used to the entrance of each Node and judge which function it will 
  further jump into. It will first get the program node from parser and 
  return the generated intermediate code and target code to the main 
  program.
*/
////////////////////////////////////////////////////////////////////////
#include "GenIntermediate.h"

SymbolTable* global_table;
vector<Instruction*>* instructions;
vector<Inter*>* intermediates;

set<Register> remainingRegisters;
set<Register> registersInUse;
map<Node*, Register> intermediate;
string label;		
string currentLoopContinueLabel;
string currentLoopBreakLabel;

set<Tempo> remainingTempos;
set<Tempo> temposInUse;
map<Node*, Tempo> interTempo;


int stackSize;


static char Global_Struct_No_Name = '0';
static char labelIndex = 'a';
// Utils
SymbolTable* pushScope(SymbolTable* table){ // Enter a new Symbol table when in a statement block.
	SymbolTable* tmp = new SymbolTable();
	tmp->parent = table;
	return tmp;
}

SymbolTable* popScope(SymbolTable* table){	// Return from the implemented symbol table
	SymbolTable* tmp = table->parent;
	delete table;
	return tmp;
}

void reclaimRegisters(){ // Reclaim all Registers
	remainingRegisters = { R_T0, R_T1, R_T2, R_T3, R_T4, R_T5, R_T6, R_T7, R_T8, R_T9};
	registersInUse = {};
}

void reclaimTempos(){
	remainingTempos = { T_0, T_1, T_2, T_3, T_4, T_5, T_6, T_7, T_8, T_9, T_10, T_11, T_12, T_13, T_14, T_15, T_16, T_17, T_18, T_19, T_20, T_21, T_22, T_23, T_24, T_25, T_26, T_27, T_28, T_29, T_30};
	temposInUse = {};
}

void returnRegister(Register r){  // Return a being used register
	remainingRegisters.insert(r);
	registersInUse.erase(r);
}

void returnTempo(Tempo t){
	remainingTempos.insert(t);
	temposInUse.erase(t);
}

Register getFreeRegister(){  // Get an unused register
	if(remainingRegisters.empty()){
		cout << "No free registers left. I haven't implemented this yet!" << endl;
		return R_ZERO;
	} else {
		Register ret = *(remainingRegisters.begin());
		remainingRegisters.erase(ret);
		registersInUse.insert(ret);
		return ret;
	}
}

Tempo getFreeTempo(){
	if(remainingTempos.empty()){
		cout << "No free tempos left. I haven't implemented this yet!" << endl;
		return T_0;
	} else {
		Tempo ret = *(remainingTempos.begin());
		remainingTempos.erase(ret);
		temposInUse.insert(ret);
		return ret;
	}
}

// Main
bool generate_intermediates(SymbolTable* symbol_table, vector<Inter*>* inters, Node* program_out, vector<Instruction*>* instrs){
	symbol_table = new SymbolTable();
	global_table = symbol_table;
	global_table->parent = NULL;
	intermediates = inters;
	// cout << "fuck\n";
	// Tempo tp = getFreeTempo();
	// cout << "fuck\n";
	instructions = instrs;
	bool flag = check(program_out, global_table);
	return flag;
}

// Check Node
bool check(Node* cur, SymbolTable* table){
	bool flag = true;
	switch(cur->me_NodeType){
		case Program:
			currentLoopBreakLabel = "";
			currentLoopContinueLabel = "";
			reclaimRegisters();
			for(int i=0; i<cur->extern_declarations->size(); ++i){
				flag = check((*(cur->extern_declarations))[i], table) && flag ;
			}
			if(table->count("main")==0 || table->getItem("main")->definition_type != type_function){
				cout << "Error: The program does not have an entrance 'main'." << endl;
				flag = false;
			}
			break;
		case Declaration:
			switch(cur->me_DeclarationType){
				case Dec_Global_Variable_Array:
					for(int i=0; i<cur->mv_Var_Arr_Dec_Info_Vector->size(); ++i){
						flag = Define_Global_Var_Array((*(cur->mv_Var_Arr_Dec_Info_Vector))[i], table, cur->mi_LineNum) && flag;
					}
					break;
				case Dec_Global_Struct:
					flag = Define_Global_Struct(cur->ms_StructName, cur->mv_StructMembers, cur->mv_StructDeclarations, table, cur->mi_LineNum);
					break;
				case Dec_Local_Variable_Array:
					for(auto it = cur->mv_Var_Arr_Dec_Info_Vector->begin(); it != cur->mv_Var_Arr_Dec_Info_Vector->end(); ++it){
						flag = Define_Local_Var_Array(*it, table, cur->mi_LineNum) && flag;
					}
					break;
				case Dec_Local_Struct:
					flag = Define_Local_Struct(cur->ms_StructName, cur->mv_StructMembers, cur->mv_StructDeclarations, table, cur->mi_LineNum);
					break;
			}
			break;
		case Function:
			flag = Define_Function(cur, table, cur->mi_LineNum);
			break;
		case Statement:
			switch(cur->me_StatementType){
				case Stmt_StatementBlock:
					for(auto it = cur->declarations_in_block->begin(); it != cur->declarations_in_block->end(); ++it){
						flag = check(*it, table) && flag;
					}
					for(auto it = cur->statements_in_block->begin(); it != cur->statements_in_block->end(); ++it){
						if(*it==NULL) continue;
						if((*it)->me_NodeType==Statement && (*it)->me_StatementType==Stmt_StatementBlock){
							table = pushScope(table);
							flag = check(*it, table) && flag;
							table = popScope(table);
						} else{
							flag = check(*it, table) && flag;
						}
						reclaimRegisters();
						reclaimTempos();
					}
					break;
				case Stmt_If:
					flag = Define_If_Statement(cur, table, cur->mi_LineNum);
					break;
				case Stmt_IfElse:
					flag = Define_IfElse_Statement(cur, table, cur->mi_LineNum);
					break;
				case Stmt_For:
					flag = Define_For_Statement(cur, table, cur->mi_LineNum);
					break;
				case Stmt_Break:
					flag = Define_Break_Statement(cur, table, cur->mi_LineNum);
					break;
				case Stmt_Continue:
					flag = Define_Continue_Statement(cur, table, cur->mi_LineNum);
					break;
				case Stmt_Return:
					flag = Define_Return_Statement(cur, table, cur->mi_LineNum);
					break;
				case Stmt_Read:
					flag = Define_Read_Statement(cur, table, cur->mi_LineNum);
					break;
				case Stmt_Write:
					flag = Define_Write_Statement(cur, table, cur->mi_LineNum);
					break;
			}
			break;
		case Expression:
			switch(cur->me_ExpressionType){
				case Exp_Assign:
					flag = Define_Assign_Expression(cur, table, cur->mi_LineNum);
					break;
				case Exp_UnaryAssign:
					flag = Define_UnaryAssign_Expression(cur, table, cur->mi_LineNum);
					break;
				case Exp_Int:
					flag = Define_Int_Expression(cur, table, cur->mi_LineNum);
					break;
				case Exp_BinaryOp:
					flag = Define_BinaryOp_Expression(cur, table, cur->mi_LineNum);
					break;
				case Exp_UnaryOp:
					flag = Define_UnaryOp_Expression(cur, table, cur->mi_LineNum);
					break;
				case Exp_Variable:
					flag = Define_Variable_Expression(cur, table, cur->mi_LineNum);
					break;
				case Exp_Array:
					flag = Define_Array_Expression(cur, table, cur->mi_LineNum);
					break;
				case Exp_FunctionCall:
					flag = Define_FunctionCall_Expression(cur, table, cur->mi_LineNum);
					break;
				case Exp_StructMember:
					flag = Define_StructMember_Expression(cur, table, cur->mi_LineNum);
					break;
			}
			break;
	}
	return flag;
}

// Define Part
bool Define_Global_Var_Array(Variable_ArrayDeclarationInfo* info, SymbolTable* table, int linenum){ // Global Variable and Array initial
	if(table->count(info->ms_Name)!=0){
		cout << "Error: Line " << linenum << " : '" << info->ms_Name << "' has already been declared in this scope." << endl;
		return false;
	}
	else {
		Definition* temp = new Definition();
		// Array
		if(info->mv_ArrayDeclarationSubscriptList.size()!=0){   
			int array_num = 1;   // Count Array Size
			for(int i=0; i<info->mv_ArrayDeclarationSubscriptList.size(); ++i) array_num *= (info->mv_ArrayDeclarationSubscriptList)[i];
			if(array_num<=0){
				cout << "Error: Line " << linenum << " : An array is initialized with non-positive size." << endl;
				return false;
			}
			else {

				if(array_num < info->mv_InitList->size()) {
					cout << "Error: Line " << linenum << " : The initialize list is too large for '" << info->ms_Name << "'." << endl;
					return false;
				}
				else {
					for(int i=0; i<info->mv_InitList->size(); ++i){
						if((*(info->mv_InitList))[i]->me_ExpressionType != Exp_Int){
							cout << "Error: Line " << linenum << " : The initialize value should be a constant expression." << endl;
							return false;
						}
						else{
							temp->array_init_list.push_back((*(info->mv_InitList))[i]->mi_IntExpression_Val);	
						}
					}
					temp->array_item_num = array_num;
					temp->definition_type = type_global_array;
					temp->array_subscript_num = info->mv_ArrayDeclarationSubscriptList.size();
					temp->array_subscript_list = info->mv_ArrayDeclarationSubscriptList;
					table->symbol_map[info->ms_Name] = temp;
					instructions->push_back(new ArrayInitGlobal(info->ms_Name, array_num * 4, temp->array_init_list));
					intermediates->push_back(new InterArrayGlobal(info->ms_Name, array_num * 4, temp->array_init_list));
					// Intermediate* inter = new Intermediate();
					// inter->initial_define_global_array(info->ms_Name, array_num, temp->array_init_list);
					// global_intermediates->push_back(inter);
				}
			}
		} else{
			if(info->mv_InitList->size() > 1){
				cout << "Error: Line " << linenum << " : Only one initialize number is required for variable '" << info->ms_Name << "'." << endl;
				return false;
			} else if(info->mv_InitList->size() == 1){
				if((*(info->mv_InitList))[0]->me_ExpressionType != Exp_Int){
					cout << "Error: Line " << linenum << " : The initialize value should be a constant expression." << endl;
					return false;
				} else temp->variable_init_value = (*(info->mv_InitList))[0]->mi_IntExpression_Val;
			} else{
				temp->variable_init_value = 0;
			}
			temp->definition_type = type_global_int;
			table->symbol_map[info->ms_Name] = temp;
			instructions->push_back(new IntGlobal(info->ms_Name, temp->variable_init_value));
			intermediates->push_back(new InterIntGlobal(info->ms_Name, temp->variable_init_value));
			// Intermediate* inter = new Intermediate();
			// inter->initial_define_global_int(info->ms_Name, temp->variable_init_value);
			// global_intermediates->push_back(inter);
		}
	}
	return true;
}

bool Define_Local_Var_Array(Variable_ArrayDeclarationInfo* info, SymbolTable* table, int linenum){ // Local Variable and Array initial
	bool flag = true;
	if(table->count(info->ms_Name)!=0){
		cout << "Error: Line " << linenum << " : '" << info->ms_Name << "' has already been declared in this scope." << endl;
		flag = false;
	}
	else {
		Definition* temp = new Definition();
		// Array
		if(info->mv_ArrayDeclarationSubscriptList.size()!=0){   
			int array_num = 1;   // Count Array Size
			for(int i=0; i<info->mv_ArrayDeclarationSubscriptList.size(); ++i) array_num *= (info->mv_ArrayDeclarationSubscriptList)[i];
			if(array_num<=0){
				cout << "Error: Line " << linenum << " : An array is initialized with non-positive size." << endl;
				flag = false;
			}
			else {
				if(array_num < info->mv_InitList->size()) {
					cout << "Error: Line " << linenum << " : The initialize list is too large for '" << info->ms_Name << "'." << endl;
					flag = false;
				}
				else {
					int originStackSize = stackSize;
					for(int i=0; i<info->mv_InitList->size(); ++i){
						if((*(info->mv_InitList))[i]->me_ExpressionType != Exp_Int){
							cout << "Error: Line " << linenum << " : The initialize value should be a constant expression." << endl;
							flag = false;
						}
						else{
							instructions->push_back(new LoadImmediate(R_T0, (*(info->mv_InitList))[i]->mi_IntExpression_Val));
							instructions->push_back(new StoreWord(R_T0, R_SP, stackSize));
							stackSize += 4;
							temp->array_init_list.push_back((*(info->mv_InitList))[i]->mi_IntExpression_Val);
						}
					}
					stackSize = originStackSize;
					temp->stackOffsite = stackSize;
					temp->array_item_num = array_num;
					temp->array_subscript_num = info->mv_ArrayDeclarationSubscriptList.size();
					temp->array_subscript_list = info->mv_ArrayDeclarationSubscriptList;
					temp->definition_type = type_local_array;
					table->symbol_map[info->ms_Name] = temp;
					intermediates->push_back(new InterArrayLocal(info->ms_Name, array_num * 4, temp->stackOffsite, temp->array_init_list));
					// Intermediate* inter = new Intermediate();
					// inter->initial_define_local_array(info->ms_Name, array_num, temp->stackOffsite, temp->array_init_list);
					// global_intermediates->push_back(inter);
					stackSize += array_num * 4;
				}
			}
		} else{
			if(info->mv_InitList->size() > 1){
				cout << "Error: Line " << linenum << " : Only one initialize number is required for variable '" << info->ms_Name << "'." << endl;
				flag = false;
			} else if(info->mv_InitList->size() == 1){
				temp->stackOffsite = stackSize;
				stackSize += 4;
				flag = check((*(info->mv_InitList))[0], table);
				Register result = intermediate[(*(info->mv_InitList))[0]];
				instructions->push_back(new StoreWord(result, R_SP, temp->stackOffsite));
				returnRegister(result);
			} else{
				temp->stackOffsite = stackSize;
				stackSize += 4;
			}
			temp->definition_type = type_local_int;
			table->symbol_map[info->ms_Name] = temp;
			intermediates->push_back(new InterIntLocal(info->ms_Name, temp->stackOffsite));
			// Intermediate* inter = new Intermediate();
			// inter->initial_define_local_int(info->ms_Name, temp->stackOffsite);
			// global_intermediates->push_back(inter);
		}
	}
	return flag;
}

bool Define_Global_Struct(string structname, vector<string>* structMembers, vector<string>* structDeclarations, SymbolTable* table, int linenum){ // Global Struct Initial
	if(structname=="#"){
		if(structMembers->size()==0 || structDeclarations->size()==0){
			cout << "Error: Line " << linenum << " : Struct Declaration with no members or name." << endl;
			return false;
		}
		structname += (Global_Struct_No_Name++);
	}
	if(structMembers->size()==0){
		//if(table->count(structname)!=0 && (table->getItem(structname)->definition_type != type_global_struct_predeclaration || table->getItem(structname)->definition_type != type_global_struct){
		if(table->count(structname)!=0 && (table->getItem(structname)->definition_type != type_global_struct_virtual)){
			cout << "Error: Line " << linenum << " : Struct type '" << structname << "' has already been declared in this scope." << endl;
			return false;
		}
		if(table->count(structname) == 0){ // Predeclaration with no initial
			Definition* tt = new Definition();
			tt->definition_type = type_global_struct_virtual;
			table->symbol_map[structname] = tt;
			StructType* tmp = new StructType();
			table->struct_map[structname] = tmp;
			for(int i=0; i<structDeclarations->size(); ++i){
				if(table->count((*structDeclarations)[i])!=0){
					cout << "Error: Line " << linenum << " : Struct variable '" << (*structDeclarations)[i] << "' has already been declared in this scope." << endl;
					return false;
				}
				Definition* temp = new Definition();
				temp->definition_type = type_global_struct;
				temp->struct_type = structname;
				temp->table = table;
				table->symbol_map[(*structDeclarations)[i]] = temp;
				tmp->Struct_List.push_back((*structDeclarations)[i]);
			}
		} else if(table->getItem(structname)->definition_type == type_global_struct_virtual){
			for(int i=0; i<structDeclarations->size(); ++i){
				if(table->count((*structDeclarations)[i])!=0){
					cout << "Error: Line " << linenum << " : Struct variable '" << (*structDeclarations)[i] << "' has already been declared in this scope." << endl;
					return false;
				}
				Definition* temp = new Definition();
				temp->definition_type = type_global_struct;
				temp->struct_type = structname;
				temp->table = table;
				table->symbol_map[(*structDeclarations)[i]] = temp;
				table->struct_map[structname]->Struct_List.push_back((*structDeclarations)[i]);
				if(table->struct_map[structname]->size()!=0){  // Already be initialized with members
					instructions->push_back(new ArrayGlobal((*structDeclarations)[i], 4 * table->struct_map[structname]->size()));
					intermediates->push_back(new InterStructGlobal((*structDeclarations)[i], 4 * table->struct_map[structname]->size()));
					// Intermediate* inter = new Intermediate();
					// inter->initial_define_global_struct((*structDeclarations)[i], table->struct_map[structname]->size());
					// global_intermediates->push_back(inter);
				}
			}
		}
	} else {

		if(table->count(structname)!=0 && ((table->getItem(structname)->definition_type != type_global_struct_virtual) ||
		 									(table->getItem(structname)->definition_type == type_global_struct_virtual && table->struct_map[structname]->size()!=0))) {
			cout << "Error: Line " << linenum << " : Struct type '" << structname << "' has already been declared in this scope." << endl;
			return false;
		}
		if (table->count(structname)==0){
			Definition* tt = new Definition();
			tt->definition_type = type_global_struct_virtual;
			table->symbol_map[structname] = tt;
			StructType* tmp = new StructType();
			table->struct_map[structname] = tmp;
		}

		for(int i=0; i<structMembers->size(); ++i){
			if(table->struct_map[structname]->count((*structMembers)[i])!=0){
				cout << "Error: Line " << linenum << " : Redeclartion member '" << (*structMembers)[i] << "' in the same struct type." << endl;
				return false;
			}
			(((table->struct_map)[structname])->Struct_Offsites)[(*structMembers)[i]] = i * 4;
		}
		for(int i=0; i<structDeclarations->size(); ++i){
			if(table->count((*structDeclarations)[i])!=0){
				cout << "Error: Line " << linenum << " : Struct variable '" << (*structDeclarations)[i] << "' has already been declared in this scope." << endl;
				return false;
			}
			Definition* temp = new Definition();
			temp->definition_type = type_global_struct;
			temp->struct_type = structname;
			temp->table = table;
			table->symbol_map[(*structDeclarations)[i]] = temp;
			table->struct_map[structname]->Struct_List.push_back((*structDeclarations)[i]);
		}
		
		for(int i=0; i<table->struct_map[structname]->Struct_List.size(); ++i){
			instructions->push_back(new ArrayGlobal((*structDeclarations)[i], 4 * table->struct_map[structname]->size()));
			intermediates->push_back(new InterStructGlobal((*structDeclarations)[i], 4 * table->struct_map[structname]->size()));
			// Intermediate* inter = new Intermediate();
			// inter->initial_define_global_struct(table->struct_map[structname]->Struct_List[i], table->struct_map[structname]->size());
			// global_intermediates->push_back(inter);
		}
	}
	return true;
}

bool Define_Local_Struct(string structname, vector<string>* structMembers, vector<string>* structDeclarations, SymbolTable* table, int linenum){	// Local Struct Initial
	if(structname=="#"){
		if(structMembers->size()==0 || structDeclarations->size()==0){
			cout << "Error: Line " << linenum << " : Struct Declaration with no members or name." << endl;
			return false;
		}
		structname += (Global_Struct_No_Name++);
	}
	if(structMembers->size()==0){
		//if(table->count(structname)!=0 && (table->getItem(structname)->definition_type != type_global_struct_predeclaration || table->getItem(structname)->definition_type != type_global_struct){
		if(table->count(structname)!=0 && (table->getItem(structname)->definition_type != type_global_struct_virtual)){
			cout << "Error: Line " << linenum << " : Struct type '" << structname << "' has already been declared in this scope." << endl;
			return false;
		}
		if(table->count(structname) == 0){ // Predeclaration with no initial
			Definition* tt = new Definition();
			tt->definition_type = type_local_struct_virtual;
			table->symbol_map[structname] = tt;
			StructType* tmp = new StructType();
			table->struct_map[structname] = tmp;
			for(int i=0; i<structDeclarations->size(); ++i){
				if(table->count((*structDeclarations)[i])!=0){
					cout << "Error: Line " << linenum << " : Struct variable '" << (*structDeclarations)[i] << "' has already been declared in this scope." << endl;
					return false;
				}
				Definition* temp = new Definition();
				temp->definition_type = type_local_struct;
				temp->struct_type = structname;
				temp->table = table;
				table->symbol_map[(*structDeclarations)[i]] = temp;
				tmp->Struct_List.push_back((*structDeclarations)[i]);
			}
		} else if(table->getItem(structname)->definition_type == type_local_struct_virtual){
			for(int i=0; i<structDeclarations->size(); ++i){
				if(table->count((*structDeclarations)[i])!=0){
					cout << "Error: Line " << linenum << " : Struct variable '" << (*structDeclarations)[i] << "' has already been declared in this scope." << endl;
					return false;
				}
				Definition* temp = new Definition();

				temp->definition_type = type_local_struct;
				temp->struct_type = structname;
				temp->table = table;
				table->symbol_map[(*structDeclarations)[i]] = temp;
				table->struct_map[structname]->Struct_List.push_back((*structDeclarations)[i]);
				if(table->struct_map[structname]->size()!=0){  // Already be initialized with members
					temp->stackOffsite = stackSize;
					stackSize += table->struct_map[structname]->size() * 4;
					intermediates->push_back(new InterStructLocal((*structDeclarations)[i], table->struct_map[structname]->size() * 4, temp->stackOffsite));
					// Intermediate* inter = new Intermediate();
					// inter->initial_define_local_struct((*structDeclarations)[i], temp->stackOffsite, table->struct_map[structname]->size());
					// global_intermediates->push_back(inter);
				}
			}
		}
	} else {

		if(table->count(structname)!=0 && ((table->getItem(structname)->definition_type != type_global_struct_virtual) ||
		 									(table->getItem(structname)->definition_type == type_global_struct_virtual && table->struct_map[structname]->size()!=0))) {
			cout << "Error: Line " << linenum << " : Struct type '" << structname << "' has already been declared in this scope." << endl;
			return false;
		}
		if (table->count(structname)==0){
			Definition* tt = new Definition();
			tt->definition_type = type_local_struct_virtual;
			table->symbol_map[structname] = tt;
			StructType* tmp = new StructType();
			table->struct_map[structname] = tmp;
		}

		for(int i=0; i<structMembers->size(); ++i){
			if(table->struct_map[structname]->count((*structMembers)[i])!=0){
				cout << "Error: Line " << linenum << " : Redeclartion member '" << (*structMembers)[i] << "' in the same struct type." << endl;
				return false;
			}
			(((table->struct_map)[structname])->Struct_Offsites)[(*structMembers)[i]] = i * 4;
		}
		for(int i=0; i<structDeclarations->size(); ++i){
			if(table->count((*structDeclarations)[i])!=0){
				cout << "Error: Line " << linenum << " : Struct variable '" << (*structDeclarations)[i] << "' has already been declared in this scope." << endl;
				return false;
			}
			Definition* temp = new Definition();
			temp->stackOffsite = stackSize;
			stackSize += table->struct_map[structname]->size() * 4;
			temp->definition_type = type_local_struct;
			temp->struct_type = structname;
			temp->table = table;
			table->symbol_map[(*structDeclarations)[i]] = temp;
			table->struct_map[structname]->Struct_List.push_back((*structDeclarations)[i]);
		}
		
		for(int i=0; i<table->struct_map[structname]->Struct_List.size(); ++i){
			string nn = table->struct_map[structname]->Struct_List[i];
			intermediates->push_back(new InterStructLocal(table->struct_map[structname]->Struct_List[i], table->struct_map[structname]->size() * 4, table->symbol_map[nn]->stackOffsite));
			// Intermediate* inter = new Intermediate();
			// string nn = table->struct_map[structname]->Struct_List[i];
			// inter->initial_define_local_struct(table->struct_map[structname]->Struct_List[i], table->symbol_map[nn]->stackOffsite, table->struct_map[structname]->size());
			// global_intermediates->push_back(inter);
		}
	}
	return true;
}

// Function declaration
bool Define_Function(Node* cur, SymbolTable* table, int linenum){ 
	reclaimRegisters();
	reclaimTempos();
	labelIndex = 'a';
	if(table->count(cur->ms_Name)!=0){
		cout << "Error: Line " << linenum << " : Function '" << cur->ms_Name << "' has already been declared in this scope." << endl;
		return false;
	}
	Definition* temp = new Definition();
	temp->definition_type = type_function;
	temp->parameter_number = cur->parameters->size();
	table->symbol_map[cur->ms_Name] = temp;
	label = cur->ms_Name;
	intermediates->push_back(new InterLabel(cur->ms_Name));
	instructions->push_back(new Label(cur->ms_Name));
	table = pushScope(table);

	stackSize = 0;

	for(auto it=cur->parameters->begin(); it!=cur->parameters->end(); ++it){
		if(table->count(*it)!=0){
			cout << "Error: Line "<< linenum << " : Variable '" << *it << "' has already been declared in this scope." << endl;
			return false;
		}
		Definition* temp = new Definition();
		temp->definition_type = type_parameter;
		temp->stackOffsite = stackSize;
		stackSize += 4;
		table->symbol_map[*it] = temp;
	}

	LoadImmediate* loadStackSize = new LoadImmediate(R_T0, 0);
	instructions->push_back(loadStackSize);
	instructions->push_back(new BinOp("sub", R_SP, R_SP, R_T0));
	instructions->push_back(new StoreWord(R_RA, R_SP, 0));
	instructions->push_back(new StoreWord(R_A0, R_SP, 4));

	stackSize = 8;
	
	if(!check(cur->function_Body, table)) return false;

	table = popScope(table);
		
	loadStackSize->setValue(stackSize);
	intermediates->push_back(new InterLabel("#" + cur->ms_Name + "_end"));
	instructions->push_back(new Label(cur->ms_Name + "_end"));
	instructions->push_back(new LoadWord(R_RA, R_SP, 0));
	instructions->push_back(new BinOpImmediate("addi", R_SP, R_SP, stackSize));
	instructions->push_back(new JumpRegister(R_RA));
	return true;
}

// If Statement
bool Define_If_Statement(Node* cur, SymbolTable* table, int linenum){
	string afterLabel = label + "_endif_" + labelIndex;
	labelIndex++;
	if(cur->if_Expression==NULL) {
		cout << "Error: Line " << linenum << " : Condition for if statement can't be empty." << endl;
		return false;
	}
	bool flag = check(cur->if_Expression, table);
	Register cond = intermediate[cur->if_Expression];
	Tempo tp = interTempo[cur->if_Expression];
	instructions->push_back(new BranchOnEqual(cond, R_ZERO, afterLabel));
	intermediates->push_back(new IfFalseGoto(tp, afterLabel));
	returnRegister(cond);
	returnTempo(tp);
	if(cur->then_Statement!=NULL){
		if(cur->then_Statement->me_StatementType==Stmt_StatementBlock){
			table = pushScope(table);
			flag = check(cur->then_Statement, table) && flag;
			table = popScope(table);
		} else {
			flag = check(cur->then_Statement, table) && flag;
		}
	}
	instructions->push_back(new Label(afterLabel));
	intermediates->push_back(new InterLabel(afterLabel));
	return flag;
}

// If_else Statement
bool Define_IfElse_Statement(Node* cur, SymbolTable* table, int linenum){
	string elseLabel = label + "_else_" + labelIndex;
	string afterLabel = label + "_endifelse_" + labelIndex;
	labelIndex++;
	if(cur->if_Expression==NULL) {
		cout << "Error: Line " << linenum << " : Condition for if statement can't be empty." << endl;
		return false;
	}
	bool flag = check(cur->if_Expression, table);
	Register cond = intermediate[cur->if_Expression];
	Tempo tp = interTempo[cur->if_Expression];
	instructions->push_back(new BranchOnEqual(cond, R_ZERO, elseLabel));
	intermediates->push_back(new IfFalseGoto(tp, elseLabel));
	returnRegister(cond);
	returnTempo(tp);
	if(cur->then_Statement!=NULL){
		if(cur->then_Statement->me_StatementType==Stmt_StatementBlock){
			table = pushScope(table);
			flag = check(cur->then_Statement, table) && flag;
			table = popScope(table);
		} else {
			flag = check(cur->then_Statement, table) && flag;
		}
	}
	instructions->push_back(new Jump(afterLabel));
	intermediates->push_back(new InterJumpLabel(afterLabel));
	instructions->push_back(new Label(elseLabel));
	intermediates->push_back(new InterLabel(elseLabel));
	if(cur->else_Statement!=NULL){
		if(cur->else_Statement->me_StatementType==Stmt_StatementBlock){
			table = pushScope(table);
			flag = check(cur->else_Statement, table) && flag;
			table = popScope(table);
		} else {
			flag = check(cur->else_Statement, table) && flag;
		}
	}
	instructions->push_back(new Label(afterLabel));
	intermediates->push_back(new InterLabel(afterLabel));
	return flag;
}

// For statement
bool Define_For_Statement(Node* cur, SymbolTable* table, int linenum){
	string condLabel = label + "_for_cond_" + labelIndex;
	string incrLabel = label + "_for_incr_" + labelIndex;
	string endLabel = label + "_for_end_" + labelIndex;
	labelIndex++;
	string continueBackup = currentLoopContinueLabel;
	string breakBackup = currentLoopBreakLabel;

	currentLoopContinueLabel = incrLabel;
	currentLoopBreakLabel = endLabel;
	bool flag = true;
	if(cur->init_Expression!=NULL) {
		flag = check(cur->init_Expression, table) && flag;
		returnRegister(intermediate[cur->init_Expression]);
		returnTempo(interTempo[cur->init_Expression]);
	}
	instructions->push_back(new Label(condLabel));
	intermediates->push_back(new InterLabel(condLabel));
	if(cur->cond_Expression!=NULL) {
		flag = check(cur->cond_Expression, table) && flag;
		Register cond = intermediate[cur->cond_Expression];
		Tempo tp = interTempo[cur->cond_Expression];
		instructions->push_back(new BranchOnEqual(cond, R_ZERO, endLabel));
		intermediates->push_back(new IfFalseGoto(tp, endLabel));
		returnRegister(cond);
		returnTempo(tp);
	}
	if(cur->for_Statement!=NULL){
		if(cur->for_Statement->me_StatementType==Stmt_StatementBlock){
			table = pushScope(table);
			flag = check(cur->for_Statement, table) && flag;
			table = popScope(table);
		} else {
			flag = check(cur->for_Statement, table) && flag;
		}
	}
	instructions->push_back(new Label(incrLabel));
	intermediates->push_back(new InterLabel(incrLabel));
	if(cur->update_Expression!=NULL) {
		flag = check(cur->update_Expression, table) && flag;
		returnRegister(intermediate[cur->update_Expression]);
		returnTempo(interTempo[cur->update_Expression]);
	}
	instructions->push_back(new Jump(condLabel));
	intermediates->push_back(new InterJumpLabel(condLabel));
	instructions->push_back(new Label(endLabel));
	intermediates->push_back(new InterLabel(endLabel));
	currentLoopContinueLabel = continueBackup;
	currentLoopBreakLabel = breakBackup;
	return flag;
}

// break statement
bool Define_Break_Statement(Node* cur, SymbolTable* table, int linenum){
	if(currentLoopBreakLabel == ""){
		cout << "Error: Line " << linenum << " : Nothing to break out of." << endl;
		return false;
	}
	instructions->push_back(new Jump(currentLoopBreakLabel));
	intermediates->push_back(new InterJumpLabel(currentLoopBreakLabel));
	return true;
}

// continue statement
bool Define_Continue_Statement(Node* cur, SymbolTable* table, int linenum){
	if(currentLoopContinueLabel == ""){
		cout << "Error: Line " << linenum << " : No loop to continue." << endl;
		return false;
	}
	instructions->push_back(new Jump(currentLoopContinueLabel));
	intermediates->push_back(new InterJumpLabel(currentLoopContinueLabel));
	return true;
}

// return statement
bool Define_Return_Statement(Node* cur, SymbolTable* table, int linenum){
	if(cur->return_Expression==NULL) {
		cout << "Error: Line " << linenum << " : Return object can't be empty." << endl;
		return false;
	}
	bool flag = check(cur->return_Expression, table);
	Register ret = intermediate[cur->return_Expression];
	Tempo tp = interTempo[cur->return_Expression];
	instructions->push_back(new BinOp("add", R_V0, ret, R_ZERO));
	intermediates->push_back(new InterReturn(tp));
	returnRegister(ret);
	returnTempo(tp);
	instructions->push_back(new Jump(label + "_end"));	
	return flag;
}

// get the definition information from the symbol table with the given name
Definition* getDefinition(string name, SymbolTable* table, int linenum){
	SymbolTable* tmp_table = table;
	do{
		if(table->count(name)!=0) return table->getItem(name);
		table = table->parent;
	} while(table!=NULL);
	while(tmp_table->parent!=NULL) tmp_table = tmp_table->parent;
	if(tmp_table->count(name+"_global")!=0) return tmp_table->getItem(name+"_global");
	return NULL;
}

// get the address of a global or local variable
Register getVarAddress(Node* cur, SymbolTable* table, int linenum){
	Definition* tmp = getDefinition(cur->ms_Name, table, linenum);
	if(tmp==NULL) {
		cout <<"Error: Line " << linenum << " : No variable is called '" << cur->ms_Name << "'." << endl;
		return R_ZERO;
	}
	if(tmp->definition_type!=type_local_int && tmp->definition_type!=type_global_int && tmp->definition_type!=type_parameter){
		cout <<"Error: Line " << linenum << " : '" <<cur->ms_Name << "' is not a variable." << endl;
		return R_ZERO;
	}
	Register result = getFreeRegister();
	// Tempo tp = getFreeTempo();
	// intermediates->push_back(new MoveVariable(tp, cur->ms_Name));
	// interTempo[cur] = tp;
	switch(tmp->definition_type){
		case type_local_int:
			instructions->push_back(new BinOpImmediate("addi", result, R_SP, tmp->stackOffsite));
			break;
		case type_global_int:
			instructions->push_back(new LoadAddress(result, cur->ms_Name+"_global"));
			break;
		case type_parameter:
			instructions->push_back(new BinOpImmediate("addi", result, R_A0, tmp->stackOffsite));
			break;
	}
	return result;
}

// get the address of a global or local struct
Register getStructMemberAddress(Node* cur, SymbolTable* table, int linenum){
	Definition* tmp = getDefinition(cur->ms_Name, table, linenum);
	if(tmp==NULL){
		cout << "Error: Line " << linenum << " : No struct is called '" << cur->ms_Name << "'." << endl;
		return R_ZERO;
	}
	if(tmp->definition_type!=type_local_struct && tmp->definition_type!=type_global_struct){
		cout << "Error: Line " << linenum << " : '" << cur->ms_Name << "' is not a struct type." << endl;
		return R_ZERO;
	}
	if(tmp->table->struct_map[tmp->struct_type]->Struct_Offsites.count(cur->ms_MemberName)==0){
		cout << "Error: Line " << linenum << " : '" << cur->ms_Name << "' does not have member '" << cur->ms_MemberName << "'." << endl;
		return R_ZERO;
	}
	if(tmp->definition_type==type_local_struct){
		Register address = getFreeRegister();
		Tempo tp = getFreeTempo();
		int offset = tmp->stackOffsite;
		offset += table->struct_map[tmp->struct_type]->Struct_Offsites[cur->ms_MemberName];
		instructions->push_back(new BinOpImmediate("addi", address, R_SP, offset));
		intermediates->push_back(new MoveStruct(tp, cur->ms_Name, cur->ms_MemberName));
		interTempo[cur] = tp;
		return address;
	}
	if(tmp->definition_type==type_global_struct){
		Register address = getFreeRegister();
		Tempo tp = getFreeTempo();
		instructions->push_back(new LoadAddress(address, cur->ms_Name+"_global"));
		instructions->push_back(new BinOpImmediate("addi", address, address, tmp->table->struct_map[tmp->struct_type]->Struct_Offsites[cur->ms_MemberName]));
		intermediates->push_back(new MoveStruct(tp, cur->ms_Name+"_global", cur->ms_MemberName));
		interTempo[cur] = tp;
		return address;
	}
}

// Get the address of a local or global array 
Register getArraySubscriptAddress(Node* cur, SymbolTable* table, int linenum){
	Definition* tmp = getDefinition(cur->ms_Name, table, linenum);
	if(tmp==NULL){
		cout << "Error: Line " << linenum << " : No array is called '" << cur->ms_Name << "'." << endl;
		return R_ZERO;
	}
	if(tmp->definition_type!=type_local_array && tmp->definition_type!=type_global_array){
		cout << "Error: Line " << linenum << " : '" << cur->ms_Name << "' is not an array type." << endl;
		return R_ZERO;
	}
	if(cur->mv_ArraySubscriptList->size() != tmp->array_subscript_num){
		cout << "Error: Line " << linenum << " : '" << cur->ms_Name << "' dimension not fit." << endl;
		return R_ZERO;
	}
	bool flag = true;
	Register result = getFreeRegister();
	Register rt = getFreeRegister();
	Tempo res = getFreeTempo();
	Tempo rtp = getFreeTempo();
	instructions->push_back(new BinOp("add", result, R_ZERO, R_ZERO));
	intermediates->push_back(new MoveImmediate(res, 0));
	Register temp;
	Tempo tp;
	int i=0;
	for(auto it = cur->mv_ArraySubscriptList->begin(); it != cur->mv_ArraySubscriptList->end(); ++it){
		if(*it==NULL) {
			cout << "Error: Line " << linenum <<" : The value of an array subscript can not be empty." << endl;
			return false;
		}
		flag = check(*it, table) && flag;
		temp = intermediate[*it];
		tp = interTempo[*it];
		intermediates->push_back(new MoveImmediate(rtp, tmp->array_subscript_list[i]));
		instructions->push_back(new LoadImmediate(rt, tmp->array_subscript_list[i++]));
		instructions->push_back(new BinOp("mul", result, result, rt));
		intermediates->push_back(new InterBinOp("mul", res, res, rtp));
		instructions->push_back(new BinOp("add", result, result, temp));
		intermediates->push_back(new InterBinOp("add", res, res, tp));
		returnRegister(temp);
		returnTempo(tp);
	}
	instructions->push_back(new LoadImmediate(rt, 4));
	intermediates->push_back(new MoveImmediate(rtp, 4));
	intermediates->push_back(new InterBinOp("mul", res, res, rtp));
	instructions->push_back(new BinOp("mul", result, result, rt));
	returnRegister(rt);
	returnTempo(rtp);
	temp = getFreeRegister();
	if(tmp->definition_type==type_local_array){
		instructions->push_back(new BinOpImmediate("addi", temp, R_SP, tmp->stackOffsite));
	} else if(tmp->definition_type==type_global_array){
		instructions->push_back(new LoadAddress(temp, cur->ms_Name+"_global"));
	}
	instructions->push_back(new BinOp("add", result, temp, result));
	returnRegister(temp);
	interTempo[cur] = res;
	return result;
}

// binary assign expression
bool Define_Assign_Expression(Node* cur, SymbolTable* table, int linenum){
	if(cur->left_Expression->mb_LValueExpression == false){
		cout << "Error: Line " << linenum << " : Attempting to assign a non L-value." << endl;
		return false;
	}
	bool flag = check(cur->right_Expression, table);
	Register value = intermediate[cur->right_Expression];
	Tempo v = interTempo[cur->right_Expression];
	Register address;
	Tempo a;
	switch(cur->left_Expression->me_ExpressionType){
		case Exp_Variable:
			address = getVarAddress(cur->left_Expression, table, cur->left_Expression->mi_LineNum);
			if(address==R_ZERO) return false;
			intermediates->push_back(new MoveToVariable(v, cur->left_Expression->ms_Name));
			break;
		case Exp_Array:
			address = getArraySubscriptAddress(cur->left_Expression, table, cur->left_Expression->mi_LineNum);
			if(address==R_ZERO) return false;
			a = interTempo[cur->left_Expression];
			intermediates->push_back(new MoveToArray(a, cur->left_Expression->ms_Name, a));
			break;
		case Exp_StructMember:
			address = getStructMemberAddress(cur->left_Expression, table, cur->left_Expression->mi_LineNum);
			if(address==R_ZERO) return false;
			intermediates->push_back(new MoveToStruct(v, cur->left_Expression->ms_Name, cur->left_Expression->ms_MemberName));
			break;
	}
	instructions->push_back(new StoreWord(value, address, 0));
	returnRegister(address);
	intermediate[cur] = value;
	interTempo[cur] = v;
	return flag;
}

// Unary assign expression for ++ and --
bool Define_UnaryAssign_Expression(Node* cur, SymbolTable* table, int linenum){
	Register address;
	Tempo tp;
	Tempo a;
	if(cur->right_Expression->mb_LValueExpression == false){
		cout << "Error: Line " << linenum << " : Attempting to assign a non L-value." << endl;
		return false;
	}
	switch(cur->right_Expression->me_ExpressionType){
		case Exp_Variable:
			address = getVarAddress(cur->right_Expression, table, cur->right_Expression->mi_LineNum);
			if(address==R_ZERO) return false;
			tp = getFreeTempo();
			intermediates->push_back(new MoveVariable(tp, cur->right_Expression->ms_Name));
			intermediates->push_back(new InterUnaryOp("inc", tp, tp));
			intermediates->push_back(new MoveToVariable(tp, cur->right_Expression->ms_Name));
			break;
		case Exp_Array:
			a = getFreeTempo();
			address = getArraySubscriptAddress(cur->right_Expression, table, cur->right_Expression->mi_LineNum);
			if(address==R_ZERO) return false;
			a = interTempo[cur->right_Expression];
			intermediates->push_back(new MoveArray(tp, cur->right_Expression->ms_Name, a));
			intermediates->push_back(new InterUnaryOp("inc", tp, tp));
			intermediates->push_back(new MoveToArray(tp, cur->right_Expression->ms_Name, a));
			returnTempo(a);
			break;
		case Exp_StructMember:
			address = getStructMemberAddress(cur->right_Expression, table, cur->right_Expression->mi_LineNum);
			if(address==R_ZERO) return false;
			tp = interTempo[cur->right_Expression];
			intermediates->push_back(new InterUnaryOp("inc", tp, tp));
			intermediates->push_back(new MoveToStruct(tp, cur->right_Expression->ms_Name, cur->right_Expression->ms_MemberName));
			break;
	}
	Register temp = getFreeRegister();
	instructions->push_back(new LoadWord(temp, address, 0));
	if(cur->me_OP==OP_PREINC) instructions->push_back(new BinOpImmediate("addi", temp, temp, 1));
	else if(cur->me_OP==OP_PREDEC) instructions->push_back(new BinOpImmediate("addi", temp, temp, -1));
	instructions->push_back(new StoreWord(temp, address, 0));
	returnRegister(address);
	intermediate[cur] = temp;
	interTempo[cur] = tp; 
	return true;
}

// Get the value of an integer expression
bool Define_Int_Expression(Node* cur, SymbolTable* table, int linenum){
	Register result = getFreeRegister();
	Tempo tp = getFreeTempo();
	instructions->push_back(new LoadImmediate(result, cur->mi_IntExpression_Val));
	intermediates->push_back(new MoveImmediate(tp, cur->mi_IntExpression_Val));
	intermediate[cur] = result;
	interTempo[cur] = tp;
	return true;
}

// Binary operator expression
bool Define_BinaryOp_Expression(Node* cur, SymbolTable* table, int linenum){
	Register left;
	Register right;
	Tempo l, r;
	bool flag = check(cur->left_Expression, table);
	left = intermediate[cur->left_Expression];
	l = interTempo[cur->left_Expression];

	if(cur->me_OP!=OP_LOGICALAND && cur->me_OP!=OP_LOGICALOR){
		flag = check(cur->right_Expression, table) && flag;
		right = intermediate[cur->right_Expression];
		r = interTempo[cur->right_Expression];
	}
	Register ret = getFreeRegister();
	Tempo tp = getFreeTempo();
	string shortcircuitLabel;
	switch(cur->me_OP){
		case OP_MUL: instructions->push_back(new BinOp("mul", ret, left, right));
					intermediates->push_back(new InterBinOp("mul", l, r, tp)); break;
		case OP_DIV: instructions->push_back(new BinOp("div", ret, left, right));
					intermediates->push_back(new InterBinOp("div", l, r, tp)); break;
		case OP_MOD: instructions->push_back(new BinOp("rem", ret, left, right));
					intermediates->push_back(new InterBinOp("mod", l, r, tp)); break;
		case OP_PLUS: instructions->push_back(new BinOp("add", ret, left, right));
					intermediates->push_back(new InterBinOp("add", l, r, tp)); break;
		case OP_MINUS: instructions->push_back(new BinOp("sub", ret, left, right));
					intermediates->push_back(new InterBinOp("sub", l, r, tp)); break;
		case OP_SHL: instructions->push_back(new BinOp("sllv", ret, left, right));
					intermediates->push_back(new InterBinOp("sll", l, r, tp)); break;
		case OP_SHR: instructions->push_back(new BinOp("srlv", ret, left, right));
					intermediates->push_back(new InterBinOp("srl", l, r, tp)); break;
		case OP_GT: instructions->push_back(new BinOp("sgt", ret, left, right));
					intermediates->push_back(new InterBinOp("sgt", l, r, tp)); break;
		case OP_GE: instructions->push_back(new BinOp("sge", ret, left, right));
					intermediates->push_back(new InterBinOp("sge", l, r, tp)); break;
		case OP_LT: instructions->push_back(new BinOp("slt", ret, left, right));
					intermediates->push_back(new InterBinOp("slt", l, r, tp)); break;
		case OP_LE: instructions->push_back(new BinOp("sle", ret, left, right));
					intermediates->push_back(new InterBinOp("sle", l, r, tp)); break;
		case OP_ET: instructions->push_back(new BinOp("seq", ret, left, right));
					intermediates->push_back(new InterBinOp("seq", l, r, tp)); break;
		case OP_NET: instructions->push_back(new BinOp("sne", ret, left, right));
					intermediates->push_back(new InterBinOp("sne", l, r, tp)); break;
		case OP_BITAND: instructions->push_back(new BinOp("and", ret, left, right));
					intermediates->push_back(new InterBinOp("bin_and", l, r, tp)); break;
		case OP_BITXOR: instructions->push_back(new BinOp("xor", ret, left, right));
					intermediates->push_back(new InterBinOp("bin_xor", l, r, tp)); break;
		case OP_BITOR: instructions->push_back(new BinOp("or", ret, left, right));
					intermediates->push_back(new InterBinOp("bin_or", l, r, tp)); break;
		case OP_LOGICALAND:
			shortcircuitLabel = label + "_shortcircuit_" + labelIndex;
			labelIndex++;
			instructions->push_back(new BinOp("add", ret, left, R_ZERO));
			intermediates->push_back(new Move(left, tp));
			instructions->push_back(new BranchOnEqual(left, R_ZERO, shortcircuitLabel));
			intermediates->push_back(new IfFalseGoto(left, shortcircuitLabel));
			flag = check(cur->right_Expression, table) && flag;
			right = intermediate[cur->right_Expression];
			r = interTempo[cur->right_Expression];
			instructions->push_back(new BinOp("add", ret, right, R_ZERO));
			intermediates->push_back(new Move(right, tp));
			instructions->push_back(new Label(shortcircuitLabel));
			intermediates->push_back(new InterLabel(shortcircuitLabel));
			break;
		case OP_LOGICALOR:
			shortcircuitLabel = label + "_shortcircuit_" + labelIndex;
			labelIndex++;
			instructions->push_back(new BinOp("add", ret, left, R_ZERO));
			intermediates->push_back(new Move(left, tp));
			instructions->push_back(new BranchNotEqual(left, R_ZERO, shortcircuitLabel));
			intermediates->push_back(new IfGoto(left, shortcircuitLabel));
			flag = check(cur->right_Expression, table) && flag;
			right = intermediate[cur->right_Expression];
			r = interTempo[cur->right_Expression];
			instructions->push_back(new BinOp("add", ret, right, R_ZERO));
			intermediates->push_back(new Move(r, tp));
			instructions->push_back(new Label(shortcircuitLabel));
			intermediates->push_back(new InterLabel(shortcircuitLabel));
			break;
	}
	returnRegister(left);
	returnTempo(l);
	returnRegister(right);
	returnTempo(r);
	intermediate[cur] = ret;
	interTempo[cur] = tp;
	return flag;
}

// Unary operator expression
bool Define_UnaryOp_Expression(Node* cur, SymbolTable* table, int linenum){
	bool flag = check(cur->right_Expression, table);
	Register ret = intermediate[cur->right_Expression];
	Tempo tp = interTempo[cur->right_Expression];
	switch(cur->me_OP){
		case OP_MINUS: instructions->push_back(new BinOp("sub", ret, R_ZERO, ret)); 
					intermediates->push_back(new InterUnaryOp("minus", tp, tp)); break;
		case OP_BITNOT: instructions->push_back(new BinOp("nor", ret, R_ZERO, ret));
					intermediates->push_back(new InterUnaryOp("bitnot", tp, tp)); break;
		case OP_LOGICALNOT: instructions->push_back(new BinOp("seq", ret, R_ZERO, ret));
					intermediates->push_back(new InterUnaryOp("logi_not", tp, tp)); break;
	}
	intermediate[cur] = ret;
	interTempo[cur] = tp;
	return flag;
}

// Get the value of a variable
bool Define_Variable_Expression(Node* cur, SymbolTable* table, int linenum){
	Register address = getVarAddress(cur, table, linenum);
	if(address==R_ZERO) return false;
	Tempo tp = getFreeTempo();
	instructions->push_back(new LoadWord(address, address, 0));
	intermediates->push_back(new MoveVariable(tp, cur->ms_Name));
	intermediate[cur] = address;
	interTempo[cur] = tp;
	return true;
}

// Get the value of an array member
bool Define_Array_Expression(Node* cur, SymbolTable* table, int linenum){
	Register result = getArraySubscriptAddress(cur, table, linenum);
	if(result==R_ZERO) return false;
	Tempo tp = interTempo[cur];
	instructions->push_back(new LoadWord(result, result, 0));
	intermediates->push_back(new MoveArray(tp, cur->ms_Name, tp));
	intermediate[cur] = result;
	interTempo[cur] = tp;
	return true;
}

// Do the function call
bool Define_FunctionCall_Expression(Node* cur, SymbolTable* table, int linenum){
	SymbolTable* tmp_table = table;
	while(tmp_table->parent!=NULL)tmp_table = tmp_table->parent;
	if(tmp_table->count(cur->ms_Name)==0 || tmp_table->getItem(cur->ms_Name)->definition_type!=type_function){
		cout << "Error: Line " << linenum << " : No declaration by name '" << cur->ms_Name << "'." << endl;
		return false;
	}
	Definition* tmp = tmp_table->getItem(cur->ms_Name);
	if(cur->mv_ArgumentList->size() != tmp->parameter_number){
		cout << "Error: Line " << linenum << " : Function call does not have the same number of arguments as the function itself." << endl;
		return false;
	}
	int oldStackOffset = stackSize;
	stackSize += tmp->parameter_number * 4;

	int paramOffset = oldStackOffset;
	bool flag = true;
	for(auto it=cur->mv_ArgumentList->begin(); it!=cur->mv_ArgumentList->end(); ++it){
		flag = check(*it, table) && flag;
		Register argValue = intermediate[*it];
		instructions->push_back(new StoreWord(argValue, R_SP, paramOffset));
		paramOffset += 4;
		returnRegister(argValue);
	}
	instructions->push_back(new BinOpImmediate("addi", R_A0, R_SP, oldStackOffset));
	int regOffset = 0;
	if(registersInUse.size() > 0) {
		for(auto it = registersInUse.begin(); it != registersInUse.end(); it++) {
			regOffset -= 4;
			instructions->push_back(new StoreWord(*it, R_SP, regOffset));
		}
		instructions->push_back(new BinOpImmediate("addi", R_SP, R_SP, regOffset));
	}
	
	instructions->push_back(new JumpAndLink(cur->ms_Name));
	
	if(registersInUse.size() > 0) {
		instructions->push_back(new BinOpImmediate("addi", R_SP, R_SP, -regOffset));
		regOffset = 0;
		for(auto it = registersInUse.begin(); it != registersInUse.end(); it++) {
			regOffset -= 4;
			instructions->push_back(new LoadWord(*it, R_SP, regOffset));
		}
	}
	intermediates->push_back(new CallFunction(cur->ms_Name));
	Tempo tp = getFreeTempo();
	interTempo[cur] = tp;
	Register ret = getFreeRegister();
	instructions->push_back(new BinOp("add", ret, R_V0, R_ZERO));
	instructions->push_back(new LoadWord(R_A0, R_SP, 4));
	intermediate[cur] = ret;
	return flag;
}

// Get the value of a struct member
bool Define_StructMember_Expression(Node* cur, SymbolTable* table, int linenum){
	Register address = getStructMemberAddress(cur, table, cur->mi_LineNum);
	if(address==R_ZERO) return false;
	instructions->push_back(new LoadWord(address, address, 0));
	intermediate[cur] = address;
	return true;
}

// Read statement
bool Define_Read_Statement(Node* cur, SymbolTable* table, int linenum){
	if(cur->io_Expression==NULL){
		cout << "Error: Line " << linenum << " : Read statement must has an argument." << endl;
		return false;
	}
	if(cur->io_Expression->mb_LValueExpression==false){
		cout << "Error: Line " << linenum << " : The read in value must be a l-value." << endl;
		return false;
	}
	Register address;
	switch(cur->io_Expression->me_ExpressionType){
		case Exp_Variable:
			address = getVarAddress(cur->io_Expression, table, linenum);
			if(address==R_ZERO) return false;
			break;
		case Exp_Array:
			address = getArraySubscriptAddress(cur->io_Expression, table, linenum);
			if(address==R_ZERO) return false;
			break;
		case Exp_StructMember:
			address = getStructMemberAddress(cur->io_Expression, table, linenum);
			if(address==R_ZERO) return false;
			break;
	}
	if(address==R_ZERO) return false;
	instructions->push_back(new BinOp("add", R_A1, R_V0, R_ZERO));
	// instructions->push_back(new BinOp("add", $R_A2, $R_A0, $R_ZERO));
	instructions->push_back(new LoadImmediate(R_V0, 5));
	instructions->push_back(new Syscall());
	instructions->push_back(new StoreWord(R_V0, address, 0));
	instructions->push_back(new BinOp("add", R_V0, R_A1, R_ZERO));
	intermediates->push_back(new CallRead());
	returnRegister(address);
	reclaimTempos();
	return true;
}

// Write Statement
bool Define_Write_Statement(Node* cur, SymbolTable* table, int linenum){
	if(cur->io_Expression==NULL){
		cout << "Error: Line " << linenum << " : Write statement must has an argument." << endl;
		return false;
	}
	if(!check(cur->io_Expression, table)) return false;
	Register tmp = intermediate[cur->io_Expression];
	instructions->push_back(new BinOp("add", R_A1, R_V0, R_ZERO));
	instructions->push_back(new BinOp("add", R_A2, R_A0, R_ZERO));
	instructions->push_back(new LoadImmediate(R_V0, 1));
	instructions->push_back(new BinOp("add", R_A0, tmp, R_ZERO));
	instructions->push_back(new Syscall());
	instructions->push_back(new BinOp("add", R_V0, R_A1, R_ZERO));
	instructions->push_back(new BinOp("add", R_A0, R_A2, R_ZERO));
	intermediates->push_back(new CallWrite());
	returnRegister(tmp);
	reclaimTempos();
	return true;
}
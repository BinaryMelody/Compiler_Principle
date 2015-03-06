////////////////////////////////////////////////////////////////////////
/*
  File Name: Info.h
  This file is the file of the Type Node implementation, the variables 
  and functions used to generate a parse tree, which are used by the 
  parser are all presented here.
*/
////////////////////////////////////////////////////////////////////////

#ifndef INFO_H
#define INFO_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;

enum NodeType{
	Expression,
	Statement,
	Function,
	Declaration,
	Program
};

enum DeclarationType{
	Dec_Global_Variable_Array,
	Dec_Global_Struct,
	Dec_Local_Variable_Array,
	Dec_Local_Struct
};

enum ExpressionType{
	Exp_Assign,
	Exp_UnaryAssign,
	Exp_Int,
	Exp_BinaryOp,
	Exp_UnaryOp,
	Exp_Variable,
	Exp_Array,
	Exp_FunctionCall,
	Exp_StructMember
};

enum StatementType{
	Stmt_Break,
	Stmt_Continue,
	Stmt_Return,
	Stmt_If,
	Stmt_IfElse,
	Stmt_StatementBlock,
	Stmt_For,
	Stmt_Read,
	Stmt_Write
};

enum OperatorType{
	OP_MUL,
	OP_DIV,
	OP_MOD,
	OP_PLUS,
	OP_MINUS,
	OP_SHL,
	OP_SHR,
	OP_GT,
	OP_GE,
	OP_LT,
	OP_LE,
	OP_ET,
	OP_NET,
	OP_BITAND,
	OP_BITXOR,
	OP_BITOR,
	OP_LOGICALAND,
	OP_LOGICALOR,
	OP_LOGICALNOT,
	OP_BITNOT,
	OP_PREINC,
	OP_PREDEC
};
struct Node;
struct Variable_ArrayDeclarationInfo;
struct Variable_ArrayDeclarationInfo {
	string ms_Name;
	vector<int> mv_ArrayDeclarationSubscriptList;
	vector<Node*>* mv_InitList;
	Variable_ArrayDeclarationInfo(){}
	~Variable_ArrayDeclarationInfo(){}
};
struct Node {
	Node* parent;
	int mi_LineNum;
	NodeType me_NodeType;
	string ms_Name;

	// ExpressionType
	ExpressionType me_ExpressionType;
	bool mb_LValueExpression;

		// Int Const Expression
		int mi_IntExpression_Val;

		// Variable Expression

		// Array Expression
		vector<Node*>* mv_ArraySubscriptList;

		// FunctionCall Argument Expression
		vector<Node*>* mv_ArgumentList;

		// StructMember Expression
		string ms_MemberName;

		// Op Expression
		Node* left_Expression; // Also ++, --, -, !
		Node* right_Expression; 
		OperatorType me_OP;


	// DeclarationType
	DeclarationType me_DeclarationType;
	
		// Variable_Array Declaration
		vector<Variable_ArrayDeclarationInfo*>* mv_Var_Arr_Dec_Info_Vector;

		// Struct Declaration
		string ms_StructName;
		vector<string>* mv_StructMembers;
		vector<string>* mv_StructDeclarations;

	// StatementType
	StatementType me_StatementType;

		// Return Statement
		Node* return_Expression;

		// If then (else) Statement
		Node* if_Expression;
		Node* then_Statement;
		Node* else_Statement;

		// For Statement
		Node* init_Expression;
		Node* cond_Expression;
		Node* update_Expression;
		Node* for_Statement;

		// StatementBlock
		vector<Node*>* declarations_in_block;
		vector<Node*>* statements_in_block;

		// Read and Write
		Node* io_Expression;

	// Function
	vector<string>* parameters;
	Node* function_Body;

	// Program
	vector<Node*>* extern_declarations;

	Node(int line_count, NodeType type){
		mi_LineNum = line_count;
		me_NodeType = type;
	}

	

	// Expression Utils****************************
	void initial_Expression_Int(int value){
		me_ExpressionType = Exp_Int;
		mi_IntExpression_Val = value;
		mb_LValueExpression = false;
	}

	// Compute integers when compiling
	void initial_Expression_BinaryOp(Node* left, OperatorType OP, Node* right){
		mb_LValueExpression = false;
		if(left->me_ExpressionType == Exp_Int && right->me_ExpressionType == Exp_Int){
			me_ExpressionType = Exp_Int;
			int a = left->mi_IntExpression_Val;
			int b = right->mi_IntExpression_Val;
			int c;
			switch(OP){
				case OP_MUL: c = a * b; break;
				case OP_DIV: c = a / b; break;
				case OP_MOD: c = a % b; break;
				case OP_PLUS: c = a + b; break;
				case OP_MINUS: c = a - b; break;
				case OP_SHL: c = a << b; break;
				case OP_SHR: c = a >> b; break;
				case OP_GT: c = a > b; break;
				case OP_GE: c = a >= b; break;
				case OP_LT: c = a < b; break;
				case OP_LE: c = a <= b; break;
				case OP_ET: c = a == b; break;
				case OP_NET: c = a != b; break;
				case OP_BITAND: c = a & b; break;
				case OP_BITXOR: c = a ^ b; break;
				case OP_BITOR: c = a | b; break;
				case OP_LOGICALAND: c = a && b; break;
				case OP_LOGICALOR: c = a || b; break;
			}
			mi_IntExpression_Val = c;
			delete left;
			delete right;
			return;
		}
		me_ExpressionType = Exp_BinaryOp;
		left_Expression = left;
 		right_Expression = right;
 		me_OP = OP;
	}

	void initial_Expression_UnaryOp(OperatorType OP, Node* right){
		mb_LValueExpression = false;
		if(right->me_ExpressionType == Exp_Int){
			me_ExpressionType = Exp_Int;
			int b = right->mi_IntExpression_Val;
			switch(OP){
				case OP_MINUS: b = -b; break;
				case OP_LOGICALNOT: b = !b; break;
				case OP_BITNOT: b = ~b; break;
			}
			mi_IntExpression_Val = b;
			delete right;
			return;
		}
		me_ExpressionType = Exp_UnaryOp;
		right_Expression = right;
		me_OP = OP;
	}

	void initial_Expression_Assign(Node* left, Node* right){
		me_ExpressionType = Exp_Assign;
		mb_LValueExpression = false;
		left_Expression = left;
		right_Expression = right;
	}

	void initial_Expression_UnaryAssign(OperatorType OP, Node* right){
		me_ExpressionType = Exp_UnaryAssign;
		mb_LValueExpression = false;
		right_Expression = right;
		me_OP = OP;
	}

	void initial_Expression_Variable_Array(string* name, vector<Node*>* subscriptList){
		ms_Name = *name;
		delete name;
		mb_LValueExpression = true;
		if(subscriptList->size()==0)
			me_ExpressionType = Exp_Variable;
		else {
			me_ExpressionType = Exp_Array;
			mv_ArraySubscriptList = subscriptList;
			// for(int i=0; i<mv_ArraySubscriptList->size(); ++i)
			// 	cout << (*(mv_ArraySubscriptList))[i]->mi_IntExpression_Val << " ";
			// cout << endl;
		}
	}

	void initial_Expression_FunctionCall(string* name, vector<Node*>* argumentList){
		if(*name!="main") ms_Name = *name + "_global";
		else ms_Name = *name;
		delete name;
		mb_LValueExpression = false;
		me_ExpressionType = Exp_FunctionCall;
		mv_ArgumentList = argumentList;
	}

	void initial_Expression_StructMember(string* name, string* memberName){
		ms_Name = *name;
		delete name;
		ms_MemberName = *memberName;
		delete memberName;
		mb_LValueExpression = true;
		me_ExpressionType = Exp_StructMember;
	}

	// Declaration Utils
	void initial_Declaration_Local_Variable_Array(vector<Variable_ArrayDeclarationInfo*>* mV_Var_Arr_Dec_Info_Vector){
		mv_Var_Arr_Dec_Info_Vector = mV_Var_Arr_Dec_Info_Vector;
		me_DeclarationType = Dec_Local_Variable_Array;
	}

	void initial_Declaration_Global_Variable_Array(vector<Variable_ArrayDeclarationInfo*>* mV_Var_Arr_Dec_Info_Vector){
		mv_Var_Arr_Dec_Info_Vector = mV_Var_Arr_Dec_Info_Vector;
		for(auto it = mv_Var_Arr_Dec_Info_Vector->begin(); it != mv_Var_Arr_Dec_Info_Vector->end(); ++it){
			(*it)->ms_Name = (*it)->ms_Name + "_global";
		}
		me_DeclarationType = Dec_Global_Variable_Array;
	}

	void initial_Declaration_Local_Struct(vector<string>* stspec, vector<string>* sdecs){
		me_DeclarationType = Dec_Local_Struct;
		mv_StructDeclarations = sdecs;
		ms_StructName = (*stspec)[stspec->size()-1];
		stspec->pop_back();
		mv_StructMembers = stspec;
	}

	void initial_Declaration_Global_Struct(vector<string>* stspec, vector<string>* sextvars){
		me_DeclarationType = Dec_Global_Struct;
		mv_StructDeclarations = sextvars;
		for(auto it=sextvars->begin(); it!=sextvars->end(); ++it){
			*it += "_global";
		}
		ms_StructName = (*stspec)[stspec->size()-1];
		stspec->pop_back();
		mv_StructMembers = stspec;
	}

	// Statement Utils
	void initial_Statement_Return(Node* expression){
		me_StatementType = Stmt_Return;
		return_Expression = expression;
	}

	void initial_Statement_If(Node* expression, Node* then_statement){
		me_StatementType = Stmt_If;
		if_Expression = expression;
		then_Statement = then_statement;
	}

	void initial_Statement_IfElse(Node* expression, Node* then_statement, Node* else_statement){
		me_StatementType = Stmt_IfElse;
		if_Expression = expression;
		then_Statement = then_statement;
		else_Statement = else_statement;
	}

	void initial_Statement_For(Node* expression1, Node* expression2, Node* expression3, Node* statement){
		me_StatementType = Stmt_For;
		init_Expression = expression1;
		cond_Expression = expression2;
		update_Expression = expression3;
		for_Statement = statement;
	}

	void initial_Statement_StmtBlock(vector<Node*>* declarations, vector<Node*>* statements){
		me_StatementType = Stmt_StatementBlock;
		declarations_in_block = declarations;
		statements_in_block = statements;
	}

	// Function Utils
	void initial_Function(vector<string>* paras, Node* body){
		if((*paras)[paras->size()-1]!="main") ms_Name = (*paras)[paras->size()-1] + "_global";
		else ms_Name = (*paras)[paras->size()-1];
		paras->pop_back();
		parameters = paras;
		function_Body = body;
	}
};


// struct Variable_ArrayDeclarationInfo {
// 	string ms_Name;
// 	vector<int> mv_ArrayDeclarationSubscriptList;
// 	vector<Node*>* mv_InitList;
// 	Variable_ArrayDeclarationInfo(){}
// 	~Variable_ArrayDeclarationInfo(){}
// };

#endif
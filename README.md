#CS215 Compiler Principles Project Report
***
####Name: Zuoming Zhang
####Student ID: 5120309626

##Introduction
**SMALLC** is a simplified *C-liked* programming language containing only the core part of C language. In this project, I have designed and implemented a simplified compiler, which can translate **SMALLC** source codes to **MIPS** assembly codes. These assembly codes can run on the **SPIM** simulator. The project was done in a Linux Environment called *Ubuntu Kylin 14.04*.

The procedure of the project was divided in to 5 parts:

* Lexical analyzer
* Syntax analyzer
* Semantic analyzer & Intermediate representation generation
* Optimization
* Target **MIPS** code generation

***
##Lexical Analyzer
A lexical analyser has been implemented in this part. It reads the source codes of **SMALLC** and separates them into tokens. The work is done using *FLEX* and the related file is `"smallc.l"`
###DEC HEX & OCT Numbers
To deal with int numbers that are not traditionally decimals, there is a quite simple way to avoid typing the translation code on your own, which requires you to `#include<stdlib.h>` first:

    0[0-7]*				{ /*OCT*/ yylval.mI_Int = strtoul(yytext, NULL, 0); return INT; }
	[1-9][0-9]*			{ /*DEC*/ yylval.mI_Int = strtoul(yytext, NULL, 0); return INT; }
	0[Xx][0-9a-fA-F]+	{ /*HEX*/ yylval.mI_Int = strtoul(yytext, NULL, 0); return INT; }
###Read and Write
Since most of the details of **TOKENS** and **Operators** are given to us in the project requirement, I will not talk about them in the report. Instead, I will show you how to deal with **read** and **write** tokens. They are also very simple:

	read	{ return READ; }
	write 	{ return WRITE; }
###Comments
There are two kinds of comments in *C* language.

The first kind is to comment the rest of the line using `\\` token. It was implemented by using the following method:

	"//"(.)*	{ /* Comments, do nothing */ }
The second kind is to comment the materials between `/*` and `*/` token pairs, which made use of the *state transition method*:

	%x comment
	
	%%
	"/*"			BEGIN(comment);
	<comment>{
	[^*\n]*			/* eat anything that's not a '*' */
	"*"+[^*/\n]*	/* eat up '*'s not followed by '/'s */
	\n
	"*"+"/"			BEGIN(INITIAL);
	}
###Line number
There are various to mark the line nubmers. In my implementation, an `updatePosition()` method is called on every token:

	void updatePosition();
	#define YY_USER_ACTION updatePosition();
	int linecount = 1;
	%%
	[\n]	{ ++linecount; }
	%%
	void updatePosition(){
		yyloc.first_line = linecount;
	}

Once you want to get the line number of a particular token $ in the *YACC* file, you can simply use `@$.first_line` to obtain the data.
***
##Syntax Analyzer
In this step, I performed the syntax analysis using *YACC* and the file name is `"smallc.y"`.
###Precedence of *IF* and *IF ELSE* Statement
There exists a conflict in the implementation of "*IF LP EXP RP STMT*" and "*IF LP EXP RP STMT ELSE STMT*", and the former one should have a lower precedence than the latter one. Here is the implementation:

	%nonassoc LOWER_THAN_ELSE
	%nonassoc ELSE
	%%
	STMT:
	 | IF LP EXP RP STMT %prec LOWER_THAN_ELSE
	 | IF LP EXP RP STMT ELSE STMT
	 ;
Pay attention that the order of the first two lines should not be exchanged.
###Read and Write
In my project, *read* and *write* are implemented in the syntax of *STMT*, which means that you can never cite them in an *EXP*. The implementation is as follows:

	STMT:
	 | READ LP EXP RP SEMI
	 | WRITE LP EXP RP SEMI
	 ;
###Error Message
The error message is done together with generating the parse tree. Once an error occurs during the procedure, the parse process will shutdown and report the just-found mistake:

	void yyerror(const char *s){
		fprintf(stderr, "[line %d]: %s %s\n", yylloc.first_line, s, yytext);
	}
It will show you the line number of the error and its error text.
***
##Semantic Analyzer & IR Generation
In this section, I have implemented the Semantic Analyzer & IR Generation together with the formation of the parse tree.
###Parse Tree Generation
Actually, the *Parse Tree Generation* part is done in the above section. Since it is closely related to *Semantic Analyzing* as well as *IR Generation*, I will talk about it in this section.

The Parse Tree Generation is based on the construction of `struct Node{}`. Different nodes of the parse tree will use only a specific part of the *Node* members. Though it seems very space-consuming, most of the members of *Node* are pointers and it won't cost too much extra space. The implementation with this method is rather simpler than using the C++ class method. The codes are implemented in `include "Info.h"` Take the generation of a *Binary Plus Operation Expression* as an example:

	EXPS: EXPS PLUS EXPS;	{
							$$ = new Node(@$.first_line, Expression); // Pass in the line number and node type is expression.
							$$->initial_Expression_BinaryOp($1, OP_PLUS, $3); // Set the attributes of the Node.
							}
	
	void initial_Expression_BinaryOp(Node* left, OperatorType OP, Node* right){
		mb_LValueExpression = false;	// This is not a LValue Expression, which means that it cannot be assigned.
		me_ExpressionType = Exp_BinaryOp;	// The type of this expression is a binary operator.
		left_Expression = left;	// left_Expression is the left node
		right_Expression = right;	// right_Expression is the right node 
		me_OP = OP;	// Operator type, in this case it is PLUS.
	}
The different variables of *Node* and there usage are shown in the table below:

<table>
	<tr>
		<td><B>Contained By</B></td>
		<td><B>Variable Name</B></td>
		<td><B>Usage</B></td>
	</tr>
	<tr>
		<td><B>All</B></td>
		<td>int mi_LineNum</td>
		<td>Line Number, used by error message</td>
	</tr>
	<tr>
		<td></td>
		<td>enum NodeType me_NodeType</td>
		<td>Type of the node, e.g. Expression, Statement, Declaration</td>
	</tr>
	<tr>
		<td></td>
		<td>ms_Name</td>
		<td>Different uses in different variables, e.g. function name</td>
	</tr>
	<tr>
		<td><B>Expression</B></td>
		<td>enum ExpressionType me_ExpressionType</td>
		<td>The type of expression, e.g. binary_operator</td>
	</tr>
	<tr>
		<td></td>
		<td>bool mb_LValueExpression</td>
		<td>Whether it is an L-Value Expression</td>
	</tr>
	<tr>
		<td>Expression:Int</td>
		<td>int mi_IntExpression_Val</td>
		<td>The value of constant int expression</td>
	</tr>
	<tr>
		<td>Expression:Array</td>
		<td>vector<Node*>* mv_ArraySubscriptList</td>
		<td>The subscript expression list of an array expression</td>
	</tr>
	<tr>
		<td>Expression:FunctionCall</td>
		<td>vector<Node*>* mv_ArgumentList</td>
		<td>The argument list of a function call</td>
	</tr>
	<tr>
		<td>Expression:Struct</td>
		<td>string ms_MemberName</td>
		<td>The name of the member of a struct type</td>
	</tr>
	<tr>
		<td>Expression:Operator</td>
		<td>Node* left_Expression</td>
		<td>Left part of assign and binary operator expression</td>
	</tr>
	<tr>
		<td></td>
		<td>Node* right_Expression</td>
		<td>Right part of unary assign, assign and binary op exp</td>
	</tr>
	<tr>
		<td></td>
		<td>enum OperatorType me_OP</td>
		<td>The operator type of the expression</td>
	</tr>
	<tr>
		<td><B>Declaration</B></td>
		<td>enum DeclarationType me_DeclarationType</td>
		<td>The declaration type of variable(s)</td>
	</tr>
	<tr>
		<td>Declaration:Array/Variable</td>
		<td>vector<Variable_ArrayDeclarationInfo*>*</td>
		<td>The information list of declare an array or a variable</td>
	</tr>
	<tr>
		<td>Declaration:Struct</td>
		<td>string ms_StructName</td>
		<td>The struct type of a struct variable</td>
	</tr>
	<tr>
		<td></td>
		<td>vector<string>* mv_StructMembers</td>
		<td>The member names of a struct type</td>
	</tr>
	<tr>
		<td></td>
		<td>vector<string>* mv_StructDeclarations</td>
		<td>The declared variables using this struct type</td>
	</tr>
	<tr>
		<td><B>Statement</B></td>
		<td>enum StatementType me_StatementType</td>
		<td>The type of statement</td>
	</tr>
	<tr>
		<td>Statement:Return</td>
		<td>Node* return_Expression</td>
		<td>Return expression</td>
	</tr>
	<tr>
		<td>Statement:If then (else)</td>
		<td>Node* if_Expression</td>
		<td>If condition Expression</td>
	</tr>
	<tr>
		<td></td>
		<td>Node* then_Statement</td>
		<td>Then Statement(block)</td>
	</tr>
	<tr>
		<td></td>
		<td>Node* else_Statement</td>
		<td>Else Statement(block)</td>
	</tr>
	<tr>
		<td>Statement:For</td>
		<td>Node* init_Expression</td>
		<td>For init exp</td>
	</tr>
	<tr>
		<td></td>
		<td>Node* cond_Expression</td>
		<td>For condition exp</td>
	</tr>
	<tr>
		<td></td>
		<td>Node* update_Expression</td>
		<td>For increment exp</td>
	</tr>
	<tr>
		<td></td>
		<td>Node* for_Statement</td>
		<td>For loop statement</td>
	</tr>
	<tr>
		<td>Statement:StatementBlock</td>
		<td>vector<Node*>* declarations_in_block</td>
		<td>Declaration list in a block</td>
	</tr>
	<tr>
		<td></td>
		<td>vector<Node*>* statements_in_block</td>
		<td>Statement list in a block</td>
	</tr>
	<tr>
		<td>Statement:Read & Write</td>
		<td>Node* io_Expression</td>
		<td>Used by Read or Write</td>
	</tr>
	<tr>
		<td><B>Function</B></td>
		<td>vector<stirng>* parameters</td>
		<td>Parameter list of a function</td>
	</tr>
	<tr>
		<td></td>
		<td>Node* function_Body</td>
		<td>Statementblock of a function</td>
	</tr>
	<tr>
		<td><B>Program</B></td>
		<td>vector<Node*>* extern_declarations</td>
		<td>EXTDECS of a program</td>
	</tr>
</table>

###Semantic Analysis
Soon after the implementation of the parse tree, the semantic analysis and syntactic checking are performed to check whether the program is the correct program. It is done in `GenIntermediate.cpp`.

The followings will show my implementation:
####In Project Requirement
I have implemented all the requirements of semantic checking in the project requirement.
#####Declaration
Variables and functions should be declared before usage:

	Definition* tmp = getDefinition(cur->ms_Name, table, linenum);
	if(tmp==NULL) {
		cout <<"Error: Line " << linenum << " : No variable is called '" << cur->ms_Name << "'." << endl;
		return R_ZERO;
	}
Variables and functions should not be re-declared:

	if(table->count(info->ms_Name)!=0){
		cout << "Error: Line " << linenum << " : '" << info->ms_Name << "' has already been declared in this scope." << endl;
		return false;
	}
#####Reserved words
Reserved words can not be used as identifiers. 

This is implemented in syntax checking in the Syntax Analyzer and will not be shown here.
#####"main()" entrance
Program must contain a function int main() to be the entrance.

	if(table->count("main")==0 || table->getItem("main")->definition_type != type_function){
		cout << "Error: The program does not have an entrance 'main'." << endl;
		flag = false;
	}
#####Function call parameters
The number and type of variable(s) passed should match the definition of the function.

	if(cur->mv_ArgumentList->size() != tmp->parameter_number){
		cout << "Error: Line " << linenum << " : Function call does not have the same number of arguments as the function itself." << endl;
		return false;
	}
##### [] and . operator
Use [] operator to a non-array variable is not allowed.

	if(tmp->definition_type!=type_local_array && tmp->definition_type!=type_global_array){
		cout << "Error: Line " << linenum << " : '" << cur->ms_Name << "' is not an array type." << endl;
		return R_ZERO;
	}
The . operator can only be used to a struct variable.

	if(tmp->definition_type!=type_local_struct && tmp->definition_type!=type_global_struct){
		cout << "Error: Line " << linenum << " : '" << cur->ms_Name << "' is not a struct type." << endl;
		return R_ZERO;
	}
#####Break and Continue
Break and continue can only be used in a for-loop

	if(currentLoopBreakLabel == ""){
		cout << "Error: Line " << linenum << " : Nothing to break out of." << endl;
		return false;
	}
	if(currentLoopContinueLabel == ""){
		cout << "Error: Line " << linenum << " : No loop to continue." << endl;
		return false;
	}
#####Right and Left Value
Right-value can not be assigned by any value or expression.

	if(cur->left_Expression->mb_LValueExpression == false){
		cout << "Error: Line " << linenum << " : Attempting to assign a non L-value." << endl;
		return false;
	}
#####Operands Type checking
The condition of if statement should be an expression with int type.

The condition of for should be an expression with int type or NULL.

Only expression with type int can be involved in arithmetic.

Since in my application, operators and assigns can only be done with int values, so the if and for condition are sure not to work with other types of variables. e.g. A struct type is called*asdf*, and when you put it in a condition, the compiler try to get it address, and treat it as avariable. It will find aa in the symbol table, but the definition type of *asdf* is *struct* instead of *variable*. It will send out an error message telling you that you cannot get the address of the variable.
####Beyond Project Requirement
The following will show my implementation of semantic checking beyond course requirement.
#####Array Declaration
In my project, you can declare an array with as large dimension as you like. And you can never declare an array with non-positive size.

	if(array_num<=0){
		cout << "Error: Line " << linenum << " : An array is initialized with non-positive size." << endl;
		return false;
	}
You can never initialize an array with initial list number more than the array size.

	if(array_num < info->mv_InitList->size()) {
		cout << "Error: Line " << linenum << " : The initialize list is too large for '" << info->ms_Name << "'." << endl;
		return false;
	}
It will also check whether the initial subscript list of an array are constants.

	if((*(info->mv_InitList))[i]->me_ExpressionType != Exp_Int){
		cout << "Error: Line " << linenum << " : The initialize value should be a constant expression." << endl;
		return false;
	}
#####Struct Declaration
Struct should not be declared with no members or name at the same time:

	if(structMembers->size()==0 || structDeclarations->size()==0){
		cout << "Error: Line " << linenum << " : Struct Declaration with no members or name." << endl;
		return false;
	}
Which means that you can not use something like `struct ;` in your program, which is meaningless.

You can predeclare a struct type like: `struct typestruct  ab, cd;` and implement it in later code: `struct typestruct { int aa; int bb; }`. After your implementation, *ab* and *cd* will both have members *aa* and *bb*.

You can also define a struct type like: `struct typestruct { int aa; int bb;}` and use it in later: `struct typestruct ab, cd;`. It will have the same effect as the above paragraph.

If you don't assign a name for struct type, it will assign a randam name for the type: `struct { int aa; int bb;} ab, cd;`. In this case, *ab* and *cd* will have a randam struct type name like *#a*. Although *#* can not be recognized as an identifier in *C* language, it will be OK since I use *string* to implement this.
#####Return Object
Return object can never be empty, since all of the functions are int type.

	if(cur->return_Expression==NULL) {
		cout << "Error: Line " << linenum << " : Return object can't be empty." << endl;
		return false;
	}
#####Struct Member Check
The right part of operator *'.'* must be a member in the struct type, otherwise it will send out an error message:

	if(tmp->table->struct_map[tmp->struct_type]->Struct_Offsites.count(cur->ms_MemberName)==0){
		cout << "Error: Line " << linenum << " : '" << cur->ms_Name << "' does not have member '" << cur->ms_MemberName << "'." << endl;
		return R_ZERO;
	}
#####Array Usage
The dimension of the array usage must fit the declaration:

	if(cur->mv_ArraySubscriptList->size() != tmp->array_subscript_num){
		cout << "Error: Line " << linenum << " : '" << cur->ms_Name << "' dimension not fit." << endl;
		return R_ZERO;
	}
###Symbol Table
In this part, I implemented a Symbol Table of the program. Each Symbol table has a parent Symbol Table pointer but has no son Symbol Table pointers. Once a Symbol Table is used, it will be poped from the current symbol table. The parent node pointer makes it possible to find the variable in a parent scope. In each Symbol Table, there are mainly two parts. One saves the names and there related information of the variables and functions(in the root Symbol Table). The other is used to save the information of a struct type, like the members it has and relative offsets in the stack of each member.
###IR Generation
In this part, I implemented the intermediate code generation. The IR code are a bit like the final **MIPS** code for the sake of simplicity of implementation. (Actually, I think the IR code is useless in this project since it is much more easy to directly generate **MIPS** without generating IR first.) The IR codes are implemented in *C++ class* and in `#include "Intermediate.h"`.The following is my IR and it is in three-address code format (**Note:** *Tempo* here means a temporary variable that randomly choosen.):

<table>
	<tr>
		<td>
			<B>Name</B>
		</td>
		<td>
			<B>Operand 1</B>
		</td>
		<td>
			<B>Operand 2</B> 
		</td>
		<td>
			<B>Destination</B>
		</td>
		<td>
			<B>Description</B>
		</td>
	</tr>
	<tr>
		<td>
			InterLabel
		</td>
		<td>
			
		</td>
		<td>
			
		</td>
		<td>
			string name
		</td>
		<td>
			a label
		</td>
	</tr>
	<tr>
		<td>
			InterJumpLabel
		</td>
		<td>
			
		</td>
		<td>
			
		</td>
		<td>
			string name
		</td>
		<td>
			jump label
		</td>
	</tr>
	<tr>
		<td>
			InterReturn
		</td>
		<td>
			Tempo ret
		</td>
		<td>
			
		</td>
		<td>
			
		</td>
		<td>
			return value in function
		</td>
	</tr>
	<tr>
		<td>
			IfGoto
		</td>
		<td>
			Tempo cond
		</td>
		<td>
			
		</td>
		<td>
			string target
		</td>
		<td>
			jump if true
		</td>
	</tr>
	<tr>
		<td>
			IfFalseGoto
		</td>
		<td>
			Tempo cond
		</td>
		<td>
			
		</td>
		<td>
			string target
		</td>
		<td>
			jump if false
		</td>
	</tr>
	<tr>
		<td>
			Move
		</td>
		<td>
			Tempo from
		</td>
		<td>
			
		</td>
		<td>
			Tempo to
		</td>
		<td>
			mov two operands
		</td>
	</tr>
	<tr>
		<td>
			InterIntGlobal
		</td>
		<td>
			Not three address code format!
		</td>
		<td>
			
		</td>
		<td>
			
		</td>
		<td>
			init information for global int
		</td>
	</tr>
	<tr>
		<td>
			InterArrayGlobal
		</td>
		<td>
			Not three address code format!
		</td>
		<td>
			
		</td>
		<td>
			
		</td>
		<td>
			init information for global array
		</td>
	</tr>
	<tr>
		<td>
			InterStructGlobal
		</td>
		<td>
			Not three address code format!
		</td>
		<td>
			
		</td>
		<td>
			
		</td>
		<td>
			init information for global struct
		</td>
	</tr>
	<tr>
		<td>
			InterIntLocal
		</td>
		<td>
			Not three address code format!
		</td>
		<td>
			
		</td>
		<td>
			
		</td>
		<td>
			init information for local int
		</td>
	</tr>
	<tr>
		<td>
			InterArrayLocal
		</td>
		<td>
			Not three address code format!
		</td>
		<td>
			
		</td>
		<td>
			
		</td>
		<td>
			init information for local array
		</td>
	</tr>
	<tr>
		<td>
			InterStructLocal
		</td>
		<td>
			Not three address code format!
		</td>
		<td>
			
		</td>
		<td>
			
		</td>
		<td>
			init information for local struct
		</td>
	</tr>
	<tr>
		<td>
			InterBinOp(string OP)
		</td>
		<td>
			Tempo left
		</td>
		<td>
			Tempo right
		</td>
		<td>
			Tempo dest
		</td>
		<td>
			binary operation
		</td>
	</tr>
	<tr>
		<td>
			InterUnaryOp(string OP)
		</td>
		<td>
			
		</td>
		<td>
			Tempo right
		</td>
		<td>
			Tempo dest
		</td>
		<td>
			unary operation
		</td>
	</tr>
	<tr>
		<td>
			MoveImmediate
		</td>
		<td>
			int value
		</td>
		<td>
			
		</td>
		<td>
			Tempo dest
		</td>
		<td>
			like li in MIPS
		</td>
	</tr>
	<tr>
		<td>
			MoveVariable
		</td>
		<td>
			string name
		</td>
		<td>
			
		</td>
		<td>
			Tempo dest
		</td>
		<td>
			move variable address to dest
		</td>
	</tr>
	<tr>
		<td>
			MoveArray
		</td>
		<td>
			string name 
		</td>
		<td>
			Tempo bias
		</td>
		<td>
			Tempo dest
		</td>
		<td>
			move array address to dest
		</td>
	</tr>
	<tr>
		<td>
			MoveStruct
		</td>
		<td>
			string name 
		</td>
		<td>
			string member
		</td>
		<td>
			Tempo dest
		</td>
		<td>
			move struct address to dest
		</td>
	</tr>
	<tr>
		<td>
			MoveToVariable
		</td>
		<td>
			Tempo from
		</td>
		<td>
			
		</td>
		<td>
			string name
		</td>
		<td>
			move content to variable address
		</td>
	</tr>
	<tr>
		<td>
			MoveToArray
		</td>
		<td>
			Tempo from
		</td>
		<td>
			Tempo bias
		</td>
		<td>
			string name
		</td>
		<td>
			move content to array address
		</td>
	</tr>
	<tr>
		<td>
			MoveToStruct
		</td>
		<td>
			Tempo from
		</td>
		<td>
			
		</td>
		<td>
			string name/member
		</td>
		<td>
			move content to struct address
		</td>
	</tr>
	<tr>
		<td>
			CallFucntion
		</td>
		<td>
			string name
		</td>
		<td>
			
		</td>
		<td>
			
		</td>
		<td>
			call function, other infomations are stored and not be shown
		</td>
	</tr>
	<tr>
		<td>
			CallRead
		</td>
		<td>
			
		</td>
		<td>
			
		</td>
		<td>
			
		</td>
		<td>
			call read function
		</td>
	</tr>
	<tr>
		<td>
			CallWrite
		</td>
		<td>
			
		</td>
		<td>
			
		</td>
		<td>
			
		</td>
		<td>
			call write function
		</td>
	</tr>
</table>

***
##Optimization(Optional)
###Compute Integer when Compiling
In this project, my compiler will automatically compute the integers arithmetics in the program when compiling. For example:

	a = b + (6 + 3) * 2;
It will translate it into **MIPS** like:

	li $t0, 18
	la $t1, b
	lw $t1, 0($t1)
	add $t1, $t1, $t0
	la $t0, a
	sw $t1, 0($t1)
So **MIPS** simulator can do much fewer instructions since the integer arithmetics have already been optimized.

This optimization is very important since you can initial an array like the following:

	int arr[4] = {1+3, 3*2, -4+8, 5%3};
It will have the same effect as:

	int arr[4] = {4, 6, 4, 2};
***
##Machine-code Generation
###Instruction Selection
Most of the students did the instruction selection part almost the same way, so did I. The work is together done in `GenIntermediate.cpp` since it is rather simple. And I will show you something special in my design.

To get a value from or store value to the variable (or array member, struct member) address, a special function called getXXXXXAddress is called:

	Register getStructMemberAddress(Node* cur, SymbolTable* table, int linenum){
		if(tmp->definition_type==type_local_struct){
			Register address = getFreeRegister();
			int offset = tmp->stackOffsite;
			offset += table->struct_map[tmp->struct_type]->Struct_Offsites[cur->ms_MemberName];
			instructions->push_back(new BinOpImmediate("addi", address, R_SP, offset));
			return address;
		}
	}
The above one is an example for struct type variable. You can get the address of the variable and save it in a register to get the variable value.

	lw $t0, 0($t0)
*$t0* here is the generated address and soon be replaced by the obtained value.
###Stack Allocation
The stack allocation of my design is a bit different from the given reference book, and it looks like the following:

<table>
	<tr>
		<td>
			<B>Materials Stored</B>
		</td>
		<td>
			<B>Address</B>
		</td>
	</tr>
	<tr>
		<td>
			.........The stack of former function call        
		</td>
		<td>
			previous $sp points to
		</td>
	</tr>
	<tr>
		<td>
			Parameter 3
		</td>
		<td>
			
		</td>
	</tr>
	<tr>
		<td>
			Parameter 2
		</td>
		<td>
			
		</td>
	</tr>
	<tr>
		<td>
			Parameter 1
		</td>
		<td>
			$a0 points to
		</td>
	</tr>
	<tr>
		<td>
			Local Variable 3
		</td>
		<td>
			
		</td>
	</tr>
	<tr>
		<td>
			Local Variable 2
		</td>
		<td>
			
		</td>
	</tr>
	<tr>
		<td>
			Local Variable 1
		</td>
		<td>
			
		</td>
	</tr>
	<tr>
		<td>
			$a0
		</td>
		<td>
			
		</td>
	</tr>
	<tr>
		<td>
			$ra
		</td>
		<td>
			$sp points to 
		</td>
	</tr>
</table>

You can see clearly in my implementation that I have saved **all** of the variables in the stack and use *$a0* to be the pointer to show the start of the function parameters. 
###Register Allocation
My implementation is very register saving, and it's algorithm is rather simple. It uses the three following functions:

	void reclaimRegisters(){
		remainingRegisters = { R_T0, R_T1, R_T2, R_T3, R_T4, R_T5, R_T6, R_T7, R_T8, R_T9};
		registersInUse = {};
	}
	void returnRegister(Register r){
		remainingRegisters.insert(r);
		registersInUse.erase(r);
	}
	Register getFreeRegister(){
		Register ret = *(remainingRegisters.begin());
		remainingRegisters.erase(ret);
		registersInUse.insert(ret);
		return ret;
	}
The usage of the above three are to initial registers, return a register and ask for a new register. Most of the allocation work are done during the procedure of generating code. For example, in the following expression:

	EXP = EXP1 + EXP2;
Assumed that *EXP1* and *EXP2* have already been computed and assigned the registers *$t0* and *$t1*. It will then assign another register *$t2* (if it is not being used now) and after doing the computation `add $t2, $t0, $t1`, it will do the following:

	returnRegister(EXP1);
	returnRegister(EXP2);
Here we use *EXP1* and *EXP2* to represent the registers they are using.

The reason why I asked for another new register to compute *EXP* instead of either register of *EXP1* or *EXP2* is because I intended to do perform optimization on *Common subexpression elimination* but due to time limit, failed to realize it.

In the above realization, my compiler will work well except that you use a test of an expression with a very large **Ershov Number**.
###Input and Output
The input and output are rather simple to implement and I have mentioned their lexical and syntax analyzation in former parts. The codes are as followings:

For read:

	instructions->push_back(new BinOp("add", R_A1, R_V0, R_ZERO));
	instructions->push_back(new LoadImmediate(R_V0, 5));
	instructions->push_back(new Syscall());
	instructions->push_back(new StoreWord(R_V0, address, 0));
	instructions->push_back(new BinOp("add", R_V0, R_A1, R_ZERO));
Which save *$v0* to *$a1* first and then do the syscall of *$v0 = 5*, and then recover *$v0* from *$a1*.

For write:

	instructions->push_back(new BinOp("add", R_A1, R_V0, R_ZERO));
	instructions->push_back(new BinOp("add", R_A2, R_A0, R_ZERO));
	instructions->push_back(new LoadImmediate(R_V0, 1));
	instructions->push_back(new BinOp("add", R_A0, tmp, R_ZERO));
	instructions->push_back(new Syscall());
	instructions->push_back(new BinOp("add", R_V0, R_A1, R_ZERO));
	instructions->push_back(new BinOp("add", R_A0, R_A2, R_ZERO));
Which save *$v0* and *$a0* to *$a1* and *$a2* first and then do the syscall of *$v0 = 1 $a0 = WriteInteger*, and then recover *$v0* and *$a0*.
***
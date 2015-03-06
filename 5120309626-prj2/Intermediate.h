////////////////////////////////////////////////////////////////////////
/*
  File Name: Intermediate.h
  This file is the header file of Intermediate.cpp. The former part is 
  deprecated since it is too complicated to initialize and print a 
  three-address code using this method, and will cost a lot of extra 
  instructions to generate the code in "GenIntermediate.cpp". The 
  reason why I still leave it here without noting it is because it 
  may be used somewhere in the program that once I delete it, errors
  will occur.
*/
////////////////////////////////////////////////////////////////////////

#ifndef INTERMEDIATE_H
#define INTERMEDIATE_H

#include <string>
#include <iostream>
#include <vector>
using namespace std;

//******************** Deprecated. Intermediate code is implemented in C++ class and you can just jump the first part
//******************** I left it here just to avoid some mistakes in the program.
enum IntermediateType{
	inter_label,
	inter_global_array,
	inter_global_int,
	inter_global_struct,
	inter_local_int,
	inter_local_array,
	inter_local_struct
};
struct Intermediate{
	
	IntermediateType type;

	string Name;


	string Operator;
	string OperandLeft;
	string OperandRight;
	string Destination;
	int IntNumber;


	// Define Global Array
	int Global_Array_Size;
	vector<int> Global_Array_Initial_Values;

	// Define Global Int
	int Global_Int_Initial_Value;

	// Define Global Struct
	int Global_Struct_Size;

	// Define Local
	int Local_Offsite;

	// Define local Array
	int Local_Array_Size;
	vector<int> Local_Array_Initial_Values;

	// Define Local Struct
	int Local_Struct_Size;

	Intermediate(){}
	~Intermediate(){}
	void initial_define_global_array(string name, int initial_size, vector<int>& initial_values){
		type = inter_global_array;
		Name = name;
		Global_Array_Size = 4 * initial_size;
		for(int i=0; i<initial_values.size(); ++i){
			Global_Array_Initial_Values.push_back(initial_values[i]);
		}
		cout << "Global_Array: " << Name << " Size: " << Global_Array_Size << " Initial List: ";
		for(int i=0; i<Global_Array_Initial_Values.size(); ++i) cout << Global_Array_Initial_Values[i] << " ";
		cout << endl;
	}

	void initial_define_local_array(string name, int initial_size, int offsite, vector<int>& initial_values){
		type = inter_local_array;
		Name = name;
		Local_Array_Size = 4 * initial_size;
		Local_Offsite = offsite;
		for(int i=0; i<initial_values.size(); ++i){
			Local_Array_Initial_Values.push_back(initial_values[i]);
		}
		cout << "Local_Array: " << Name << " Size: " << Local_Array_Size << " Offsite: " << Local_Offsite << " Initial List: ";
		for(int i=0; i<Local_Array_Initial_Values.size(); ++i) cout << Local_Array_Initial_Values[i] << " ";
		cout << endl;
	}

	void initial_define_global_struct(string name, int initial_size){
		type = inter_global_struct;
		Name = name;
		Global_Struct_Size = 4 * initial_size;
		cout << "Global_Struct: " << Name << " Size: " << Global_Struct_Size << endl;
	}

	void initial_define_local_struct(string name, int offsite, int initial_size){
		type = inter_local_struct;
		Name = name;
		Local_Offsite = offsite;
		Local_Struct_Size = 4 * initial_size;
		cout << "Global_Struct: " << Name << " Size: " << Global_Struct_Size << " Offsite: " << Local_Offsite << endl;
	}

	void initial_define_global_int(string name, int value){
		type = inter_global_int;
		Name = name;
		Global_Int_Initial_Value = value;
		cout << "Global_Int: " << Name << " Initial Value: " << Global_Int_Initial_Value << endl;
	}

	void initial_define_local_int(string name, int offsite){
		type = inter_local_int;
		Name = name;
		Local_Offsite = offsite;
		cout << "Local_Int: " << Name << " Offsite: " << Local_Offsite << endl;
	}
};
//*****************************************************Deprecated

//*************** The following part are in real usage
typedef unsigned short Tempo;

extern const Tempo T_0;
extern const Tempo T_1;
extern const Tempo T_2;
extern const Tempo T_3;
extern const Tempo T_4;
extern const Tempo T_5;
extern const Tempo T_6;
extern const Tempo T_7;
extern const Tempo T_8;
extern const Tempo T_9;
extern const Tempo T_10;
extern const Tempo T_11;
extern const Tempo T_12;
extern const Tempo T_13;
extern const Tempo T_14;
extern const Tempo T_15;
extern const Tempo T_16;
extern const Tempo T_17;
extern const Tempo T_18;
extern const Tempo T_19;
extern const Tempo T_20;
extern const Tempo T_21;
extern const Tempo T_22;
extern const Tempo T_23;
extern const Tempo T_24;
extern const Tempo T_25;
extern const Tempo T_26;
extern const Tempo T_27;
extern const Tempo T_28;
extern const Tempo T_29;
extern const Tempo T_30;


std::string tempoStr(Tempo t);

class Inter;

std::ostream &operator<<(std::ostream& output, const Inter&);

// Father class of all intermediates
class Inter {
private:
public:
	Inter();
	Inter(const Inter&) = delete;
	virtual ~Inter();
	virtual const Inter& operator=(const Inter&) = delete;
	virtual std::ostream& output(std::ostream& o) const = 0;
};

class InterLabel : public Inter {
private:
	std::string name;
public:
	InterLabel(const std::string& name);
	InterLabel(const InterLabel&) = delete;
	virtual ~InterLabel();
	virtual const InterLabel& operator=(const InterLabel&) = delete;
	virtual std::ostream& output(std::ostream& o) const;
};

class InterJumpLabel : public Inter {
private:
	std::string name;
public:
	InterJumpLabel(const std::string& name);
	InterJumpLabel(const InterJumpLabel&) = delete;
	virtual ~InterJumpLabel();
	virtual const InterJumpLabel& operator=(const InterJumpLabel&) = delete;
	virtual std::ostream& output(std::ostream& o) const;
};

class InterReturn : public Inter {
private:
	Tempo ret;
public:
	InterReturn(Tempo ret);
	InterReturn(const InterReturn&) = delete;
	virtual ~InterReturn();
	virtual const InterReturn& operator=(const InterReturn&) = delete;
	virtual std::ostream& output(std::ostream& o) const;
};

class IfGoto : public Inter {
private:
	Tempo cond;
	std::string target;
public:
	IfGoto(Tempo cond, const std::string& target);
	IfGoto(const IfGoto&) = delete;
	virtual ~IfGoto();
	virtual const IfGoto& operator=(const IfGoto&) = delete;
	virtual std::ostream& output(std::ostream& o) const;
};

class IfFalseGoto : public Inter {
private:
	Tempo cond;
	std::string target;
public:
	IfFalseGoto(Tempo cond, const std::string& target);
	IfFalseGoto(const IfFalseGoto&) = delete;
	virtual ~IfFalseGoto();
	virtual const IfFalseGoto& operator=(const IfFalseGoto&) = delete;
	virtual std::ostream& output(std::ostream& o) const;
};

class Move : public Inter {
private:
	Tempo from;
	Tempo to;
public:
	Move(Tempo from, Tempo to);
	Move(const Move&) = delete;
	virtual ~Move();
	virtual const Move& operator=(const Move&) = delete;
	virtual std::ostream& output(std::ostream& o) const;
};

class InterIntGlobal : public Inter{
private:
	std::string name;
	int value;
public:
	InterIntGlobal(const std::string& name, int value);
	InterIntGlobal(const InterIntGlobal&) = delete;
	virtual ~InterIntGlobal();
	virtual const InterIntGlobal& operator=(const InterIntGlobal&) = delete;
	virtual std::ostream& output(std::ostream& o) const;
};

class InterArrayGlobal : public Inter{
private:
	std::string name;
	int Global_Array_Size;
	vector<int> Initial_Values;
public:
	InterArrayGlobal(const std::string& name, int global_array_size, vector<int> initial_values);
	InterArrayGlobal(const InterArrayGlobal&) = delete;
	virtual ~InterArrayGlobal();
	virtual const InterArrayGlobal& operator=(const InterArrayGlobal&) = delete;
	virtual std::ostream& output(std::ostream& o) const;
};

class InterStructGlobal : public Inter{
private:
	std::string name;
	int Global_Struct_Size;
public:
	InterStructGlobal(const std::string& name, int global_struct_size);
	InterStructGlobal(const InterStructGlobal&) = delete;
	virtual ~InterStructGlobal();
	virtual const InterStructGlobal& operator=(const InterStructGlobal&) = delete;
	virtual std::ostream& output(std::ostream& o) const;
};

class InterIntLocal : public Inter{
private:
	std::string name;
	int Stack_Offset;
public:
	InterIntLocal(const std::string& name, int stackoffset);
	InterIntLocal(const InterIntLocal&) = delete;
	virtual ~InterIntLocal();
	virtual const InterIntLocal& operator=(const InterIntLocal&) = delete;
	virtual std::ostream& output(std::ostream& o) const;
};

class InterArrayLocal : public Inter{
private:
	std::string name;
	int Initial_Size;
	int Stack_Offset;
	vector<int> Initial_Values;
public:
	InterArrayLocal(const std::string& name, int initial_size, int offsite, vector<int> initial_values);
	InterArrayLocal(const InterArrayLocal&) = delete;
	virtual ~InterArrayLocal();
	virtual const InterArrayLocal& operator=(const InterArrayLocal&) = delete;
	virtual std::ostream& output(std::ostream& o) const;
};

class InterStructLocal : public Inter{
private:
	std::string name;
	int Initial_Size;
	int Stack_Offset;
public:
	InterStructLocal(const std::string& name, int initial_size, int offset);
	InterStructLocal(const InterStructLocal&) = delete;
	virtual ~InterStructLocal();
	virtual const InterStructLocal& operator=(const InterStructLocal&) = delete;
	virtual std::ostream& output(std::ostream& o) const;
};

class InterBinOp : public Inter{
private:
	Tempo left;
	Tempo right;
	Tempo dest;
	std::string op;
public:
	InterBinOp(const std::string& op, Tempo left, Tempo right, Tempo dest);
	InterBinOp(const InterBinOp&) = delete;
	virtual ~InterBinOp();
	virtual const InterBinOp& operator=(const InterBinOp&) = delete;
	virtual std::ostream& output(std::ostream& o) const;
};

class InterUnaryOp : public Inter{
private:
	Tempo right;
	Tempo dest;
	std::string op;
public:
	InterUnaryOp(const std::string& op, Tempo right, Tempo dest);
	InterUnaryOp(const InterUnaryOp&) = delete;
	virtual ~InterUnaryOp();
	virtual const InterUnaryOp& operator=(const InterUnaryOp&) = delete;
	virtual std::ostream& output(std::ostream& o) const;
};

class MoveImmediate : public Inter{
private:
	Tempo dest;
	int value;
public:
	MoveImmediate(Tempo dest, int value);
	MoveImmediate(const MoveImmediate&) = delete;
	virtual ~MoveImmediate();
	virtual const MoveImmediate& operator=(const MoveImmediate&) = delete;
	virtual std::ostream& output(std::ostream& o) const;
};

class MoveVariable : public Inter{
private:
	Tempo dest;
	std::string name; 
public:
	MoveVariable(Tempo dest, string name);
	MoveVariable(const MoveVariable&) = delete;
	virtual ~MoveVariable();
	virtual const MoveVariable& operator=(const MoveVariable&) = delete;
	virtual std::ostream& output(std::ostream& o) const;
};

class MoveArray : public Inter{
private:
	Tempo dest;
	std::string name;
	Tempo bias;
public:
	MoveArray(Tempo dest, string name, Tempo bias);
	MoveArray(const MoveArray&) = delete;
	virtual ~MoveArray();
	virtual const MoveArray& operator=(const MoveArray&) = delete;
	virtual std::ostream& output(std::ostream& o) const;
};

class MoveStruct : public Inter {
private:
	Tempo dest;
	std::string name;
	std::string member;
public:
	MoveStruct(Tempo dest, string name, string member);
	MoveStruct(const MoveStruct&) = delete;
	virtual ~MoveStruct();
	virtual const MoveStruct& operator=(const MoveStruct&) = delete;
	virtual std::ostream& output(std::ostream& o) const;
};

class MoveToVariable : public Inter{
private:
	Tempo from;
	std::string name; 
public:
	MoveToVariable(Tempo from, string name);
	MoveToVariable(const MoveToVariable&) = delete;
	virtual ~MoveToVariable();
	virtual const MoveToVariable& operator=(const MoveToVariable&) = delete;
	virtual std::ostream& output(std::ostream& o) const;
};

class MoveToArray : public Inter{
private:
	Tempo from;
	std::string name;
	Tempo bias;
public:
	MoveToArray(Tempo from, string name, Tempo bias);
	MoveToArray(const MoveToArray&) = delete;
	virtual ~MoveToArray();
	virtual const MoveToArray& operator=(const MoveToArray&) = delete;
	virtual std::ostream& output(std::ostream& o) const;
};

class MoveToStruct : public Inter {
private:
	Tempo from;
	std::string name;
	std::string member;
public:
	MoveToStruct(Tempo from, string name, string member);
	MoveToStruct(const MoveToStruct&) = delete;
	virtual ~MoveToStruct();
	virtual const MoveToStruct& operator=(const MoveToStruct&) = delete;
	virtual std::ostream& output(std::ostream& o) const;
};

class CallFunction : public Inter {
private:
	std::string name;
public:
	CallFunction(string name);
	CallFunction(const CallFunction&) = delete;
	virtual ~CallFunction();
	virtual const CallFunction& operator=(const CallFunction&) = delete;
	virtual std::ostream& output(std::ostream& o) const;
};

class CallRead : public Inter{
private:
public:
	CallRead();
	CallRead(const CallRead&) = delete;
	virtual ~CallRead();
	virtual const CallRead& operator=(const CallRead&) = delete;
	virtual std::ostream& output(std::ostream& o) const;
};

class CallWrite : public Inter{
private:
public:
	CallWrite();
	CallWrite(const CallWrite&) = delete;
	virtual ~CallWrite();
	virtual const CallWrite& operator=(const CallWrite&) = delete;
	virtual std::ostream& output(std::ostream& o) const;
};
// class InterArray : public Inter{
// private:
// 	std::string name;
// 	std::string offset;
// public:
// 	InterArray(std::string name, std::string offset);
// 	InterArray(const InterArray&) = delete;
// 	virtual ~InterArray();
// 	virtual const InterArray& operator=(const InterArray&) = delete;
// 	virtual std::ostream& output(std::ostream& o) const;
// };

// class InterStructMember : public Inter{
// private:
// 	std::string name;
// 	std::string member;
// public:
// 	InterStructMember(std::string name, std::string member);
// 	InterStructMember(const InterStructMember&) = delete;
// 	virtual ~InterStructMember();
// 	virtual const InterStructMember& operator=(const InterStructMember&) = delete;
// 	virtual std::ostream& output(std::ostream& o) const;
// };

#endif
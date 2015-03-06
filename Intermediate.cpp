////////////////////////////////////////////////////////////////////////
/*
  File Name: Intermediate.cpp
  This file is more like a utility file rather than doing real works. This
  file is all implemented via the method of "class", mainly to make it 
  easier to print the intermediate code to anywhere you want, like stdio 
  and into files. Most of the instructions are in three address forms. 
  And there operator "<<" have been reimplemented to print their specific
  three-address code information.
*/
////////////////////////////////////////////////////////////////////////

#include "Intermediate.h"
#include <string>
#include <vector>
#include <sstream>
#include <map>

using namespace std;

template<class T>
std::string toString(T t){
	std::stringstream s;
	s << t;
	return s.str();
}

const Tempo T_0 = 0;
const Tempo T_1 = 1;
const Tempo T_2 = 2;
const Tempo T_3 = 3;
const Tempo T_4 = 4;
const Tempo T_5 = 5;
const Tempo T_6 = 6;
const Tempo T_7 = 7;
const Tempo T_8 = 8;
const Tempo T_9 = 9;
const Tempo T_10 = 10;
const Tempo T_11 = 11;
const Tempo T_12 = 12;
const Tempo T_13 = 13;
const Tempo T_14 = 14;
const Tempo T_15 = 15;
const Tempo T_16 = 16;
const Tempo T_17 = 17;
const Tempo T_18 = 18;
const Tempo T_19 = 19;
const Tempo T_20 = 20;
const Tempo T_21 = 21;
const Tempo T_22 = 22;
const Tempo T_23 = 23;
const Tempo T_24 = 24;
const Tempo T_25 = 25;
const Tempo T_26 = 26;
const Tempo T_27 = 27;
const Tempo T_28 = 28;
const Tempo T_29 = 29;
const Tempo T_30 = 30;

string tempoStr(Tempo t){
	map<Tempo, string> substitutions;
	substitutions[T_0] = "#0";
	substitutions[T_1] = "#1";
	substitutions[T_2] = "#2";
	substitutions[T_3] = "#3";
	substitutions[T_4] = "#4";
	substitutions[T_5] = "#5";
	substitutions[T_6] = "#6";
	substitutions[T_7] = "#7";
	substitutions[T_8] = "#8";
	substitutions[T_9] = "#9";
	substitutions[T_10] = "#10";
	substitutions[T_11] = "#11";
	substitutions[T_12] = "#12";
	substitutions[T_13] = "#13";
	substitutions[T_14] = "#14";
	substitutions[T_15] = "#15";
	substitutions[T_16] = "#16";
	substitutions[T_17] = "#17";
	substitutions[T_18] = "#18";
	substitutions[T_19] = "#19";
	substitutions[T_20] = "#20";
	substitutions[T_21] = "#21";
	substitutions[T_22] = "#22";
	substitutions[T_23] = "#23";
	substitutions[T_24] = "#24";
	substitutions[T_25] = "#25";
	substitutions[T_26] = "#26";
	substitutions[T_27] = "#27";
	substitutions[T_28] = "#28";
	substitutions[T_29] = "#29";
	substitutions[T_30] = "#30";
	
	return substitutions[t];
}

ostream& operator<<(ostream& output, const Inter& inter){
	return inter.output(output);
}

Inter::Inter() {

}

Inter::~Inter() {

}

InterLabel::InterLabel(const string& name) : name(name) {

}

InterLabel::~InterLabel() {

}

ostream& InterLabel::output(ostream& output) const {
	return output << endl << name << ":" << endl;
}

InterJumpLabel::InterJumpLabel(const string& name) : name(name) {

}

InterJumpLabel::~InterJumpLabel() {

}

ostream& InterJumpLabel::output(ostream& output) const {
	return output << "jmp\t" << name << endl;
}

InterReturn::InterReturn(Tempo ret) : ret(ret) {

}

InterReturn::~InterReturn() {

}

ostream& InterReturn::output(ostream& output) const {
	return output << "return\t" << tempoStr(ret) << endl;
}


IfGoto::IfGoto(Tempo cond, const string& target) : cond(cond), target(target) {

}

IfGoto::~IfGoto() {

}

ostream& IfGoto::output(ostream& output) const {
	return output << "if\t" << tempoStr(cond) << "\tgoto\t" << target << endl;
}

IfFalseGoto::IfFalseGoto(Tempo cond, const string& target) : cond(cond), target(target) {

}

IfFalseGoto::~IfFalseGoto() {

}

ostream& IfFalseGoto::output(ostream& output) const {
	return output << "ifFalse\t" << tempoStr(cond) << "\tgoto\t" << target << endl;
}

Move::Move(Tempo from, Tempo to) : from(from), to(to) {

}

Move::~Move() {

}

ostream& Move::output(ostream& output) const {
	return output << "mov\t" << tempoStr(from) << "\t\t" << tempoStr(to) << endl;
}

InterIntGlobal::InterIntGlobal(const string& name, int value) : name(name), value(value) {

}

InterIntGlobal::~InterIntGlobal() {

}

ostream& InterIntGlobal::output(ostream& output) const {
	return output << "global_int\t" << name << "\t" << "initial\t" << value << endl;
}

InterArrayGlobal::InterArrayGlobal(const string& name, int global_array_size, vector<int> initial_values) : name(name), Global_Array_Size(global_array_size), Initial_Values(initial_values) {

}

InterArrayGlobal::~InterArrayGlobal() {

}

ostream& InterArrayGlobal::output(ostream& output) const {
	string tmp = "global_array\t";
	tmp += name;
	tmp += "\tsize\t";
	tmp += toString(Global_Array_Size);
	tmp += "\tinitial\t";
	for(auto it=Initial_Values.begin(); it!=Initial_Values.end(); ++it){
		tmp += toString(*it);
		tmp += " ";
	}
	return output << tmp << endl;
}

InterStructGlobal::InterStructGlobal(const string& name, int global_struct_size) : name(name), Global_Struct_Size(global_struct_size) {

}

InterStructGlobal::~InterStructGlobal() {

}

ostream& InterStructGlobal::output(ostream& output) const {
	return output << "global_struct\t" << name << "\tsize\t" << toString(Global_Struct_Size) << endl; 
}

InterIntLocal::InterIntLocal(const string& name, int stackoffset) : name(name), Stack_Offset(stackoffset) {

}

InterIntLocal::~InterIntLocal() {

}

ostream& InterIntLocal::output(ostream& output) const {
	return output << "local_int\t" << name << "\tstack_offset\t" << toString(Stack_Offset) << endl;
}


InterArrayLocal::InterArrayLocal(const string& name, int initial_size, int offset, vector<int> initial_values) : name(name), Initial_Size(initial_size), Stack_Offset(offset), Initial_Values(initial_values) {

}

InterArrayLocal::~InterArrayLocal() {

}

ostream& InterArrayLocal::output(ostream& output) const {
	string tmp = "local_array\t";
	tmp += name;
	tmp += "\tstack_offset\t";
	tmp += toString(Stack_Offset);
	tmp += "\tsize\t";
	tmp += toString(Initial_Size);
	tmp += "\tinitial\t";
	for(auto it=Initial_Values.begin(); it!=Initial_Values.end(); ++it){
		tmp += toString(*it);
		tmp += " ";
	}
	return output << tmp << endl;
}

InterStructLocal::InterStructLocal(const string& name, int initial_size, int offset) : name(name), Initial_Size(initial_size), Stack_Offset(offset) {

}

InterStructLocal::~InterStructLocal() {

}

ostream& InterStructLocal::output(ostream& output) const {
	return output << "local_struct\t" << name << "\tstack_offset\t" << toString(Stack_Offset) << "\tsize\t" << toString(Initial_Size) << endl;
}

InterBinOp::InterBinOp(const string& op, Tempo left, Tempo right, Tempo dest) : op(op), left(left), right(right), dest(dest) {

}

InterBinOp::~InterBinOp() {

}

ostream& InterBinOp::output(ostream& output) const {
	return output << op << "\t" << tempoStr(left) << "\t" << tempoStr(right) << "\t" << tempoStr(dest) << endl;
}

InterUnaryOp::InterUnaryOp(const string& op, Tempo right, Tempo dest) : op(op), right(right), dest(dest) {

}

InterUnaryOp::~InterUnaryOp() {

}

ostream& InterUnaryOp::output(ostream& output) const {
	return output << op << "\t" << tempoStr(right) << "\t\t" << tempoStr(dest) << endl;
}

MoveImmediate::MoveImmediate(Tempo dest, int value) : dest(dest), value(value) {

}

MoveImmediate::~MoveImmediate() {

}

ostream& MoveImmediate::output(ostream& output) const {
	return output << "mov\t" << value << "\t\t" << tempoStr(dest) << endl;
}

MoveVariable::MoveVariable(Tempo dest, string name) : dest(dest), name(name) {

}

MoveVariable::~MoveVariable() {

}

ostream& MoveVariable::output(ostream& output) const {
	return output << "mov\t" << name << "\t\t" << tempoStr(dest) << endl;;
}

MoveArray::MoveArray(Tempo dest, string name, Tempo bias) : dest(dest), name(name), bias(bias) {

}

MoveArray::~MoveArray() {

}

ostream& MoveArray::output(ostream& output) const {
	return output << "mov_arr\t" << name << "\t" << tempoStr(bias) << "\t" << tempoStr(dest) <<endl;
}

MoveStruct::MoveStruct(Tempo dest, string name, string member) : dest(dest), name(name), member(member) {

}

MoveStruct::~MoveStruct() {

}

ostream& MoveStruct::output(ostream& output) const {
	return output << "mov_struct\t" << name << "\t" << member << "\t" << tempoStr(dest) <<endl;
}

MoveToVariable::MoveToVariable(Tempo from, string name) : from(from), name(name) {

}

MoveToVariable::~MoveToVariable() {

}

ostream& MoveToVariable::output(ostream& output) const {
	return output << "mov\t" << tempoStr(from) << "\t\t" << name << endl;;
}

MoveToArray::MoveToArray(Tempo from, string name, Tempo bias) : from(from), name(name), bias(bias) {

}

MoveToArray::~MoveToArray() {

}

ostream& MoveToArray::output(ostream& output) const {
	return output << "mov_arr\t" << tempoStr(from) << "\t" << tempoStr(bias) << "\t" << name << "\t" << endl;
}

MoveToStruct::MoveToStruct(Tempo from, string name, string member) : from(from), name(name), member(member) {

}

MoveToStruct::~MoveToStruct() {

}

ostream& MoveToStruct::output(ostream& output) const {
	return output << "mov_struct\t" << tempoStr(from) << "\t" << name << "\t" << member << "\t" <<endl;
}

CallFunction::CallFunction(string name) : name(name) {

}

CallFunction::~CallFunction() {

}

ostream& CallFunction::output(ostream& output) const {
	return output << "call\t" << name << "\t" <<endl;
}

CallRead::CallRead() {

}

CallRead::~CallRead() {

}

ostream& CallRead::output(ostream& output) const {
	return output << "read" << endl;
}

CallWrite::CallWrite() {

}

CallWrite::~CallWrite() {

}

ostream& CallWrite::output(ostream& output) const {
	return output << "write" << endl;
}
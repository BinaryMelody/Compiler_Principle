////////////////////////////////////////////////////////////////////////
/*
  File Name: MIPS32.cpp
  This is the file where all the MIPS instructions are implemented.
  It is also implemented via class, which looks like the "Intermediate.cpp" 
  very much. You can simply push the instructions in a vector and print 
  them to anywhere you wang one by one. It is implemented in the way of 
  "class", and the ostream has been reimplemented.
*/
////////////////////////////////////////////////////////////////////////
#include "MIPS32.h"
#include <string>
#include <stdexcept>
#include <vector>
#include <sstream>
#include <map>

using namespace std;

template<class T>
std::string toString(T t) {
	std::stringstream s;
	s << t;
	return s.str();
}

const Register R_ZERO = 0;

const Register R_AT = 1;

const Register R_V0 = 2;
const Register R_V1 = 3;

const Register R_A0 = 4;
const Register R_A1 = 5;
const Register R_A2 = 6;
const Register R_A3 = 7;

const Register R_T0 = 8;
const Register R_T1 = 9;
const Register R_T2 = 10;
const Register R_T3 = 11;
const Register R_T4 = 12;
const Register R_T5 = 13;
const Register R_T6 = 14;
const Register R_T7 = 15;

const Register R_S0 = 16;
const Register R_S1 = 17;
const Register R_S2 = 18;
const Register R_S3 = 19;
const Register R_S4 = 20;
const Register R_S5 = 21;
const Register R_S6 = 22;
const Register R_S7 = 23;

const Register R_T8 = 24;
const Register R_T9 = 25;

const Register R_K0 = 26;
const Register R_K1 = 27;

const Register R_GP = 28;

const Register R_SP = 29;

const Register R_S8 = 30;

const Register R_RA = 31;

string registerStr(Register r) {
	map<Register, string> substitutions;
	substitutions[R_ZERO] = "$zero";
	
	substitutions[R_AT] = "$at";
	
	substitutions[R_V0] = "$v0";
	substitutions[R_V1] = "$v1";
	
	substitutions[R_A0] = "$a0";
	substitutions[R_A1] = "$a1";
	substitutions[R_A2] = "$a2";
	substitutions[R_A3] = "$a3";
	
	substitutions[R_T0] = "$t0";
	substitutions[R_T1] = "$t1";
	substitutions[R_T2] = "$t2";
	substitutions[R_T3] = "$t3";
	substitutions[R_T4] = "$t4";
	substitutions[R_T5] = "$t5";
	substitutions[R_T6] = "$t6";
	substitutions[R_T7] = "$t7";
	
	substitutions[R_S0] = "$s0";
	substitutions[R_S1] = "$s1";
	substitutions[R_S2] = "$s2";
	substitutions[R_S3] = "$s3";
	substitutions[R_S4] = "$s4";
	substitutions[R_S5] = "$s5";
	substitutions[R_S6] = "$s6";
	substitutions[R_S7] = "$s7";
	
	substitutions[R_T8] = "$t8";
	substitutions[R_T9] = "$t9";
	
	substitutions[R_K0] = "$k0";
	substitutions[R_K1] = "$k1";
	
	substitutions[R_GP] = "$gp";
	
	substitutions[R_SP] = "$sp";
	
	substitutions[R_S8] = "$s8";
	
	substitutions[R_RA] = "$ra";
	
	if(substitutions.count(r)) {
		return substitutions[r];
	} else {
		throw runtime_error("Unknown register: " + toString(r));
	}
}

ostream& operator<<(ostream& output, const Instruction& ins) {
	return ins.output(output);
}

Instruction::Instruction() {
	
}

Instruction::~Instruction() {
	
}

ControlFlowInstruction::ControlFlowInstruction() {
	
}

ControlFlowInstruction::~ControlFlowInstruction() {
	
}

Label::Label(const string& name) : name(name) {
	
}

Label::~Label() {
	
}

ostream& Label::output(ostream& output) const {
	return output << endl << name << ":" << endl;
}

bool Label::readsRegister(Register r) const {
	return false;
}

bool Label::writesToRegister() const {
	return false;
}

Register Label::destinationRegister() const {
	throw runtime_error("Label does not write to any register");
}

const string& Label::getName() const {
	return name;
}

Jump::Jump(const string& target) : target(target) {
	
}

Jump::~Jump() {
	
}

ostream& Jump::output(ostream& output) const {
	return output << "\tj " << target << endl;
}

bool Jump::readsRegister(Register r) const {
	return false;
}

bool Jump::writesToRegister() const {
	return false;
}

Register Jump::destinationRegister() const {
	throw runtime_error("Jump does not write to any register");
}

const string& Jump::getTarget() const {
	return target;
}

JumpRegister::JumpRegister(Register target) : target(target) {
	
}

JumpRegister::~JumpRegister() {
	
}

ostream& JumpRegister::output(ostream& output) const {
	return output << "\tjr " << registerStr(target) << endl;
}

bool JumpRegister::readsRegister(Register r) const {
	return r == target;
}

bool JumpRegister::writesToRegister() const {
	return false;
}

Register JumpRegister::destinationRegister() const {
	throw runtime_error("JumpRegister does not write to any register");
}

Register JumpRegister::getTarget() const {
	return target;
}

JumpAndLink::JumpAndLink(const string& target) : target(target) {
	
}

JumpAndLink::~JumpAndLink() {
	
}

ostream& JumpAndLink::output(ostream& output) const {
	return output << "\tjal " << target << endl;
}

bool JumpAndLink::readsRegister(Register r) const {
	return false;
}

bool JumpAndLink::writesToRegister() const {
	return false;
}

Register JumpAndLink::destinationRegister() const {
	throw runtime_error("JumpAndLink does not write to any register");
}

const string& JumpAndLink::getTarget() const {
	return target;
}

BranchOnEqual::BranchOnEqual(Register left, Register right, const string& target) : left(left), right(right), target(target) {
	
}

BranchOnEqual::~BranchOnEqual() {
	
}

ostream& BranchOnEqual::output(ostream& output) const {
	return output << "\tbeq " << registerStr(left) << ", " << registerStr(right) << ", " << target << endl;
}

bool BranchOnEqual::readsRegister(Register r) const {
	return left == r || right == r;
}

bool BranchOnEqual::writesToRegister() const {
	return false;
}

Register BranchOnEqual::destinationRegister() const {
	throw runtime_error("BranchOnEqual does not write to any register");
}

Register BranchOnEqual::getLeft() const {
	return left;
}

Register BranchOnEqual::getRight() const {
	return right;
}

const string& BranchOnEqual::getTarget() const {
	return target;
}

BranchNotEqual::BranchNotEqual(Register left, Register right, const string& target) : left(left), right(right), target(target) {
	
}

BranchNotEqual::~BranchNotEqual() {
	
}

ostream& BranchNotEqual::output(ostream& output) const {
	return output << "\tbne " << registerStr(left) << ", " << registerStr(right) << ", " << target << endl;
}

bool BranchNotEqual::readsRegister(Register r) const {
	return left == r || right == r;
}

bool BranchNotEqual::writesToRegister() const {
	return false;
}

Register BranchNotEqual::destinationRegister() const {
	throw runtime_error("BranchNotEqual does not write to any register");
}

Register BranchNotEqual::getLeft() const {
	return left;
}

Register BranchNotEqual::getRight() const {
	return right;
}

const string& BranchNotEqual::getTarget() const {
	return target;
}

StoreWord::StoreWord(Register data, Register location, int offset) : data(data), location(location), offset(offset) {
	
}

StoreWord::~StoreWord() {
	
}

ostream& StoreWord::output(ostream& output) const {
	return output << "\tsw " << registerStr(data) << ", " << offset << "(" << registerStr(location) << ")" << endl;
}

bool StoreWord::readsRegister(Register r) const {
	return r == data || r == location;
}

bool StoreWord::writesToRegister() const {
	return false;
}

Register StoreWord::destinationRegister() const {
	throw runtime_error("StoreWord does not write to any register");
}

Register StoreWord::getData() const {
	return data;
}

Register StoreWord::getLocation() const {
	return location;
}

int StoreWord::getOffset() const {
	return offset;
}

LoadWord::LoadWord(Register data, Register location, int offset) : data(data), location(location), offset(offset) {
	
}

LoadWord::~LoadWord() {
	
}

ostream& LoadWord::output(ostream& output) const {
	return output << "\tlw " << registerStr(data) << ", " << offset << "(" << registerStr(location) << ")" << endl;
}

bool LoadWord::readsRegister(Register r) const {
	return r == location;
}

bool LoadWord::writesToRegister() const {
	return true;
}

Register LoadWord::destinationRegister() const {
	return data;
}

Register LoadWord::getData() const {
	return data;
}

Register LoadWord::getLocation() const {
	return location;
}

int LoadWord::getOffset() const {
	return offset;
}

Syscall::Syscall() {
	
}

Syscall::~Syscall() {
	
}

ostream& Syscall::output(ostream& output) const {
	return output << "\tsyscall" << endl;
}

bool Syscall::readsRegister(Register r) const {
	return r == R_ZERO;
}

bool Syscall::writesToRegister() const {
	return true;
}

Register Syscall::destinationRegister() const {
	return R_ZERO;
}

Register Syscall::getData() const {
	return R_ZERO;
}

Register Syscall::getLocation() const {
	return R_ZERO;
}

int Syscall::getOffset() const {
	return 0;
}

LoadAddress::LoadAddress(Register data, const string& address) : data(data), address(address) {
	
}

LoadAddress::~LoadAddress() {
	
}

ostream& LoadAddress::output(ostream& output) const {
	return output << "\tla " << registerStr(data) << ", " << address << endl;
}

bool LoadAddress::readsRegister(Register r) const {
	return false;
}

bool LoadAddress::writesToRegister() const {
	return true;
}

Register LoadAddress::destinationRegister() const {
	return data;
}

Register LoadAddress::getData() const {
	return data;
}

const string& LoadAddress::getAddress() const {
	return address;
}

IntGlobal::IntGlobal(const std::string& name, unsigned int value) : name(name), value(value) {
	
}

IntGlobal::~IntGlobal() {
	
}

ostream& IntGlobal::output(ostream& output) const {
	return output << "\t.data" << endl << name << ": .word " << value << endl << "\t.text" << endl;
}

bool IntGlobal::readsRegister(Register r) const {
	return false;
}

bool IntGlobal::writesToRegister() const {
	return false;
}

Register IntGlobal::destinationRegister() const {
	throw runtime_error("IntGlobal does not write to any register");
}

const string& IntGlobal::getName() const {
	return name;
}

unsigned int IntGlobal::getValue() const {
	return value;
}

ArrayGlobal::ArrayGlobal(const std::string& name, int size) : name(name), size(size) {
	
}

ArrayGlobal::~ArrayGlobal() {
	
}

ostream& ArrayGlobal::output(ostream& output) const {
	return output << "\t.data" << endl << name << ": .space " << size << endl << "\t.text" << endl;
}

bool ArrayGlobal::readsRegister(Register r) const {
	return false;
}

bool ArrayGlobal::writesToRegister() const {
	return false;
}

Register ArrayGlobal::destinationRegister() const {
	throw runtime_error("ArrayGlobal does not write to any register");
}

const string& ArrayGlobal::getName() const {
	return name;
}

int ArrayGlobal::getSize() const {
	return size;
}

ArrayInitGlobal::ArrayInitGlobal(const std::string& name, int size, std::vector<int> list) : name(name), size(size), array_init_list(list) {
	
}

ArrayInitGlobal::~ArrayInitGlobal() {
	
}

ostream& ArrayInitGlobal::output(ostream& output) const {
	int size_new = size;
	std::string cur = "\t.data\n" + name + ":\n";
	for(auto it=array_init_list.begin(); it!=array_init_list.end(); ++it){
		cur += ("\t.word "+ toString(*it) + "\n");
		size_new -= 4;
	}
	if(size_new!=0){
		cur += ("\t.space " + toString(size_new) +"\n");
	}
	cur += "\t.text";
	return output << cur << endl;
	// return output << "\t.data" << endl << name << ": .space " << size << endl << "\t.text" << endl;
}

bool ArrayInitGlobal::readsRegister(Register r) const {
	return false;
}

bool ArrayInitGlobal::writesToRegister() const {
	return false;
}

Register ArrayInitGlobal::destinationRegister() const {
	throw runtime_error("ArrayGlobal does not write to any register");
}

const string& ArrayInitGlobal::getName() const {
	return name;
}

int ArrayInitGlobal::getSize() const {
	return size;
}

StringGlobal::StringGlobal(const std::string& name, const string& value) : name(name), value(value) {
	
}

StringGlobal::~StringGlobal() {
	
}

ostream& StringGlobal::output(ostream& output) const {
	return output << "\t.data" << endl << name << ": .asciiz \"" << value << '"' << endl << "\t.text" << endl;
}

bool StringGlobal::readsRegister(Register r) const {
	return false;
}

bool StringGlobal::writesToRegister() const {
	return false;
}

Register StringGlobal::destinationRegister() const {
	throw runtime_error("StringGlobal does not write to any register");
}

const string& StringGlobal::getName() const {
	return name;
}

const string& StringGlobal::getValue() const {
	return value;
}

BinOp::BinOp(const std::string& op, Register dest, Register left, Register right) : op(op), dest(dest), left(left), right(right) {
	
}

BinOp::~BinOp() {
	
}

const string& BinOp::getOp() const {
	return op;
}

Register BinOp::getDest() const {
	return dest;
}

Register BinOp::getLeft() const {
	return left;
}

Register BinOp::getRight() const {
	return right;
}

ostream& BinOp::output(ostream& output) const {
	return output << "\t" << op << " " << registerStr(dest) << ", " << registerStr(left) << ", " << registerStr(right) << endl;
}

bool BinOp::readsRegister(Register r) const {
	return left == r || right == r;
}

bool BinOp::writesToRegister() const {
	return true;
}

Register BinOp::destinationRegister() const {
	return getDest();
}

BinOpImmediate::BinOpImmediate(const std::string& op, Register dest, Register left, short right) : op(op), dest(dest), left(left), right(right) {
	
}

BinOpImmediate::~BinOpImmediate() {
	
}

const string& BinOpImmediate::getOp() const {
	return op;
}

Register BinOpImmediate::getDest() const {
	return dest;
}

Register BinOpImmediate::getLeft() const {
	return left;
}

short BinOpImmediate::getRight() const {
	return right;
}

ostream& BinOpImmediate::output(ostream& output) const {
	return output << "\t" << op << " " << registerStr(dest) << ", " << registerStr(left) << ", " << right << endl;
}

bool BinOpImmediate::readsRegister(Register r) const {
	return left == r;
}

bool BinOpImmediate::writesToRegister() const {
	return true;
}

Register BinOpImmediate::destinationRegister() const {
	return getDest();
}

LoadImmediate::LoadImmediate(Register reg, int value) : reg(reg), value(value) {
	
}

LoadImmediate::~LoadImmediate() {
	
}

ostream& LoadImmediate::output(ostream& output) const {
	return output << "\tli " << registerStr(reg) << ", " << value << endl;
}

bool LoadImmediate::readsRegister(Register r) const {
	return false;
}

void LoadImmediate::setRegister(Register r) {
	reg = r;
}

void LoadImmediate::setValue(int v) {
	value = v;
}

Register LoadImmediate::getRegister() const {
	return reg;
}

int LoadImmediate::getValue() const {
	return value;
}

bool LoadImmediate::writesToRegister() const {
	return true;
}

Register LoadImmediate::destinationRegister() const {
	return getRegister();
}
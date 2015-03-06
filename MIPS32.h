////////////////////////////////////////////////////////////////////////
/*
  File Name: MIPS32.h
  This is the header file of MIPS32.cpp. For detailed information, see
  "MIPS32.cpp"
*/
////////////////////////////////////////////////////////////////////////

#ifndef MIPS32_H
#define MIPS32_H

#include <iostream>
#include <string>
#include <vector>

typedef unsigned short Register;

extern const Register R_ZERO;

extern const Register R_AT;

extern const Register R_V0;
extern const Register R_V1;

extern const Register R_A0;
extern const Register R_A1;
extern const Register R_A2;
extern const Register R_A3;

extern const Register R_T0;
extern const Register R_T1;
extern const Register R_T2;
extern const Register R_T3;
extern const Register R_T4;
extern const Register R_T5;
extern const Register R_T6;
extern const Register R_T7;

extern const Register R_S0;
extern const Register R_S1;
extern const Register R_S2;
extern const Register R_S3;
extern const Register R_S4;
extern const Register R_S5;
extern const Register R_S6;
extern const Register R_S7;

extern const Register R_T8;
extern const Register R_T9;

extern const Register R_K0;
extern const Register R_K1;

extern const Register R_GP;

extern const Register R_SP;

extern const Register R_S8;
	
extern const Register R_RA;
	
std::string registerStr(Register r);

class Instruction;

std::ostream &operator<<(std::ostream& output, const Instruction&);

class Instruction {
private:
	
public:
	Instruction();
	Instruction(const Instruction&) = delete;
	virtual ~Instruction();
	virtual const Instruction& operator=(const Instruction&) = delete;
	
	virtual std::ostream& output(std::ostream& o) const = 0;
	virtual bool readsRegister(Register) const = 0;
	virtual bool writesToRegister() const = 0;
	virtual Register destinationRegister() const = 0;
};

class ControlFlowInstruction : public Instruction {
public:
	ControlFlowInstruction();
	ControlFlowInstruction(const ControlFlowInstruction&) = delete;
	virtual ~ControlFlowInstruction();
	virtual const ControlFlowInstruction& operator=(const ControlFlowInstruction&) = delete;
	
	virtual std::ostream& output(std::ostream& o) const = 0;
	virtual bool readsRegister(Register) const = 0;
	virtual bool writesToRegister() const = 0;
	virtual Register destinationRegister() const = 0;
};

class Label : public ControlFlowInstruction {
private:
	std::string name;
public:
	Label(const std::string& name);
	Label(const Label&) = delete;
	virtual ~Label();
	virtual const Label& operator=(const Label&) = delete;
	
	virtual std::ostream& output(std::ostream& o) const;
	virtual bool readsRegister(Register) const;
	virtual bool writesToRegister() const;
	virtual Register destinationRegister() const;
	
	virtual const std::string& getName() const;
};

class Jump : public ControlFlowInstruction {
private:
	std::string target;
public:
	Jump(const std::string& target);
	Jump(const Jump&) = delete;
	virtual ~Jump();
	virtual const Jump& operator=(const Jump&) = delete;
	
	virtual std::ostream& output(std::ostream& o) const;
	virtual bool readsRegister(Register) const;
	virtual bool writesToRegister() const;
	virtual Register destinationRegister() const;
	
	virtual const std::string& getTarget() const;
};

class JumpRegister : public ControlFlowInstruction {
private:
	Register target;
public:
	JumpRegister(Register target);
	JumpRegister(const JumpRegister&) = delete;
	virtual ~JumpRegister();
	virtual const JumpRegister& operator=(const JumpRegister&) = delete;
	
	virtual std::ostream& output(std::ostream& o) const;
	virtual bool readsRegister(Register) const;
	virtual bool writesToRegister() const;
	virtual Register destinationRegister() const;
	
	virtual Register getTarget() const;
};

class JumpAndLink : public ControlFlowInstruction {
private:
	std::string target;
public:
	JumpAndLink(const std::string& target);
	JumpAndLink(const JumpAndLink&) = delete;
	virtual ~JumpAndLink();
	virtual const JumpAndLink& operator=(const JumpAndLink&) = delete;
	
	virtual std::ostream& output(std::ostream& o) const;
	virtual bool readsRegister(Register) const;
	virtual bool writesToRegister() const;
	virtual Register destinationRegister() const;
	
	virtual const std::string& getTarget() const;
};

class BranchOnEqual : public ControlFlowInstruction {
private:
	Register left;
	Register right;
	std::string target;
public:
	BranchOnEqual(Register left, Register right, const std::string& target);
	BranchOnEqual(const BranchOnEqual&) = delete;
	virtual ~BranchOnEqual();
	virtual const BranchOnEqual& operator=(const BranchOnEqual&) = delete;
	
	virtual std::ostream& output(std::ostream& o) const;
	virtual bool readsRegister(Register) const;
	virtual bool writesToRegister() const;
	virtual Register destinationRegister() const;
	
	virtual Register getLeft() const;
	virtual Register getRight() const;
	virtual const std::string& getTarget() const;
};

class BranchNotEqual : public ControlFlowInstruction {
private:
	Register left;
	Register right;
	std::string target;
public:
	BranchNotEqual(Register left, Register right, const std::string& target);
	BranchNotEqual(const BranchNotEqual&) = delete;
	virtual ~BranchNotEqual();
	virtual const BranchNotEqual& operator=(const BranchNotEqual&) = delete;
	
	virtual std::ostream& output(std::ostream& o) const;
	virtual bool readsRegister(Register) const;
	virtual bool writesToRegister() const;
	virtual Register destinationRegister() const;
	
	virtual Register getLeft() const;
	virtual Register getRight() const;
	virtual const std::string& getTarget() const;
};

class StoreWord : public Instruction {
private:
	Register data;
	Register location;
	int offset;
public:
	StoreWord(Register data, Register location, int offset);
	StoreWord(const StoreWord&) = delete;
	virtual ~StoreWord();
	virtual const StoreWord& operator=(const StoreWord&) = delete;
	
	virtual std::ostream& output(std::ostream& o) const;
	virtual bool readsRegister(Register) const;
	virtual bool writesToRegister() const;
	virtual Register destinationRegister() const;
	
	virtual Register getData() const;
	virtual Register getLocation() const;
	virtual int getOffset() const;
};

class LoadWord : public Instruction {
private:
	Register data;
	Register location;
	int offset;
public:
	LoadWord(Register data, Register location, int offset);
	LoadWord(const LoadWord&) = delete;
	virtual ~LoadWord();
	virtual const LoadWord& operator=(const LoadWord&) = delete;
	
	virtual std::ostream& output(std::ostream& o) const;
	virtual bool readsRegister(Register) const;
	virtual bool writesToRegister() const;
	virtual Register destinationRegister() const;
	
	virtual Register getData() const;
	virtual Register getLocation() const;
	virtual int getOffset() const;
};

class Syscall : public Instruction {
private:

public:
	Syscall();
	Syscall(const Syscall&) = delete;
	virtual ~Syscall();
	virtual const Syscall& operator=(const Syscall&) = delete;
	
	virtual std::ostream& output(std::ostream& o) const;
	virtual bool readsRegister(Register) const;
	virtual bool writesToRegister() const;
	virtual Register destinationRegister() const;
	
	virtual Register getData() const;
	virtual Register getLocation() const;
	virtual int getOffset() const;
};

class LoadAddress : public Instruction {
private:
	Register data;
	std::string address;
public:
	LoadAddress(Register data, const std::string& address);
	LoadAddress(const LoadAddress&) = delete;
	virtual ~LoadAddress();
	virtual const LoadAddress& operator=(const LoadAddress&) = delete;
	
	virtual std::ostream& output(std::ostream& o) const;
	virtual bool readsRegister(Register) const;
	virtual bool writesToRegister() const;
	virtual Register destinationRegister() const;
	
	virtual Register getData() const;
	virtual const std::string& getAddress() const;
};

class IntGlobal : public Instruction {
private:
	std::string name;
	unsigned int value;
public:
	IntGlobal(const std::string& name, unsigned int value = 0);
	IntGlobal(const IntGlobal&) = delete;
	virtual ~IntGlobal();
	virtual const IntGlobal& operator=(const IntGlobal&) = delete;
	
	virtual std::ostream& output(std::ostream& o) const;
	virtual bool readsRegister(Register) const;
	virtual bool writesToRegister() const;
	virtual Register destinationRegister() const;
	
	virtual const std::string& getName() const;
	virtual unsigned int getValue() const;
};

class ArrayGlobal : public Instruction {
private:
	std::string name;
	int size;
public:
	ArrayGlobal(const std::string& name, int size);
	ArrayGlobal(const ArrayGlobal&) = delete;
	virtual ~ArrayGlobal();
	virtual const ArrayGlobal& operator=(const ArrayGlobal&) = delete;
	
	virtual std::ostream& output(std::ostream& o) const;
	virtual bool readsRegister(Register) const;
	virtual bool writesToRegister() const;
	virtual Register destinationRegister() const;
	
	virtual const std::string& getName() const;
	virtual int getSize() const;
};

class ArrayInitGlobal : public Instruction {
private:
	std::string name;
	std::vector<int> array_init_list;
	int size;
public:
	ArrayInitGlobal(const std::string& name, int size, std::vector<int> list);
	ArrayInitGlobal(const ArrayGlobal&) = delete;
	virtual ~ArrayInitGlobal();
	virtual const ArrayInitGlobal& operator=(const ArrayInitGlobal&) = delete;
	
	virtual std::ostream& output(std::ostream& o) const;
	virtual bool readsRegister(Register) const;
	virtual bool writesToRegister() const;
	virtual Register destinationRegister() const;
	
	virtual const std::string& getName() const;
	virtual int getSize() const;
};

class StringGlobal : public Instruction {
private:
	std::string name;
	std::string value;
public:
	StringGlobal(const std::string& name, const std::string& value);
	StringGlobal(const StringGlobal&) = delete;
	virtual ~StringGlobal();
	virtual const StringGlobal& operator=(const StringGlobal&) = delete;
	
	virtual std::ostream& output(std::ostream& o) const;
	virtual bool readsRegister(Register) const;
	virtual bool writesToRegister() const;
	virtual Register destinationRegister() const;
	
	virtual const std::string& getName() const;
	virtual const std::string& getValue() const;
};

class BinOp : public Instruction {
private:
	std::string op;
	Register dest;
	Register left;
	Register right;
public:
	BinOp(const std::string& op, Register dest, Register left, Register right);
	BinOp(const BinOp&) = delete;
	virtual ~BinOp();
	virtual const BinOp& operator=(const BinOp&) = delete;
	
	virtual std::ostream& output(std::ostream&) const;
	virtual bool readsRegister(Register) const;
	virtual bool writesToRegister() const;
	virtual Register destinationRegister() const;
	
	virtual const std::string& getOp() const;
	virtual Register getDest() const;
	virtual Register getLeft() const;
	virtual Register getRight() const;
};

class BinOpImmediate : public Instruction {
private:
	std::string op;
	Register dest;
	Register left;
	short right;
public:
	BinOpImmediate(const std::string& op, Register dest, Register left, short right);
	BinOpImmediate(const BinOpImmediate&) = delete;
	virtual ~BinOpImmediate();
	virtual const BinOpImmediate& operator=(const BinOpImmediate&) = delete;
	
	virtual std::ostream& output(std::ostream&) const;
	virtual bool readsRegister(Register) const;
	virtual bool writesToRegister() const;
	virtual Register destinationRegister() const;
	
	virtual const std::string& getOp() const;
	virtual Register getDest() const;
	virtual Register getLeft() const;
	virtual short getRight() const;
};

class LoadImmediate : public Instruction {
private:
	Register reg;
	int value;
public:
	LoadImmediate(Register reg, int value);
	LoadImmediate(const LoadImmediate&);
	virtual ~LoadImmediate();
	virtual const LoadImmediate& operator=(const LoadImmediate&) = delete;
	
	virtual std::ostream& output(std::ostream&) const;
	virtual bool readsRegister(Register) const;
	virtual bool writesToRegister() const;
	virtual Register destinationRegister() const;
	
	virtual void setRegister(Register);
	virtual void setValue(int);
	
	virtual Register getRegister() const;
	virtual int getValue() const;
};


#endif
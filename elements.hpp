#ifndef DATA_VALUE_HPP
#define DATA_VALUE_HPP

#include <iostream>

using namespace std;

class Data_Value {
  double value = 0.0;
	bool valid = false;

public:
  double getValue() { return this->value; };
	void writeValue(double value) { this->value = value; valid = true; };
	bool isValid() { return this->valid; };
	void toggleValid() { this->valid = !valid; };
};

#endif

#ifndef CPU_REGISTER_HHP
#define CPU_REGISTER_HHP

#include <list>
#include <iostream>
#include <map>
using namespace std;

enum op_code_t { NOP, ADD, SUB, MUL, DIV };

class instruction_types { // MAPPING for translating instructions
public:
	map<string, op_code_t> types;

	instruction_types() {
		this->types["NOP"] = NOP;
		this->types["ADD"] = ADD;
		this->types["SUB"] = SUB;
		this->types["MUL"] = MUL;
		this->types["DIV"] = DIV;
	}
};


class CPU_Register {
  list<Data_Value> FIFO;

public:
  bool empty();
  Data_Value read();
  void store(Data_Value value);
	void print();
};

#endif

#ifndef PROGRAM_INSTRUCTION_HPP
#define PROGRAM_INSTRUCTION_HPP

#include <iostream>
#include <string>

using namespace std;

class Program_Instruction {
public:
  op_code_t op_code;
	double op1;
	double op2;

  Data_Value compute();
  Program_Instruction(string instruction_line);
};

#endif


#ifndef CPU_PROGRAM_HPP
#define CPU_PROGRAM_HPP

#include <iostream>
#include <string>
#include <vector>
#include <fstream>


using namespace std;

class CPU_Program {
  int instruction_pointer = 0;
	vector<Program_Instruction> instructions;

public:
  Program_Instruction compute_next();
  bool is_done();
  void reset();
	CPU_Program(string path);
	void showInstructions();
};

#endif

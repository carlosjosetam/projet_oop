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
  std::list<double> FIFO;

public:
  bool empty();
  double read_register();
  void store(double value);
};

#endif

#ifndef PROGRAM_INSTRUCTION_HPP
#define PROGRAM_INSTRUCTION_HPP

#include <iostream>
#include <string>

using namespace std;

class Program_Instruction {
  op_code_t op_code;
	double op1;
	double op2;

public:
  double compute();
  Program_Instruction(string instruction_line);
};

#endif


#ifndef CPU_PROGRAM_HPP
#define CPU_PROGRAM_HPP

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class CPU_Program {
  int instruction_pointer;
	vector<Program_Instruction> instructions;

public:
  Program_Instruction compute();
  bool is_done();
  void reset();
	CPU_Program(string path);
};

#endif

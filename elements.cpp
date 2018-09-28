#include "elements.hpp"
#include <iostream>
#include <sstream>
#include <map>

using namespace std;

// CPU_REGISTER_HHP

bool CPU_Register::empty() {
  if (this->FIFO.empty()) {
    return true;
  }
  else return false;
}

Data_Value CPU_Register::read() {
  Data_Value pop_value = this->FIFO.front();
  this->FIFO.pop_front();
  return pop_value;
}

void CPU_Register::store(Data_Value value) {
  this->FIFO.push_back(value);
}

void CPU_Register::print() {
  std::cout << "Printing internal register" << '\n';
  for (Data_Value value : this->FIFO) {
    cout << value.getValue() << " | valid : " << value.isValid() << "\n";
  }
  std::cout << '\n';
}

// PROGRAM_INSTRUCTION_HPP

Program_Instruction::Program_Instruction(string instruction_line) {
  //Recieves the line of the instruction and creates the element Program_Instruction

  instruction_types types;
  istringstream iss(instruction_line);
  string element;
  iss >> element;
  this->op_code = types.types[element];
  iss >> element;
  this->op1 = stod(element);
  iss >> element;
  this->op2 = stod(element);
  cout << "created instruction " << instruction_line << '\n';
}


Data_Value Program_Instruction::compute() {

  // enum op_code_t { NOP, ADD, SUB, MUL, DIV };

  Data_Value value;
  value.toggleValid();

  switch (op_code) {
    case 0:
    value.writeValue(0.0); return value;

    case 1:
    value.writeValue(this->op1 + this->op2); return value;

    case 2:
    value.writeValue(this->op1 - this->op2); return value;

    case 3:
    value.writeValue(this->op1 * this->op2); return value;

    case 4:
    value.writeValue(this->op1 / this->op2); return value;
  }

}


// CPU_PROGRAM_HPP

Program_Instruction CPU_Program::compute_next() {
  if (this->is_done()) {
    Program_Instruction instruction_NOP("NOP 0 0");
    return instruction_NOP;
  }
  this->instruction_pointer++;
  return this->instructions[instruction_pointer - 1];
}

bool CPU_Program::is_done() {
  if (this->instruction_pointer >= this->instructions.size()) {
    return true;
  }
  return false;
}

void CPU_Program::reset() {
  this->instruction_pointer = 0;
}

CPU_Program::CPU_Program(string path) {
  this->instruction_pointer = 0;
  vector<Program_Instruction> v;

  // Read file from path
  string line;
  ifstream myfile (path);
  if (myfile.is_open()) {
    while (! myfile.eof() ) {
      getline (myfile,line);
      Program_Instruction p = Program_Instruction(line);
      v.push_back(p);
    }
    std::cout << '\n';
    myfile.close();
  }

  this->instructions = v;
}

void CPU_Program::showInstructions() {
  for (int i = 0; i < this->instructions.size(); i++) {
    cout << "Instruction #" << this->instructions[i].op_code << " " << this->instructions[i].op1 << " " << this->instructions[i].op2 << '\n';
  }
}

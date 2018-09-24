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

double CPU_Register::read_register() {
  double pop_value = this->FIFO.front();
  this->FIFO.pop_front();
  return pop_value;
}

void CPU_Register::store(double value) {
  this->FIFO.push_back(value);
}

// PROGRAM_INSTRUCTION_HPP

Program_Instruction::Program_Instruction(string instruction_line) {
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


double Program_Instruction::compute() {
  return 44.0;
}


// CPU_PROGRAM_HPP

Program_Instruction CPU_Program::compute() {
  return this->instructions[instruction_pointer];
}

bool CPU_Program::is_done() {
  // to do {
  return true;
}

void CPU_Program::reset() {
  this->instruction_pointer = 0;
}

CPU_Program::CPU_Program(string path) {
  this->instruction_pointer = 0;
  vector<Program_Instruction> v;
  Program_Instruction p("ADD 1 2");
  v.push_back(p);
  v.push_back(p);
  this->instructions = v;
}

#include "modules.hpp"
#include "interfaces.hpp"
#include "elements.hpp"
#include <iostream>
#include <sstream>
#include <map>

using namespace std;

// CPU
CPU::CPU (string path) {
  /* takes a .txt text file with the discription of the CPU
  At this point we know already its a CPU
  We always consider that there's never a problem with syntax,
  to simplify, there's no error verification
  There will always be 5 lines described this way

  -- Example --
  TYPE: CPU
  LABEL: Main processing unit
  CORES: 2
  FREQUENCY: 4
  PROGRAM: /path/to/program/file.txt
  */

  // Read file from path
  string line, element;
  ifstream myfile (path);
  if (myfile.is_open()) {
    while (! myfile.eof() ) {
      getline (myfile,line); // discart first line : we know its a CPU

      // LABEL
      getline (myfile,line);
      istringstream iss_label(line);
      iss_label >> element;
      if (element != "LABEL:") { cout << "ERROR in LABEL syntax" << '\n'; exit(0);}
      this->writeLabel(iss_label.str().substr(7));

      // CORES
      getline(myfile,line);
      istringstream iss_cores(line);
      iss_cores >> element;
      if (element != "CORES:") { cout << "ERROR in CORES syntax" << '\n'; exit(0);}
      this->n_cores = stoi(iss_cores.str().substr(6));

      // FREQUENCY
      getline(myfile,line);
      istringstream iss_frequency(line);
      iss_frequency >> element;
      if (element != "FREQUENCY:") { cout << "ERROR in FREQUENCY syntax" << '\n'; exit(0);}
      this->frequency = stoi(iss_frequency.str().substr(10));

      // program_path
      getline(myfile,line);
      istringstream iss_program_path(line);
      iss_program_path >> element;
      if (element != "PROGRAM:") { cout << "ERROR in PROGRAM syntax" << '\n'; exit(0);}
      string program_path = iss_program_path.str().substr(9);

      cout << "==> CPU created : '" << this->getLabel() << "' with program '" << program_path << "'"<< endl;
      cout << "cores: " << this->n_cores << endl;
      cout << "frequency: " << this->frequency << endl;

      cout << "==> Reading Program: " << program_path << '\n';
      CPU_Program * program = new CPU_Program(program_path);
      this->program = program;

      CPU_Register internal_register;
      this->internal_register = internal_register;

    }
    myfile.close();
  }

  CPU_Register internal_register;
  this->internal_register = internal_register;


}

Data_Value CPU::read() {

  if(this->internal_register.empty()) {
    Data_Value value;
    return value;
  }

  Data_Value value = this->internal_register.read();
  return value;
}

void CPU::simulate() {
  cout << "==> Simulating CPU " << this->getLabel() << '\n';

  Data_Value value;
  Program_Instruction current_instruction("NOP 0 0");

  this->active_core = 1;
  for (int i = 0; i < this->n_cores; i++) {
    std::cout << "Executing core " << this->active_core << '\n';

    this->program->reset();
    while (!this->program->is_done()) {
      current_instruction = this->program->compute_next();
      for (int i = 0; i < this->frequency; i++) { // Execute each instruction F times
        value = current_instruction.compute();
      }
      this->internal_register.store(value);
    }
    this->active_core++;
  }

  // print CPU_Register
  this->internal_register.print();


}

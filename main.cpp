#include "elements.hpp"
#include "interfaces.hpp"
#include "modules.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace std;



int main() {

  std::cout << "Introduction to Object-Oriented Programming with C++" << '\n';
  std::cout << "Hardware Platform Simulator" << '\n';
  std::cout << "Authors : Carlos Tamancoldi and Margareth Mee Lima" << '\n';
  std::cout << '\n';

  /* TEST INSTRUCTIONS
  cout << '\n' << "TEST INSTRUCTIONS" << '\n';
  cout << "Type the path with the instructions" << '\n';
  string path_instructions;
  //cin >> path_instructions;
  path_instructions = "testdata/program.txt";
  CPU_Program program(path_instructions);

  // TEST CPU
  cout << "TEST CPU" << '\n';
  Readable * cpu_1 = new CPU("testdata/cpu1.txt");
  Readable * cpu_2 = new CPU("testdata/cpu2.txt");
  Readable * bus_1 = new BUS("testdata/bus1.txt");
  Readable * bus_2 = new BUS("testdata/bus2.txt");
  Readable * mem_1 = new MEMORY("testdata/mem1.txt");
  Readable * mem_2 = new MEMORY("testdata/mem2.txt");
  Component * display = new DISPLAY("testdata/display.txt");
  */

  // TEST PLATAFORM
  cout << "TEST PLATAFORM" << '\n';
  PLATFORM plataform1("testdata/platform.txt");

  plataform1.simulate();


  return 0;
}

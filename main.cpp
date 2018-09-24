#include "elements.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace std;



int main() {

  // TEST REGISTER
  CPU_Register register_test;
  cout << "empty " << register_test.empty() << '\n';
  register_test.store(5.0);
  register_test.store(4.0);
  cout << "empty " << register_test.empty() << '\n';
  cout << "read " << register_test.read_register() << '\n';
  cout << "read " << register_test.read_register() << '\n';
  cout << "empty " << register_test.empty() << '\n';

  // TEST INSTRUCTIONS
  CPU_Program program("ola");


  return 0;
}

#include "modules.hpp"
#include "interfaces.hpp"
#include "elements.hpp"
#include <iostream>
#include <sstream>
#include <map>

using namespace std;

// PLATFORM

PLATFORM::PLATFORM (string path) {
  /* takes a .txt text file with the discription of the PLATFORM
  IT reads each file and sends it to the right constructor

  -- Example --
  /path/to/cpu2/file.txt
  /path/to/bus/file.txt
  /path/to/memory/file.txt
  /path/to/display/file.txt
  */

  // Read file from path
  cout << "==> Reading Platform Configuration from file : " << path <<  '\n' << endl;
  string line, element, element_type;
  ifstream myfile (path);
  ifstream my_component;
  if (myfile.is_open()) {
    while (! myfile.eof() ) {
      getline(myfile,line);
      my_component.open(line);
      getline(my_component, element);
      element_type = element.substr(6);
      if (element_type == "CPU") {
        CPU * cpu_component = new CPU(line);
        this->cpu_vector.push_back(cpu_component);
      }
      if (element_type == "BUS") {
        BUS * bus_component = new BUS(line);
        this->bus_vector.push_back(bus_component);
      }
      if (element_type == "MEMORY") {
        MEMORY * memory_component = new MEMORY(line);
        this->memory_vector.push_back(memory_component);
      }
      if (element_type == "DISPLAY") {
        DISPLAY * display_component = new DISPLAY(line);
        this->display_vector.push_back(display_component);
      }
      my_component.close();
    }
    myfile.close();
  }

  // 2 Phase :  binding
  this->bind();
}

void PLATFORM::simulate() {
  cout << "==> Simulating PLATFORM" << '\n';
  std::cout << '\n';

  // Simulate cpu_vector
  for (int i = 0; i < this->cpu_vector.size(); i++) {
    this->cpu_vector[i]->simulate();
  }

  // Simulate bus_vector
  for (int i = 0; i < this->bus_vector.size(); i++) {
    // Simulate each one 2 times to fill up ready
    this->bus_vector[i]->simulate();
    this->bus_vector[i]->simulate();
  }


  // Simulate memory_vector
  for (int i = 0; i < this->memory_vector.size(); i++) {
    this->memory_vector[i]->simulate();
  }

  // Simulate bus_vector
  for (int i = 0; i < this->bus_vector.size(); i++) {
    this->bus_vector[i]->simulate();
  }

  // Simulate memory_vector
  for (int i = 0; i < this->memory_vector.size(); i++) {
    this->memory_vector[i]->simulate();
  }

  // Simulate display_vector
  for (int i = 0; i < this->display_vector.size(); i++) {
    this->display_vector[i]->simulate();
  }

  std::cout << "==> END OF SIMULATION" << '\n';

}

void PLATFORM::bind() {
  cout << "==> Binding Components" << '\n';
  string source;

  // Binding BUS
  for (int i = 0; i < this->bus_vector.size(); i++) {
    // Now we have one bus to bind bus_vector[i].
    // We have to search the source_label that corresponds
    Readable * source = find_source(this->bus_vector[i]->source_label);
    if (source != NULL) {
      this->bus_vector[i]->source = source;
      cout << "Component " << this->bus_vector[i]->getLabel() << " binded to " << this->bus_vector[i]->source_label << '\n';
    }
    else cout << "Bind component not found" << '\n';
  }


  // Binding Display
  for (int i = 0; i < this->display_vector.size(); i++) {
    // Now we have one display to bind display_vector[i].
    // We have to search the source_label that corresponds
    Readable * source = find_source(this->display_vector[i]->source_label);
    if (source != NULL) {
      this->display_vector[i]->source = source;
      cout << "Component " << this->display_vector[i]->getLabel() << " binded to " << this->display_vector[i]->source_label << '\n';
    }
    else cout << "Bind component not found" << '\n';
  }

  // Binding memory
  for (int i = 0; i < this->memory_vector.size(); i++) {
    // Now we have one memory to bind memory_vector[i].
    // We have to search the source_label that corresponds
    Readable * source = find_source(this->memory_vector[i]->source_label);
    if (source != NULL) {
      this->memory_vector[i]->source = source;
      cout << "Component " << this->memory_vector[i]->getLabel() << " binded to " << this->memory_vector[i]->source_label << '\n';
    }
    else cout << "Bind component not found" << '\n';
  }

  std::cout << '\n';
}

Readable * PLATFORM::find_source(string source_label) {
  // Search in bus_vector
  for (int i = 0; i < this->bus_vector.size(); i++) {
    if (this->bus_vector[i]->getLabel() == source_label) {
      Readable * source = this->bus_vector[i];
      return source;
    }
  }
  // Search in cpu_vector
  for (int i = 0; i < this->cpu_vector.size(); i++) {
    if (this->cpu_vector[i]->getLabel() == source_label) {
      Readable * source = this->cpu_vector[i];
      return source;
    }
  }
  // Search in memory_vector
  for (int i = 0; i < this->memory_vector.size(); i++) {
    if (this->memory_vector[i]->getLabel() == source_label) {
      Readable * source = this->memory_vector[i];
      return source;
    }
  }
  return NULL;
}

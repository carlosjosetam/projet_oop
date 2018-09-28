#include "modules.hpp"
#include "interfaces.hpp"
#include "elements.hpp"
#include <iostream>
#include <sstream>
#include <map>

using namespace std;

// MEMORY

MEMORY::MEMORY (string path) {
  /* takes a .txt text file with the discription of the MEMORY
  At this point we know already its a MEMORY
  We always consider that there's never a problem with syntax,
  to simplify, there's no error verification
  There will always be 5 lines described this way

  -- Example --
  TYPE: MEMORY
  LABEL: DRAM 1
  SIZE: 32
  ACCESS: 3
  SOURCE: My bus 1
  */

  // Read file from path
  string line, element;
  ifstream myfile (path);
  if (myfile.is_open()) {
    while (! myfile.eof() ) {
      getline (myfile,line); // discart first line : we know its a MEMORY

      // LABEL
      getline (myfile,line);
      istringstream iss_label(line);
      iss_label >> element;
      if (element != "LABEL:") { cout << "ERROR in LABEL syntax" << '\n'; exit(0);}
      this->writeLabel(iss_label.str().substr(7));

      // SIZE
      getline(myfile,line);
      istringstream iss_size(line);
      iss_size >> element;
      if (element != "SIZE:") { cout << "ERROR in SIZE syntax" << '\n'; exit(0);}
      this->size = stoi(iss_size.str().substr(5));

      // ACCESS
      getline(myfile,line);
      istringstream iss_access(line);
      iss_access >> element;
      if (element != "ACCESS:") { cout << "ERROR in ACCESS syntax" << '\n'; exit(0);}
      this->access_time = stoi(iss_access.str().substr(7));

      // SOURCE
      getline(myfile,line);
      istringstream iss_source(line);
      iss_source >> element;
      if (element != "SOURCE:") { cout << "ERROR in SOURCE syntax" << '\n'; exit(0);}
      string source = iss_source.str().substr(8);
      this->source_label = source;

      cout << "==> MEMORY created : '" << this->getLabel() << "' with source '" << source << "'"<< endl;
      cout << "size: " << this->size << endl;
      cout << "access_time: " << this->access_time << endl << '\n';

    }
    myfile.close();
  }
}

Data_Value MEMORY::read() {
  // A Memory can be read. Each time it is read, it returns the next oldest DataValue.
  // If there are no more values to read (i.e. all the stored values have been read once),
  // then it returns an invalid DataValue.
  if(this->data.empty()) {
    Data_Value value;
    return value;
  }

  Data_Value value = this->data.front();
  this->data.pop_front();
  return value;
}


void MEMORY::simulate() {
  cout << "==> Simulating MEMORY " << this->getLabel() << '\n';
  std::cout << "Reading data from " << this->source_label << '\n';

  Data_Value value = this->source->read();

  while (value.isValid()) {
    if (this->data.size() == this->size) {
      this->data.pop_front();
      this->data.push_back(value);
    }
    else {
      this->data.push_back(value);
    }
    value = this->source->read();
  }

  cout << "Printing data from " << this->getLabel() << '\n';
  for (Data_Value aux : this->data) {
    cout << aux.getValue() << " | valid : " << aux.isValid() << "\n";
  }
  std::cout << '\n';
}

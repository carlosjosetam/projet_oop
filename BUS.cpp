#include "modules.hpp"
#include "interfaces.hpp"
#include "elements.hpp"
#include <iostream>
#include <sstream>
#include <map>

using namespace std;

// BUS
BUS::BUS (string path) {
  /* takes a .txt text file with the discription of the BUS
  At this point we know already its a BUS
  We always consider that there's never a problem with syntax,
  to simplify, there's no error verification
  There will always be 5 lines described this way

  -- Example --
  TYPE: BUS
  LABEL: My bus 1
  WIDTH: 2
  SOURCE: Main processing unit
  */

  // Read file from path
  string line, element;
  ifstream myfile (path);
  if (myfile.is_open()) {
    while (! myfile.eof() ) {
      getline (myfile,line); // discart first line : we know its a BUS

      // LABEL
      getline (myfile,line);
      istringstream iss_label(line);
      iss_label >> element;
      if (element != "LABEL:") { cout << "ERROR in LABEL syntax" << '\n'; exit(0);}
      this->writeLabel(iss_label.str().substr(7));

      // WIDTH
      getline(myfile,line);
      istringstream iss_width(line);
      iss_width >> element;
      if (element != "WIDTH:") { cout << "ERROR in WIDTH syntax" << '\n'; exit(0);}
      this->width = stoi(iss_width.str().substr(6));

      // SOURCE
      getline(myfile,line);
      istringstream iss_source(line);
      iss_source >> element;
      if (element != "SOURCE:") { cout << "ERROR in SOURCE syntax" << '\n'; exit(0);}
      string source = iss_source.str().substr(8);
      this->source_label = source;

      // Initialize vectors
      Data_Value invalid_data;
      vector<Data_Value> pending;
      vector<Data_Value> ready;
      for (int i = 0; i < this->width; i++) {
        pending.push_back(invalid_data);
        ready.push_back(invalid_data);
      }

      this->ready = ready;
      this->pending = pending;

      cout << "==> BUS created : '" << this->getLabel() << "' with source '" << source << "'"<< endl;
      cout << "width: " << this->width << endl << '\n';


    }
    myfile.close();
  }
}


Data_Value BUS::read() {
  // A Bus can be read. Each time it is read, it returns the oldest DataValue that is ready.
  // If there are no ready values, then it returns an invalid DataValue.
  // The bus counts the number of times it is read.
  Data_Value invalid_data;

  this->count_read++;
  if (this->ready.empty()) {
    return invalid_data;
  }

  Data_Value value = this->ready.front();
  for (int i = 0; i < this->ready.size() - 1; i++) {
    this->ready[i] = this->ready[i + 1];
  }
  this->ready[this->ready.size() - 1] = invalid_data;
  return value;
}

void BUS::simulate() {
  cout << "==> Simulating BUS " << this->getLabel() << '\n';

  int i;
  Data_Value invalid_data;

  cout << "ready | pending (before simulate)" << '\n';
  for (i = 0; i < this->width; i++){
    std::cout << this->ready[i].getValue() << " <- " << this->pending[i].getValue() <<  '\n';
  }
  for (i = 0; i < this->width; i++){
    this->ready[i] = this->pending[i];
    this->pending[i] = invalid_data;
  }

  Data_Value value;

  // then it reads at most W times from its source,
  // stopping as soon as an invalid value is obtained.
  // W is the width of the Bus. All the read values (but the invalid one) are stored as pending.
  std::cout << "Reading " << this->width << " values from " << this->source_label << '\n';
  for (int i = 0; i < this->width; i++) {
    value = this->source->read();

    if (value.isValid()) {
      this->pending[i] = value;
    }
    else break;
  }
  cout << "ready | pending (after simulate)" << '\n';
  for (i = 0; i < this->width; i++){
    std::cout << this->ready[i].getValue() << " <- " << this->pending[i].getValue() <<  '\n';
  }

  std::cout << '\n';

}

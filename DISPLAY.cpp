#include "modules.hpp"
#include "interfaces.hpp"
#include "elements.hpp"
#include <iostream>
#include <sstream>
#include <map>

using namespace std;

// DISPLAY

DISPLAY::DISPLAY(string path) {
  /* takes a .txt text file with the discription of the DISPLAY
  At this point we know already its a DISPLAY
  We always consider that there's never a problem with syntax,
  to simplify, there's no error verification
  There will always be 3 lines described this way

  -- Example --
  TYPE: DISPLAY
  REFRESH: 8
  SOURCE: DRAM 1
  */

  // Read file from path
  string line, element;
  ifstream myfile (path);
  if (myfile.is_open()) {
    while (! myfile.eof() ) {
      getline (myfile,line); // discart first line : we know its a DISPLAY

      // REFRESH
      getline(myfile,line);
      istringstream iss_refresh(line);
      iss_refresh >> element;
      if (element != "REFRESH:") { cout << "ERROR in REFRESH syntax" << '\n'; exit(0);}
      this->refresh_rate = stoi(iss_refresh.str().substr(8));

      // SOURCE
      getline(myfile,line);
      istringstream iss_source(line);
      iss_source >> element;
      if (element != "SOURCE:") { cout << "ERROR in SOURCE syntax" << '\n'; exit(0);}
      string source = iss_source.str().substr(8);
      this->source_label = source;

      this->writeLabel("DISPLAY");

      cout << "==> DISPLAY created with source '" << source << "'"<< endl;
      cout << "refresh_rate: " << this->refresh_rate << endl << '\n';

    }
    myfile.close();
  }
}

void DISPLAY::simulate() {
  cout << "==> Simulating DISPLAY" << '\n';
  cout << "Showing data from " << this->source_label << '\n';

  // When DISPLAY reacts it reads all data from source until invalid value
  Data_Value value = this->source->read();

  cout << "-- DISPLAY --" << '\n';
  while (value.isValid()) {
    cout << value.getValue() << '\n';
    value = this->source->read();
  }

  std::cout << '\n';
}

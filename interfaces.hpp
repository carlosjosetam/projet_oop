#ifndef COMPONENT_HHP
#define COMPONENT_HHP

#include <iostream>
#include <string>
using namespace std;

class Component {
	string label;

public:
	string getLabel() { return this->label; };
	void writeLabel(string label) { this->label = label; };
  virtual void simulate() = 0;
};

#endif

#ifndef READABLE_HHP
#define READABLE_HHP

#include <iostream>
#include "elements.hpp"
using namespace std;

class Readable {
public:
  virtual Data_Value read() = 0;
};

#endif

#ifndef BINDABLE_HHP
#define BINDABLE_HHP

#include <iostream>
using namespace std;

class Bindable {
public:
	Readable * source;
	string source_label;
  
};

#endif

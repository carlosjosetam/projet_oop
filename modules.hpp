#ifndef CPU_HHP
#define CPU_HHP

#include <iostream>
#include <string>
#include "interfaces.hpp"
#include "elements.hpp"

using namespace std;

class CPU : public Readable, public Component {
private:
  CPU_Program * program;
  CPU_Register internal_register;
  int frequency;
  int n_cores;
  int active_core;


public:
  CPU (string path);
  Data_Value read();
  void simulate();
};

#endif

#ifndef BUS_HHP
#define BUS_HHP

#include <iostream>
#include <string>
#include <vector>

#include "interfaces.hpp"
#include "elements.hpp"

using namespace std;

class BUS : public Readable, public Component, public Bindable {
private:
  int width;
  int count_read = 0;

  vector<Data_Value> pending;
  vector<Data_Value> ready;

public:
  BUS (string path);
  Data_Value read();
  void simulate();
};

#endif

#ifndef MEMORY_HHP
#define MEMORY_HHP

#include <iostream>
#include <string>
#include <list>

#include "interfaces.hpp"
#include "elements.hpp"

using namespace std;

class MEMORY : public Readable, public Component, public Bindable {
private:
  int size;
  int access_time;

  list<Data_Value> data;

public:
  MEMORY (string path);
  Data_Value read();
  void simulate();

};

#endif

#ifndef DISPLAY_HHP
#define DISPLAY_HHP

#include <iostream>
#include <string>
#include <list>

#include "interfaces.hpp"
#include "elements.hpp"

using namespace std;

class DISPLAY : public Component, public Bindable {
private:
  int refresh_rate;

public:
  DISPLAY (string path);
  void simulate();

};

#endif

#ifndef PLATFORM_HHP
#define PLATFORM_HHP

#include <iostream>
#include <string>
#include <list>

#include "interfaces.hpp"
#include "elements.hpp"

using namespace std;

class PLATFORM {
private:
  vector<CPU * > cpu_vector;
  vector<BUS * > bus_vector;
  vector<MEMORY * > memory_vector;
  vector<DISPLAY * > display_vector;

  Readable * find_source(string source_label);

public:
  PLATFORM (string path);
  void simulate();
  void bind();
};

#endif

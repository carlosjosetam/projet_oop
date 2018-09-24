src = $(wildcard *.cpp)
obj = $(src:.cpp=.o)
MYPROGRAM = test
CC = g++

LDFLAGS =

all: $(MYPROGRAM)

$(MYPROGRAM): $(src)

	$(CC) -std=c++11 $(src) -o$(MYPROGRAM)

clean:
	rm -f $(MYPROGRAM)

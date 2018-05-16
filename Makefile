CXX = g++
CXX_FLAGS = -Wall
PROGNAME = prog
OBJS = util.o xor_cipher.o

# This is just to avoid running clean if no argument is given to make.
default:
	@echo "usage: make [setname]"

clean:
	rm -f $(OBJS)
	rm -f "$(PROGNAME)"

set11: $(OBJS)
	$(CXX) $(CXX_FLAGS) set11.cpp $^ -o $(PROGNAME)

set12: $(OBJS)
	$(CXX) $(CXX_FLAGS) set12.cpp $^ -o $(PROGNAME)

set13: $(OBJS)
	$(CXX) $(CXX_FLAGS) set13.cpp $^ -o $(PROGNAME)

set14: $(OBJS)
	$(CXX) $(CXX_FLAGS) set14.cpp $^ -o $(PROGNAME)

set15: $(OBJS)
	$(CXX) $(CXX_FLAGS) set15.cpp $^ -o $(PROGNAME)

set16: $(OBJS)
	$(CXX) $(CXX_FLAGS) set16.cpp $^ -o $(PROGNAME)

set17: $(OBJS) aes.hpp
	$(CXX) $(CXX_FLAGS) -lcrypto++ set16.cpp $^ -o $(PROGNAME)

.PHONY: clean

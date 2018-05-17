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

set1: $(OBJS)
	$(CXX) $(CXX_FLAGS) set1/1.cpp $^ -o $(PROGNAME)

set2: $(OBJS)
	$(CXX) $(CXX_FLAGS) set1/2.cpp $^ -o $(PROGNAME)

set3: $(OBJS)
	$(CXX) $(CXX_FLAGS) set1/3.cpp $^ -o $(PROGNAME)

set4: $(OBJS)
	$(CXX) $(CXX_FLAGS) set1/4.cpp $^ -o $(PROGNAME)

set5: $(OBJS)
	$(CXX) $(CXX_FLAGS) set1/5.cpp $^ -o $(PROGNAME)

set6: $(OBJS)
	$(CXX) $(CXX_FLAGS) set1/6.cpp $^ -o $(PROGNAME)

set7: $(OBJS)
	$(CXX) $(CXX_FLAGS) -lcrypto++ set1/7.cpp $^ -o $(PROGNAME)

.PHONY: clean

CXX       = g++
CXXFLAGS  = -g -O2 -Wall -c
LDFLAGS   = -g -O2 -Wall -lGL -lglut
RM        = rm -f
EXEC      = a.out

all: $(EXEC)

$(EXEC): minigl.o main.o
	$(CXX) $^ -o $@ $(LDFLAGS)

minigl.o: minigl.cpp minigl.h
	$(CXX) $(CXXFLAGS) $< -o $@

main.o: main.cpp minigl.h
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	$(RM) *~ *.bak *.o $(EXEC)

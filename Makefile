#Project Othello

DIR = bin
BIN = $(DIR)/Othello
OBJ = $(DIR)/main.o $(DIR)/AI.o $(DIR)/error.o $(DIR)/init.o $(DIR)/IO.o $(DIR)/operations.o $(DIR)/UI.o
LIB = -Lfreeglut -Wl,-Bstatic -lglut -Wl,-Bdynamic -lGL -lX11 -lXxf86vm -g3
CXX = g++
CXXFLAGS = -I"freeglut_l/include" -Wall -g3

.PHONY: test clean cleanbackup cb win

$(BIN): $(DIR) $(OBJ)
	$(CXX) $(OBJ) -o $(BIN) $(LIB)

$(DIR):
	mkdir $(DIR)

test : $(BIN)
	./$(BIN)

$(DIR)/main.o : main.cpp base.h declaration.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(DIR)/AI.o : AI.cpp base.h extern.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(DIR)/error.o : error.cpp base.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(DIR)/init.o : init.cpp base.h extern.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(DIR)/IO.o : IO.cpp base.h extern.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(DIR)/operations.o : operations.cpp base.h extern.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(DIR)/UI.o : UI.cpp base.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

cleanbackup :
	rm -vf *~ *.orig .*~

cb : cleanbackup

clean :
	rm -vf $(BIN) $(OBJ)

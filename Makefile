#Project Othello

DIR = bin
BIN = $(DIR)/Othello
OBJ = $(DIR)/main.o $(DIR)/AI.o $(DIR)/error.o $(DIR)/init.o $(DIR)/IO.o $(DIR)/operations.o $(DIR)/UI.o $(DIR)/declarations.o $(DIR)/board.o
LIB = -Lfreeglut -Wl,-Bstatic -lglut -Wl,-Bdynamic -lGL -lX11 -lXxf86vm -g3
CXX = g++
CXXFLAGS = -I"freeglut_l/include" -Wall -g3 -std=c++0x

.PHONY: test clean cleanbackup cb win

$(BIN): $(DIR) $(OBJ)
	$(CXX) $(OBJ) -o $(BIN) $(LIB)

$(DIR):
	mkdir $(DIR)

test : $(BIN)
	./$(BIN)

AIbase.h : base.h

elements.h : base.h

$(DIR)/main.o : main.cpp elements.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(DIR)/AI.o : AI.cpp elements.h AIbase.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(DIR)/error.o : error.cpp base.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(DIR)/init.o : init.cpp elements.h AIbase.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(DIR)/IO.o : IO.cpp elements.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(DIR)/operations.o : operations.cpp elements.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(DIR)/UI.o : UI.cpp elements.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(DIR)/declarations.o : declarations.cpp elements.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(DIR)/board.o : board.cpp elements.h
	$(CXX) $(CXXFLAGS) -c $< -o $@


cleanbackup :
	rm -vf *~ *.orig .*~

cb : cleanbackup

clean :
	rm -vf $(BIN) $(OBJ)

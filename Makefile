#Project JetOthello

DIR = bin
BIN = $(DIR)/JetOthello
OBJ = $(DIR)/main.o $(DIR)/UI.o $(DIR)/error.o $(DIR)/init.o $(DIR)/IO.o $(DIR)/Jacob.o $(DIR)/board.o
LIB = -Lfreeglut -Wl,-Bstatic -lglut -Wl,-Bdynamic -lXxf86vm -g3 -lpthread -lGL -lX11 -lXi -lXrandr
CXX = g++
CXXFLAGS = -I"freeglut/include" -Wall -g3 -ofast -std=c++11

.PHONY: test clean cleanbackup cb win

$(BIN): $(DIR) $(OBJ)
	$(CXX) $(OBJ) -o $(BIN) $(LIB)

$(DIR):
	mkdir $(DIR)

test : $(BIN)
	./$(BIN)

elements.h : base.h

board.h : elements.h

init.h : elements.h

IO.h : elements.h

Jacob.h : base.h

main.h : elements.h

UI.h : elements.h

$(DIR)/main.o : main.cpp main.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(DIR)/UI.o : UI.cpp UI.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(DIR)/error.o : error.cpp base.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(DIR)/init.o : init.cpp init.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(DIR)/IO.o : IO.cpp IO.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(DIR)/Jacob.o : Jacob.cpp elements.h Jacob.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(DIR)/board.o : board.cpp board.h
	$(CXX) $(CXXFLAGS) -c $< -o $@


cleanbackup :
	rm -vf *~ *.orig .*~

cb : cleanbackup

clean :
	rm -vf $(BIN) $(OBJ)

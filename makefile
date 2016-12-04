# Object files to either reference or create
SOURCE = main.cpp class/Battalion.cpp class/Citizen.cpp class/Polis.cpp class/Soldier.cpp class/Archer.cpp class/Lancer.cpp class/Knave.cpp class/Knight.cpp class/Peltast.cpp class/Hoplite.cpp class/Pezhetairos.cpp class/Worker.cpp class/Barrack.cpp class/Cave.cpp class/Edifice.cpp class/Farm.cpp class/Mine.cpp class/Temple.cpp class/Wall.cpp class/Player.cpp class/Library.cpp class/cpuPlayer.cpp class/cpuPlayer.cpp
OBJECTS = main.o class/Battalion.o class/Citizen.o class/Polis.o class/Soldier.o class/Archer.o class/Lancer.o class/Knave.o class/Knight.o class/Peltast.o class/Hoplite.o class/Pezhetairos.o class/Worker.o class/Barrack.o class/Cave.o class/Edifice.o class/Farm.o class/Mine.o class/Temple.o class/Wall.o class/Player.o class/Library.o class/cpuPlayer.o class/cpuPlayer.o
# The executable file that will be created at the end
EXEC = bin/main.out

# The flags to use for compilation
CXXFLAGS = -Wall

# The code compiler to use for compilation
CC=g++ -std=c++11

compila:$(OBJECTS)
	$(CC) $(CXXFLAGS) -o $(EXEC) $(OBJECTS)
	@echo " "
	@echo "Compilazione completata!"
	@echo " "
	mv $(OBJECTS) build/

clean:
	rm build/*.o
rm $(EXEC)
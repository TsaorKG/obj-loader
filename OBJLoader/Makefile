#------------------------------------------------------------------------------

SOURCE=main.cpp mesh.cpp utilities.cpp vector.cpp
MYPROGRAM=prog
#MYINCLUDES=/home/scale/g++Projects/gLib/

MYLIBRARIES=-lGL -lGLU -lglut
CC=g++

#------------------------------------------------------------------------------



all: $(MYPROGRAM)



$(MYPROGRAM): $(SOURCE)

	$(CC) $(SOURCE) -o$(MYPROGRAM) $(MYLIBRARIES)

clean:

	rm -f $(MYPROGRAM)
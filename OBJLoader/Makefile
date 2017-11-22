#------------------------------------------------------------------------------

SOURCE=main.cpp mesh.cpp utilities.cpp vector.cpp
MYPROGRAM=prog

MYLIBRARIES=-lGL -lGLU -lglut
CC=g++

#------------------------------------------------------------------------------



all: $(MYPROGRAM)



$(MYPROGRAM): $(SOURCE)

	$(CC) $(SOURCE) -o$(MYPROGRAM) $(MYLIBRARIES)

clean:

	rm -f $(MYPROGRAM)
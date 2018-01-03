#------------------------------------------------------------------------------

SOURCE=main.cpp mesh.cpp utilities.cpp vector.cpp texture.cpp
MYPROGRAM=OBJLoader

MYLIBRARIES=-lGL -lGLU -lglut -ljpeg
CC=g++

#------------------------------------------------------------------------------



all: $(MYPROGRAM)



$(MYPROGRAM): $(SOURCE)

	$(CC) $(SOURCE) -o$(MYPROGRAM) $(MYLIBRARIES)

clean:

	rm -f $(MYPROGRAM)

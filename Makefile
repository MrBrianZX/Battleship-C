CC = gcc
CFLAGS = -Wall -Wextra -I./libs
LDFLAGS = -L./libs
TARGET = programa
SRC = main.c
LIB_SRC = $(wildcard ./libs/*.c)  # Todos los archivos fuente en la carpeta libs
LIB_OBJ = $(LIB_SRC:.c=.o)  # Archivos objeto de la biblioteca
LIBRARY = .\libs\terminalFX.a  # Nombre de la biblioteca estática a generar

all: $(TARGET)

$(TARGET): $(SRC) $(LIBRARY)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET) $(SRC) $(LIBRARY)

$(LIBRARY): $(LIB_OBJ)
	ar rcs $(LIBRARY) $(LIB_OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del $(TARGET).exe $(LIBRARY) $(LIBRARY:.a=.o)

CC=clang
CFLAGS=-Iinclude
SRCDIR=src
OBJDIR=obj
BINDIR=bin
EXECUTABLE=run

SOURCES := $(shell find $(SRCDIR) -type f -name '*.c')
OBJECTS := $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SOURCES))

all: directories $(EXECUTABLE)

directories:
	@mkdir -p $(dir $(OBJECTS))
	@mkdir -p $(BINDIR)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(BINDIR)/$(EXECUTABLE)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(CC) -c $< $(CFLAGS) -o $@

clean:
	rm -f $(OBJDIR)/*.o $(OBJDIR)/**/*.o
	rm -f $(BINDIR)/$(EXECUTABLE)
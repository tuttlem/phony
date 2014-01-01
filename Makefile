# Phony game base code makefile

CC := g++
SRCDIR := src
BUILDDIR := build
CFLAGS := -g -Wall -Ilibs/SFML-2.1/include
TARGET := bin/phony
LFLAGS := -Llibs/SFML-2.1/lib -lsfml-graphics -lsfml-window -lsfml-system -lGL -lGLU

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
DEPS := $(OBJECTS:.o=.deps)

$(TARGET): $(OBJECTS)
	@echo " Linking..."; $(CC) $^ $(LFLAGS) -o $(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@mkdir -p $(BUILDDIR)/fwk
	@mkdir -p $(BUILDDIR)/util
	@echo " CC $<"; $(CC) $(CFLAGS) -MD -MF $(@:.o=.deps) -c -o $@ $<

clean:
	@echo " Cleaning..."; $(RM) -r $(BUILDDIR) $(TARGET)

-include $(DEPS)

.PHONY: clean

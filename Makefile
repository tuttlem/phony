# Phony game base code makefile

CC := g++
SRCDIR := src
BUILDDIR := build
CFLAGS := -g -std=c++11 -Wall -fPIC -Ilibs/glm `pkg-config --cflags sdl2 SDL2_mixer`
TARGET := bin/phony
LFLAGS := `pkg-config --libs sdl2 SDL2_mixer SDL2_ttf` -lGL -lGLU -lpthread -llua -ldl

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
DEPS := $(OBJECTS:.o=.deps)

$(TARGET): $(OBJECTS)
	@echo " Linking..."; $(CC) $^ $(LFLAGS) -o $(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@mkdir -p $(BUILDDIR)/phony/util
	@mkdir -p $(BUILDDIR)/phony/fwk
	@echo " CC $<"; $(CC) $(CFLAGS) -MD -MF $(@:.o=.deps) -c -o $@ $<

clean:
	@echo " Cleaning..."; $(RM) -r $(BUILDDIR) $(TARGET)

-include $(DEPS)

.PHONY: clean

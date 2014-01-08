# Phony game base code makefile

CC := g++
SRCDIR := src
BUILDDIR := build
CFLAGS := -g -std=c++11 -Wall -Ilibs/lua-5.2.3/include `pkg-config --cflags sdl2`
TARGET := bin/phony
LFLAGS := -Llibs/lua-5.2.3/lib/ `pkg-config --libs sdl2` -lGL -lGLU -lpthread -llua -ldl

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

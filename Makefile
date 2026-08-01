# All-In-One Makefile for small/medium C projects.
# Directory-based build system: drop .c files under src/ and it just works.
#
# Layout:
#   inc/           public headers (incl. your single-header library, e.g. inc/maya.h)
#   lib/           external/vendor libraries to link against (-L), and the
#                  output location for the built shared library
#   src/           all your own source
#   src/shared/    source that gets compiled into the shared library
#                  (e.g. a single .c that #defines MAYA_IMPLEMENTATION and
#                  #includes the single-header library)
#   build/         object files + generated .d dependency files
#   bin/           final binary

### Compiler ###
CC := gcc

### BUILD TYPE ###
# Usage: make               (plain build: just the base warnings/std below,
#                             no optimization flags, no sanitizers)
#        make BUILD=debug   (or `make debug`)
#        make BUILD=release (or `make release`)
BUILD ?= default

ifeq ($(BUILD),default)
  # intentionally no extra flags - base CFLAGS below is all you get
else ifeq ($(BUILD),debug)
  CFLAGS  += -g -O0 -DDEBUG -fsanitize=address,undefined -fno-omit-frame-pointer
  LDFLAGS += -fsanitize=address,undefined
else ifeq ($(BUILD),release)
  CFLAGS  += -O2 -DNDEBUG
else
  $(error Unknown BUILD "$(BUILD)"; expected "default", "debug", or "release")
endif

### PROJECT OPTIONS ###
TARGET     := maya
SRCDIR     := src
INCDIR     := inc
LIBDIR     := lib
BUILDROOT  := build
BINROOT    := bin
# The plain/default build keeps the classic flat build/ and bin/ paths;
# debug and release get their own subdirectory so switching between them
# never relinks stale objects built with different flags.
BUILDDIR   := $(if $(filter default,$(BUILD)),$(BUILDROOT),$(BUILDROOT)/$(BUILD))
BINDIR     := $(if $(filter default,$(BUILD)),$(BINROOT),$(BINROOT)/$(BUILD))
SHAREDDIR  := shared

# FLAGS
CPPFLAGS := -I$(INCDIR)
CFLAGS   += -Wall -Wextra -Wpedantic -std=c99
LDFLAGS  += -L$(LIBDIR)
LDLIBS   :=

### FILES ###
# rwildcard: recursive glob using Make's own builtin, no forked `find` process.
rwildcard = $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2)$(filter $(subst *,%,$2),$d))

# Skip source discovery entirely for a bare `make clean` (nothing below needs it).
ifneq ($(MAKECMDGOALS),clean)
SRC       := $(call rwildcard,$(SRCDIR)/,*.c)
SHAREDSRC := $(filter $(SRCDIR)/$(SHAREDDIR)/%,$(SRC))
MAINSRC   := $(filter-out $(SHAREDSRC),$(SRC))
endif

OBJ  := $(MAINSRC:$(SRCDIR)/%.c=$(BUILDDIR)/%.o)
SOBJ := $(SHAREDSRC:$(SRCDIR)/$(SHAREDDIR)/%.c=$(BUILDDIR)/$(SHAREDDIR)/%.o)

DEPS := $(OBJ:.o=.d) $(SOBJ:.o=.d)

BIN    := $(BINDIR)/$(TARGET)
SHARED := $(LIBDIR)/lib$(TARGET).so

### TARGETS ###
.PHONY: all build build-full shared shared-full debug release clean

# Builds the binary always; also builds the .so if src/shared has any sources.
all: build $(if $(SHAREDSRC),shared)

build:       $(BIN)
build-full:  clean build

shared:      $(SHARED)
shared-full: clean shared

# Convenience wrappers. Re-invoke make so BUILD is set before the flag
# conditionals above are evaluated (a plain recipe-body assignment is too late).
debug:
	$(MAKE) BUILD=debug all

release:
	$(MAKE) BUILD=release all

# LINK SHARED LIBRARY
$(SHARED): $(SOBJ) | $(LIBDIR)
	$(CC) -shared -o $@ $^

# LINK BINARY
$(BIN): $(OBJ) | $(BINDIR)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

# COMPILE - shared-library objects (need position-independent code)
$(SOBJ): $(BUILDDIR)/$(SHAREDDIR)/%.o: $(SRCDIR)/$(SHAREDDIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -fPIC -MMD -MP -c $< -o $@

# COMPILE - regular objects
$(OBJ): $(BUILDDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -c $< -o $@

# DIRECTORIES
$(BINDIR) $(LIBDIR):
	mkdir -p $@

# CLEAN — wipes both debug/ and release/ trees, not just the current BUILD
clean:
	rm -rf $(BUILDROOT) $(BINROOT) $(SHARED)

# DEPENDENCIES
-include $(DEPS)
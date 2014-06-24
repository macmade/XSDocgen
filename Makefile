#-------------------------------------------------------------------------------
# The MIT License (MIT)
# 
# Copyright (c) 2014 Jean-David Gadina - www-xs-labs.com
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#-------------------------------------------------------------------------------


# $Id$

#-------------------------------------------------------------------------------
# Configuration
#-------------------------------------------------------------------------------

CC                              := clang
OPTIM                           := Os

#-------------------------------------------------------------------------------
# Products
#-------------------------------------------------------------------------------

PRODUCT                         := XSDocgen

#-------------------------------------------------------------------------------
# Paths
#-------------------------------------------------------------------------------

# Root directory
DIR                             := ./

# Root build directory
DIR_BUILD                       := $(DIR)Build/

# Relative build directories
DIR_BUILD_PRODUCTS              := $(DIR_BUILD)Products/
DIR_BUILD_TEMP                  := $(DIR_BUILD)Intermediates/

# Source directories
DIR_SRC                         := $(DIR)Source/
DIR_INC                         := $(DIR)Source/include/

# Resources directories
DIR_RESOURCES                   := $(DIR)Resources/

#-------------------------------------------------------------------------------
# File suffixes
#-------------------------------------------------------------------------------

# File extensions
EXT_C                           := .c
EXT_H                           := .h
EXT_O                           := .o

# Adds the suffixes used in this file
.SUFFIXES: $(EXT_C) $(EXT_H) $(EXT_O)

#-------------------------------------------------------------------------------
# Search paths
#-------------------------------------------------------------------------------

# Define the search paths for source files
vpath %$(EXT_C) $(DIR_SRC)
vpath %$(EXT_H) $(DIR_INC)

#-------------------------------------------------------------------------------
# Files
#-------------------------------------------------------------------------------

# Gets every C file in a specific source directory
_GET_C_FILES    = $(foreach dir,$(1), $(wildcard $(dir)*$(EXT_C)))

# Gets every C file in the source directories
_FILES_C       += $(call _GET_C_FILES, $(DIR_SRC))

# Gets only the file name of the C files
_FILES_C_REL    = $(subst $(DIR_SRC),,$(_FILES_C))

# Replace the code extension by the object one
_FILES_C_OBJ    = $(subst $(EXT_C),$(EXT_O),$(_FILES_C_REL))

# Prefix all object files with the build directory for each platform
_FILES_C_BUILD  = $(addprefix $(DIR_BUILD_TEMP),$(_FILES_C_OBJ))

#-------------------------------------------------------------------------------
# Commands configuration
#-------------------------------------------------------------------------------

_CC = $(CC) -Werror -$(OPTIM) -std=c99 -fno-strict-aliasing -I$(DIR_INC)

#-------------------------------------------------------------------------------
# Display
#-------------------------------------------------------------------------------

# Terminal colors
COLOR_NONE                              := "\x1b[0m"
COLOR_GRAY                              := "\x1b[30;01m"
COLOR_RED                               := "\x1b[31;01m"
COLOR_GREEN                             := "\x1b[32;01m"
COLOR_YELLOW                            := "\x1b[33;01m"
COLOR_BLUE                              := "\x1b[34;01m"
COLOR_PURPLE                            := "\x1b[35;01m"
COLOR_CYAN                              := "\x1b[36;01m"

# Pretty printing
_PRINT_FILE = $(call _PRINT,$(1),"$(COLOR_GRAY)"$(notdir $(2)))
_PRINT      = "["$(COLOR_GREEN)" XSDocgen "$(COLOR_NONE)"]> $(1): "$(COLOR_YELLOW)"$(2)"$(COLOR_NONE)

#-------------------------------------------------------------------------------
# Built-in targets
#-------------------------------------------------------------------------------

# Declaration for phony targets, to avoid problems with local files
.PHONY: all             \
        clean           \
        test            \
        install

# Declaration for precious targets, to avoid cleaning of intermediate files
.PRECIOUS:  $(DIR_BUILD_TEMP)%$(EXT_O)

#-------------------------------------------------------------------------------
# Phony targets
#-------------------------------------------------------------------------------

# Main Target
all: $(_FILES_C_BUILD)
	
	@echo $(call _PRINT,Build,Linking main executable)
	@$(_CC) -o $(DIR_BUILD_PRODUCTS)$(PRODUCT) $(_FILES_C_BUILD)
	
# Cleans all build files
clean:
	
	@echo $(call _PRINT,Clean,Cleaning all intermediate files)
	@rm -rf $(DIR_BUILD_TEMP)*
	@echo $(call _PRINT,Clean,Cleaning all product files)
	@rm -rf $(DIR_BUILD_PRODUCTS)*

# Test Target
test: all
	
	@echo $(call _PRINT,Test,Testing product)
	@$(DIR_BUILD_PRODUCTS)$(PRODUCT)

# Install Target
install: all
	
	@echo $(call _PRINT,Install,Installing product)
	@install -d -m 755 /usr/local/bin
	@install -d -m 755 /usr/local/share/XSDocgen/CSS/Resources
	@install -d -m 755 /usr/local/share/XSDocgen/PHP/Classes/XS/Docset
	@install -m 644 $(DIR_RESOURCES)headerdoc.config /usr/local/share/XSDocgen
	@install -m 644 $(DIR_RESOURCES)CSS/XSDoc.css /usr/local/share/XSDocgen/CSS
	@install -m 644 $(DIR_RESOURCES)CSS/XSDoc-Old.css /usr/local/share/XSDocgen/CSS
	@for f in $(DIR_RESOURCES)CSS/Resources/*; do install -m 644 $$f /usr/local/share/XSDocgen/CSS/Resources; done
	@for f in $(DIR_RESOURCES)PHP/Classes/XS/*.php; do install -m 644 $$f /usr/local/share/XSDocgen/PHP/Classes/XS; done
	@for f in $(DIR_RESOURCES)PHP/Classes/XS/Docset/*.php; do install -m 644 $$f /usr/local/share/XSDocgen/PHP/Classes/XS/Docset; done
	@install -m 755 $(DIR_BUILD_PRODUCTS)$(PRODUCT) /usr/local/bin

#-------------------------------------------------------------------------------
# Targets with second expansion
#-------------------------------------------------------------------------------

.SECONDEXPANSION:

# Target: i386 object file
$(DIR_BUILD_TEMP)%$(EXT_O): %$(EXT_C)
	
	@echo $(call _PRINT_FILE,"Build",$<)
	@$(_CC) -o $@ -c $<

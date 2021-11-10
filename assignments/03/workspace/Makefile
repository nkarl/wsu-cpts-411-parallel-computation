##################################################################
## MAKEFILE                                                     ##
##################################################################
HDIR            := hdr
SDIR            := src
ODIR            := obj

EXET            := a
OBJS            := main.o unit_a.o

OSRC            := $(addprefix $(ODIR)/, $(OBJS))

CXX             := g++
CLG             := clang++

OMPF            := -fopenmp

CXXFLAGS        := -I$(HDIR) $(OMPF) -g -std=c++2a \
				-Wall -Wextra -Wconversion -pedantic

GCC_CXXFLAGS    := -DMESSAGE='"Compiled with GCC"'
CLNG_CXXFLAGS   := -DMESSAGE='"Compiled with Clang"'


ifeq ($(CXX), g++)
	CXXFLAGS += $(GXX_CXXFLAGS)
else ifeq ($(CXX), clang++)
	CXXFLAGS += $(CLNG_CXXFLAGS)
endif


##################################################################
## BUILD DIRECTIVE                                              ##
##################################################################
all : $(EXET)

$(EXET) : $(OSRC)
	$(CXX) $(CXXFLAGS) $^ -o $@ 

$(ODIR)/%.o : $(SDIR)/%.cpp | $(ODIR)
	$(CXX) $(CXXFLAGS) -c $^ -o $@

# $(EXET) : $(OSRC)
# 	$(CLG) $(CXXFLAGS) $^ -o $@ 

# $(ODIR)/%.o : $(SDIR)/%.cpp | $(ODIR)
# 	$(CLG) $(CXXFLAGS) -c $^ -o $@

$(ODIR):
	@if [ ! -d "$(ODIR)" ]; then mkdir $(ODIR); fi


##################################################################
## CLEAN TASK                                                   ##
##################################################################
.PHONY: clean
clean:
	rm -r $(EXET) $(ODIR)/*

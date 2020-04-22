SYSTEMC   ?= /opt/tools/SystemC/current
ARCH       = linux64

CPPFLAGS  =  -isystem $(SYSTEMC)/include
CXXFLAGS  =  -Wall -g
LDFLAGS   =  -L$(SYSTEMC)/lib-$(ARCH)
LDLIBS    =  -lsystemc

LINK.o = $(CXX) $(LDFLAGS) $(TARGET_ARCH)


all:$(TARGET)

$(TARGET):$(DEPS)

clean:
	rm -f $(TARGET)
	rm -f $(DEPS)

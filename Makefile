CXX=g++
TP_INCLUDE_DIRS=-Ithird-party/include
INCLUDE_DIRS=-Iinclude $(TP_INCLUDE_DIRS)
ERRFLAGS=-Werror -Wall -Wstrict-prototypes
CXXFLAGS=-std=c++17 -O2 $(INCLUDE_DIRS) $(ERRFLAGS)
BINARY_NAME=obft

FORMAT_OBJS = \
	third-party/src/fmt/format.o \
	third-party/src/fmt/os.o

FORMAT_HEADERS = \
	third-party/include/fmt/chrono.h \
	third-party/include/fmt/color.h \
	third-party/include/fmt/compile.h \
	third-party/include/fmt/core.h \
	third-party/include/fmt/format-inl.h \
	third-party/include/fmt/format.h \
	third-party/include/fmt/locale.h \
	third-party/include/fmt/os.h \
	third-party/include/fmt/ostream.h \
	third-party/include/fmt/posix.h \
	third-party/include/fmt/printf.h \
	third-party/include/fmt/ranges.h

OBJS = \
	src/collector.o \
	src/interpreter.o \
	src/ir.o \
	src/main.o \
	src/opts.o \
	src/parser.o \
	$(FORMAT_OBJS)

HEADERS = \
	include/collector.h \
	include/consts.h \
	include/interpreter.h \
	include/ir.h \
	include/opts.h \
	include/parser.h \
	$(FORMAT_HEADERS)

%.o: %.cpp $(HEADERS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(BINARY_NAME): $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS)


.PHONY: clean
clean:
	find . -name '*.[oa]' -exec rm -f {} ';'
	rm -f $(BINARY_NAME)

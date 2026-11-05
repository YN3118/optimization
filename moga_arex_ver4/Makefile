.RECIPEPREFIX := >

CXX := g++
TARGET := main

CXXFLAGS := -std=c++17 -O2 -Wall -Wextra -pedantic -MMD -MP
INCLUDES := -Iinclude -Ithird_party -Ithird_party/WFG_Toolkit

SRC := \
    main.cpp \
    src/parameter.cpp \
    src/population.cpp \
    src/evaluator.cpp \
    src/arex.cpp \
    src/nsga2.cpp \
    src/knn.cpp \
    src/csv_writer.cpp


WFG_SRC := $(wildcard third_party/WFG_Toolkit/*.cpp)

SRCS := $(SRC) $(WFG_SRC)
OBJS := $(SRCS:.cpp=.o)
DEPS := $(OBJS:.o=.d)

.PHONY: all clean run debug

all: $(TARGET)

$(TARGET): $(OBJS)
>$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

%.o: %.cpp
>$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

run: $(TARGET)
>./$(TARGET) -fn WFG1 -M 2 -k 4 -l 20 -p 120 -g 1 -s 1 -o results/test.csv

debug: CXXFLAGS := -std=c++17 -g -O0 -Wall -Wextra -pedantic -MMD -MP
debug: clean $(TARGET)

clean:
>rm -f $(OBJS) $(DEPS) $(TARGET)

-include $(DEPS)
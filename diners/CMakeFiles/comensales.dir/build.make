# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/joaquin/ClionProjects/Restorrente/diners

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/joaquin/ClionProjects/Restorrente/diners

# Include any dependencies generated for this target.
include CMakeFiles/comensales.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/comensales.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/comensales.dir/flags.make

CMakeFiles/comensales.dir/main.cpp.o: CMakeFiles/comensales.dir/flags.make
CMakeFiles/comensales.dir/main.cpp.o: main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joaquin/ClionProjects/Restorrente/diners/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/comensales.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/comensales.dir/main.cpp.o -c /home/joaquin/ClionProjects/Restorrente/diners/main.cpp

CMakeFiles/comensales.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/comensales.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joaquin/ClionProjects/Restorrente/diners/main.cpp > CMakeFiles/comensales.dir/main.cpp.i

CMakeFiles/comensales.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/comensales.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joaquin/ClionProjects/Restorrente/diners/main.cpp -o CMakeFiles/comensales.dir/main.cpp.s

CMakeFiles/comensales.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/comensales.dir/main.cpp.o.requires

CMakeFiles/comensales.dir/main.cpp.o.provides: CMakeFiles/comensales.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/comensales.dir/build.make CMakeFiles/comensales.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/comensales.dir/main.cpp.o.provides

CMakeFiles/comensales.dir/main.cpp.o.provides.build: CMakeFiles/comensales.dir/main.cpp.o


CMakeFiles/comensales.dir/logger/logger.cpp.o: CMakeFiles/comensales.dir/flags.make
CMakeFiles/comensales.dir/logger/logger.cpp.o: logger/logger.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joaquin/ClionProjects/Restorrente/diners/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/comensales.dir/logger/logger.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/comensales.dir/logger/logger.cpp.o -c /home/joaquin/ClionProjects/Restorrente/diners/logger/logger.cpp

CMakeFiles/comensales.dir/logger/logger.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/comensales.dir/logger/logger.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joaquin/ClionProjects/Restorrente/diners/logger/logger.cpp > CMakeFiles/comensales.dir/logger/logger.cpp.i

CMakeFiles/comensales.dir/logger/logger.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/comensales.dir/logger/logger.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joaquin/ClionProjects/Restorrente/diners/logger/logger.cpp -o CMakeFiles/comensales.dir/logger/logger.cpp.s

CMakeFiles/comensales.dir/logger/logger.cpp.o.requires:

.PHONY : CMakeFiles/comensales.dir/logger/logger.cpp.o.requires

CMakeFiles/comensales.dir/logger/logger.cpp.o.provides: CMakeFiles/comensales.dir/logger/logger.cpp.o.requires
	$(MAKE) -f CMakeFiles/comensales.dir/build.make CMakeFiles/comensales.dir/logger/logger.cpp.o.provides.build
.PHONY : CMakeFiles/comensales.dir/logger/logger.cpp.o.provides

CMakeFiles/comensales.dir/logger/logger.cpp.o.provides.build: CMakeFiles/comensales.dir/logger/logger.cpp.o


CMakeFiles/comensales.dir/utils/ipcs/Semaforo.cpp.o: CMakeFiles/comensales.dir/flags.make
CMakeFiles/comensales.dir/utils/ipcs/Semaforo.cpp.o: utils/ipcs/Semaforo.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joaquin/ClionProjects/Restorrente/diners/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/comensales.dir/utils/ipcs/Semaforo.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/comensales.dir/utils/ipcs/Semaforo.cpp.o -c /home/joaquin/ClionProjects/Restorrente/diners/utils/ipcs/Semaforo.cpp

CMakeFiles/comensales.dir/utils/ipcs/Semaforo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/comensales.dir/utils/ipcs/Semaforo.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joaquin/ClionProjects/Restorrente/diners/utils/ipcs/Semaforo.cpp > CMakeFiles/comensales.dir/utils/ipcs/Semaforo.cpp.i

CMakeFiles/comensales.dir/utils/ipcs/Semaforo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/comensales.dir/utils/ipcs/Semaforo.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joaquin/ClionProjects/Restorrente/diners/utils/ipcs/Semaforo.cpp -o CMakeFiles/comensales.dir/utils/ipcs/Semaforo.cpp.s

CMakeFiles/comensales.dir/utils/ipcs/Semaforo.cpp.o.requires:

.PHONY : CMakeFiles/comensales.dir/utils/ipcs/Semaforo.cpp.o.requires

CMakeFiles/comensales.dir/utils/ipcs/Semaforo.cpp.o.provides: CMakeFiles/comensales.dir/utils/ipcs/Semaforo.cpp.o.requires
	$(MAKE) -f CMakeFiles/comensales.dir/build.make CMakeFiles/comensales.dir/utils/ipcs/Semaforo.cpp.o.provides.build
.PHONY : CMakeFiles/comensales.dir/utils/ipcs/Semaforo.cpp.o.provides

CMakeFiles/comensales.dir/utils/ipcs/Semaforo.cpp.o.provides.build: CMakeFiles/comensales.dir/utils/ipcs/Semaforo.cpp.o


CMakeFiles/comensales.dir/parser/Parser.cpp.o: CMakeFiles/comensales.dir/flags.make
CMakeFiles/comensales.dir/parser/Parser.cpp.o: parser/Parser.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joaquin/ClionProjects/Restorrente/diners/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/comensales.dir/parser/Parser.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/comensales.dir/parser/Parser.cpp.o -c /home/joaquin/ClionProjects/Restorrente/diners/parser/Parser.cpp

CMakeFiles/comensales.dir/parser/Parser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/comensales.dir/parser/Parser.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joaquin/ClionProjects/Restorrente/diners/parser/Parser.cpp > CMakeFiles/comensales.dir/parser/Parser.cpp.i

CMakeFiles/comensales.dir/parser/Parser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/comensales.dir/parser/Parser.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joaquin/ClionProjects/Restorrente/diners/parser/Parser.cpp -o CMakeFiles/comensales.dir/parser/Parser.cpp.s

CMakeFiles/comensales.dir/parser/Parser.cpp.o.requires:

.PHONY : CMakeFiles/comensales.dir/parser/Parser.cpp.o.requires

CMakeFiles/comensales.dir/parser/Parser.cpp.o.provides: CMakeFiles/comensales.dir/parser/Parser.cpp.o.requires
	$(MAKE) -f CMakeFiles/comensales.dir/build.make CMakeFiles/comensales.dir/parser/Parser.cpp.o.provides.build
.PHONY : CMakeFiles/comensales.dir/parser/Parser.cpp.o.provides

CMakeFiles/comensales.dir/parser/Parser.cpp.o.provides.build: CMakeFiles/comensales.dir/parser/Parser.cpp.o


CMakeFiles/comensales.dir/procesos/Diner.cpp.o: CMakeFiles/comensales.dir/flags.make
CMakeFiles/comensales.dir/procesos/Diner.cpp.o: procesos/Diner.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joaquin/ClionProjects/Restorrente/diners/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/comensales.dir/procesos/Diner.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/comensales.dir/procesos/Diner.cpp.o -c /home/joaquin/ClionProjects/Restorrente/diners/procesos/Diner.cpp

CMakeFiles/comensales.dir/procesos/Diner.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/comensales.dir/procesos/Diner.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joaquin/ClionProjects/Restorrente/diners/procesos/Diner.cpp > CMakeFiles/comensales.dir/procesos/Diner.cpp.i

CMakeFiles/comensales.dir/procesos/Diner.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/comensales.dir/procesos/Diner.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joaquin/ClionProjects/Restorrente/diners/procesos/Diner.cpp -o CMakeFiles/comensales.dir/procesos/Diner.cpp.s

CMakeFiles/comensales.dir/procesos/Diner.cpp.o.requires:

.PHONY : CMakeFiles/comensales.dir/procesos/Diner.cpp.o.requires

CMakeFiles/comensales.dir/procesos/Diner.cpp.o.provides: CMakeFiles/comensales.dir/procesos/Diner.cpp.o.requires
	$(MAKE) -f CMakeFiles/comensales.dir/build.make CMakeFiles/comensales.dir/procesos/Diner.cpp.o.provides.build
.PHONY : CMakeFiles/comensales.dir/procesos/Diner.cpp.o.provides

CMakeFiles/comensales.dir/procesos/Diner.cpp.o.provides.build: CMakeFiles/comensales.dir/procesos/Diner.cpp.o


CMakeFiles/comensales.dir/utils/Serializador.cpp.o: CMakeFiles/comensales.dir/flags.make
CMakeFiles/comensales.dir/utils/Serializador.cpp.o: utils/Serializador.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joaquin/ClionProjects/Restorrente/diners/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/comensales.dir/utils/Serializador.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/comensales.dir/utils/Serializador.cpp.o -c /home/joaquin/ClionProjects/Restorrente/diners/utils/Serializador.cpp

CMakeFiles/comensales.dir/utils/Serializador.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/comensales.dir/utils/Serializador.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joaquin/ClionProjects/Restorrente/diners/utils/Serializador.cpp > CMakeFiles/comensales.dir/utils/Serializador.cpp.i

CMakeFiles/comensales.dir/utils/Serializador.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/comensales.dir/utils/Serializador.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joaquin/ClionProjects/Restorrente/diners/utils/Serializador.cpp -o CMakeFiles/comensales.dir/utils/Serializador.cpp.s

CMakeFiles/comensales.dir/utils/Serializador.cpp.o.requires:

.PHONY : CMakeFiles/comensales.dir/utils/Serializador.cpp.o.requires

CMakeFiles/comensales.dir/utils/Serializador.cpp.o.provides: CMakeFiles/comensales.dir/utils/Serializador.cpp.o.requires
	$(MAKE) -f CMakeFiles/comensales.dir/build.make CMakeFiles/comensales.dir/utils/Serializador.cpp.o.provides.build
.PHONY : CMakeFiles/comensales.dir/utils/Serializador.cpp.o.provides

CMakeFiles/comensales.dir/utils/Serializador.cpp.o.provides.build: CMakeFiles/comensales.dir/utils/Serializador.cpp.o


CMakeFiles/comensales.dir/utils/ipcs/Fifo.cpp.o: CMakeFiles/comensales.dir/flags.make
CMakeFiles/comensales.dir/utils/ipcs/Fifo.cpp.o: utils/ipcs/Fifo.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joaquin/ClionProjects/Restorrente/diners/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/comensales.dir/utils/ipcs/Fifo.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/comensales.dir/utils/ipcs/Fifo.cpp.o -c /home/joaquin/ClionProjects/Restorrente/diners/utils/ipcs/Fifo.cpp

CMakeFiles/comensales.dir/utils/ipcs/Fifo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/comensales.dir/utils/ipcs/Fifo.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joaquin/ClionProjects/Restorrente/diners/utils/ipcs/Fifo.cpp > CMakeFiles/comensales.dir/utils/ipcs/Fifo.cpp.i

CMakeFiles/comensales.dir/utils/ipcs/Fifo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/comensales.dir/utils/ipcs/Fifo.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joaquin/ClionProjects/Restorrente/diners/utils/ipcs/Fifo.cpp -o CMakeFiles/comensales.dir/utils/ipcs/Fifo.cpp.s

CMakeFiles/comensales.dir/utils/ipcs/Fifo.cpp.o.requires:

.PHONY : CMakeFiles/comensales.dir/utils/ipcs/Fifo.cpp.o.requires

CMakeFiles/comensales.dir/utils/ipcs/Fifo.cpp.o.provides: CMakeFiles/comensales.dir/utils/ipcs/Fifo.cpp.o.requires
	$(MAKE) -f CMakeFiles/comensales.dir/build.make CMakeFiles/comensales.dir/utils/ipcs/Fifo.cpp.o.provides.build
.PHONY : CMakeFiles/comensales.dir/utils/ipcs/Fifo.cpp.o.provides

CMakeFiles/comensales.dir/utils/ipcs/Fifo.cpp.o.provides.build: CMakeFiles/comensales.dir/utils/ipcs/Fifo.cpp.o


CMakeFiles/comensales.dir/utils/ipcs/Lock.cpp.o: CMakeFiles/comensales.dir/flags.make
CMakeFiles/comensales.dir/utils/ipcs/Lock.cpp.o: utils/ipcs/Lock.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joaquin/ClionProjects/Restorrente/diners/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/comensales.dir/utils/ipcs/Lock.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/comensales.dir/utils/ipcs/Lock.cpp.o -c /home/joaquin/ClionProjects/Restorrente/diners/utils/ipcs/Lock.cpp

CMakeFiles/comensales.dir/utils/ipcs/Lock.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/comensales.dir/utils/ipcs/Lock.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joaquin/ClionProjects/Restorrente/diners/utils/ipcs/Lock.cpp > CMakeFiles/comensales.dir/utils/ipcs/Lock.cpp.i

CMakeFiles/comensales.dir/utils/ipcs/Lock.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/comensales.dir/utils/ipcs/Lock.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joaquin/ClionProjects/Restorrente/diners/utils/ipcs/Lock.cpp -o CMakeFiles/comensales.dir/utils/ipcs/Lock.cpp.s

CMakeFiles/comensales.dir/utils/ipcs/Lock.cpp.o.requires:

.PHONY : CMakeFiles/comensales.dir/utils/ipcs/Lock.cpp.o.requires

CMakeFiles/comensales.dir/utils/ipcs/Lock.cpp.o.provides: CMakeFiles/comensales.dir/utils/ipcs/Lock.cpp.o.requires
	$(MAKE) -f CMakeFiles/comensales.dir/build.make CMakeFiles/comensales.dir/utils/ipcs/Lock.cpp.o.provides.build
.PHONY : CMakeFiles/comensales.dir/utils/ipcs/Lock.cpp.o.provides

CMakeFiles/comensales.dir/utils/ipcs/Lock.cpp.o.provides.build: CMakeFiles/comensales.dir/utils/ipcs/Lock.cpp.o


CMakeFiles/comensales.dir/utils/ipcs/signals/SignalHandler.cpp.o: CMakeFiles/comensales.dir/flags.make
CMakeFiles/comensales.dir/utils/ipcs/signals/SignalHandler.cpp.o: utils/ipcs/signals/SignalHandler.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joaquin/ClionProjects/Restorrente/diners/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/comensales.dir/utils/ipcs/signals/SignalHandler.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/comensales.dir/utils/ipcs/signals/SignalHandler.cpp.o -c /home/joaquin/ClionProjects/Restorrente/diners/utils/ipcs/signals/SignalHandler.cpp

CMakeFiles/comensales.dir/utils/ipcs/signals/SignalHandler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/comensales.dir/utils/ipcs/signals/SignalHandler.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joaquin/ClionProjects/Restorrente/diners/utils/ipcs/signals/SignalHandler.cpp > CMakeFiles/comensales.dir/utils/ipcs/signals/SignalHandler.cpp.i

CMakeFiles/comensales.dir/utils/ipcs/signals/SignalHandler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/comensales.dir/utils/ipcs/signals/SignalHandler.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joaquin/ClionProjects/Restorrente/diners/utils/ipcs/signals/SignalHandler.cpp -o CMakeFiles/comensales.dir/utils/ipcs/signals/SignalHandler.cpp.s

CMakeFiles/comensales.dir/utils/ipcs/signals/SignalHandler.cpp.o.requires:

.PHONY : CMakeFiles/comensales.dir/utils/ipcs/signals/SignalHandler.cpp.o.requires

CMakeFiles/comensales.dir/utils/ipcs/signals/SignalHandler.cpp.o.provides: CMakeFiles/comensales.dir/utils/ipcs/signals/SignalHandler.cpp.o.requires
	$(MAKE) -f CMakeFiles/comensales.dir/build.make CMakeFiles/comensales.dir/utils/ipcs/signals/SignalHandler.cpp.o.provides.build
.PHONY : CMakeFiles/comensales.dir/utils/ipcs/signals/SignalHandler.cpp.o.provides

CMakeFiles/comensales.dir/utils/ipcs/signals/SignalHandler.cpp.o.provides.build: CMakeFiles/comensales.dir/utils/ipcs/signals/SignalHandler.cpp.o


# Object files for target comensales
comensales_OBJECTS = \
"CMakeFiles/comensales.dir/main.cpp.o" \
"CMakeFiles/comensales.dir/logger/logger.cpp.o" \
"CMakeFiles/comensales.dir/utils/ipcs/Semaforo.cpp.o" \
"CMakeFiles/comensales.dir/parser/Parser.cpp.o" \
"CMakeFiles/comensales.dir/procesos/Diner.cpp.o" \
"CMakeFiles/comensales.dir/utils/Serializador.cpp.o" \
"CMakeFiles/comensales.dir/utils/ipcs/Fifo.cpp.o" \
"CMakeFiles/comensales.dir/utils/ipcs/Lock.cpp.o" \
"CMakeFiles/comensales.dir/utils/ipcs/signals/SignalHandler.cpp.o"

# External object files for target comensales
comensales_EXTERNAL_OBJECTS =

comensales: CMakeFiles/comensales.dir/main.cpp.o
comensales: CMakeFiles/comensales.dir/logger/logger.cpp.o
comensales: CMakeFiles/comensales.dir/utils/ipcs/Semaforo.cpp.o
comensales: CMakeFiles/comensales.dir/parser/Parser.cpp.o
comensales: CMakeFiles/comensales.dir/procesos/Diner.cpp.o
comensales: CMakeFiles/comensales.dir/utils/Serializador.cpp.o
comensales: CMakeFiles/comensales.dir/utils/ipcs/Fifo.cpp.o
comensales: CMakeFiles/comensales.dir/utils/ipcs/Lock.cpp.o
comensales: CMakeFiles/comensales.dir/utils/ipcs/signals/SignalHandler.cpp.o
comensales: CMakeFiles/comensales.dir/build.make
comensales: CMakeFiles/comensales.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/joaquin/ClionProjects/Restorrente/diners/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX executable comensales"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/comensales.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/comensales.dir/build: comensales

.PHONY : CMakeFiles/comensales.dir/build

CMakeFiles/comensales.dir/requires: CMakeFiles/comensales.dir/main.cpp.o.requires
CMakeFiles/comensales.dir/requires: CMakeFiles/comensales.dir/logger/logger.cpp.o.requires
CMakeFiles/comensales.dir/requires: CMakeFiles/comensales.dir/utils/ipcs/Semaforo.cpp.o.requires
CMakeFiles/comensales.dir/requires: CMakeFiles/comensales.dir/parser/Parser.cpp.o.requires
CMakeFiles/comensales.dir/requires: CMakeFiles/comensales.dir/procesos/Diner.cpp.o.requires
CMakeFiles/comensales.dir/requires: CMakeFiles/comensales.dir/utils/Serializador.cpp.o.requires
CMakeFiles/comensales.dir/requires: CMakeFiles/comensales.dir/utils/ipcs/Fifo.cpp.o.requires
CMakeFiles/comensales.dir/requires: CMakeFiles/comensales.dir/utils/ipcs/Lock.cpp.o.requires
CMakeFiles/comensales.dir/requires: CMakeFiles/comensales.dir/utils/ipcs/signals/SignalHandler.cpp.o.requires

.PHONY : CMakeFiles/comensales.dir/requires

CMakeFiles/comensales.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/comensales.dir/cmake_clean.cmake
.PHONY : CMakeFiles/comensales.dir/clean

CMakeFiles/comensales.dir/depend:
	cd /home/joaquin/ClionProjects/Restorrente/diners && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/joaquin/ClionProjects/Restorrente/diners /home/joaquin/ClionProjects/Restorrente/diners /home/joaquin/ClionProjects/Restorrente/diners /home/joaquin/ClionProjects/Restorrente/diners /home/joaquin/ClionProjects/Restorrente/diners/CMakeFiles/comensales.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/comensales.dir/depend

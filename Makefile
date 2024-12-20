# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/mnt/d/Git/cpl for github/RAMShell"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/mnt/d/Git/cpl for github/RAMShell"

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start "/mnt/d/Git/cpl for github/RAMShell/CMakeFiles" "/mnt/d/Git/cpl for github/RAMShell//CMakeFiles/progress.marks"
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start "/mnt/d/Git/cpl for github/RAMShell/CMakeFiles" 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named ramfs-shell

# Build rule for target.
ramfs-shell: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 ramfs-shell
.PHONY : ramfs-shell

# fast build rule for target.
ramfs-shell/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/ramfs-shell.dir/build.make CMakeFiles/ramfs-shell.dir/build
.PHONY : ramfs-shell/fast

#=============================================================================
# Target rules for targets named git_commit

# Build rule for target.
git_commit: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 git_commit
.PHONY : git_commit

# fast build rule for target.
git_commit/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/git_commit.dir/build.make CMakeFiles/git_commit.dir/build
.PHONY : git_commit/fast

fs/ramfs.o: fs/ramfs.c.o
.PHONY : fs/ramfs.o

# target to build an object file
fs/ramfs.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/ramfs-shell.dir/build.make CMakeFiles/ramfs-shell.dir/fs/ramfs.c.o
.PHONY : fs/ramfs.c.o

fs/ramfs.i: fs/ramfs.c.i
.PHONY : fs/ramfs.i

# target to preprocess a source file
fs/ramfs.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/ramfs-shell.dir/build.make CMakeFiles/ramfs-shell.dir/fs/ramfs.c.i
.PHONY : fs/ramfs.c.i

fs/ramfs.s: fs/ramfs.c.s
.PHONY : fs/ramfs.s

# target to generate assembly for a file
fs/ramfs.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/ramfs-shell.dir/build.make CMakeFiles/ramfs-shell.dir/fs/ramfs.c.s
.PHONY : fs/ramfs.c.s

main.o: main.c.o
.PHONY : main.o

# target to build an object file
main.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/ramfs-shell.dir/build.make CMakeFiles/ramfs-shell.dir/main.c.o
.PHONY : main.c.o

main.i: main.c.i
.PHONY : main.i

# target to preprocess a source file
main.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/ramfs-shell.dir/build.make CMakeFiles/ramfs-shell.dir/main.c.i
.PHONY : main.c.i

main.s: main.c.s
.PHONY : main.s

# target to generate assembly for a file
main.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/ramfs-shell.dir/build.make CMakeFiles/ramfs-shell.dir/main.c.s
.PHONY : main.c.s

sh/shell.o: sh/shell.c.o
.PHONY : sh/shell.o

# target to build an object file
sh/shell.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/ramfs-shell.dir/build.make CMakeFiles/ramfs-shell.dir/sh/shell.c.o
.PHONY : sh/shell.c.o

sh/shell.i: sh/shell.c.i
.PHONY : sh/shell.i

# target to preprocess a source file
sh/shell.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/ramfs-shell.dir/build.make CMakeFiles/ramfs-shell.dir/sh/shell.c.i
.PHONY : sh/shell.c.i

sh/shell.s: sh/shell.c.s
.PHONY : sh/shell.s

# target to generate assembly for a file
sh/shell.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/ramfs-shell.dir/build.make CMakeFiles/ramfs-shell.dir/sh/shell.c.s
.PHONY : sh/shell.c.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... git_commit"
	@echo "... ramfs-shell"
	@echo "... fs/ramfs.o"
	@echo "... fs/ramfs.i"
	@echo "... fs/ramfs.s"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
	@echo "... sh/shell.o"
	@echo "... sh/shell.i"
	@echo "... sh/shell.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system


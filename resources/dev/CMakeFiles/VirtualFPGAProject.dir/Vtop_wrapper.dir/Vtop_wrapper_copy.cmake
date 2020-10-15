# Verilated -*- CMake -*-
# DESCRIPTION: Verilator output: CMake include script with class lists
#
# This CMake script lists generated Verilated files, for including in higher level CMake scripts.
# This file is meant to be consumed by the verilate() function,
# which becomes available after executing `find_package(verilator).

### Constants...
set(PERL "perl" CACHE FILEPATH "Perl executable (from $PERL)")
set(VERILATOR_ROOT "/usr/local/share/verilator" CACHE PATH "Path to Verilator kit (from $VERILATOR_ROOT)")

### Compiler flags...
# User CFLAGS (from -CFLAGS on Verilator command line)
set(Vtop_wrapper_USER_CFLAGS )
# User LDLIBS (from -LDFLAGS on Verilator command line)
set(Vtop_wrapper_USER_LDLIBS )

### Switches...
# SystemC output mode?  0/1 (from --sc)
set(Vtop_wrapper_SC 0)
# Coverage output mode?  0/1 (from --coverage)
set(Vtop_wrapper_COVERAGE 0)
# Threaded output mode?  0/1/N threads (from --threads)
set(Vtop_wrapper_THREADS 0)
# VCD Tracing output mode?  0/1 (from --trace)
set(Vtop_wrapper_TRACE_VCD 0)
# FST Tracing output mode? 0/1 (from --fst-trace)
set(Vtop_wrapper_TRACE_FST 0)

### Sources...
# Global classes, need linked once per executable
set(Vtop_wrapper_GLOBAL "${VERILATOR_ROOT}/include/verilated.cpp")
# Generated module classes, non-fast-path, compile with low/medium optimization
set(Vtop_wrapper_CLASSES_SLOW "/home/bugra/Ozu/Projects/VirtualFPGA/resources/dev/CMakeFiles/VirtualFPGAProject.dir/Vtop_wrapper.dir/Vtop_wrapper__Slow.cpp")
# Generated module classes, fast-path, compile with highest optimization
set(Vtop_wrapper_CLASSES_FAST "/home/bugra/Ozu/Projects/VirtualFPGA/resources/dev/CMakeFiles/VirtualFPGAProject.dir/Vtop_wrapper.dir/Vtop_wrapper.cpp")
# Generated support classes, non-fast-path, compile with low/medium optimization
set(Vtop_wrapper_SUPPORT_SLOW "/home/bugra/Ozu/Projects/VirtualFPGA/resources/dev/CMakeFiles/VirtualFPGAProject.dir/Vtop_wrapper.dir/Vtop_wrapper__Syms.cpp")
# Generated support classes, fast-path, compile with highest optimization
set(Vtop_wrapper_SUPPORT_FAST )
# All dependencies
set(Vtop_wrapper_DEPS "/usr/local/bin/verilator_bin" "UDC.v" "top_wrapper.v")
# User .cpp files (from .cpp's on Verilator command line)
set(Vtop_wrapper_USER_CLASSES )

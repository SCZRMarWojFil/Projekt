# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/marcel/Documents/SCZR_2020/Projekt/mq

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/marcel/Documents/SCZR_2020/Projekt/build

# Include any dependencies generated for this target.
include CMakeFiles/producer.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/producer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/producer.dir/flags.make

CMakeFiles/producer.dir/src/producer.cpp.o: CMakeFiles/producer.dir/flags.make
CMakeFiles/producer.dir/src/producer.cpp.o: /home/marcel/Documents/SCZR_2020/Projekt/mq/src/producer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/marcel/Documents/SCZR_2020/Projekt/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/producer.dir/src/producer.cpp.o"
	/usr/bin/x86_64-linux-gnu-g++-10  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/producer.dir/src/producer.cpp.o -c /home/marcel/Documents/SCZR_2020/Projekt/mq/src/producer.cpp

CMakeFiles/producer.dir/src/producer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/producer.dir/src/producer.cpp.i"
	/usr/bin/x86_64-linux-gnu-g++-10 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marcel/Documents/SCZR_2020/Projekt/mq/src/producer.cpp > CMakeFiles/producer.dir/src/producer.cpp.i

CMakeFiles/producer.dir/src/producer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/producer.dir/src/producer.cpp.s"
	/usr/bin/x86_64-linux-gnu-g++-10 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marcel/Documents/SCZR_2020/Projekt/mq/src/producer.cpp -o CMakeFiles/producer.dir/src/producer.cpp.s

CMakeFiles/producer.dir/src/producer.cpp.o.requires:

.PHONY : CMakeFiles/producer.dir/src/producer.cpp.o.requires

CMakeFiles/producer.dir/src/producer.cpp.o.provides: CMakeFiles/producer.dir/src/producer.cpp.o.requires
	$(MAKE) -f CMakeFiles/producer.dir/build.make CMakeFiles/producer.dir/src/producer.cpp.o.provides.build
.PHONY : CMakeFiles/producer.dir/src/producer.cpp.o.provides

CMakeFiles/producer.dir/src/producer.cpp.o.provides.build: CMakeFiles/producer.dir/src/producer.cpp.o


# Object files for target producer
producer_OBJECTS = \
"CMakeFiles/producer.dir/src/producer.cpp.o"

# External object files for target producer
producer_EXTERNAL_OBJECTS =

bin/producer: CMakeFiles/producer.dir/src/producer.cpp.o
bin/producer: CMakeFiles/producer.dir/build.make
bin/producer: /usr/lib/x86_64-linux-gnu/libopencv_shape.so.3.2.0
bin/producer: /usr/lib/x86_64-linux-gnu/libopencv_stitching.so.3.2.0
bin/producer: /usr/lib/x86_64-linux-gnu/libopencv_superres.so.3.2.0
bin/producer: /usr/lib/x86_64-linux-gnu/libopencv_videostab.so.3.2.0
bin/producer: /usr/lib/x86_64-linux-gnu/libopencv_aruco.so.3.2.0
bin/producer: /usr/lib/x86_64-linux-gnu/libopencv_bgsegm.so.3.2.0
bin/producer: /usr/lib/x86_64-linux-gnu/libopencv_bioinspired.so.3.2.0
bin/producer: /usr/lib/x86_64-linux-gnu/libopencv_ccalib.so.3.2.0
bin/producer: /usr/lib/x86_64-linux-gnu/libopencv_datasets.so.3.2.0
bin/producer: /usr/lib/x86_64-linux-gnu/libopencv_dpm.so.3.2.0
bin/producer: /usr/lib/x86_64-linux-gnu/libopencv_face.so.3.2.0
bin/producer: /usr/lib/x86_64-linux-gnu/libopencv_freetype.so.3.2.0
bin/producer: /usr/lib/x86_64-linux-gnu/libopencv_fuzzy.so.3.2.0
bin/producer: /usr/lib/x86_64-linux-gnu/libopencv_hdf.so.3.2.0
bin/producer: /usr/lib/x86_64-linux-gnu/libopencv_line_descriptor.so.3.2.0
bin/producer: /usr/lib/x86_64-linux-gnu/libopencv_optflow.so.3.2.0
bin/producer: /usr/lib/x86_64-linux-gnu/libopencv_plot.so.3.2.0
bin/producer: /usr/lib/x86_64-linux-gnu/libopencv_reg.so.3.2.0
bin/producer: /usr/lib/x86_64-linux-gnu/libopencv_saliency.so.3.2.0
bin/producer: /usr/lib/x86_64-linux-gnu/libopencv_stereo.so.3.2.0
bin/producer: /usr/lib/x86_64-linux-gnu/libopencv_structured_light.so.3.2.0
bin/producer: /usr/lib/x86_64-linux-gnu/libopencv_surface_matching.so.3.2.0
bin/producer: /usr/lib/x86_64-linux-gnu/libopencv_text.so.3.2.0
bin/producer: /usr/lib/x86_64-linux-gnu/libopencv_ximgproc.so.3.2.0
bin/producer: /usr/lib/x86_64-linux-gnu/libopencv_xobjdetect.so.3.2.0
bin/producer: /usr/lib/x86_64-linux-gnu/libopencv_xphoto.so.3.2.0
bin/producer: /usr/lib/x86_64-linux-gnu/libopencv_video.so.3.2.0
bin/producer: /usr/lib/x86_64-linux-gnu/libopencv_viz.so.3.2.0
bin/producer: /usr/lib/x86_64-linux-gnu/libopencv_phase_unwrapping.so.3.2.0
bin/producer: /usr/lib/x86_64-linux-gnu/libopencv_rgbd.so.3.2.0
bin/producer: /usr/lib/x86_64-linux-gnu/libopencv_calib3d.so.3.2.0
bin/producer: /usr/lib/x86_64-linux-gnu/libopencv_features2d.so.3.2.0
bin/producer: /usr/lib/x86_64-linux-gnu/libopencv_flann.so.3.2.0
bin/producer: /usr/lib/x86_64-linux-gnu/libopencv_objdetect.so.3.2.0
bin/producer: /usr/lib/x86_64-linux-gnu/libopencv_ml.so.3.2.0
bin/producer: /usr/lib/x86_64-linux-gnu/libopencv_highgui.so.3.2.0
bin/producer: /usr/lib/x86_64-linux-gnu/libopencv_photo.so.3.2.0
bin/producer: /usr/lib/x86_64-linux-gnu/libopencv_videoio.so.3.2.0
bin/producer: /usr/lib/x86_64-linux-gnu/libopencv_imgcodecs.so.3.2.0
bin/producer: /usr/lib/x86_64-linux-gnu/libopencv_imgproc.so.3.2.0
bin/producer: /usr/lib/x86_64-linux-gnu/libopencv_core.so.3.2.0
bin/producer: CMakeFiles/producer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/marcel/Documents/SCZR_2020/Projekt/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin/producer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/producer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/producer.dir/build: bin/producer

.PHONY : CMakeFiles/producer.dir/build

CMakeFiles/producer.dir/requires: CMakeFiles/producer.dir/src/producer.cpp.o.requires

.PHONY : CMakeFiles/producer.dir/requires

CMakeFiles/producer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/producer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/producer.dir/clean

CMakeFiles/producer.dir/depend:
	cd /home/marcel/Documents/SCZR_2020/Projekt/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/marcel/Documents/SCZR_2020/Projekt/mq /home/marcel/Documents/SCZR_2020/Projekt/mq /home/marcel/Documents/SCZR_2020/Projekt/build /home/marcel/Documents/SCZR_2020/Projekt/build /home/marcel/Documents/SCZR_2020/Projekt/build/CMakeFiles/producer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/producer.dir/depend

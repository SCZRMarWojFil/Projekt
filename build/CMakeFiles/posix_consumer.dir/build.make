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
include CMakeFiles/posix_consumer.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/posix_consumer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/posix_consumer.dir/flags.make

CMakeFiles/posix_consumer.dir/src/posix_consumer.cpp.o: CMakeFiles/posix_consumer.dir/flags.make
CMakeFiles/posix_consumer.dir/src/posix_consumer.cpp.o: /home/marcel/Documents/SCZR_2020/Projekt/mq/src/posix_consumer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/marcel/Documents/SCZR_2020/Projekt/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/posix_consumer.dir/src/posix_consumer.cpp.o"
	/usr/bin/x86_64-linux-gnu-g++-10  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/posix_consumer.dir/src/posix_consumer.cpp.o -c /home/marcel/Documents/SCZR_2020/Projekt/mq/src/posix_consumer.cpp

CMakeFiles/posix_consumer.dir/src/posix_consumer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/posix_consumer.dir/src/posix_consumer.cpp.i"
	/usr/bin/x86_64-linux-gnu-g++-10 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marcel/Documents/SCZR_2020/Projekt/mq/src/posix_consumer.cpp > CMakeFiles/posix_consumer.dir/src/posix_consumer.cpp.i

CMakeFiles/posix_consumer.dir/src/posix_consumer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/posix_consumer.dir/src/posix_consumer.cpp.s"
	/usr/bin/x86_64-linux-gnu-g++-10 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marcel/Documents/SCZR_2020/Projekt/mq/src/posix_consumer.cpp -o CMakeFiles/posix_consumer.dir/src/posix_consumer.cpp.s

CMakeFiles/posix_consumer.dir/src/posix_consumer.cpp.o.requires:

.PHONY : CMakeFiles/posix_consumer.dir/src/posix_consumer.cpp.o.requires

CMakeFiles/posix_consumer.dir/src/posix_consumer.cpp.o.provides: CMakeFiles/posix_consumer.dir/src/posix_consumer.cpp.o.requires
	$(MAKE) -f CMakeFiles/posix_consumer.dir/build.make CMakeFiles/posix_consumer.dir/src/posix_consumer.cpp.o.provides.build
.PHONY : CMakeFiles/posix_consumer.dir/src/posix_consumer.cpp.o.provides

CMakeFiles/posix_consumer.dir/src/posix_consumer.cpp.o.provides.build: CMakeFiles/posix_consumer.dir/src/posix_consumer.cpp.o


# Object files for target posix_consumer
posix_consumer_OBJECTS = \
"CMakeFiles/posix_consumer.dir/src/posix_consumer.cpp.o"

# External object files for target posix_consumer
posix_consumer_EXTERNAL_OBJECTS =

bin/posix_consumer: CMakeFiles/posix_consumer.dir/src/posix_consumer.cpp.o
bin/posix_consumer: CMakeFiles/posix_consumer.dir/build.make
bin/posix_consumer: /usr/lib/x86_64-linux-gnu/libopencv_shape.so.3.2.0
bin/posix_consumer: /usr/lib/x86_64-linux-gnu/libopencv_stitching.so.3.2.0
bin/posix_consumer: /usr/lib/x86_64-linux-gnu/libopencv_superres.so.3.2.0
bin/posix_consumer: /usr/lib/x86_64-linux-gnu/libopencv_videostab.so.3.2.0
bin/posix_consumer: /usr/lib/x86_64-linux-gnu/libopencv_aruco.so.3.2.0
bin/posix_consumer: /usr/lib/x86_64-linux-gnu/libopencv_bgsegm.so.3.2.0
bin/posix_consumer: /usr/lib/x86_64-linux-gnu/libopencv_bioinspired.so.3.2.0
bin/posix_consumer: /usr/lib/x86_64-linux-gnu/libopencv_ccalib.so.3.2.0
bin/posix_consumer: /usr/lib/x86_64-linux-gnu/libopencv_datasets.so.3.2.0
bin/posix_consumer: /usr/lib/x86_64-linux-gnu/libopencv_dpm.so.3.2.0
bin/posix_consumer: /usr/lib/x86_64-linux-gnu/libopencv_face.so.3.2.0
bin/posix_consumer: /usr/lib/x86_64-linux-gnu/libopencv_freetype.so.3.2.0
bin/posix_consumer: /usr/lib/x86_64-linux-gnu/libopencv_fuzzy.so.3.2.0
bin/posix_consumer: /usr/lib/x86_64-linux-gnu/libopencv_hdf.so.3.2.0
bin/posix_consumer: /usr/lib/x86_64-linux-gnu/libopencv_line_descriptor.so.3.2.0
bin/posix_consumer: /usr/lib/x86_64-linux-gnu/libopencv_optflow.so.3.2.0
bin/posix_consumer: /usr/lib/x86_64-linux-gnu/libopencv_plot.so.3.2.0
bin/posix_consumer: /usr/lib/x86_64-linux-gnu/libopencv_reg.so.3.2.0
bin/posix_consumer: /usr/lib/x86_64-linux-gnu/libopencv_saliency.so.3.2.0
bin/posix_consumer: /usr/lib/x86_64-linux-gnu/libopencv_stereo.so.3.2.0
bin/posix_consumer: /usr/lib/x86_64-linux-gnu/libopencv_structured_light.so.3.2.0
bin/posix_consumer: /usr/lib/x86_64-linux-gnu/libopencv_surface_matching.so.3.2.0
bin/posix_consumer: /usr/lib/x86_64-linux-gnu/libopencv_text.so.3.2.0
bin/posix_consumer: /usr/lib/x86_64-linux-gnu/libopencv_ximgproc.so.3.2.0
bin/posix_consumer: /usr/lib/x86_64-linux-gnu/libopencv_xobjdetect.so.3.2.0
bin/posix_consumer: /usr/lib/x86_64-linux-gnu/libopencv_xphoto.so.3.2.0
bin/posix_consumer: /usr/lib/x86_64-linux-gnu/libopencv_video.so.3.2.0
bin/posix_consumer: /usr/lib/x86_64-linux-gnu/libopencv_viz.so.3.2.0
bin/posix_consumer: /usr/lib/x86_64-linux-gnu/libopencv_phase_unwrapping.so.3.2.0
bin/posix_consumer: /usr/lib/x86_64-linux-gnu/libopencv_rgbd.so.3.2.0
bin/posix_consumer: /usr/lib/x86_64-linux-gnu/libopencv_calib3d.so.3.2.0
bin/posix_consumer: /usr/lib/x86_64-linux-gnu/libopencv_features2d.so.3.2.0
bin/posix_consumer: /usr/lib/x86_64-linux-gnu/libopencv_flann.so.3.2.0
bin/posix_consumer: /usr/lib/x86_64-linux-gnu/libopencv_objdetect.so.3.2.0
bin/posix_consumer: /usr/lib/x86_64-linux-gnu/libopencv_ml.so.3.2.0
bin/posix_consumer: /usr/lib/x86_64-linux-gnu/libopencv_highgui.so.3.2.0
bin/posix_consumer: /usr/lib/x86_64-linux-gnu/libopencv_photo.so.3.2.0
bin/posix_consumer: /usr/lib/x86_64-linux-gnu/libopencv_videoio.so.3.2.0
bin/posix_consumer: /usr/lib/x86_64-linux-gnu/libopencv_imgcodecs.so.3.2.0
bin/posix_consumer: /usr/lib/x86_64-linux-gnu/libopencv_imgproc.so.3.2.0
bin/posix_consumer: /usr/lib/x86_64-linux-gnu/libopencv_core.so.3.2.0
bin/posix_consumer: CMakeFiles/posix_consumer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/marcel/Documents/SCZR_2020/Projekt/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin/posix_consumer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/posix_consumer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/posix_consumer.dir/build: bin/posix_consumer

.PHONY : CMakeFiles/posix_consumer.dir/build

CMakeFiles/posix_consumer.dir/requires: CMakeFiles/posix_consumer.dir/src/posix_consumer.cpp.o.requires

.PHONY : CMakeFiles/posix_consumer.dir/requires

CMakeFiles/posix_consumer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/posix_consumer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/posix_consumer.dir/clean

CMakeFiles/posix_consumer.dir/depend:
	cd /home/marcel/Documents/SCZR_2020/Projekt/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/marcel/Documents/SCZR_2020/Projekt/mq /home/marcel/Documents/SCZR_2020/Projekt/mq /home/marcel/Documents/SCZR_2020/Projekt/build /home/marcel/Documents/SCZR_2020/Projekt/build /home/marcel/Documents/SCZR_2020/Projekt/build/CMakeFiles/posix_consumer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/posix_consumer.dir/depend

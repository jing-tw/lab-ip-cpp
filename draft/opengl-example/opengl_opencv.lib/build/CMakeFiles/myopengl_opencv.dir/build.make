# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

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
CMAKE_SOURCE_DIR = /home/jing/test/lab-ip-cpp/draft/opengl-example/opengl_opencv.lib

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jing/test/lab-ip-cpp/draft/opengl-example/opengl_opencv.lib/build

# Include any dependencies generated for this target.
include CMakeFiles/myopengl_opencv.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/myopengl_opencv.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/myopengl_opencv.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/myopengl_opencv.dir/flags.make

CMakeFiles/myopengl_opencv.dir/src/mylib/mylibopengl_opencv.cpp.o: CMakeFiles/myopengl_opencv.dir/flags.make
CMakeFiles/myopengl_opencv.dir/src/mylib/mylibopengl_opencv.cpp.o: ../src/mylib/mylibopengl_opencv.cpp
CMakeFiles/myopengl_opencv.dir/src/mylib/mylibopengl_opencv.cpp.o: CMakeFiles/myopengl_opencv.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jing/test/lab-ip-cpp/draft/opengl-example/opengl_opencv.lib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/myopengl_opencv.dir/src/mylib/mylibopengl_opencv.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/myopengl_opencv.dir/src/mylib/mylibopengl_opencv.cpp.o -MF CMakeFiles/myopengl_opencv.dir/src/mylib/mylibopengl_opencv.cpp.o.d -o CMakeFiles/myopengl_opencv.dir/src/mylib/mylibopengl_opencv.cpp.o -c /home/jing/test/lab-ip-cpp/draft/opengl-example/opengl_opencv.lib/src/mylib/mylibopengl_opencv.cpp

CMakeFiles/myopengl_opencv.dir/src/mylib/mylibopengl_opencv.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/myopengl_opencv.dir/src/mylib/mylibopengl_opencv.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jing/test/lab-ip-cpp/draft/opengl-example/opengl_opencv.lib/src/mylib/mylibopengl_opencv.cpp > CMakeFiles/myopengl_opencv.dir/src/mylib/mylibopengl_opencv.cpp.i

CMakeFiles/myopengl_opencv.dir/src/mylib/mylibopengl_opencv.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/myopengl_opencv.dir/src/mylib/mylibopengl_opencv.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jing/test/lab-ip-cpp/draft/opengl-example/opengl_opencv.lib/src/mylib/mylibopengl_opencv.cpp -o CMakeFiles/myopengl_opencv.dir/src/mylib/mylibopengl_opencv.cpp.s

CMakeFiles/myopengl_opencv.dir/src/mylib/MyPictureCV.cpp.o: CMakeFiles/myopengl_opencv.dir/flags.make
CMakeFiles/myopengl_opencv.dir/src/mylib/MyPictureCV.cpp.o: ../src/mylib/MyPictureCV.cpp
CMakeFiles/myopengl_opencv.dir/src/mylib/MyPictureCV.cpp.o: CMakeFiles/myopengl_opencv.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jing/test/lab-ip-cpp/draft/opengl-example/opengl_opencv.lib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/myopengl_opencv.dir/src/mylib/MyPictureCV.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/myopengl_opencv.dir/src/mylib/MyPictureCV.cpp.o -MF CMakeFiles/myopengl_opencv.dir/src/mylib/MyPictureCV.cpp.o.d -o CMakeFiles/myopengl_opencv.dir/src/mylib/MyPictureCV.cpp.o -c /home/jing/test/lab-ip-cpp/draft/opengl-example/opengl_opencv.lib/src/mylib/MyPictureCV.cpp

CMakeFiles/myopengl_opencv.dir/src/mylib/MyPictureCV.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/myopengl_opencv.dir/src/mylib/MyPictureCV.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jing/test/lab-ip-cpp/draft/opengl-example/opengl_opencv.lib/src/mylib/MyPictureCV.cpp > CMakeFiles/myopengl_opencv.dir/src/mylib/MyPictureCV.cpp.i

CMakeFiles/myopengl_opencv.dir/src/mylib/MyPictureCV.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/myopengl_opencv.dir/src/mylib/MyPictureCV.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jing/test/lab-ip-cpp/draft/opengl-example/opengl_opencv.lib/src/mylib/MyPictureCV.cpp -o CMakeFiles/myopengl_opencv.dir/src/mylib/MyPictureCV.cpp.s

# Object files for target myopengl_opencv
myopengl_opencv_OBJECTS = \
"CMakeFiles/myopengl_opencv.dir/src/mylib/mylibopengl_opencv.cpp.o" \
"CMakeFiles/myopengl_opencv.dir/src/mylib/MyPictureCV.cpp.o"

# External object files for target myopengl_opencv
myopengl_opencv_EXTERNAL_OBJECTS =

libmyopengl_opencv.so: CMakeFiles/myopengl_opencv.dir/src/mylib/mylibopengl_opencv.cpp.o
libmyopengl_opencv.so: CMakeFiles/myopengl_opencv.dir/src/mylib/MyPictureCV.cpp.o
libmyopengl_opencv.so: CMakeFiles/myopengl_opencv.dir/build.make
libmyopengl_opencv.so: /usr/lib/x86_64-linux-gnu/libGL.so
libmyopengl_opencv.so: /usr/lib/x86_64-linux-gnu/libGLU.so
libmyopengl_opencv.so: /usr/local/lib/libopencv_gapi.so.4.1.0
libmyopengl_opencv.so: /usr/local/lib/libopencv_stitching.so.4.1.0
libmyopengl_opencv.so: /usr/local/lib/libopencv_aruco.so.4.1.0
libmyopengl_opencv.so: /usr/local/lib/libopencv_bgsegm.so.4.1.0
libmyopengl_opencv.so: /usr/local/lib/libopencv_bioinspired.so.4.1.0
libmyopengl_opencv.so: /usr/local/lib/libopencv_ccalib.so.4.1.0
libmyopengl_opencv.so: /usr/local/lib/libopencv_dnn_objdetect.so.4.1.0
libmyopengl_opencv.so: /usr/local/lib/libopencv_dpm.so.4.1.0
libmyopengl_opencv.so: /usr/local/lib/libopencv_face.so.4.1.0
libmyopengl_opencv.so: /usr/local/lib/libopencv_freetype.so.4.1.0
libmyopengl_opencv.so: /usr/local/lib/libopencv_fuzzy.so.4.1.0
libmyopengl_opencv.so: /usr/local/lib/libopencv_hfs.so.4.1.0
libmyopengl_opencv.so: /usr/local/lib/libopencv_img_hash.so.4.1.0
libmyopengl_opencv.so: /usr/local/lib/libopencv_line_descriptor.so.4.1.0
libmyopengl_opencv.so: /usr/local/lib/libopencv_quality.so.4.1.0
libmyopengl_opencv.so: /usr/local/lib/libopencv_reg.so.4.1.0
libmyopengl_opencv.so: /usr/local/lib/libopencv_rgbd.so.4.1.0
libmyopengl_opencv.so: /usr/local/lib/libopencv_saliency.so.4.1.0
libmyopengl_opencv.so: /usr/local/lib/libopencv_stereo.so.4.1.0
libmyopengl_opencv.so: /usr/local/lib/libopencv_structured_light.so.4.1.0
libmyopengl_opencv.so: /usr/local/lib/libopencv_superres.so.4.1.0
libmyopengl_opencv.so: /usr/local/lib/libopencv_surface_matching.so.4.1.0
libmyopengl_opencv.so: /usr/local/lib/libopencv_tracking.so.4.1.0
libmyopengl_opencv.so: /usr/local/lib/libopencv_videostab.so.4.1.0
libmyopengl_opencv.so: /usr/local/lib/libopencv_xfeatures2d.so.4.1.0
libmyopengl_opencv.so: /usr/local/lib/libopencv_xobjdetect.so.4.1.0
libmyopengl_opencv.so: /usr/local/lib/libopencv_xphoto.so.4.1.0
libmyopengl_opencv.so: ../libmyopencv.so
libmyopengl_opencv.so: /usr/local/lib/libopencv_shape.so.4.1.0
libmyopengl_opencv.so: /usr/local/lib/libopencv_datasets.so.4.1.0
libmyopengl_opencv.so: /usr/local/lib/libopencv_plot.so.4.1.0
libmyopengl_opencv.so: /usr/local/lib/libopencv_text.so.4.1.0
libmyopengl_opencv.so: /usr/local/lib/libopencv_dnn.so.4.1.0
libmyopengl_opencv.so: /usr/local/lib/libopencv_ml.so.4.1.0
libmyopengl_opencv.so: /usr/local/lib/libopencv_phase_unwrapping.so.4.1.0
libmyopengl_opencv.so: /usr/local/lib/libopencv_optflow.so.4.1.0
libmyopengl_opencv.so: /usr/local/lib/libopencv_ximgproc.so.4.1.0
libmyopengl_opencv.so: /usr/local/lib/libopencv_video.so.4.1.0
libmyopengl_opencv.so: /usr/local/lib/libopencv_objdetect.so.4.1.0
libmyopengl_opencv.so: /usr/local/lib/libopencv_calib3d.so.4.1.0
libmyopengl_opencv.so: /usr/local/lib/libopencv_features2d.so.4.1.0
libmyopengl_opencv.so: /usr/local/lib/libopencv_flann.so.4.1.0
libmyopengl_opencv.so: /usr/local/lib/libopencv_highgui.so.4.1.0
libmyopengl_opencv.so: /usr/local/lib/libopencv_videoio.so.4.1.0
libmyopengl_opencv.so: /usr/local/lib/libopencv_imgcodecs.so.4.1.0
libmyopengl_opencv.so: /usr/local/lib/libopencv_photo.so.4.1.0
libmyopengl_opencv.so: /usr/local/lib/libopencv_imgproc.so.4.1.0
libmyopengl_opencv.so: /usr/local/lib/libopencv_core.so.4.1.0
libmyopengl_opencv.so: CMakeFiles/myopengl_opencv.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jing/test/lab-ip-cpp/draft/opengl-example/opengl_opencv.lib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX shared library libmyopengl_opencv.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/myopengl_opencv.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/myopengl_opencv.dir/build: libmyopengl_opencv.so
.PHONY : CMakeFiles/myopengl_opencv.dir/build

CMakeFiles/myopengl_opencv.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/myopengl_opencv.dir/cmake_clean.cmake
.PHONY : CMakeFiles/myopengl_opencv.dir/clean

CMakeFiles/myopengl_opencv.dir/depend:
	cd /home/jing/test/lab-ip-cpp/draft/opengl-example/opengl_opencv.lib/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jing/test/lab-ip-cpp/draft/opengl-example/opengl_opencv.lib /home/jing/test/lab-ip-cpp/draft/opengl-example/opengl_opencv.lib /home/jing/test/lab-ip-cpp/draft/opengl-example/opengl_opencv.lib/build /home/jing/test/lab-ip-cpp/draft/opengl-example/opengl_opencv.lib/build /home/jing/test/lab-ip-cpp/draft/opengl-example/opengl_opencv.lib/build/CMakeFiles/myopengl_opencv.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/myopengl_opencv.dir/depend

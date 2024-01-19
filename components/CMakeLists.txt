#
# (C) Copyright 2019-2024 Johns Hopkins University (JHU), All Rights Reserved.
#
# --- begin cisst license - do not edit ---
#
# This software is provided "as is" under an open source license, with
# no warranty.  The complete license can be found in license.txt and
# http://www.cisst.org/cisst/license.txt.
#
# --- end cisst license ---

cmake_minimum_required (VERSION 3.10)
project (sawConstraintOptimizer VERSION 1.0.0)

# create a list of required cisst libraries
set (REQUIRED_CISST_LIBRARIES
  cisstCommon
  cisstVector
  cisstNumerical)

find_package (cisst 1.2.1 REQUIRED ${REQUIRED_CISST_LIBRARIES})

if (cisst_FOUND_AS_REQUIRED)

  # load cisst configuration
  include (${CISST_USE_FILE})

  # catkin/ROS paths
  cisst_set_output_path ()

  # create/configure file for find_package (sawConstraintOptimizer)
  set (sawConstraintOptimizer_INCLUDE_DIR
       "${sawConstraintOptimizer_SOURCE_DIR}/include"
       "${sawConstraintOptimizer_BINARY_DIR}/include")
  set (sawConstraintOptimizer_HEADER_DIR "${sawConstraintOptimizer_SOURCE_DIR}/include/sawConstraintOptimizer")
  set (sawConstraintOptimizer_LIBRARY_DIR "${LIBRARY_OUTPUT_PATH}")
  set (sawConstraintOptimizer_LIBRARIES sawConstraintOptimizer)

  # Allow c++ code to find local header files
  include_directories (${sawConstraintOptimizer_INCLUDE_DIR} ${sawConstraintOptimizer_BINARY_DIR})

  # add all config files for this component
  cisst_add_config_files (sawConstraintOptimizer)

  add_library (sawConstraintOptimizer
    ${sawConstraintOptimizer_HEADER_DIR}/sawConstraintOptimizerExport.h
    ${sawConstraintOptimizer_HEADER_DIR}/osaConstrainedOptimization.h
    ${sawConstraintOptimizer_HEADER_DIR}/osaConstraintEquality.h
    ${sawConstraintOptimizer_HEADER_DIR}/osaConstraintInequality.h
    ${sawConstraintOptimizer_HEADER_DIR}/osaConstraintIntervals.h
    ${sawConstraintOptimizer_HEADER_DIR}/osaConstraintPlane.h
    ${sawConstraintOptimizer_HEADER_DIR}/osaEquation.h
    ${sawConstraintOptimizer_HEADER_DIR}/osaObjective.h
    ${sawConstraintOptimizer_HEADER_DIR}/osaObjectiveFreeMotion.h
    code/osaConstrainedOptimization.cpp
    code/osaConstraintIntervals.cpp)

  set_target_properties (sawConstraintOptimizer PROPERTIES
    VERSION ${sawConstraintOptimizer_VERSION}
    FOLDER "sawConstraintOptimizer")
  cisst_target_link_libraries (sawConstraintOptimizer ${REQUIRED_CISST_LIBRARIES})

  # Install target for headers and library
  install (DIRECTORY
    "${sawConstraintOptimizer_SOURCE_DIR}/include/sawConstraintOptimizer"
    "${sawConstraintOptimizer_BINARY_DIR}/include/sawConstraintOptimizer"
    DESTINATION include
    COMPONENT sawConstraintOptimizer-dev)

  install (TARGETS sawConstraintOptimizer
    COMPONENT sawConstraintOptimizer
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)

else (cisst_FOUND_AS_REQUIRED)
  message ("Information: code in ${CMAKE_CURRENT_SOURCE_DIR} will not be compiled, it requires ${REQUIRED_CISST_LIBRARIES}")
endif (cisst_FOUND_AS_REQUIRED)

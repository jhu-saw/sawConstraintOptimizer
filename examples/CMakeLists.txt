#
# (C) Copyright 2011-2024 Johns Hopkins University (JHU), All Rights Reserved.
#
# --- begin cisst license - do not edit ---
#
# This software is provided "as is" under an open source license, with
# no warranty.  The complete license can be found in license.txt and
# http://www.cisst.org/cisst/license.txt.
#
# --- end cisst license ---

cmake_minimum_required (VERSION 3.10)
project (sawConstraintOptimizerExamples VERSION 1.0.0)

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

  # sawConstraintOptimizer has been compiled within cisst, we should find it automatically
  find_package (sawConstraintOptimizer 1.0.0)

  if (sawConstraintOptimizer_FOUND)

    # sawConstraintOptimizer configuration
    include_directories (${sawConstraintOptimizer_INCLUDE_DIR})
    link_directories (${sawConstraintOptimizer_LIBRARY_DIR})

    add_executable (sawConstraintOptimizerExample osaConstrainedOptimizationExample.cpp)
    set_target_properties (sawConstraintOptimizerExample
      PROPERTIES
      COMPONENTS sawConstraintOptimizer-Examples
      FOLDER "sawConstraintOptimizer")

    # link against non cisst libraries and saw components
    target_link_libraries (sawConstraintOptimizerExample
      ${sawConstraintOptimizer_LIBRARIES})

    # link against cisst libraries (and dependencies)
    cisst_target_link_libraries (sawConstraintOptimizerExample ${REQUIRED_CISST_LIBRARIES})

    install (
      TARGETS sawConstraintOptimizerExample
      COMPONENT sawConstraintOptimizer-Examples
      RUNTIME DESTINATION bin
      LIBRARY DESTINATION lib
      ARCHIVE DESTINATION lib)

  else (sawConstraintOptimizer_FOUND)
    message ("Information: code in ${CMAKE_CURRENT_SOURCE_DIR} will not be compiled, it requires sawConstraintOptimizer")
  endif (sawConstraintOptimizer_FOUND)

endif (cisst_FOUND_AS_REQUIRED)

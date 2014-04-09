#
# $Id: CMakeLists.txt 4605 2013-12-12 21:37:52Z adeguet1 $
#
# (C) Copyright 2011-2013 Johns Hopkins University (JHU), All Rights
# Reserved.
#
# --- begin cisst license - do not edit ---
#
# This software is provided "as is" under an open source license, with
# no warranty.  The complete license can be found in license.txt and
# http://www.cisst.org/cisst/license.txt.
#
# --- end cisst license ---

set (REQUIRED_CISST_LIBRARIES
     cisstCommon
     cisstVector
     cisstOSAbstraction
     cisstMultiTask
     cisstParameterTypes
     cisstRobot
     cisstNumerical)

find_package (cisst REQUIRED ${REQUIRED_CISST_LIBRARIES})

if (cisst_FOUND_AS_REQUIRED)

  # load cisst configuration
  include (${CISST_USE_FILE})

  # create/configure file for find_package (sawConstraintController)
  set (sawConstraintController_INCLUDE_DIR "${sawConstraintController_SOURCE_DIR}/include")
  set (sawConstraintController_LIBRARY_DIR "${LIBRARY_OUTPUT_PATH}")
  set (sawConstraintController_LIBRARIES sawConstraintController)

  include_directories (${sawConstraintController_INCLUDE_DIR})
  set (sawConstraintController_HEADER_DIR "${sawConstraintController_INCLUDE_DIR}/sawConstraintController")

  set (HEADER_FILES
       ${sawConstraintController_HEADER_DIR}/osaConstrainedOptimization.h
       ${sawConstraintController_HEADER_DIR}/osaConstraintEquality.h
       ${sawConstraintController_HEADER_DIR}/osaConstraintInequality.h
       ${sawConstraintController_HEADER_DIR}/osaConstraintIntervals.h
       ${sawConstraintController_HEADER_DIR}/osaConstraintPlane.h
       ${sawConstraintController_HEADER_DIR}/osaEquation.h
       ${sawConstraintController_HEADER_DIR}/osaObjective.h
       ${sawConstraintController_HEADER_DIR}/osaObjectiveFreeMotion.h
       ${sawConstraintController_HEADER_DIR}/mtsObjectiveFreeMotion.h)

  set (SOURCE_FILES
       osaConstrainedOptimization.cpp
       osaConstraintIntervals.cpp)

  add_library (sawConstraintController ${HEADER_FILES} ${SOURCE_FILES})
  cisst_target_link_libraries (sawConstraintController ${REQUIRED_CISST_LIBRARIES})
  set_property (TARGET sawConstraintController PROPERTY FOLDER "sawConstraintController")

  configure_file ("${CMAKE_CURRENT_SOURCE_DIR}/sawConstraintControllerConfig.cmake.in"
                  "${sawConstraintController_BINARY_DIR}/sawConstraintControllerConfig.cmake"
                  @ONLY@)

  # Install targets for headers and library
  install (DIRECTORY
           ${sawConstraintController_INCLUDE_DIR}/sawConstraintController
           DESTINATION include
           PATTERN .svn EXCLUDE)

  install (TARGETS sawConstraintController
           RUNTIME DESTINATION bin
           LIBRARY DESTINATION lib
           ARCHIVE DESTINATION lib)

  install (FILES "${sawConstraintController_BINARY_DIR}/sawConstraintControllerConfig.cmake"
           DESTINATION "${CISST_CMAKE_INSTALL_SUFFIX}/saw")

endif (cisst_FOUND_AS_REQUIRED)

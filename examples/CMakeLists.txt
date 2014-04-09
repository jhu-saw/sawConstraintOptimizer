#
# $Id: CMakeLists.txt 4605 2013-12-12 21:37:52Z adeguet1 $
#
# (C) Copyright 2011-2012 Johns Hopkins University (JHU), All Rights
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
  include( ${CISST_USE_FILE} )

  cisst_find_saw_component (sawConstraintController REQUIRED)

  if (sawConstraintController_FOUND)

    include_directories (${sawConstraintController_INCLUDE_DIR})

    set (sawConstraintController_EXAMPLES
         osaConstrainedOptimizationExample
         )

    foreach (_example ${sawConstraintController_EXAMPLES})
      add_executable (${_example} ${_example}.cpp)
      target_link_libraries (${_example} ${sawConstraintController_LIBRARIES})
      cisst_target_link_libraries (${_example} ${REQUIRED_CISST_LIBRARIES})
      set_property (TARGET ${_example} PROPERTY FOLDER "sawConstraintController")
    endforeach ()

    # copy configuration XML to the executable directory
    execute_process (COMMAND ${CMAKE_COMMAND} -E copy
       ${CMAKE_CURRENT_SOURCE_DIR}/configPID.xml
       ${EXECUTABLE_OUTPUT_PATH}/${CMAKE_CFG_INTDIR}/configPID.xml
       )

  endif (sawConstraintController_FOUND)

endif (cisst_FOUND_AS_REQUIRED)

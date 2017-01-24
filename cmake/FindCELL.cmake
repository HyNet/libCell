# Try to find CELL headers and libraries.
#
# Use this module as follows:
#
#     find_package(CELL)
#
# Variables used by this module (they can change the default behaviour and need
# to be set before calling find_package):
#
#  CELL_ROOT_DIR  Set this variable either to an installation prefix or to wa
#                CELL build directory where to look for the CELL libraries.
#
# Variables defined by this module:
#
#  CELL_FOUND              System has CELL headers and library
#  CELL_LIBRARIES          List of library files  for all components
#  CELL_INCLUDE_DIRS       List of include paths for all components
#  CELL_LIBRARY_$C         Library file for component $C
#  CELL_INCLUDE_DIR_$C     Include path for component $C

# iterate over user-defined components
foreach (comp ${CELL_FIND_COMPONENTS})
  # we use uppercase letters only for variable names
  string(TOUPPER "${comp}" UPPERCOMP)
  if ("${comp}" STREQUAL "core")
    set(HDRNAME "cell/all.hpp")
  elseif ("${comp}" STREQUAL "test")
    set(HDRNAME "cell/test/unit_test.hpp")
  else ()
    set(HDRNAME "cell/${comp}/all.hpp")
  endif ()
  if (CELL_ROOT_DIR)
    set(header_hints
        "${CELL_ROOT_DIR}/include"
        "${CELL_ROOT_DIR}/../libcell_${comp}")
  endif ()
  find_path(CELL_INCLUDE_DIR_${UPPERCOMP}
            NAMES
              ${HDRNAME}
              HINTS
              ${header_hints}
              /usr/include
              /usr/local/include
              /opt/local/include
              /sw/include
              ${CMAKE_INSTALL_PREFIX}/include)
  mark_as_advanced(CELL_INCLUDE_DIR_${UPPERCOMP})
  if (NOT "${CELL_INCLUDE_DIR_${UPPERCOMP}}"
      STREQUAL "CELL_INCLUDE_DIR_${UPPERCOMP}-NOTFOUND")
    # mark as found (set back to false in case library cannot be found)
    set(CELL_${comp}_FOUND true)
    # add to CELL_INCLUDE_DIRS only if path isn't already set
    set(duplicate false)
    foreach (p ${CELL_INCLUDE_DIRS})
      if (${p} STREQUAL ${CELL_INCLUDE_DIR_${UPPERCOMP}})
        set(duplicate true)
      endif ()
    endforeach ()
    if (NOT duplicate)
      set(CELL_INCLUDE_DIRS ${CELL_INCLUDE_DIRS} ${CELL_INCLUDE_DIR_${UPPERCOMP}})
    endif()
    # look for (.dll|.so|.dylib) file, again giving hints for non-installed CELLs
    # skip probe_event as it is header only
    if (NOT ${comp} STREQUAL "probe_event" AND NOT ${comp} STREQUAL "test")
      if (CELL_ROOT_DIR)
        set(library_hints "${CELL_ROOT_DIR}/lib")
      endif ()
      find_library(CELL_LIBRARY_${UPPERCOMP}
                   NAMES
                     "cell_${comp}"
                   HINTS
                     ${library_hints}
                     /usr/lib
                     /usr/local/lib
                     /opt/local/lib
                     /sw/lib
                     ${CMAKE_INSTALL_PREFIX}/lib)
      mark_as_advanced(CELL_LIBRARY_${UPPERCOMP})
      if ("${CELL_LIBRARY_${UPPERCOMP}}" STREQUAL "CELL_LIBRARY-NOTFOUND")
        set(CELL_${comp}_FOUND false)
      else ()
        set(CELL_LIBRARIES ${CELL_LIBRARIES} ${CELL_LIBRARY_${UPPERCOMP}})
      endif ()
    endif ()
  endif ()
endforeach ()

# let CMake check whether all requested components have been found
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(CELL
                                  FOUND_VAR CELL_FOUND
                                  REQUIRED_VARS CELL_LIBRARIES CELL_INCLUDE_DIRS
                                  HANDLE_COMPONENTS)

# final step to tell CMake we're done
mark_as_advanced(CELL_ROOT_DIR
                 CELL_LIBRARIES
                 CELL_INCLUDE_DIRS)


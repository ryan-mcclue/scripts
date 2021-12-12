# SPDX-License-Identifier: zlib-acknowledgement

include(${CMAKE_CURRENT_LIST_DIR}/CPM.cmake)
include(CTest)

find_package(cmocka QUIET)
if(NOT cmocka_FOUND)
  CPMAddPackage(
    NAME cmocka
    GIT_REPOSITORY https://git.cryptomilk.org/projects/cmocka.git/
    VERSION 1.1.5
    GIT_TAG cmocka-1.1.5
    DOWNLOAD_ONLY YES
  )

  set(cmocka_static_filename
    ${CMAKE_STATIC_LIBRARY_PREFIX}cmocka-static${CMAKE_STATIC_LIBRARY_SUFFIX}
  )

  include(ExternalProject)
  ExternalProject_Add(project_cmocka
    SOURCE_DIR ${cmocka_SOURCE_DIR}
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/cmocka
    BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/cmocka
    CMAKE_ARGS
      -DBUILD_STATIC_LIB=ON
      -DWITH_STATIC_LIB=ON
      -DWITH_EXAMPLES=OFF
      -DCMAKE_BUILD_TYPE=Debug
      -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_BINARY_DIR}/cmocka
    BUILD_BYPRODUCTS ${CMAKE_CURRENT_BINARY_DIR}/cmocka/lib/${cmocka_static_filename}
  )

  ExternalProject_Get_Property(project_cmocka BINARY_DIR)

  add_library(cmocka-static STATIC IMPORTED)
  set_target_properties(cmocka-static PROPERTIES
    IMPORTED_LOCATION ${BINARY_DIR}/lib/${cmocka_static_filename}
  )
  add_dependencies(cmocka-static project_cmocka)

  set(CMOCKA_LIBRARIES cmocka-static)
  set(CMOCKA_INCLUDE_DIR ${BINARY_DIR}/include)
endif()

function(cmocka_add_test name files_list)
  add_executable(${name})
  target_sources(${name} PRIVATE ${files_list})
  target_compile_options(${name} PRIVATE 
    -DTESTING
    ${COMPILER_FLAGS}
  )
  target_link_libraries(${name} PRIVATE ${CMOCKA_LIBRARIES})
  target_include_directories(${name} PRIVATE ${CMOCKA_INCLUDE_DIR})

  add_test(NAME ${name}.test
    COMMAND ${name} 
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/work
  )
endfunction()

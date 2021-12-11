# SPDX-License-Identifier: zlib-acknowledgement

include(CTest)

set(__global_test_names)

function(cmocka_add_test name files_list)
  add_executable(${name})
  target_sources(${name} PRIVATE ${files_list})
  target_compile_definitions(${name} PRIVATE TESTING)
  target_include_directories(${name} PRIVATE ${PROJECT_SOURCE_DIR}/code)
  target_link_libraries(${name} PRIVATE cmocka)

  add_test(NAME ${name}.test
    COMMAND ${name} 
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/tests
  )

  list(APPEND __global_tests_names)
endfunction()

function(cmocka_add_single_test_target)
  add_custom_target(single-test-target
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/tests
  )
  foreach(test_name IN LISTS __global_test_names)
    add_dependencies(single-test-target ${test_name})
  endforeach()
endfunction()

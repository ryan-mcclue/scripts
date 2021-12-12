# SPDX-License-Identifier: zlib-acknowledgement

include(CTest)

function(cmocka_add_test name files_list)
  add_executable(${name})
  target_sources(${name} PRIVATE ${files_list})
  target_compile_options(${name} PRIVATE 
    -DTESTING
    ${COMPILER_FLAGS}
  )
  target_include_directories(${name} PRIVATE ${PROJECT_SOURCE_DIR}/code)
  target_link_libraries(${name} PRIVATE cmocka)

  add_test(NAME ${name}.test
    COMMAND ${name} 
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/work
  )
endfunction()

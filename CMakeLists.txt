cmake_minimum_required(VERSION 3.10)

set(PATCH_VERSION "2" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.1.${PATCH_VERSION})

project(veditor VERSION ${PROJECT_VESRION})

set(EXEC_NAME ${CMAKE_PROJECT_NAME})
set(TEST_NAME test_${CMAKE_PROJECT_NAME})
include_directories("inc/")
set(SRC_PATH "src/")
set(TEST_PATH "test/")

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

configure_file(${TEST_PATH}/version.h.in ${TEST_PATH}/version.h)

add_executable(${EXEC_NAME} 
  ${SRC_PATH}/main.cpp
  ${SRC_PATH}/core/editorview.cpp 
  ${SRC_PATH}/core/editorcontroller.cpp 
  ${SRC_PATH}/core/editormodel.cpp 
)

add_library(${TEST_NAME} ${TEST_PATH}/lib.cpp)
add_executable(test_version ${TEST_PATH}/test_version.cpp)

target_include_directories(${EXEC_NAME} 
    PRIVATE "${CMAKE_BINARY_DIR}"
)

set_target_properties(${EXEC_NAME} ${TEST_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

set_target_properties(test_version PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_link_libraries(${EXEC_NAME} PRIVATE
  ${TEST_NAME}
)

target_link_libraries(test_version
    ${Boost_LIBRARIES}
    ${TEST_NAME}
)

if (MSVC)
    target_compile_options(${EXEC_NAME} PRIVATE /W4)
    target_compile_options(${TEST_NAME} PRIVATE /W4)
    target_compile_options(test_version PRIVATE /W4)
else ()
    target_compile_options(${EXEC_NAME} PRIVATE -Wall -Wextra -pedantic -Werror)
    target_compile_options(${TEST_NAME} PRIVATE -Wall -Wextra -pedantic -Werror)
    target_compile_options(test_version PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

install(TARGETS ${EXEC_NAME} RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

enable_testing()

add_test(test_version test_version)
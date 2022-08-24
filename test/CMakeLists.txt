find_package(Python REQUIRED)
enable_testing()

if (WIN32)
    set(NUMERO ../${CMAKE_BUILD_TYPE}/${PROJECT_NAME})
else()
    set(NUMERO ../${PROJECT_NAME})
endif (WIN32)

set(TESTROOT ../../test)

file(GLOB tests "t_*")
foreach(test ${tests})
    add_test(${test} ${Python_EXECUTABLE} ${test}/main.py)
    set_property(TEST ${test} PROPERTY ENVIRONMENT "PYTHONPATH=${TESTROOT};NUMERO=${NUMERO};TESTROOT=${TESTROOT}")
endforeach()

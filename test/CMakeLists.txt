find_package(Python REQUIRED)
enable_testing()

set(NUMERO ../${PROJECT_NAME})
set(TESTROOT ../../test)

file(GLOB tests "t_*")
foreach(test ${tests})
    add_test(${test} ${Python_EXECUTABLE} ${test}/main.py)
    set_property(TEST ${test} PROPERTY ENVIRONMENT "PYTHONPATH=${TESTROOT};NUMERO=${NUMERO};TESTROOT=${TESTROOT}")
endforeach()

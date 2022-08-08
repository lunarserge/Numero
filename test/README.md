# How to work with Numero tests
* Tests are implemented in a form of Python scripts that invoke `numero` executable with various command line parameters / input data.
* Each test has to be in its own folder starting with "t_".
* New tests don't need to be manually registered anywhere except putting them into a new folder per above - they will be picked up automaticaly.
* Tests are supposed to have `main.py` script as the entry point that is run by the `ctest` framework.
* Tests should have a description in a form of a docstring at the top of their `main.py`.
* Tests have access to the following environment variables:
  * `NUMERO`: Numero executable to run.
  * `TEST_ROOT`: path to the folder with tests.
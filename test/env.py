"Common test environment loader"

import os
import subprocess
import sys

numero = os.environ['NUMERO']
test_root = os.environ['TESTROOT']

def output_with(options):
    "Runs Numero with provided options and return the output"
    return subprocess.run([numero, options], capture_output=True, text=True).stderr

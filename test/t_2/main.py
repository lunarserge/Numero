"Test #2: Running Numero with '-h' or '--help' argument"

from env import *

output_ref  = open(test_root+"/help.txt").read()

output_test = subprocess.run([numero, "-h"], capture_output=True, text=True).stderr
if output_ref != output_test:
    sys.exit(1)

output_test = subprocess.run([numero, "--help"], capture_output=True, text=True).stderr
sys.exit(output_ref != output_test)
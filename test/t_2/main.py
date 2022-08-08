"Test #2: Running Numero with '--h' argument"

from env import *

output_ref  = open(test_root+"/help.txt").read()
output_test = subprocess.run([numero, "--h"], capture_output=True, text=True).stderr

sys.exit(output_ref != output_test)

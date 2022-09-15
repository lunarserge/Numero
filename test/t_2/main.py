"Test #2: Running Numero with '-h' or '--help' argument"

from env import *

output_ref  = open(test_root+"/help.txt").read()

sys.exit(output_with("-h") != output_ref or output_with("--help") != output_ref)

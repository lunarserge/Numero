"Test #1: Running Numero with no arguments"

from env import *

output_ref  = "No input dates file is selected. Exiting.\n\n" + open(test_root+os.path.sep+"help.txt").read()
output_test = subprocess.run(numero, capture_output=True, text=True).stderr

sys.exit(output_ref != output_test)

"Test #4: Running Numero with an argument that doesn't get recognized because of a single dash (-h)"

from env import *

output_ref  = "Unknown option: -h. Notice that options start with '--'. Exiting.\n\n" + open(test_root+"/help.txt").read()
output_test = subprocess.run([numero, "-h"], capture_output=True, text=True).stderr

sys.exit(output_ref != output_test)

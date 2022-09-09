"Test #3: Running Numero with an unknown argument (--g)"

from env import *

output_ref  = "Unknown option: --g. Exiting.\n\n" + open(test_root+"/help.txt").read()
output_test = subprocess.run([numero, "--g"], capture_output=True, text=True).stderr

sys.exit(output_ref != output_test)

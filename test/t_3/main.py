"Test #3: Running Numero with an unknown argument (-g or --gelp)"

from env import *

def run_with(option):
    return output_with(option) != ("Unknown option: " + option + ". Exiting.\n\n" + open(test_root+"/help.txt").read())

sys.exit(run_with("-g") | run_with("--gelp"))

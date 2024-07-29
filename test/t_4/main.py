"Test #4: Running Numero with the '-b' option"

from env import *

output_ref = "Results listed in local time zone:\n2022-Jul-31 11:22:00: John Doe / 10 year(s)\n"
output_test = subprocess.run([numero, "--b", "7,31,2022,11,22", "TechFriends.csv"], capture_output=True, text=True).stdout

sys.exit(output_ref != output_test)

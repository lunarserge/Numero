"Test #4: Running Numero with the '-b' option"

from env import *

output_ref = "Results listed in local time zone:\nMon Aug 26 20:52:55 2024: Amazon,Facebook,Google,Nvidia / 100 year(s)\n"
output_test = subprocess.run([numero, "--b", "7,31,2022,11,22", "TechFriends.csv"], capture_output=True, text=True).stdout

sys.exit(output_test.startswith(output_ref))

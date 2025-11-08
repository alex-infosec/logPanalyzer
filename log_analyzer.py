with open("/var/log/system.log") as f:
    fails = [l for l in f if "Failed" in l]
print(len(fails), "failed logins")

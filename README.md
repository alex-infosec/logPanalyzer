# Log Analyzer

A quick Python tool that scans system logs and counts failed login attempts.

## Overview
This script reads a local log file and prints how many lines contain the word **"Failed"**.  
It’s meant as a first step toward building small SOC-style alert tools.

## How to Run
```bash
python3 log_analyzer.py
```

## Example Output
```
12 failed logins
```

## Tech Used
Python • macOS Terminal • VS Code • Git

## What I Learned
- Reading and parsing log files  
- Using Git from the command line  
- Keeping commits and pushes clean

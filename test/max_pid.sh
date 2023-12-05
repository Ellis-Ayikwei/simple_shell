#!/bin/bash

# Read the maximum process ID value from /proc/sys/kernel/pid_max
max_pid=$(cat /proc/sys/kernel/pid_max)

# Print the result
echo "Maximum Process ID Value: $max_pid"


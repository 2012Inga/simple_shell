#!/bin/bash

pid_max_value=$(cat /proc/sys/kernel/pid_max)
echo "Maximum PID value: $pid_max_value"

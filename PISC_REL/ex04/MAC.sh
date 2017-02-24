#!/bin/sh
ifconfig -a | grep "ether" | sed 's/\(.*\)ether //g' | sed 's/ //g'

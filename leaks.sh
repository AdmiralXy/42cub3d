#!/bin/bash

for ((;;))
do
	clear
	leaks cub3d | grep -A10 for
	sleep 1
done
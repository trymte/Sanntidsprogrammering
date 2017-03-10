#!/bin/bash
clear

echo "Enter sanntid username:"
read username

echo "Enter last byte of the starting elevators IP:"
read IP
echo "Connecting to 129.241.187."$IP

scp -rq test_heis
$user@129.241.187.$IP:~/heisprosjekt

ssh
$user@129.241.187.$IP

# Run this in ssh:
	cd home/heisprosjekt
	./test_heis


#!/bin/bash
rm -f fname
./program_name fname add foo 2.0 2
./program_name fname report
sleep 1
./program_name fname add blech 3.5 9
./program_name fname report
sleep 1
./program_name fname add boo 1.5 1
./program_name fname report
sleep 1
./program_name fname add boobity 4.5 3
./program_name fname report
sleep 1
./program_name fname add booberry 7.3 5
./program_name fname report
sleep 1
./program_name fname add captain_crunch 3.5 2
./program_name fname report
sleep 1
./program_name fname delete boo
./program_name fname report
sleep 1
./program_name fname delete boobity
./program_name fname report
sleep 1
./program_name fname delete booberry
./program_name fname report
sleep 1
./program_name fname delete captain_crunch
./program_name fname report
sleep 1

echo off

start wc.exe wc.exe -w test0.c -o output0.txt

start wc.exe wc.exe -l test0.c -o output1.txt

start wc.exe wc.exe -l -a test0.c -o output2.txt

start wc.exe wc.exe -c test0.c -o output3.txt

start wc.exe wc.exe -w -c test0.c -o output4.txt

start wc.exe wc.exe -w -c -l test0.c -o output5.txt

start wc.exe wc.exe -w -c -l -a test0.c -o output6.txt

start wc.exe wc.exe -s -w -o -c -l -a *.c -o output7.txt

start wc.exe wc.exe -w -c -l -a test0.c  -e stop.txt 

start wc.exe wc.exe -w test0.c -e stop.txt 



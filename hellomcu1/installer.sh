#! /bin/bash
echo Today is `date`
echo Intallation starts now!

echo First, install gcc
sudo apt update; sudo apt install gcc -y

echo Second, download hellomcu.c
mkdir src || (rm -r src; mkdir src)
wget https://raw.githubusercontent.com/goodgodgd/microprocessor/master/hellomcu1/hellomcu.c -O src/hellomcu.c
gcc -o hellomcu1 hellomcu.c
chmod u+x hellomcu

echo Third, move hellomcu to mybin and add mybin to PATH
mkdir ~/mybin
cp src/hellomcu ~/mybin
echo excute hellomcu here: "`pwd`"
hellomcu
export PATH=~/mybin:$PATH
echo excute hellomcu at "`pwd`" after add mybin to 'PATH'
hellomcu

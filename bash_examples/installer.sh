#! /bin/bash
echo Today is `date`
echo Intallation starts now!

echo -e "\nStep1: install gcc"
sudo apt update; sudo apt install gcc -y
read -p "Press [enter] to continue"

echo -e "\nStep2: download hellomcu.c and built it"
mkdir src || (rm -r src; mkdir src)
wget https://raw.githubusercontent.com/goodgodgd/microprocessor/master/bash_examples/hellomcu.c -O src/hellomcu.c
gcc -o src/hellomcu src/hellomcu.c
chmod u+x src/hellomcu
read -p "Press [enter] to continue"

echo -e "\nStep3: move hellomcu to mybin try to execute it"
mkdir ~/mybin
cp src/hellomcu ~/mybin
echo excute hellomcu at "`pwd`"
hellomcu
read -p "Press [enter] to continue"

echo -e "\nStep4: add mybin to PATH and execute it again"
OLDPATH=$PATH
export PATH=~/mybin:$PATH
hellomcu
export PATH=$OLDPATH

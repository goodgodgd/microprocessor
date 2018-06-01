#! /bin/bash
echo Today is `date`
echo Rearrangement starts now!

echo -e "\nStep1: download projects and unzip it"
sudo apt install unzip silversearcher-ag -y
wget https://github.com/goodgodgd/microprocessor/blob/master/bash_examples/projects.zip?raw=true -O projects.zip
rm -r projects
unzip projects.zip -d projects
mv projects.zip projects
read -p "Press [enter] to continue"

echo -e "\nStep2: copy *.c files to projects/src"
mkdir projects/src
cp `find -name "*.c"` projects/src
read -p "Press [enter] to continue"

echo -e "\nStep3: list src files using Timer/Counter and move them to projects/tcsrc"
mkdir projects/tcsrc
ag tccr projects/src
cp `ag -l tccr projects/src` projects/tcsrc

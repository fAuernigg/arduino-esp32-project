#!/bin/bash 
cd `dirname $0` 
spath=`pwd`

sudo apt-get install -y git wget make libncurses-dev flex bison gperf python python-serial gawk gperf grep gettext libncurses-dev python python-dev automake bison flex texinfo help2man libtool
#if [ $? -ne 0 ] ; then echo "error apt install" ; exit 1; fi


if  [ ! -d "xtensa-esp32-elf" ] ; then
	#file="xtensa-esp32-elf-linux64-1.22.0-61-gab8375a-5.2.0.tar.gz"
	file="xtensa-esp32-elf-linux64-1.22.0-80-g6c4433a-5.2.0.tar.gz"
	wget "https://dl.espressif.com/dl/$file"
	tar -xzf "$file"

	if [ $? -ne 0 ] ; then echo "error untar xtensa-esp32 compiler" ; exit 1; fi

	if  [ ! -d "xtensa-esp32-elf" ] ; then echo "error xtensa-esp32-elf download untar failed" ; exit 1; fi
fi

export PATH=$PATH:$spath/xtensa-esp32-elf/bin

cd $spath
git submodule update --init

cd esp-idf
if [ $? -ne 0 ] ; then echo "error apt install" ; exit 1; fi
git submodule update --init


cd "$spath"
if [ $? -ne 0 ] ; then echo "error apt install" ; exit 1; fi
python -m pip install --user -r esp-idf/requirements.txt


echo "----------------------"
echo "installtoolchain done"
echo "----------------------"
echo " "
echo "--------------------------------------------------------------"
echo "source the toolchain by running . ./initpath.sh"
echo "--------------------------------------------------------------"


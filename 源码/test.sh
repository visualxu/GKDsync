#!/bin/bash
DIR="./share_dir"
echo $1 | sudo -S umount $DIR > /dev/null
if [ -e $DIR ]
then
	echo $1 | sudo -S rm -rf $DIR
	mkdir $DIR
else
	mkdir $DIR
fi
echo $1 | sudo -S mount -t cifs $2 $DIR -o username=$3,password=$4,dir_mode=0777,file_mode=0777
if [ $? -eq 0 ]
then
	echo "connect success!";
else
	echo "failed!";
fi

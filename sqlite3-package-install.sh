#!/usr/bin/bash
echo 没用交叉编译 如果要用自行修改目标架构和gcc
tar -zxvf sqlite-autoconf-3380500.tar.gz

sudo mkdir /usr/local/sqlite

cd sqlite-autoconf-3380500

./configure --host=arm-linux --prefix=/usr/local/sqlite/ #CC=arm-none-linux-gnueabi-gcc CXX=arm-none-linux-gnueabi-g++

make
make install

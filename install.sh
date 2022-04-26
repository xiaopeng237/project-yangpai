#!/bin/bash

rm target* -rf
mkdir ./target/bin -p &>/dev/null
mkdir ./target/lib -p &>/dev/null
mkdir ./target/etc -p &>/dev/null
mkdir ./target/install -p &>/dev/null

cp ./depend/{dlt,dbus}/bin/* ./target/bin &>/dev/null
cp ./depend/{dlt,dbus}/lib/* ./target/lib &>/dev/null
cp ./depend/{dlt,dbus}/*     ./target/	  &>/dev/null
cp ./depend/{dlt,dbus}/etc/* ./target/etc &>/dev/null
cp ./depend/bin/* ./target/bin &>/dev/null
cp ./depend/lib/* ./target/lib &>/dev/null
cp ./depend/dlt/dlt_logstorage.conf ./target/install
cp ./daemon-yp.sh ./target/
#DIR=dev_data_pre,freemodbus,mysql,pioneers,ypdbus2,adjust
#
#echo "$DIR" | awk -F, '{i=1; while(i<=NF){print "cp ./cmake-build-debug/"$i"/"$i,"./target/bin &>/dev/null";i++}}'   |bash
#echo "$DIR" | awk -F, '{i=1; while(i<=NF){print "cp ./cmake-build-debug/"$i"/*.so","./target/lib &>/dev/null";i++}}' |bash

chmod a+x ./target/bin/*
tar cf target.tar ./target

rm target -rf
md5sum target.tar > version.txt

#sed -i 's/\r$//' xxxx
#chmod a+x /usr/local/bin/scp
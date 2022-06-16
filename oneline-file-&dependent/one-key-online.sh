#!/usr/bin/bash


while ((1))
do
   	ping -c 5 -w 30 202.108.22.5             #百度的ip地址
	if [[ $? != 0 ]];then                    #语法垃圾!!! 主要是空格的问题
		echo  ping不通 执行ruijie脚本
		/usr/local/bin/ruijie_general.sh  18450150331 308118
	else
        	echo  ping通sleep 10m
		sleep 10m
	fi

done

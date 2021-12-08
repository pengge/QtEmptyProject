#!/bin/bash
LibDir=$PWD"/lib"  #获取lib目录路径
Target=$1
lib_array=($(ldd $Target | grep -o "/.*" | grep -o "/.*/[^[:space:]]*"))
$(mkdir $LibDir)   #创建lib目录
for Variable in ${lib_array[@]}  #循环所有依赖的动态库路径
do
    cp "$Variable" $LibDir  #拷贝到lib目录中
done

#1.给脚本赋予权限
#chmod 777 copy.sh

#2.执行脚本，参数是可执行文件名
#./copy.sh emptyproject

#3.将生成的lib目录中的所有文件移动到上层，与可执行文件同级,然后将lib目录删除

#4.进入QT安装目录,#/usr/local/Qt-5.15.2/plugins/platforms目录下,copy.sh放到该目录下并执行
#./copy.sh libqxcb.so

#5. 将生成的platforms/lib中的所有文件放到test目录下

#!/bin/sh
appname=`basename $0 | sed s,\.sh$,,`

dirname=`dirname $0`
tmp="${dirname#?}"

if [ "${dirname%$tmp}" != "/" ]; then
dirname=$PWD/$dirname
fi
LD_LIBRARY_PATH=$dirname
export LD_LIBRARY_PATH
$dirname/$appname "$@"

#1.赋予运行脚本权限
#Chmod 777 emptyproject.sh

#2.现在可以将test目录拷贝到其他主机上,通过./emptyproject.sh来运行

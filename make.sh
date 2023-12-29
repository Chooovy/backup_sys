#!/bin/bash
FOLDER_ROOT=$PWD

if [ "$(uname)" != "Linux" ]; then    
    exit
fi
# 检查是否存在Openssl
if test -f "${FOLDER_ROOT}/lib/libcrypto.so" && test -f "${FOLDER_ROOT}/lib/libssl.so" && test -d "${FOLDER_ROOT}/include/openssl"; then
    if ! test -d "build"; then
        mkdir build
    fi
    cd build
    rm -rf ./*
    cmake ${FOLDER_ROOT}
    make
    cd ${FOLDER_ROOT}
    echo "Run ./bin/main"    
    ${FOLDER_ROOT}/bin/main
else
    # 如果不存在，则安装
    echo "Can't find Openssl, Download and Compile it!"
    if ! test -f "${FOLDER_ROOT}/openssl-1.1.1v.tar.gz"; then
        wget https://www.openssl.org/source/old/1.1.1/openssl-1.1.1v.tar.gz
    fi
    if ! test -d "${FOLDER_ROOT}/openssl-1.1.1v"; then
        tar -zxvf openssl-1.1.1v.tar.gz
    fi
    if ! test -f "${FOLDER_ROOT}/openssl-1.1.1v/libcrypto.so" || ! test -f "${FOLDER_ROOT}/openssl-1.1.1v/libssl.so"; then
        cd ${FOLDER_ROOT}/openssl-1.1.1v
        ./config --prefix=$PWD -fPIC
        make
    fi
    cd ${FOLDER_ROOT}
    cp ${FOLDER_ROOT}/openssl-1.1.1v/*.so ./lib/
    cp  -r ${FOLDER_ROOT}/openssl-1.1.1v/include/openssl ./include/
    rm -rf ${FOLDER_ROOT}/openssl-1.1.1v ${FOLDER_ROOT}/openssl-1.1.1v.tar.gz
    ./make.sh
fi
#!/usr/bin/env bash

BASE_DIR=/tmp/zmk-config

if [ -d "$BASE_DIR" ]; then
    echo "Removing existing directory: $BASE_DIR"
    #rm -rf $BASE_DIR
else
    echo "Creating new directory: $BASE_DIR"
fi

mkdir -p $BASE_DIR

cp -R tests/* $BASE_DIR/tests/

cd $BASE_DIR
if [ ! -d "$BASE_DIR/.west" ]; then
    west init -l $BASE_DIR/tests
    west update
fi

west zephyr-export
west build --pristine --board native_posix_64 -- -DZMK_CONFIG=/workspace/behavior/tests/ \
     -DZMK_EXTRA_MODULES="/workspace/behavior"
west test tests

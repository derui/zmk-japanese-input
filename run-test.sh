#!/usr/bin/env bash

testcase=$1

BASE_DIR=/tmp/zmk-config

if [ -d "$BASE_DIR" ]; then
    echo "Removing existing directory: $BASE_DIR"
    #rm -rf $BASE_DIR
else
    echo "Creating new directory: $BASE_DIR"
fi

mkdir -p $BASE_DIR/tests

cp -R tests/* $BASE_DIR/tests/

cd $BASE_DIR
if [ ! -d "$BASE_DIR/.west" ]; then
    west init -l $BASE_DIR/tests
    west update
fi

west zephyr-export
west build -s zmk/app --pristine -b native_posix_64 -- -DZMK_CONFIG=/workspaces/behavior/tests/$testcase \
     -DCONFIG_ASSERT=y \
     -DZMK_EXTRA_MODULES="/workspaces/behavior"

${BASE_DIR}/build/zephyr/zmk.exe |
    sed -e "s/.*> //" |
    tee /workspaces/behavior/tests/$testcase/keycode_events_full.log |
    sed -n -f /workspaces/behavior/tests/$testcase/events.patterns > /workspaces/behavior/tests/$testcase/keycode_events.log

diff -auZ  /workspaces/behavior/tests/$testcase/keycode_events.snapshot /workspaces/behavior/tests/$testcase/keycode_events.log

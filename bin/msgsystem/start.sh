#!/bin/sh
killall -9 msg_system_svr
sleep 2
ulimit -c unlimited
cd /home/im/yunquantest/bin/msgsystem
./msg_system_svr  -id 20000 -tcp 127.0.0.1:8300
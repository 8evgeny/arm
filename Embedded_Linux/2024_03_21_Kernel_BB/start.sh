#!/usr/bin/bash

if [ ! -d ti-linux-kernel-dev ] then
    git clone https://github.com/RobertCNelson/ti-linux-kernel-dev.git
fi
cd ti-linux-kernel-dev
git checkout origin/ti-linux-4.19.y -b tmp
./build_kernel.sh

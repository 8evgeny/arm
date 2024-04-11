#!/usr/bin/bash
docker build -t yocto .
docker run -v $(pwd):/mnt -ti yocto


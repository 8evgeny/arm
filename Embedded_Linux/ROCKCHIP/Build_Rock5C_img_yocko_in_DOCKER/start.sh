#!/usr/bin/bash

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
echo "Папка скрипта: $SCRIPT_DIR"
# docker build  --no-cache /home/evg/extNVME2T/Current_book/Embedded_Linux/2_Embedded_Linux_Development_Using_Yocto
docker build -t yocto_rock5c  $SCRIPT_DIR

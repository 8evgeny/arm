https://github.com/herry13/raspberrypi-yocto-builder

РАБОТАЕТ!!!  при сборке далее возникает ошибка 
по аналогии сделать в предыдущей папке


Raspberry Pi Yocto Builder
==========================

This repo contains necessary files to build a Raspberry Pi based on Yocto project using Docker.


To build:

```sh
$ docker build -t yocto .
```

To run:

```sh
$ docker run -v $(pwd):/mnt -ti yocto
```

FROM ubuntu:16.04
ENV DEBIAN_FRONTEND noninteractive  #не задавать вопросов
RUN apt-get update && apt-get install -y make binutils build-essential diffutils gcc g++ patch bzip2 cpio unzip rsync file bc findutils wget
 
#RUN export DEBIAN_FRONTEND=noninteractive && locale-gen en_US.UTF-8 && update-locale LC_ALL=en_US.UTF-8 LANG=en_US.UTF-8

ENV LANG en_US.UTF-8
ENV LC_ALL en_US.UTF-8
RUN groupadd evg && useradd -p 123 -b /home -d /home/evg -m -g evg -s /bin/bash -G sudo evg
USER evg
WORKDIR /home/evg
#
#RUN git clone --single-branch --branch u-boot-2016.09.y --progress git://git.denx.de/u-boot.git u-boot/ && cd u-boot &&  make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- am335x_boneblack_defconfig && make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf-
#
#RUN git clone --single-branch --branch beaglev-v5.10.113-1.1.2-ubuntu  --progress  https://github.com/beagleboard/linux.git
#
#USER root
#RUN apt-get install -y flex bison libgmp3-dev libmpfr-dev libmpc-dev libssl-dev gcc-arm-linux-gnueabihf
#USER evg
#WORKDIR /home/evg/linux
#COPY .config /home/evg/linux
#RUN make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- uImage dtbs LOADADDR=0x80008000 -j4







CMD ["/bin/bash"]


# * master
#   remotes/origin/HEAD -> origin/master
#   remotes/origin/WIP/resync-dtc-v1.6.0-31-gcbca977ea121-v5
#   remotes/origin/master
#   remotes/origin/next
#   remotes/origin/u-boot-2009.11.y
#   remotes/origin/u-boot-2013.01.y
#   remotes/origin/u-boot-2016.09.y
#   remotes/origin/u-boot-2023.07.y



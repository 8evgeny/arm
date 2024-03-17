FROM ubuntu:16.04
ENV DEBIAN_FRONTEND noninteractive  #не задавать вопросов
RUN apt-get update && apt-get install -y gawk wget git diffstat unzip texinfo gcc-multilib build-essential chrpath socat cpio bc python3 python3-pip python3-pexpect xz-utils debianutils iputils-ping libsdl1.2-dev xterm locales nano mc qemu sudo make gcc g++ unzip bzip2 libncurses5-dev patch cpio rsync libelf-dev u-boot-tools
RUN apt-get install -y gcc-5-multilib gcc-5-arm-linux-gnueabihf gcc-arm-linux-gnueabihf
RUN export DEBIAN_FRONTEND=noninteractive && locale-gen en_US.UTF-8 && update-locale LC_ALL=en_US.UTF-8 LANG=en_US.UTF-8
RUN mkdir -pv /opt/linaro
RUN wget -P /opt/linaro -c https://releases.linaro.org/components/toolchain/binaries/5.3-2016.02/arm-linux-gnueabihf/gcc-linaro-5.3-2016.02-x86_64_arm-linux-gnueabihf.tar.xz
RUN cd /opt/linaro && tar xf gcc-linaro-5.3-2016.02-x86_64_arm-linux-gnueabihf.tar.xz && cd gcc-linaro-5.3-2016.02-x86_64_arm-linux-gnueabihf && mv ./* ../ && cd ../ && rmdir gcc-linaro-5.3-2016.02-x86_64_arm-linux-gnueabihf && rm gcc-linaro-5.3-2016.02-x86_64_arm-linux-gnueabihf.tar.xz 
ENV PATH="/opt/linaro/bin:$PATH"
RUN arm-linux-gnueabihf-gcc --version
ENV LANG en_US.UTF-8
ENV LC_ALL en_US.UTF-8
RUN groupadd evg && useradd -p 123 -b /home -d /home/evg -m -g evg -s /bin/bash -G sudo evg
USER evg
WORKDIR /home/evg
RUN git clone --single-branch --branch u-boot-2016.09.y --progress git://git.denx.de/u-boot.git u-boot/ && cd u-boot &&  make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- am335x_boneblack_defconfig && make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf-
# RUN wget -c https://rcn-ee.com/repos/git/u-boot-patches/v2016.03/0001-am335x_evm-uEnv.txt-bootz-n-fixes.patch
# RUN patch -p1 < 0001-am335x_evm-uEnv.txt-bootz-n-fixes.patch

# Uboot  закончен (часть BOOT) перехожу к ядру
RUN git clone --single-branch --branch beaglev-v5.10.113-1.1.2-ubuntu  --progress  https://github.com/beagleboard/linux.git
# beaglebone-3.2
# beaglev-v5.10.113-1.1.2
# beaglev-v5.10.113-1.1.2-ubuntu
# make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- bb.org_defconfig     такого файла нет
USER root
RUN apt-get install -y flex bison libgmp3-dev libmpfr-dev libmpc-dev libssl-dev gcc-arm-linux-gnueabihf
USER evg
WORKDIR /home/evg/linux
RUN make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- omap2plus_defconfig
# RUN make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- uImage dtbs LOADADDR=0x80008000 -j4

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



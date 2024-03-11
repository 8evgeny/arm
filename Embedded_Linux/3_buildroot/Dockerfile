FROM ubuntu:16.04
ENV DEBIAN_FRONTEND noninteractive  #не задавать вопросов
RUN apt-get update && apt-get install -y gawk wget git diffstat unzip texinfo gcc-multilib build-essential chrpath socat cpio bc python3 python3-pip python3-pexpect xz-utils debianutils iputils-ping libsdl1.2-dev xterm locales nano mc qemu sudo make gcc g++ unzip bzip2 libncurses5-dev patch cpio rsync libelf-dev
RUN export DEBIAN_FRONTEND=noninteractive && locale-gen en_US.UTF-8 && update-locale LC_ALL=en_US.UTF-8 LANG=en_US.UTF-8
ENV LANG en_US.UTF-8
ENV LC_ALL en_US.UTF-8
RUN groupadd evg && useradd -p 123 -b /home -d /home/evg -m -g evg -s /bin/bash -G sudo evg
USER evg
WORKDIR /home/evg
# RUN git clone git://git.buildroot.net/buildroot -b 2020.02.9
RUN git clone git://git.buildroot.net/buildroot 
RUN cd buildroot && make imx8mmpico_defconfig && make
# RUN make qemu_arm_versatile_defconfig  
CMD ["/bin/bash"]


FROM ubuntu:16.04
ENV DEBIAN_FRONTEND noninteractive  #не задавать вопросов
RUN apt-get update && apt-get install -y gawk wget git diffstat unzip texinfo gcc-multilib build-essential chrpath socat cpio  python3 python3-pip python3-pexpect xz-utils debianutils iputils-ping libsdl1.2-dev xterm locales nano
RUN export DEBIAN_FRONTEND=noninteractive && locale-gen en_US.UTF-8 && update-locale LC_ALL=en_US.UTF-8 LANG=en_US.UTF-8
ENV LANG en_US.UTF-8
ENV LC_ALL en_US.UTF-8
RUN groupadd evg && useradd -b /home -d /home/evg -m -g evg -s /bin/bash -G sudo evg
USER evg
WORKDIR /home/evg
RUN git clone git://git.yoctoproject.org/poky -b rocko 
RUN cd /home/evg/poky && . ./oe-init-build-env && bitbake core-image-full-cmdline
CMD ["/bin/bash"]


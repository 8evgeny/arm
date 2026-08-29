FROM ubuntu:22.04
ENV DEBIAN_FRONTEND noninteractive  #не задавать вопросов

RUN apt-get update && apt-get install -y build-essential chrpath cpio debianutils diffstat file gawk gcc git iputils-ping libacl1 lz4 locales python3 python3-git python3-jinja2 python3-pexpect python3-pip python3-subunit socat texinfo unzip wget xz-utils zstd xterm locales nano mc qemu sudo
RUN apt-get install -y curl repo

RUN export DEBIAN_FRONTEND=noninteractive && locale-gen en_US.UTF-8 && update-locale LC_ALL=en_US.UTF-8 LANG=en_US.UTF-8
ENV LANG en_US.UTF-8
ENV LC_ALL en_US.UTF-8

RUN mkdir -p ~/bin
RUN curl https://storage.googleapis.com/git-repo-downloads/repo > ~/bin/repo
RUN chmod a+x ~/bin/repo
RUN export PATH="$HOME/bin:$PATH"

RUN mkdir ~/yocto-rockchip-sdk && cd ~/yocto-rockchip-sdk
RUN repo init -u https://github.com/radxa/yocto-manifests.git -b scarthgap
RUN repo sync -j1 --fail-fast

RUN cd ~/yocto-rockchip-sdk/build/conf
RUN ln -sf rockchip-rk3588s-rock-5c.conf local.conf

RUN cd ~/yocto-rockchip-sdk
RUN source ./oe-init-build-env
RUN bitbake core-image-minimal
#After successful build, the corresponding image files for ROCK 5C will be generated in the ~/yocto-rockchip-sdk/build/tmp/deploy/images/ directory.

#RUN mkdir -p /dev/net && mknod /dev/net/tun c 10 200 && chmod 0666 /dev/net/tun
#RUN groupadd user && useradd -p 123 -b /home -d /home/user -m -g user -s /bin/bash -G sudo user
#USER user
#WORKDIR /home/user
#RUN git clone git://git.yoctoproject.org/poky -b rocko
#RUN cd /home/user/poky && . ./oe-init-build-env && bitbake core-image-full-cmdline
# RUN apt-get install -y mc qemu-kvm qemu virt-manager virt-viewer libvirt-bin
CMD ["/bin/bash"]


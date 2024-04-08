FROM ubuntu:16.04
ENV DEBIAN_FRONTEND noninteractive  #не задавать вопросов
RUN apt-get update && apt-get install -y make binutils build-essential diffutils gcc g++ patch bzip2 cpio unzip rsync file bc findutils wget git locales gawk diffstat texinfo gcc-multilib chrpath socat libsdl1.2-dev xterm sed cvs subversion coreutils texi2html docbook-utils python-pysqlite2 help2man desktop-file-utils libgl1-mesa-dev libglu1-mesa-dev mercurial autoconf automake groff curl lzop asciidoc u-boot-tools sudo 
RUN apt-get install -y python python3 python3-pip python3-pexpect python3-git xz-utils debianutils iputils-ping zstd liblz4-tool
RUN export DEBIAN_FRONTEND=noninteractive && locale-gen en_US.UTF-8 && update-locale LC_ALL=en_US.UTF-8 LANG=en_US.UTF-8
# linux-headers-$(uname -r)
ENV LANG en_US.UTF-8
ENV LC_ALL en_US.UTF-8
RUN groupadd evg && useradd -p 123 -b /home -d /home/evg -m -g evg -s /bin/bash -G sudo evg
USER evg
WORKDIR /home/evg
RUN mkdir -p ~/.bin
ENV PATH="/home/evg/.bin:$PATH"
RUN curl https://storage.googleapis.com/git-repo-downloads/repo > ~/.bin/repo && chmod a+rx ~/.bin/repo
RUN mkdir raspberrypi && cd raspberrypi && git clone git://git.yoctoproject.org/poky -b langdale && cd poky && git clone git://git.openembedded.org/openembedded-core -b langdale && git clone git://git.openembedded.org/meta-openembedded -b langdale && git clone git://git.yoctoproject.org/meta-raspberrypi -b langdale && git clone git://git.yoctoproject.org/meta-security -b langdale && source oe-init-build-env

CMD ["/bin/bash"]




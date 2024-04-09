FROM ubuntu:16.04
ENV DEBIAN_FRONTEND noninteractive  #не задавать вопросов
RUN apt-get update && apt-get install -y make binutils build-essential diffutils gcc g++ patch bzip2 cpio unzip rsync file bc findutils wget git locales gawk diffstat texinfo gcc-multilib chrpath socat libsdl1.2-dev xterm sed cvs subversion coreutils texi2html docbook-utils python-pysqlite2 help2man desktop-file-utils libgl1-mesa-dev libglu1-mesa-dev mercurial autoconf automake groff curl lzop asciidoc u-boot-tools sudo python python3 python3-pip python3-pexpect python3-git xz-utils debianutils iputils-ping zstd liblz4-tool
#In Ubuntu, /bin/sh is a link to /bin/dash. The dash shell does not support the source command. However, we need the source command in the very last line of the Dockerfile. We replace dash by bash with
RUN rm /bin/sh && ln -s bash /bin/sh
RUN export DEBIAN_FRONTEND=noninteractive && locale-gen en_US.UTF-8 && update-locale LC_ALL=en_US.UTF-8 LANG=en_US.UTF-8
ENV USER_NAME evg
ENV PROJECT rpi4image
ENV LANG en_US.UTF-8
ENV LC_ALL en_US.UTF-8
ARG host_uid=1001
ARG host_gid=1001
RUN groupadd -g $host_gid $USER_NAME && useradd -g $host_gid -p 123 -b /home -d /home/$USER_NAME -m -g $USER_NAME -s /bin/bash -G sudo $USER_NAME
USER $USER_NAME
WORKDIR /home/$USER_NAME
RUN mkdir -p ~/.bin
ENV PATH="/home/evg/.bin:$PATH"
#RUN curl https://storage.googleapis.com/git-repo-downloads/repo > ~/.bin/repo && chmod a+rx ~/.bin/repo && mkdir raspberrypi && cd raspberrypi && git clone git://git.yoctoproject.org/poky -b langdale  && cd poky && git clone git://git.openembedded.org/openembedded-core -b langdale && git clone git://git.openembedded.org/meta-openembedded -b langdale && git clone git://git.yoctoproject.org/meta-raspberrypi -b langdale && git clone git://git.yoctoproject.org/meta-security -b langdale 
#RUN cd raspberrypi/poky && ./oe-init-build-env build-rpi && rm /home/evg/raspberrypi/poky/build-rpi/conf/local.conf && echo \
#'MACHINE = "raspberrypi4-64"'>build-rpi/conf/local.conf && echo \
#'DISTRO = "poky"'>>build-rpi/conf/local.conf && echo \
#'EXTRA_IMAGE_FEATURES ?= "debug-tweaks" # NOTE this is incompatible with security features'>>build-rpi/conf/local.conf && echo \
#'#DISTRO_FEATURES:append = " security" #NOTE enable this when the image development is finalized'>>build-rpi/conf/local.conf && echo \
#'USER_CLASSES ?= "buildstats"'>>build-rpi/conf/local.conf && echo \
#'PATCHRESOLVE = "noop"'>>build-rpi/conf/local.conf && echo \
#'BB_DISKMON_DIRS ??= "\'>>build-rpi/conf/local.conf && echo \
#'    STOPTASKS,${TMPDIR},1G,100K \'>>build-rpi/conf/local.conf && echo \
#'    STOPTASKS,${DL_DIR},1G,100K \'>>build-rpi/conf/local.conf && echo \
#'    STOPTASKS,${SSTATE_DIR},1G,100K \'>>build-rpi/conf/local.conf && echo \
#'    STOPTASKS,/tmp,100M,100K \'>>build-rpi/conf/local.conf && echo \
#'    ABORT,${TMPDIR},100M,1K \'>>build-rpi/conf/local.conf && echo \
#'    ABORT,${DL_DIR},100M,1K \'>>build-rpi/conf/local.conf && echo \
#'    ABORT,${SSTATE_DIR},100M,1K \'>>build-rpi/conf/local.conf && echo \
#'    ABORT,/tmp,10M,1K"'>>build-rpi/conf/local.conf && echo \
#'PACKAGECONFIG:append_pn-qemu-system-native = " sdl"'>>build-rpi/conf/local.conf && echo \
#'CONF_VERSION = "2"'>>build-rpi/conf/local.conf && echo \
#'#DL_DIR ?= "${TOPDIR}/downloads"'>>build-rpi/conf/local.conf && echo \
#'ACCEPT_FSL_EULA = "1"'>>build-rpi/conf/local.conf && echo \
#'# Switch to Debian packaging and include package-management in the image'>>build-rpi/conf/local.conf && echo \
#'PACKAGE_CLASSES = "package_deb"'>>build-rpi/conf/local.conf && echo \
#'#PACKAGE_FEED_URIS = "http://172.20.1.35:8000" # Enable this when you know your local IP for serving apt packages'>>build-rpi/conf/local.conf && echo \
#'EXTRA_IMAGE_FEATURES += "package-management" # And enable this too'>>build-rpi/conf/local.conf && echo \
#'LICENSE_FLAGS_ACCEPTED += "commercial "'>>build-rpi/conf/local.conf && echo \
#'PACKAGECONFIG_pn-gstreamer1.0-plugins-ugly += "x264"'>>build-rpi/conf/local.conf && echo \
#'# Additional install packages'>>build-rpi/conf/local.conf && echo \
#'IMAGE_INSTALL:append = " gcc g++ make dpkg-dev libc6-dev python3-fail2ban openssh" # Here is where we add packages we want built into the final image'>>build-rpi/conf/local.conf && echo \
#'PARALLEL_MAKE="-j16"'>>build-rpi/conf/local.conf && echo \
#'BB_NUMBER_THREADS="16"'>>build-rpi/conf/local.conf && echo \
#'INHERIT += "buildhistory"'>>build-rpi/conf/local.conf && echo \
#'BUILDHISTORY_COMMIT = "1"'>>build-rpi/conf/local.conf && echo \
#'And edit nano conf/bblayers.conf to look like this:'>>build-rpi/conf/local.conf && echo \
#'# POKY_BBLAYERS_CONF_VERSION is increased each time build/conf/bblayers.conf'>>build-rpi/conf/local.conf && echo \
#'# changes incompatibly'>>build-rpi/conf/local.conf && echo \
#'POKY_BBLAYERS_CONF_VERSION = "2"'>>build-rpi/conf/local.conf && echo \
#'BBPATH = "${TOPDIR}"'>>build-rpi/conf/local.conf && echo \
#'BBFILES ?= ""'>>build-rpi/conf/local.conf && echo \
#'BBLAYERS ?= " \'>>build-rpi/conf/local.conf && echo \
#' /home/evg/raspberrypi/poky/meta \'>>build-rpi/conf/local.conf && echo \
#' /home/evg/raspberrypi/poky/meta-poky \'>>build-rpi/conf/local.conf && echo \
#' /home/evg/raspberrypi/poky/meta-yocto-bsp \'>>build-rpi/conf/local.conf && echo \
#' /home/evg/raspberrypi/poky/meta-raspberrypi \'>>build-rpi/conf/local.conf && echo \
#' /home/evg/raspberrypi/poky/meta-openembedded/meta-oe \'>>build-rpi/conf/local.conf && echo \
#' /home/evg/raspberrypi/poky/meta-openembedded/meta-networking \'>>build-rpi/conf/local.conf && echo \
#' /home/evg/raspberrypi/poky/meta-openembedded/meta-filesystems \'>>build-rpi/conf/local.conf && echo \
#' /home/evg/raspberrypi/poky/meta-openembedded/meta-multimedia \'>>build-rpi/conf/local.conf && echo \
#' /home/evg/raspberrypi/poky/meta-openembedded/meta-python \'>>build-rpi/conf/local.conf && echo \
#' /home/evg/raspberrypi/poky/meta-openembedded/meta-gnome \'>>build-rpi/conf/local.conf && echo \
#' /home/evg/raspberrypi/poky/meta-openembedded/meta-xfce \'>>build-rpi/conf/local.conf && echo \
#' /home/evg/raspberrypi/poky/meta-security \'>>build-rpi/conf/local.conf && echo \
#' "'>>build-rpi/conf/local.conf &&  \
#bitbake 
# WORKDIR /home/evg/raspberrypi/poky/build-rpi/conf
CMD ["/bin/bash"]




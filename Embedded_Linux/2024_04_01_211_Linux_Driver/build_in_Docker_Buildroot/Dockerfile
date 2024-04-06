FROM ubuntu:16.04
ENV DEBIAN_FRONTEND noninteractive  #не задавать вопросов
RUN apt-get update && apt-get install -y make binutils build-essential diffutils gcc g++ patch bzip2 cpio unzip rsync file bc findutils wget git locales
RUN export DEBIAN_FRONTEND=noninteractive && locale-gen en_US.UTF-8 && update-locale LC_ALL=en_US.UTF-8 LANG=en_US.UTF-8
ENV LANG en_US.UTF-8
ENV LC_ALL en_US.UTF-8
RUN groupadd evg && useradd -p 123 -b /home -d /home/evg -m -g evg -s /bin/bash -G sudo evg
USER evg
WORKDIR /home/evg
RUN git clone --single-branch --branch 2023.02.x --progress git://git.buildroot.net/buildroot  
RUN cd buildroot &&  make raspberrypi4_64_defconfig && make 
USER root
RUN apt-get install -y libncurses-dev
USER evg
WORKDIR /home/evg/buildroot
CMD ["/bin/bash"]



FROM ubuntu:22.04
ENV DEBIAN_FRONTEND noninteractive  #не задавать вопросов
RUN apt-get update && apt-get install -y make binutils build-essential diffutils gcc g++ patch bzip2 cpio unzip rsync file bc findutils wget git locales
RUN  apt-get install -y mc libncurses5-dev libncursesw5-dev qtbase5-dev qt5-qmake
RUN export DEBIAN_FRONTEND=noninteractive && locale-gen en_US.UTF-8 && update-locale LC_ALL=en_US.UTF-8 LANG=en_US.UTF-8
ENV LANG en_US.UTF-8
ENV LC_ALL en_US.UTF-8
RUN groupadd user && useradd -p 123 -b /home -d /home/user -m -g user -s /bin/bash -G sudo  user
USER user
WORKDIR /home/user
RUN git clone --single-branch --branch 2024.08.x --progress git://git.buildroot.net/buildroot  
RUN cd buildroot &&  make raspberrypi4_defconfig && make 
CMD ["/bin/bash"]



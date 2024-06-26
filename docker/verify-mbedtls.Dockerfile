FROM priyasiddharth/seahorn-llvm14:ownsem

ENV SEAHORN=/home/usea/seahorn/bin/sea PATH="$PATH:/home/usea/seahorn/bin"

## install required pacakges
USER root

## Install latest cmake
RUN apt -y remove --purge cmake
RUN apt -y update
RUN apt -y install wget python3-pip
RUN python3 -m pip install --upgrade pip
RUN pip3 install cmake --upgrade
RUN pip3 install matplotlib pandas seaborn numpy
RUN apt -y install nano

## import seamock
USER usea
WORKDIR /home/usea
#
##
RUN mkdir verify-mbedtls
COPY --chown=usea:usea . verify-mbedtls

#
WORKDIR /home/usea/verify-mbedtls/seamock
# build seamock
RUN rm -Rf build && mkdir build && cd build && cmake -DCMAKE_C_COMPILER=clang-14 -DCMAKE_CXX_COMPILER=clang++-14 -DSEAHORN_ROOT=/home/usea/seahorn  -DSEA_LINK=llvm-link-14 ../ -GNinja && cmake --build .
WORKDIR /home/usea/verify-mbedtls
# build verify-mbedtls
RUN rm -Rf build && mkdir build && cd build && cmake -DCMAKE_C_COMPILER=clang-14 -DCMAKE_CXX_COMPILER=clang++-14 -DSEAHORN_ROOT=/home/usea/seahorn -DSEA_LINK=llvm-link-14 ../ -GNinja && cmake --build .

#
### set default user and wait for someone to login and start running verification tasks
USER usea

FROM ubuntu:latest
ARG DEBIAN_FRONTEND=noninteractive
WORKDIR /root
RUN apt-get update && apt-get -y upgrade
RUN apt-get -y install make gcc g++ gdb git neovim gcc-multilib
RUN git clone https://gitlab.com/toobi7007/ss22

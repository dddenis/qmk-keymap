FROM debian:latest

RUN apt update && apt install -y git python3 python3-pip sudo gcc-arm-none-eabi dfu-util

RUN python3 -m pip install qmk appdirs --break-system-packages

WORKDIR /root

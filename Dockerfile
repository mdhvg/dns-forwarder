FROM ubuntu:jammy

RUN apt update --fix-missing && apt install -y \
    cmake \
    build-essential \
    make \
    ninja-build \
    wget \
    curl \
    git \
    zip \
    tar \
    unzip \
    gdb

WORKDIR /code

COPY . .

RUN rm -rf /code/build

ENTRYPOINT [ "sh" ]
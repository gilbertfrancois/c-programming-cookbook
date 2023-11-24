FROM ubuntu:22.04

# Install dependencies
RUN apt update && apt install -y \
    build-essential \
    cmake \
    git \
    libssl-dev \
    pkg-config \
    wget \
    && rm -rf /var/lib/apt/lists/*

COPY llvm.list /etc/apt/sources.list.d/llvm.list

RUN wget -qO- https://apt.llvm.org/llvm-snapshot.gpg.key | tee /etc/apt/trusted.gpg.d/apt.llvm.org.asc

RUN apt update && apt install -y \
    clang-17 \
    lldb-17 \
    lld-17 \
    clangd-17 \
    clang-format-17 \
    clang-tidy-17 \
    && rm -rf /var/lib/apt/lists/*

ENV CC=clang-17
ENV CXX=clang++-17

WORKDIR /workdir

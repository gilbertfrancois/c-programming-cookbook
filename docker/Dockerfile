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

COPY ./llvm.list /etc/apt/sources.list.d/llvm.list

RUN wget -qO- https://apt.llvm.org/llvm-snapshot.gpg.key | tee /etc/apt/trusted.gpg.d/apt.llvm.org.asc

RUN apt update && apt install -y \
    clang-16 \
    lldb-16 \
    lld-16 \
    clangd-16 \
    clang-format-16 \
    clang-tidy-16 \
    && rm -rf /var/lib/apt/lists/*

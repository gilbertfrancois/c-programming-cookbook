# C Programming Cookbook

_Gilbert François Duivesteijn_

## About

This repository contains some personal notes as running code and snipplets that can be used as receipes for common tasks for programming in C. 



"Everything must be made as simple as possible, but not one bit simpler." -- *Albert Einstein*, 1962



## Develop on the local machine (macOS, Linux)

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
cmake --install build
```

All binaries are now installed in the `./dist` folder.



## Develop with Docker

*(Tested with docker version 20.10.22)*

If you want to use the latest stable LLVM compiler and debugger, you can use this Docker image, instead of installing the toolchain on your machine. The idea is that you edit the source files with your favourite editor on the host and run/debug in a Docker container, to have a consistent working environment. The whole project folder is mounted inside the docker container in the folder `/workdir`.

Start (and build) the docker container in *detached* mode with:

```sh
docker compose up -d
```

To build run and debug the code, just add `docker container exec c-programming-cookbook-dev-1` to your normal build cmake commands:

```sh
docker container exec c-programming-cookbook-dev-1 \
    cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug

docker container exec c-programming-cookbook-dev-1 \
    cmake --build build

docker container exec c-programming-cookbook-dev-1 \
    cmake --install build


# Run your program, e.g. 'ascii'
docker container exec c-programming-cookbook-dev-1 \
    ./dist/ascii
    
# Debug your program:
docker container exec -it --security-opt=seccomp:unconfined c-programming-cookbook-dev-1 \
    lldb-16 ./dist/ascii
```

Stop the docker with:

```
docker compose down
```



## Develop with Docker, the easy way

Install [just](https://github.com/casey/just) and use the following commands (note that the steps are *just* aliases of the aforementioned commands):

```sh
# Start the docker
docker compose up -d

just init
just build
just install
just run ./dist/ascii     # Or another program ;)

just debug ./dist/ascii   # debug with lldb

# Stop the docker when you're done
docker compose down
```



## Trouble shooting

- If you get strange errors from cmake, just delete the `build` and `dist` folders and try again.
- If you have no permission to edit or delete the content of `build` or `dist` folder after using docker, add `sudo` to your command. The docker is running as root and writes with root permissions to these folders.

- If you try to connect with `lldb` to a binary and get the error `Operation not permitted`, it has likely to do with lack of permissions in Docker [[1](https://stackoverflow.com/questions/19215177/how-to-solve-ptrace-operation-not-permitted-when-trying-to-attach-gdb-to-a-pro)] [[2](https://linux-audit.com/protect-ptrace-processes-kernel-yama-ptrace_scope/)]. Add `--security-opt=seccomp:unconfined` to your docker command or add 

  ```yaml
  security_opt:
        - seccomp:unconfined
  ```

​		to the `docker-compose.yaml` file.

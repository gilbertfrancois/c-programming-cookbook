# C Programming Cookbook

_Gilbert François Duivesteijn_

## About

This repository contains some simple snipplets that can be used as receipes for common tasks for programming in C.



## Build on the local machine (macOS, Linux)

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
cmake --install build
```

All binaries are now installed in the `./dist` folder.



## Build with Docker

If you want to use the latest stable LLVM compiler and debugger, you can use this docker image, instead of installing it on your machine. Start (and build) the docker container in *detached* mode with:

```sh
docker compose up -d
```

To build and run the code, just add `docker container exec c-programming-cookbook-dev-1` to your normal build cmake commands:

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
```

Stop the docker with:

```
docker compose down
```



## Build with Docker, the easy way

Install [just](https://github.com/casey/just) and use the following commands (note that the steps are *just* aliases of the aforementioned commands:

```sh
# Start the docker
docker compose up -d

just init
just build
just install
just run ./dist/ascii   # Or another program ;)

just debug ./dist/ascii # debug with lldb

# Stop the docker when you're done
docker compose down
```



## Trouble shooting

- If you get strange errors from cmake, just delete the `build` and `dist` folders and try again.
- If you have no permission to edit or delete the content of `build` or `dist` folder after using docker, add `sudo` to your command. The docker is running as root and writes with root permissions to these folders.

- If you try to connect with `lldb` to a binary and get the error `Operation not permitted`, it has likely to do with lack of permissions in docker. Add `--security-opt=seccomp:unconfined` to your docker command or add 

  ```yaml
  security_opt:
        - seccomp:unconfined
  ```

​		to the `docker-compose.yaml` file.

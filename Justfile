default:
    @just --list

init:
    docker container exec c-programming-cookbook-dev-1 cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

build:
    docker container exec c-programming-cookbook-dev-1 cmake --build build

install:
    docker container exec c-programming-cookbook-dev-1 cmake --install build

run arg:
    docker container exec c-programming-cookbook-dev-1 {{arg}}

debug arg:
    docker container exec -it c-programming-cookbook-dev-1 lldb-16 {{arg}}
    
clean:
    rm -rf dist build

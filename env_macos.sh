# Additional environment settings for macOS, in case you want to use the latest
# version of LLVM, clang and lldb from homebrew.
#
# Before running cmake, run:
# source env_macos.sh

PREFIX=`brew --prefix`

export LDFLAGS="-L${PREFIX}/opt/llvm/lib"
export CPPFLAGS="-I${PREFIX}/opt/llvm/include"
export LDFLAGS="-L${PREFIX}/opt/llvm/lib/c++ -Wl,-rpath,${PREFIX}/opt/llvm/lib/c++"
export export PATH="${PREFIX}/opt/llvm/bin:$PATH"
export CC="${PREFIX}/opt/llvm/bin/clang"
export CXX="${PREFIX}/opt/llvm/bin/clang++"


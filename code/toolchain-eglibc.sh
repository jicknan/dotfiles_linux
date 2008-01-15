# !/bin/bash
# this little script is based on the cross building
# intructions mentioned on eglibc.org
# This downloads the sources and builds and installs them
# if you find any problem with this script you
# are most welcome to fix it.
# 
# Original author: Khem Raj <kraj@mvista.com>
# Modified by Jim Huang <jserv.tw@gmail.com>
# Modified by Jick nan <jicknan@gmail.com> at 2008-01-15

if [[ $# -lt 1 || $# -gt 2 ]]; then
    echo "
    Usage: buildtoolchain <arch>
    Example: buildtoolchain.sh x86
    "
    exit 1
fi

build=i686-pc-linux-gnu
host=$build
binutilsv=binutils-2.17.50.0.17
gccv=gcc-4.1.2
linuxv=linux-2.6.23.12
libcv=eglibc

cpus=`cat /proc/cpuinfo |grep processor|wc -l`
proc_per_cpu=2
parallelism=$(($cpus * $proc_per_cpu))
additional_gcc_configure_opts=

case $1 in
    ppc)
        target=powerpc-none-linux-gnu
        linux_arch=powerpc
        ;;
    arm)
        target=arm-none-linux-gnueabi
        linux_arch=arm
        ;;
    x86)
        target=i486-linux-gnu
        linux_arch=i386
        additional_gcc_configure_opts="--with-arch=i486"
        ;;
    mips)
        target=mips-none-linux-gnu
        linux_arch=mips
        ;;
    *)
        echo "Specify one {arm x86 ppc mips} architecture to build."
        exit 1
        ;;
esac

top=$HOME/cross-build/$target
src=$HOME/cross-build/src

obj=$top/obj
tools=$top/tools
sysroot=$top/sysroot

# Workaround
mkdir -p $tools/info/dir

set -x
mkdir -p $src
pushd $src
if [ ! -d $linuxv ]; then
[ -f $linuxv.tar.bz2 ] || wget http://www.kernel.org/pub/linux/kernel/v2.6/$linuxv.tar.bz2
tar -xjf $linuxv.tar.bz2
fi
if [ ! -d $gccv ]; then
[ -f $gccv.tar.bz2 ] || wget ftp://mirrors.kernel.org/gnu/gcc/$gccv/$gccv.tar.bz2
tar -xjf $gccv.tar.bz2
fi
if [ ! -d $binutilsv ]; then
[ -f $binutilsv.tar.bz2 ] || wget http://www.kernel.org/pub/linux/devel/binutils/$binutilsv.tar.bz2
tar -xjf $binutilsv.tar.bz2
fi
if [ ! -d $libcv ]; then
svn co svn://svn.eglibc.org/trunk eglibc
pushd eglibc/libc
ln -s ../ports .
popd
fi
popd

mkdir -p $obj/binutils
cd $obj/binutils
$src/$binutilsv/configure \
     --target=$target \
     --prefix=$tools \
     --with-sysroot=$sysroot || exit
make -j $parallelism || exit
make -j $parallelism install || exit


mkdir -p $obj/gcc1
cd $obj/gcc1
$src/$gccv/configure \
     --target=$target \
     --prefix=$tools \
     --without-headers --with-newlib \
     --disable-shared --disable-threads --disable-libssp \
     --disable-libgomp --disable-libmudflap \
     --enable-languages=c $additional_gcc_configure_opts || exit
PATH=$tools/bin:$PATH make -j $parallelism || exit
PATH=$tools/bin:$PATH make -j $parallelism install || exit

cp -r $src/$linuxv $obj/linux
cd $obj/linux


PATH=$tools/bin:$PATH \
make -j $parallelism headers_install \
      ARCH=$linux_arch CROSS_COMPILE=$target- \
      INSTALL_HDR_PATH=$sysroot/usr || exit


mkdir -p $obj/eglibc-headers
cd $obj/eglibc-headers
BUILD_CC=gcc \
CC=$tools/bin/$target-gcc \
CXX=$tools/bin/$target-g++ \
AR=$tools/bin/$target-ar \
RANLIB=$tools/bin/$target-ranlib \
$src/eglibc/libc/configure \
    --prefix=/usr \
    --with-headers=$sysroot/usr/include \
    --build=$build \
    --host=$target \
    --disable-profile --without-gd --without-cvs --enable-add-ons || exit

make PARALLELMFLAGS=-j$parallelism install-headers install_root=$sysroot \
                     install-bootstrap-headers=yes || exit

mkdir -p $sysroot/usr/lib
make csu/subdir_lib
cp csu/crt1.o csu/crti.o csu/crtn.o $sysroot/usr/lib
$tools/bin/$target-gcc -nostdlib -nostartfiles -shared -x c /dev/null \
                       -o $sysroot/usr/lib/libc.so || exit

mkdir -p $obj/gcc2
cd $obj/gcc2
$src/$gccv/configure \
    --target=$target \
    --prefix=$tools \
    --with-sysroot=$sysroot \
    --disable-libssp --disable-libgomp --disable-libmudflap \
    --enable-languages=c $additional_gcc_configure_opts || exit
PATH=$tools/bin:$PATH make -j $parallelism || exit
PATH=$tools/bin:$PATH make -j $parallelism install || exit


mkdir -p $obj/eglibc
cd $obj/eglibc
BUILD_CC=gcc \
CC=$tools/bin/$target-gcc \
CXX=$tools/bin/$target-g++ \
AR=$tools/bin/$target-ar \
RANLIB=$tools/bin/$target-ranlib \
$src/eglibc/libc/configure \
    --prefix=/usr \
    --with-headers=$sysroot/usr/include \
    --build=$build \
    --host=$target \
    --disable-profile --without-gd --without-cvs --enable-add-ons || exit
PATH=$tools/bin:$PATH make PARALLELMFLAGS=-j$parallelism || exit
PATH=$tools/bin:$PATH make PARALLELMFLAGS=-j$parallelism install \
    install_root=$sysroot || exit

mkdir -p $obj/gcc3
cd $obj/gcc3
$src/$gccv/configure \
    --target=$target \
    --prefix=$tools \
    --with-sysroot=$sysroot \
    --disable-libssp --disable-libgomp --disable-libmudflap \
    --enable-languages=c,c++ $additional_gcc_configure_opts
PATH=$tools/bin:$PATH make -j $parallelism
PATH=$tools/bin:$PATH make -j $parallelism install


cp -d $tools/$target/lib/libgcc_s.so* $sysroot/lib
cp -d $tools/$target/lib/libstdc++.so* $sysroot/usr/lib

# testing eglibc in cross env

#cd $obj/eglibc
#make cross-test-wrapper='sh $HOME/cross-build/src/eglibc/libc/scripts/cross-test-ssh.sh apollo' -k tests

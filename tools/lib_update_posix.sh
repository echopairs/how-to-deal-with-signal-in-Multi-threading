#!/bin/bash
#-------------------------------------
# Filename: lib_update_posix.sh
# Revision: 1.0
# Data: 2017/5/4
# Des: build Dependent libraries
# Env: Ubuntu 16.04.1
#-------------------------------------

script=$(readlink -f "$0")
route=$(dirname "$script")

EXTERNAL_LIBS_DIR="$route"/../third_parties
LIBS_RPM=$EXTERNAL_LIBS_DIR/libs_rpm # save external_libs rpm Reduce project members compile time

HAS_CHECKINSTALL=`which checkinstall >/dev/null 2>&1 && echo true || echo false` # checkinstall

GPERTOOLS_VERSION=2.5.0

mkdir -p $EXTERNAL_LIBS_DIR/libs_rpm

# 1. judge external_libs if exist && depends
if [ ! -d "$route/"../third_parties ]; then
  echo "---external_libs dir is not exist,  mkdir third_parties "
  mkdir -p "$route"/../third_parties
fi
## check checkinstall if exist
if [ "$HAS_CHECKINSTALL"x = "false"x ]; then
echo "--please install checkinstall first"
echo "-- down src : git clone http://checkinstall.izto.org/checkinstall.git"
exit -1;
fi

# 2. init gperftools
sudo apt-get install libunwind-dev
sudo apt-get install graphviz 

if [ ! -f "$route/"../third_parties/gperftools.tar.gz ]; then
  echo "--- gperftools is not exist , git clone https://github.com/gperftools/gperftools.git down it"
  cd "$route"/../third_parties
  git clone https://github.com/gperftools/gperftools.git
  cd "$EXTERNAL_LIBS_DIR"/gperftools
  git checkout -b gperftools-2.5
else
  tar -zxvf "$EXTERNAL_LIBS_DIR"/gperftools.tar.gz -C $EXTERNAL_LIBS_DIR || exit -2
  cd "$EXTERNAL_LIBS_DIR"/gperftools
fi

## gen configure
./autogen.sh || { echo "init autoreconf "; exit -2; }
./configure
make -j 2

if [ -f "$LIBS_RPM"/gperftools-"$GPERTOOLS_VERSION"-1.x86_64.rpm ]; then
  rpm -qa | grep -q gperftools > /dev/null 1>&2 && rpm -e gperftools # remove old
  rpm -ivh "$LIBS_RPM"/gperftools-"$GPERTOOLS_VERSION"-1.x86_64.rpm || { echo "--rpm gperftools is failed"; exit -2; }
else
 sudo  checkinstall -D --install=yes --default --pkgname=gperftools --pkgversion=$GPERTOOLS_VERSION --pakdir=$LIBS_RPM --fstrans=no || { echo "build gperftools rpm is failed"; exit -2; }
fi
## rm the tmp
rm -rf "$EXTERNAL_LIBS_DIR"/gperftools
echo "-------------------init gperftools is success------------------------------"

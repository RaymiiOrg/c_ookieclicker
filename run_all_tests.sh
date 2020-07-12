#!/bin/bash

mkdir -p cmake-build-debug
cd cmake-build-debug

cmake ..
make -j8 all

./src/Game/tst/Game_tst
if [[ $? != 0 ]]; then
  exit 1;
fi

./src/Commands/tst/Commands_tst
if [[ $? != 0 ]]; then
  exit 1;
fi

./src/Wallet/tst/Wallet_tst
if [[ $? != 0 ]]; then
  exit 1;
fi

./src/Store/tst/Store_tst
if [[ $? != 0 ]]; then
  exit 1;
fi


cd ..
#!/bin/bash

if [[ $1 == "runcmake" ]]; then
  mkdir -p cmake-build-debug-no-boost
  pushd cmake-build-debug-no-boost
  cmake .. -DCMAKE_BUILD_TYPE=Debug -G "Unix Makefiles" -DBUILD_TESTS=Y
  make -j8 all
  if [[ $? != 0 ]]; then
    echo "Make failed"
    cd ..
    exit 1;
  fi
fi

if [[ $1 == "runcmakeboost" ]]; then
  mkdir -p cmake-build-debug-with-boost
  pushd cmake-build-debug-with-boost
  cmake .. -DCMAKE_BUILD_TYPE=Debug -G "Unix Makefiles" -DBUILD_TESTS=Y -DUSEBOOST_MPP=Y
  make -j8 all
  if [[ $? != 0 ]]; then
    echo "Make failed"
    cd ..
    exit 1;
  fi
fi

tests="$(cmake --build . --target help | grep -o -E "[a-zA-Z]*_tst")"

for testexecutable in ${tests}; do
  testfolder=${testexecutable%"_tst"}
  testpath=./src/${testfolder}/tst/${testexecutable}
  if [[ ${testexecutable} == "cookieclicker_tst" ]]; then
    continue
  fi
  echo "Running test: ${testpath}"
  ./${testpath}
  if [[ $? != 0 ]]; then
    popd
    exit 1;
  fi
  echo
done

popd

#make checkstyle;

cd ..
#!/bin/bash

mkdir -p cmake-build-debug
cd cmake-build-debug

if [[ $1 == "runcmake" ]]; then
  cmake ..
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
  echo "Running test: ${testpath}"
  ./${testpath}
  if [[ $? != 0 ]]; then
    cd ..
    exit 1;
  fi
  echo
done

make checkstyle;

cd ..
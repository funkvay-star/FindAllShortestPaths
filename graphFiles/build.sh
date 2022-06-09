presentDirectory=$(dirname $0)

rm -rf $presentDirectory/build
mkdir $presentDirectory/build
cd $presentDirectory/build
cmake ..
make
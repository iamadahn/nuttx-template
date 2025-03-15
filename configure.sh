cd nuttx-apps
ln -s ../app custom_app
cd ../nuttx
make distclean
./tools/configure.sh -l ../board/configs/nsh
cd ../nuttx-apps
rm -rf custom_app


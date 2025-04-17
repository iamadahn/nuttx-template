cd nuttx-apps
ln -s ../app custom_app
cd ../nuttx
make menuconfig
cd ../nuttx-apps
rm -rf custom_app

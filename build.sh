cd nuttx-apps
ln -s ../app custom_app
cd ../nuttx
make -j
cd ../nuttx-apps
rm -rf custom_app

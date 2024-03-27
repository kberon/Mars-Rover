Try running make in this directory.

If it doesn't work/it cannot find the directory then do the following:
**NOTE if any of the below steps fail, go to IF STILL DOESN'T WORK section, do not continue running the next commands NOTE**
cd WiringPi
rm wiringpi_3.2_armhf.deb
./build debian
mv wiringpi_3.2_armhf.deb .
sudo apt install ./wiringpi_3.2_armhf.deb



IF IT STILL DOESN'T WORK
return to firware directory
rm -r WiringPi
git clone 
cd WiringPi
./build debian
mv debian-template/wiringpi_3.2_armhf.deb .
sudo apt install ./wiringpi_3.2_armhf.deb 

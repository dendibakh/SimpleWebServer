#/bin/bash

sudo apt-get install libboost-all-dev
git clone https://github.com/nodejs/http-parser.git
cd http-parser
sudo make install

#to update gcc version:
sudo add-apt-repository ppa:ubuntu-toolchain-r/test
sudo apt-get update
sudo apt-get install gcc-4.9 g++-4.9
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.9 60 --slave /usr/bin/g++ g++ /usr/bin/g++-4.9

./final --h=127.0.0.1 --p=12345 --d=/home/bakhvalo/workspace/StepicMultithreading/WebServerDir/
./final --h=127.0.0.1 --p=12345 --d=/home/denis/WorkSpace/WebServerDir/

wget http://localhost:12345/.gitignore

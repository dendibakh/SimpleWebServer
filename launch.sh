#/bin/bash

sudo apt-get install libboost-all-dev
git clone https://github.com/nodejs/http-parser.git
cd http-parser
sudo make install

./final --h=127.0.0.1 --p=12345 --d=/home/bakhvalo/workspace/StepicMultithreading/WebServerDir/
./final --h=127.0.0.1 --p=12345 --d=/home/denis/WorkSpace/WebServerDir/

wget http://localhost:12345/.gitignore

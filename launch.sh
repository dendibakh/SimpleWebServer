#/bin/bash

sudo apt-get install libboost-all-dev
git clone https://github.com/nodejs/http-parser.git
cd http-parser
sudo make install

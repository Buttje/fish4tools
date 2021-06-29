#!/bin/sh

cd slate
sudo docker run --rm --name slate -v $(pwd)/build:/srv/slate/build -v $(pwd)/source:/srv/slate/source slatedocs/slate
cd ../doc
mkdir UserDoc
cp -R ../slate/build/* UserDoc



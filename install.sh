#!/bin/bash
helper=../src/applications/helper
model=../src/applications/model
headers=../build/ns3
echo "Copying program files into NS-3 directory..."

echo "Copying main program file..."
cp ./networkComp0.cc  ../scratch

echo "Copying default testing INI file..."
cp ./testing.ini ../

echo "Copying modified UDP client/server files..."
cp ./udp-echo-client.cc $model
cp ./udp-echo-server.cc $model

# TODO: Uncomment this when we figure out how to instantiate the TCP client/server properly
# echo "Copying TCP client/server files..."
# cp ./tcp-echo-client.cc $model
# cp ./tcp-echo-client.h $model
# cp ./tcp-echo-client.h $headers
# cp ./tcp-echo-server.cc $model
# cp ./tcp-echo-server.h $model
# cp ./tcp-echo-server.h $headers

# echo "Copying TCP echo helper files..."
# cp ./tcp-echo-helper.h $helper
# cp ./tcp-echo-helper.cc $helper

echo "Copying Finished."







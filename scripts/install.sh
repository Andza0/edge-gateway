#!/bin/sh
make build
sudo cp ./systemd/edge-gateway.service /etc/systemd/system/
sudo mkdir -p /etc/edge-gateway
sudo cp ./config/config.conf /etc/edge-gateway/config.conf
sudo cp ./edge-gateway /usr/local/bin/
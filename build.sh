#!/usr/bin/env bash

if [ -z "$1" ]; then
  echo "Usage: $0 [upload|compile]"
  exit 1
fi

if [ "$1" = "upload" ]; then
  echo "Uploading sketch."
  arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:esp32:nano_nora trackball.ino
else
  echo "Compiling sketch."
  arduino-cli compile --fqbn arduino:esp32:nano_nora trackball.ino
fi

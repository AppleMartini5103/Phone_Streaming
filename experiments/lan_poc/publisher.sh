#!/usr/bin/env bash
ffmpeg \
  -re \
  -f lavfi -i "testsrc=size=1280x720:rate=30" \
  -f lavfi -i "sine=frequency=1000:sample_rate=48000" \
  -c:v libx264 -preset ultrafast -tune zerolatency -profile:v baseline -g 60 -pix_fmt yuv420p \
  -c:a aac -b:a 128k -ar 48000 \
  -f rtsp -rtsp_transport tcp \
  rtsp://127.0.0.1:8554/live
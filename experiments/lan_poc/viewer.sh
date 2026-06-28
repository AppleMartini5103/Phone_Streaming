#!/usr/bin/env bash
ffplay \
  -fflags nobuffer -flags low_delay -framedrop \
  -probesize 32 -analyzeduration 0 \
  -rtsp_transport udp rtsp://127.0.0.1:8554/live
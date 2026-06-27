#!/usr/bin/env bash
ffplay \
  -rtsp_transport tcp \
  -fflags nobuffer -flags low_delay -framedrop \
  rtsp://127.0.0.1:8554/live
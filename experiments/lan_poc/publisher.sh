ffmpeg \
  -f x11grab -framerate 30 -video_size 1280x720 -i :1.0+0,0 \
  -c:v libx264 -preset ultrafast -tune zerolatency -profile:v baseline -g 60 -pix_fmt yuv420p \
  -an \
  -f rtsp -rtsp_transport udp \
  rtsp://127.0.0.1:8554/live
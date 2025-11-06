
REM HP HD Camera
REM ffmpeg.exe -f dshow -video_size 1280x720 -i video="HP HD Camera" -c:v libx264 -preset veryfast -tune zerolatency -c:a aac -f rtsp -rtsp_transport tcp -muxdelay 0.1 rtsp://127.0.0.1:8554/mystream
REM ffmpeg.exe -f dshow -video_size 640x480 -i video="HP HD Camera" -c:v libx264 -preset veryfast -tune zerolatency -c:a aac -f rtsp -rtsp_transport tcp -muxdelay 0.1 rtsp://127.0.0.1:8554/mystream
REM 1920x1080 I/O error
REM 1280x720 2.5-5 Mbps
REM 640x480 0.8-1.8 Mbps 

REM j5 WebCam JVU430 - change input
REM ffmpeg.exe -f dshow -video_size 3840x2160 -i video="j5 WebCam JVU430" -c:v libx264 -preset veryfast -tune zerolatency -c:a aac -f rtsp -rtsp_transport tcp -muxdelay 0.1 rtsp://127.0.0.1:8554/mystream
ffmpeg.exe -f dshow -video_size 1920x1080 -i video="j5 WebCam JVU430" -c:v libx264 -preset veryfast -tune zerolatency -c:a aac -f rtsp -rtsp_transport tcp -muxdelay 0.1 rtsp://127.0.0.1:8554/mystream
REM ffmpeg.exe -f dshow -video_size 1280x720 -i video="j5 WebCam JVU430" -c:v libx264 -preset veryfast -tune zerolatency -c:a aac -f rtsp -rtsp_transport tcp -muxdelay 0.1 rtsp://127.0.0.1:8554/mystream
REM ffmpeg.exe -f dshow -video_size 640x480 -i video="j5 WebCam JVU430" -c:v libx264 -preset veryfast -tune zerolatency -c:a aac -f rtsp -rtsp_transport tcp -muxdelay 0.1 rtsp://127.0.0.1:8554/mystream
REM 3840x2160:60 > 20, 無法正確顯示在 NB client 端順暢顯示
REM 1920x1080:60 10-15 Mbps  
REM 1280x720:60 4-7 Mbps
REM 640x480:30 1.6-2.5 Mbps

REM j5 WebCam JVU430 - change outpupt
REM ffmpeg.exe -f dshow -i video="j5 WebCam JVU430" -vf "scale=1920:1080" -c:v libx264 -preset veryfast -tune zerolatency -c:a aac -f rtsp -rtsp_transport tcp -muxdelay 0.1 rtsp://127.0.0.1:8554/mystream
REM ffmpeg.exe -f dshow -i video="j5 WebCam JVU430" -vf "scale=1280:720" -c:v libx264 -preset veryfast -tune zerolatency -c:a aac -f rtsp -rtsp_transport tcp -muxdelay 0.1 rtsp://127.0.0.1:8554/mystream
REM ffmpeg.exe -f dshow -i video="j5 WebCam JVU430" -vf "scale=640:480" -c:v libx264 -preset veryfast -tune zerolatency -c:a aac -f rtsp -rtsp_transport tcp -muxdelay 0.1 rtsp://127.0.0.1:8554/mystream
REM 1920x1080:30 10-15 Mbps
REM 1280x720:30 4-6.4 Mbps 
REM 640x480:30 1.7-2.6 Mbps

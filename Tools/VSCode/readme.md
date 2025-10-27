```
cd mediamtx_v1.15.2_windows_amd64
start mediamtx.exe
cd ..\

timeout 1 /nobreak > NUL

cd ffmpeg-master-latest-win64-gpl-shared\bin
start ffmpeg.exe -f dshow -i video="HP HD Camera" -c:v libx264 -preset veryfast -tune zerolatency -c:a aac -f rtsp -rtsp_transport tcp -muxdelay 0.1 rtsp://127.0.0.1:8554/mystream
start ffmpeg.exe -f dshow -i video="j5 WebCam JVU430" -c:v libx264 -preset veryfast -tune zerolatency -c:a aac -f rtsp -rtsp_transport tcp -muxdelay 0.1 -vf "scale=1920:1080" rtsp://127.0.0.1:8554/mystream
cd ..\..\

cd iperf3.13_64
start iperf3.exe -s -i1
cd ..\

pause

```

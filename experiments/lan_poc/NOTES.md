# LAN RTSP PoC (어댑터)
구성: A(ffmpeg push) → mediamtx(RTSP 서버 :8554) → B(ffplay pull)

## 도구 (핀 버전)
- ffmpeg/ffplay 6.1.1 (시스템 apt)
- mediamtx v1.12.3 (단일 바이너리, git 제외)
  받기: wget https://github.com/bluenviron/mediamtx/releases/download/v1.12.3/mediamtx_v1.12.3_linux_amd64.tar.gz && tar xzf ...

## mediamtx를 git에 커밋하지 않는 이유
- 히스토리에 영구 잔존 → 저장소 부풀고, 지워도 clone마다 계속 받아짐.
- 핀 버전 다운로드 가능

## 실행 (터미널 3개)
1. ./mediamtx          # RTSP 서버
2. bash publisher.sh   # A push → rtsp://127.0.0.1:8554/live
3. bash viewer.sh      # B pull

## 결과
- [v] 같은 PC 재생 OK (컬러바+타이머 영상 + 1kHz 오디오)
- [ ] 다른 기기에서 LAN IP 재생
- [ ] 지연 실측
- [ ] UDP vs TCP 비교
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
- [v] 다른 기기에서 LAN IP 재생
- [v] 지연 실측 (~300ms대, 아래 참고)
- [v] UDP vs TCP 비교 (localhost에선 동등, 아래 참고)

## 지연 측정 (2026-06-28)
방법: ms 시계(clock.html)를 브라우저로 띄우고, publisher 입력을
testsrc → x11grab 화면캡처로 교체해 그 시계 화면을 송출.
같은 PC 한 화면에서 ffplay(저지연)로 재생 → 스크린샷 1장에
[진짜 시계]와 [영상 속 시계]를 같이 잡아 차이 = 전체 파이프라인 지연.
표본 5장 평균. 정밀도: 캡처·재생 30fps → 약 ±33ms 양자화.

ffplay 저지연 옵션:
  -fflags nobuffer -flags low_delay -framedrop -probesize 32 -analyzeduration 0

| 트랜스포트 | 평균 지연 | 범위 (5장) |
|---|---|---|
| TCP | 306 ms | 299~317 |
| UDP | 313 ms | 298~319 |

결론:
- 파이프라인 순수 지연 ~300ms대 (localhost라 네트워크 지연 ≈ 0).
- TCP ≈ UDP: localhost는 패킷 손실 0이라 TCP 재전송이 안 일어남.
  → 지연의 주범은 트랜스포트가 아니라 인코딩 + ffplay 표시 버퍼.
- 트랜스포트(UDP vs TCP) 최종 선택은 손실 있는 실제 네트워크(M4)로 보류.
  (PROGRESS "아직 안 정한 것"과 일치 — 데이터로 "지금은 못 정한다" 확인)

## 측정 시 함정 메모
- 뷰어 두 개(ffplay vs VLC) 비교는 지연 측정이 아님 — 둘 다 자기 버퍼만큼
  늦어 ground truth가 없음. 반드시 "진짜 시계 vs 영상 속 시계"로.
- x11grab은 모니터 앞 데스크톱 세션에서 실행해야 함 (SSH 터미널은 화면 연결 없음).
- DISPLAY=:1 (GDM이 :0 점유). publisher는 :0.0 하드코딩 대신 $DISPLAY+0,0 권장.
- ffplay 창은 캡처 영역 "바깥"에 둘 것 — 안에 두면 무한 거울(피드백 루프).
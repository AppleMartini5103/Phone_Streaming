#pragma once
#include <cstdint>
#include <memory>

namespace streamcore {

enum class MediaType  { Video, Audio };
enum class VideoCodec { H264, H265 };
enum class AudioCodec { AAC, Opus };

class BufferRef;

struct RawVideoFrame {
    std::shared_ptr<BufferRef> data;
    int     width  = 0;
    int     height = 0;
    int     rotation = 0;            // 0/90/180/270
    int64_t pts_us = 0;             // presentation timestamp (마이크로초)
    int64_t capture_mono_ns = 0;    // 캡처 시점 단조 클럭 (A/V 싱크 기준)
};

struct RawAudioFrame {
    std::shared_ptr<BufferRef> data;
    int     sampleRate = 0;
    int     channels   = 0;
    int     frames     = 0;         // 채널당 샘플 수
    int64_t pts_us = 0;
    int64_t capture_mono_ns = 0;
};

struct EncodedFrame {
    MediaType type = MediaType::Video;
    std::shared_ptr<BufferRef> data;
    int64_t pts_us = 0;
    int64_t dts_us = 0;
    bool    keyframe = false;
};

struct RtpPacket {
    std::shared_ptr<BufferRef> data;
    int64_t recv_mono_ns = 0;       // 수신 시점
};

const char* version();

} // namespace streamcore
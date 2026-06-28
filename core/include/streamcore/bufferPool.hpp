#pragma once
#include <mutex>
#include <cstdint>
#include <cstddef>
#include <memory>
#include <vector>
#include "streamcore/types.hpp"

namespace streamcore {

class BufferPool;

class BufferRef {
public:
    BufferRef(BufferPool* pool, size_t index, uint8_t* data, size_t capacity);
    ~BufferRef();

    uint8_t* data();
    size_t size() const;
    size_t capacity() const;
    void setSize(size_t n);

    BufferRef(const BufferRef&) = delete;
    BufferRef& operator=(const BufferRef&) = delete;

private:
    BufferPool* pool_;
    size_t index_;
    uint8_t* data_;
    size_t capacity_;
    size_t size_ = 0;
};

class BufferPool {
public:
    BufferPool(size_t slotCount, size_t slotCapacity);
    std::shared_ptr<BufferRef> acquire();
    size_t available() const;

private:
    void release(size_t index);
    friend class BufferRef;

    std::vector<std::vector<uint8_t>> slots_;
    std::vector<size_t> freeList_;
    mutable std::mutex mtx_;
};

}
#include "streamcore/bufferPool.hpp"

namespace streamcore {

BufferRef::BufferRef(BufferPool* pool, size_t index, uint8_t* data, size_t capacity)
    : pool_(pool), index_(index), data_(data), capacity_(capacity) {
}

BufferRef::~BufferRef() {
    pool_->release(index_);
}

uint8_t* BufferRef::data() { return data_; }
size_t BufferRef::size() const { return size_; }
size_t BufferRef::capacity() const { return capacity_; }
void BufferRef::setSize(size_t n) { size_ = n; }


BufferPool::BufferPool(size_t slotCount, size_t slotCapacity) {
    slots_.resize(slotCount);
    for (size_t i = 0; i < slotCount; ++i) {
        slots_[i].resize(slotCapacity);
        freeList_.push_back(i);
    }
}

std::shared_ptr<BufferRef> BufferPool::acquire() {
    std::lock_guard<std::mutex> lock(mtx_);

    if (freeList_.empty()) return nullptr;

    size_t index = freeList_.back();
    freeList_.pop_back();

    uint8_t* ptr = slots_[index].data();
    size_t cap = slots_[index].size();

    return std::make_shared<BufferRef>(this, index, ptr, cap);
}

void BufferPool::release(size_t index) {
    std::lock_guard<std::mutex> lock(mtx_);

    freeList_.push_back(index);
}

size_t BufferPool::available() const {
    std::lock_guard<std::mutex> lock(mtx_);
    
    return freeList_.size();
}

} // namespace streamcore
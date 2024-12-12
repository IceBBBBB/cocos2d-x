#include "CCData.h"
#include <cstring>
#include <stdlib.h>

//#include "base/Log.h"

namespace cocos2d { namespace experimental {

const Data Data::NULL_DATA;

Data::Data() = default;

Data::Data(Data &&other) noexcept {
    //    CC_LOG_INFO("In the move constructor of Data.");
    move(other);
}

Data::Data(const Data &other) {
    //    CC_LOG_INFO("In the copy constructor of Data.");
    copy(other._bytes, other._size);
}

Data::~Data() {
    //    CC_LOG_INFO("deallocing Data: %p", this);
    clear();
}

Data &Data::operator=(const Data &other) {
    //    CC_LOG_INFO("In the copy assignment of Data.");
    if (this != &other) {
        copy(other._bytes, other._size);
    }
    return *this;
}

Data &Data::operator=(Data &&other) noexcept {
    //    CC_LOG_INFO("In the move assignment of Data.");
    move(other);
    return *this;
}

void Data::move(Data &other) {
    clear();

    _bytes = other._bytes;
    _size = other._size;

    other._bytes = nullptr;
    other._size = 0;
}

bool Data::isNull() const {
    return (_bytes == nullptr || _size == 0);
}

uint8_t *Data::getBytes() const {
    return _bytes;
}

uint32_t Data::getSize() const {
    return _size;
}

void Data::copy(const unsigned char *bytes, uint32_t size) {
    clear();

    if (size > 0) {
        _size = size;
        _bytes = static_cast<unsigned char *>(malloc(sizeof(unsigned char) * _size));
        memcpy(_bytes, bytes, _size);
    }
}

void Data::fastSet(unsigned char *bytes, uint32_t size) {
    free(_bytes);
    _bytes = bytes;
    _size = size;
}

void Data::resize(uint32_t size) {
    CC_ASSERT(size);
    if (_size == size) {
        return;
    }
    _size = size;
    _bytes = static_cast<unsigned char *>(realloc(_bytes, sizeof(unsigned char) * _size));
}

void Data::clear() {
    free(_bytes);
    _bytes = nullptr;
    _size = 0;
}

uint8_t *Data::takeBuffer(uint32_t *size) {
    auto *buffer = getBytes();
    if (size) {
        *size = getSize();
    }

    _bytes = nullptr;
    _size = 0;
    return buffer;
}

}} // namespace cocos2d { namespace experimental

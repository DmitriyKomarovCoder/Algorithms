#pragma once
#include <iostream>
#include <vector>

typedef unsigned char byte;

struct IInputStream {
    // Возвращает false, если поток закончился
    virtual bool Read(byte& value) = 0;
};

struct IOutputStream {
    virtual void Write(byte value) = 0;
};


class VectorOutput : public IOutputStream {
public:
    VectorOutput(std::vector<byte>* output_buffer): buf(output_buffer) {

    }

    virtual void Write(byte value) {
        buf->push_back(value);
    }
    virtual bool ReadTest(byte& value) {
        size_t pos = 0;
        if (pos >= buf->size())
            return false;
        value = (*buf)[pos++];
        return true;
    }

private:
    std::vector<byte>* buf;
};


class VectorInput : public IInputStream {
 public:
    VectorInput(std::vector<byte>* input_buffer ) : buf(input_buffer), pos(0) {}
    virtual bool Read(byte& value) {
        if (pos >= buf->size())
            return false;
        value = (*buf)[pos++];
        return true;
    }

 private:
    std::vector<byte>* buf;
    size_t pos;
};

class BitReader {
 public:
    BitReader(IInputStream& in_stream) : in(in_stream), buf(0), pos(0) {}

    bool read_bit(byte& value) {
        if (pos == 0) {
            bool res = in.Read(buf);
            if (!res) {
                return false;
            }
        }

        value = (buf >> (7 - pos++)) & 1;
        if (pos == 8) {
            pos = 0;
        }
        return true;
    }

    void SkipBits(int count) {
        pos += count;
        if (pos >= 8) {
            byte temp;
            while (pos >= 8) {
                pos -= 8;
                in.Read(temp);
            }
            buf = temp;
        }
    }

 private:
    IInputStream& in;
    byte buf;
    int pos;
};


class BitWriter {
 public:
    BitWriter()
    : bitCount(0) {}

    void WriteBit(unsigned char bit) {
        if (bitCount % 8 == 0) {
            buffer.push_back(0);
        }
        if (bit) {
            buffer[bitCount/8] |= 1 << (7 - bitCount % 8);
        }
        bitCount++;
    }

    void WriteByte(unsigned char byte) {
        if (bitCount % 8 == 0) {
            buffer.push_back(byte);
        } else {
            int offset = bitCount % 8;
            buffer[bitCount/8] |= byte >> offset;
            buffer.push_back(byte << (8 - offset));
        }
        bitCount += 8;
    }

    const std::vector<unsigned char> &GetBuffer() const {
        return buffer;
    }

    size_t GetBitCount() const {
        return bitCount;
    }

 private:
    std::vector<unsigned char> buffer;
    size_t bitCount;
};

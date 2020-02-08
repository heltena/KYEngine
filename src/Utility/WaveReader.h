#pragma once

#include <string>

class WaveReader
{
public:
    WaveReader(const std::string& filename);
    virtual ~WaveReader();

public:
    enum FormatCode {
        WAVE_FORMAT_PCM        = 0x0001,
        WAVE_FORMAT_IEEE_FLOAT = 0x0003,
        WAVE_FORMAT_ALAW       = 0x0006,
        WAVE_FORMAT_MULAW      = 0x0007,
        WAVE_FORMAT_EXTENSIBLE = 0xFFFE
    };

public:
    const std::string& filename() const { return m_filename; }
    bool validInfo() const { return m_validInfo; }
    void* buffer() const { return m_buffer; }
    int len() const { return m_len; }
    int frequency() const { return m_frequency; }

private:
    const std::string convertToString(unsigned char* buff, int len);
    int convertToInt16(unsigned char* buff);
    int convertToInt32(unsigned char* buff);
    void readRawBuffer(FILE* f, unsigned char* buff, int len, const std::string& msgError);
    void compareString(unsigned char* buff, int len, const std::string& compare, const std::string& msgError);
    int readFmtChunk(FILE* f);
    int readFLLRChunk(FILE* f);
    int readDataChunk(FILE* f);
    int readUnknownChunk(FILE* f);
    void read();

private:
    std::string m_filename;
    bool m_validInfo;
    unsigned char * m_buffer;
    int m_len;
    int m_frequency;
};
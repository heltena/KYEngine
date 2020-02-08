#include <KYEngine/Utility/WaveReader.h>
#include <KYEngine/Private/Natives/NativeUtils.h>

#include <iostream>
#include <sstream>
#include <stdexcept>

WaveReader::WaveReader(const std::string& filename)
    : m_filename(filename)
    , m_validInfo(false)
    , m_buffer(NULL)
    , m_len(0)
{
    read();
}

WaveReader::~WaveReader()
{
    if (m_buffer)
        delete m_buffer;
}

const std::string WaveReader::convertToString(unsigned char* buff, int len)
{
    char result[len + 1];
    memcpy(result, buff, len);
    result[len] = 0;
    return std::string(result);
}

int WaveReader::convertToInt16(unsigned char* buff)
{
    int result = buff[0];
    result |= buff[1] << 8;
    return result;
}

int WaveReader::convertToInt32(unsigned char* buff)
{
    int result = buff[0];
    result |= buff[1] << 8;
    result |= buff[2] << 16;
    result |= buff[3] << 24;
    return result;
}

void WaveReader::readRawBuffer(FILE* f, unsigned char* buff, int len, const std::string& msgError)
{
    size_t rd = fread(buff, 1, len, f);
    if (rd != len) {
        std::stringstream ss;
        ss << msgError << " (read " << rd << " of " << len << ") " << m_filename;
        throw std::runtime_error(ss.str());
    }
}

void WaveReader::compareString(unsigned char* buff, int len, const std::string& compare, const std::string& msgError)
{
    if (convertToString(buff, 4) != compare)
        throw std::runtime_error(msgError + ": " + m_filename);
}

void WaveReader::read()
{
    m_validInfo = false;
    
    FILE* f = fopen(m_filename.c_str(), "rb");
    if (NULL == f)
        throw std::runtime_error("File not found: " + m_filename);
    
    unsigned char tmp[5];

    readRawBuffer(f, tmp, 4, "RIFF Header error");
    compareString(tmp, 4, "RIFF", "RIFF error");
    
    readRawBuffer(f, tmp, 4, "ckSize error");
    int ckSize = convertToInt32(tmp);

    readRawBuffer(f, tmp, 4, "waveId error");
    compareString(tmp, 4, "WAVE", "waveId error");

    ckSize -= 4; // WAVE info

    m_len = 0;
    while (ckSize > 0) {
        readRawBuffer(f, tmp, 4, "chunk id error");
        std::string ckId = convertToString(tmp, 4);
        ckSize -= 8; // for ckId + subCkSize
        
        if (ckId == "fmt ")
            ckSize -= readFmtChunk(f);
        else if (ckId == "FLLR")
            ckSize -= readFLLRChunk(f);
        else if (ckId == "data")
            ckSize -= readDataChunk(f);
        else
            ckSize -= readUnknownChunk(f);
    }
    
    m_validInfo = m_len > 0;
    fclose(f);
}

int WaveReader::readFmtChunk(FILE* f)
{
    unsigned char tmp[5];

    readRawBuffer(f, tmp, 4, "ckHeaderSize error");
    int ckSize = convertToInt32(tmp);
    
    if (ckSize != 16 && ckSize != 18 && ckSize != 40) {
        std::stringstream ss;
        ss << "ckSize error (" << ckSize << "): " << m_filename;
        throw std::runtime_error(ss.str());
    }
    
    readRawBuffer(f, tmp, 2, "wFormatTag");
    int wFormatTag = convertToInt16(tmp);
    if (wFormatTag != WAVE_FORMAT_PCM) {
        std::stringstream ss;
        ss << "Bad format: " << wFormatTag << ": " << m_filename;
        throw std::runtime_error(ss.str());
    }
    
    readRawBuffer(f, tmp, 2, "nChannels");
    int nChannels = convertToInt16(tmp);
    if (nChannels != 1)
        throw std::runtime_error("Only mono format: " + m_filename);

    readRawBuffer(f, tmp, 4, "nSamplesPerSec");
    int nSamplesPerSec = convertToInt32(tmp);
    if (nSamplesPerSec != 44100)
        throw std::runtime_error("Only 44100 Hz: " + m_filename);
    
    m_frequency = nSamplesPerSec;

    readRawBuffer(f, tmp, 4, "nAvgBytesPerSec");
    /*int nAvgBytesPerSec = convertToInt32(tmp);*/
    
    readRawBuffer(f, tmp, 2, "nBlockAlign");
    /*int nBlockAlign = convertToInt16(tmp);*/
    
    readRawBuffer(f, tmp, 2, "wBitsPerSample");
    /*int wBitsPerSample = convertToInt16(tmp);*/

    int cbSize = 0;
    if (ckSize > 16) {
        readRawBuffer(f, tmp, 2, "cbSize");
        cbSize = convertToInt16(tmp);
    }
    
    int wValidBitsPerSample = 0;
    int dwChannelMask = 0;
    unsigned char subFormat[16];
    if (ckSize > 18) {
        readRawBuffer(f, tmp, 2, "wValidBitsPerSample");
        wValidBitsPerSample = convertToInt16(tmp);
        
        readRawBuffer(f, tmp, 4, "dwChannelMask");
        dwChannelMask = convertToInt16(tmp);
        
        readRawBuffer(f, subFormat, 16, "subFormat");
    }
    
    return ckSize;
}

int WaveReader::readFLLRChunk(FILE* f)
{
    unsigned char buff[5];
    readRawBuffer(f, buff, 4, "ckSize FLLR Chunk");
    int ckSize = convertToInt32(buff);
    fseek(f, ckSize, SEEK_CUR);
    return ckSize;
}

int WaveReader::readDataChunk(FILE* f)
{
    unsigned char buff[5];
    readRawBuffer(f, buff, 4, "ckSize FLLR Chunk");
    int ckSize = convertToInt32(buff);

    m_len = ckSize;
    m_buffer = new unsigned char [m_len];
    readRawBuffer(f, m_buffer, m_len, "Raw Data");
    return ckSize;
}

int WaveReader::readUnknownChunk(FILE* f)
{
    unsigned char buff[5];
    readRawBuffer(f, buff, 4, "ckSize Unknown Chunk");
    int ckSize = convertToInt32(buff);
    fseek(f, ckSize, SEEK_CUR);
    return ckSize;
}


#include "DeviceDriver.h"
#include <stdexcept>
#include <string>

class ReadFailException : public std::logic_error {
public:
    using _Mybase = logic_error;
    explicit ReadFailException(const std::string& _Message) : _Mybase(_Message.c_str()) {}
    explicit ReadFailException(const char* _Message) : _Mybase(_Message) {}
};
class WriteFailException : public std::logic_error {
public:
    using _Mybase = logic_error;
    explicit WriteFailException(const std::string& _Message) : _Mybase(_Message.c_str()) {}
    explicit WriteFailException(const char* _Message) : _Mybase(_Message) {}
};

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    // TODO: implement this method properly
    return (int)(m_hardware->read(address));
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}
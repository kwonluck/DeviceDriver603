#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../DeviceDriver/DeviceDriver.cpp"

using namespace testing;

class FlashMemoryDeviceMock : public FlashMemoryDevice {
public:
    MOCK_METHOD(unsigned char, read, (long), (override));
    MOCK_METHOD(void, write, (long, unsigned char), (override));
};

class DeviceDriverFixture : public testing::Test {
public:
    FlashMemoryDeviceMock memory;
    DeviceDriver driver{ &memory };
};

TEST_F(DeviceDriverFixture, ReadExceptionWhenReturndiffvaluewhile5count) {
    EXPECT_CALL(memory, read)
        .WillOnce(Return(0x02))
        .WillOnce(Return(0x02))
        .WillOnce(Return(0x02))
        .WillOnce(Return(0x02))
        .WillOnce(Return(0x32));

    EXPECT_THROW(driver.read(1), ReadFailException);
}

TEST_F(DeviceDriverFixture, ReadExceptionWhenReturndiffvaluewhile2count) {
    EXPECT_CALL(memory, read)
        .WillOnce(Return(0x02))
        .WillOnce(Return(0x03));
    EXPECT_THROW(driver.read(1), ReadFailException);
}

TEST_F(DeviceDriverFixture, ReadMethod) {
    EXPECT_CALL(memory, read)
        .Times(5)
        .WillOnce(Return(0x02))
        .WillOnce(Return(0x02))
        .WillOnce(Return(0x02))
        .WillOnce(Return(0x02))
        .WillOnce(Return(0x02));
    EXPECT_EQ(driver.read(1), 2);
}

TEST_F(DeviceDriverFixture, WriteExceptionWhenWriteAddressNotEmpty) {
    EXPECT_CALL(memory, read)
        .Times(1)
        .WillOnce(Return(0xfe));
    EXPECT_THROW(driver.write(1, 2), WriteFailException);
}

TEST_F(DeviceDriverFixture, WriteMethod) {
    EXPECT_CALL(memory, read)
        .Times(1)
        .WillOnce(Return(0xff));
    EXPECT_CALL(memory, write(1, 2))
        .Times(1);
    driver.write(1, 2);
}
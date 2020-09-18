#include <string.h>
#include <time.h>
#include "ds3231.h"

#define CHECK_ARG(ARG) do { if (!ARG) return 0; } while (0)

extern I2C_HandleTypeDef hi2c2;
static i2c_dev_t rtc_dev;

uint8_t bcd2dec(uint8_t val)
{
    return (val >> 4) * 10 + (val & 0x0f);
}

uint8_t dec2bcd(uint8_t val)
{
    return ((val / 10) << 4) + (val % 10);
}

uint8_t ds3231_init(void)
{
    i2c_master_init(&rtc_dev,&hi2c2);
    return 1;
}

uint8_t ds3231_set_time(struct tm *time)
{
    CHECK_ARG(time);

    uint8_t data[7];

    /* time/date data */
    data[0] = dec2bcd(time->tm_sec);
    data[1] = dec2bcd(time->tm_min);
    data[2] = dec2bcd(time->tm_hour);
    /* The week data must be in the range 1 to 7, and to keep the start on the
     * same day as for tm_wday have it start at 1 on Sunday. */
    data[3] = dec2bcd(time->tm_wday + 1);
    data[4] = dec2bcd(time->tm_mday);
    data[5] = dec2bcd(time->tm_mon + 1);
    data[6] = dec2bcd(time->tm_year - 2000);

    return i2c_dev_write_reg(&rtc_dev, DS3231_ADDR, DS3231_ADDR_TIME, data, 7);
}

uint8_t ds3231_get_raw_temp(int16_t *temp)
{
    CHECK_ARG(temp);

    uint8_t data[2];

    uint8_t res = i2c_dev_read_reg(&rtc_dev, DS3231_ADDR|0x01, DS3231_ADDR_TEMP, data, sizeof(data));
    if (res == 1)
        *temp = (int16_t)(int8_t)data[0] << 2 | data[1] >> 6;

    return res;
}

uint8_t ds3231_get_temp_integer(int8_t *temp)
{
    CHECK_ARG(temp);

    int16_t t_int;

    uint8_t res = ds3231_get_raw_temp(&t_int);
    if (res == 1)
        *temp = t_int >> 2;

    return res;
}

uint8_t ds3231_get_temp_float(float *temp)
{
    CHECK_ARG(temp);

    int16_t t_int;

    uint8_t res = ds3231_get_raw_temp(&t_int);
    if (res == 1)
        *temp = t_int * 0.25;

    return res;
}

uint8_t ds3231_get_time(struct tm *time)
{
    CHECK_ARG(time);

    uint8_t data[7];

    /* read time */
    uint8_t res = i2c_dev_read_reg(&rtc_dev, DS3231_ADDR|0x01, DS3231_ADDR_TIME, data, 7);
        if (res != 1) return res;

    /* convert to unix time structure */
    time->tm_sec = bcd2dec(data[0]);
    time->tm_min = bcd2dec(data[1]);
    if (data[2] & DS3231_12HOUR_FLAG)
    {
        /* 12H */
        time->tm_hour = bcd2dec(data[2] & DS3231_12HOUR_MASK) - 1;
        /* AM/PM? */
        if (data[2] & DS3231_PM_FLAG) time->tm_hour += 12;
    }
    else time->tm_hour = bcd2dec(data[2]); /* 24H */
    time->tm_wday = bcd2dec(data[3]) - 1;
    time->tm_mday = bcd2dec(data[4]);
    time->tm_mon  = bcd2dec(data[5] & DS3231_MONTH_MASK) - 1;
    time->tm_year = bcd2dec(data[6]) + 2000;
    time->tm_isdst = 0;

    // apply a time zone (if you are not using localtime on the rtc or you want to check/apply DST)
    //applyTZ(time);

    return 1;
}

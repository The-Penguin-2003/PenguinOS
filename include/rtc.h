#ifndef __RTC_H__
#define __RTC_H__

#include <types.h>

typedef struct
{
	uint8_t seconds;
	uint8_t minutes;
	uint8_t hours;
	uint8_t day;
	uint8_t month;
	uint8_t year;
} rtc_time_t;

void rtc_read_time(rtc_time_t* time);
long time_seed();
void print_time(const rtc_time_t* time);

#endif /* __RTC_H__ */

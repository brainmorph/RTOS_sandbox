/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef LOGGING_H_
#define LOGGING_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>

// Increase the total system error count
void log_incrementErrorCount();

// Return the total system errors encountered so far
int log_totalErrorCount();



/* Interface suggested by "Making Embedded Systems" */
#define FALSE (0)
#define TRUE (1)

typedef uint8_t tBoolean;


enum eLogSubSystem
{
	LOG_COMMS,
	LOG_DISPLAY,
	LOG_SYSTEM,
	LOG_MPU,
	LOG_BME280,
	LOG_GPS,
	LOG_NUM_LOG_LEVELS
};

enum eLogLevel
{
	LOG_NONE,
	LOG_INFO,
	LOG_DEBUGGING,
	LOG_WARNING,
	LOG_ERROR,
	LOG_CRITICAL,
	LOG_NUM_LOG_SUBSYSTEMS
};

typedef struct{
	tBoolean logOn;
	enum eLogLevel outputLevel[LOG_NUM_LOG_SUBSYSTEMS];
} sLogStruct;



void Log(enum eLogSubSystem sys, enum eLogLevel level, char *msg);
//void LogWithNum(enum eLogSubSystem sys, enum eLogLevel level, char *msg, int number);
//void LogSetOutputLevel(enum eLogSubSystem sys, enum eLogLevel level);
//void LogGlobalOn();
//void LogGlobalOff();

sLogStruct* LogInit();



#endif /* LOGGING_H_ */

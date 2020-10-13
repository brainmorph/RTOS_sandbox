/*
 * logging.c
 *
 *  Created on: Jun 8, 2020
 *      Author: DC
 */

#include "logging.h"
#include "usart.h"

#include <stdlib.h>

static int systemErrorCount = 0;

// Increase the total system error count
void log_incrementErrorCount()
{
	systemErrorCount++;
}

// Return the total system errors encountered so far
int log_totalErrorCount()
{
	return systemErrorCount;
}




/* Interface suggested by "Making Embedded Systems" */

tBoolean gLogOnPublic;

//static tBoolean gLogOnPrivate;

static sLogStruct *gLogData;



sLogStruct *LogInit()
{
	sLogStruct *logData = malloc(sizeof(sLogStruct));

	if(logData == NULL)
		return NULL;


	logData->logOn = FALSE;
	for(int i=0; i < LOG_NUM_LOG_SUBSYSTEMS; i++) {
		logData-> outputLevel[i] = LOG_NONE;
	}

	return logData;
}


/*
 * Outside functions will call Log() from different modules.
 * The idea is to be able to easily control what gets logged by simple switches
 */
void Log(enum eLogSubSystem sys, enum eLogLevel level, char *msg)
{
	if(gLogData->logOn == TRUE)
	{
		switch(level)
		{
		case LOG_NONE:
			break;
		case LOG_INFO:
			break;
		case LOG_DEBUGGING:
			break;
		case LOG_WARNING:
			break;
		case LOG_ERROR:
			break;
		case LOG_CRITICAL:
			break;

		default:
			break;
		}
	}
}

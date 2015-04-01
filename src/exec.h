

#ifndef __EXEC_H__
#define __EXEC_H__


#include <stdbool.h>
#include <stdlib.h>

//Prototypes
pid_t Exec_SpawnProcess(const char *ExecuteString);
bool Exec_WaitForExit(const pid_t PID, const unsigned Delay, int *ExitStatus);

#endif //__EXEC_H__

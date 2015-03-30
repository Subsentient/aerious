

//Prototypes
pid_t Exec_SpawnProcess(const char *ExecuteString);
bool Exec_WaitForExit(const pid_t PID, const unsigned Delay, int *ExitStatus);

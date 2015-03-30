#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "substrings/substrings.h"

pid_t Exec_SpawnProcess(const char *ExecuteString)
{ //Executes the command specified via fork, then returns the child PID.
	if (!ExecuteString || !*ExecuteString) return -1;
	
	pid_t PID = fork();

	//If error
	if (PID == -1) return -1;
	//Or if we're the parent.
	else if (PID > 0) return PID;
	
	///If we are going to need a shell
	if (strpbrk(ExecuteString, "&^$#@!()*%{}`~+|\\<>?;:'[]\"\t") != NULL)
	{ //We will need the shell for this
		execlp("/bin/sh", "sh", "-c", ExecuteString, NULL);
		_exit(97); //Failed to exec
	}
	
	///If we don't need to call the shell
	int NumSpaces = 1;
	const char *Worker = ExecuteString;
	char **ArgV = NULL;
	
	//Get the number of required spaces.
	while ((Worker = SubStrings.Line.WhitespaceJump(Worker))) ++NumSpaces;
	
	ArgV = calloc((NumSpaces + 1), sizeof(char*)); //Allocate the number of required pointers.
	
	int Inc = 0;
	for (Worker = ExecuteString; Inc < NumSpaces && Worker != NULL; ++Inc)
	{
		int ArgLen = 0;
		
		//Find the amount of needed space
		for (; Worker[ArgLen] != ' ' && Worker[ArgLen] != '\t' && Worker[ArgLen]; ++ArgLen);
		
		//Allocate it
		ArgV[Inc] = calloc(ArgLen + 1, 1);
		
		//Copy it in
		SubStrings.CopyUntilC(ArgV[Inc], ArgLen + 1, &Worker, " \t", true);
		///Note: the above line modifies the Worker pointer!
	}
	
	ArgV[NumSpaces] = NULL;
	
	execvp(*ArgV, ArgV);
	
	_exit(97); //We'll use 97 to indicate execvp() failure
}

bool Exec_WaitForExit(const pid_t PID, const unsigned Delay, int *ExitStatus)
{ //Delay is in tenths of a second.
	
	for (int Inc = 0; Inc < 100; ++Inc)
	{ //Divide the delay into 100 chunks.
		usleep(Delay * 1000);
	
		int Temp;
		if (waitpid(PID, &Temp, WNOHANG) > 0)
		{
			*ExitStatus = WEXITSTATUS(Temp);
			return true;
		}
	}
	
	return false; //Our value that says this is not a normal exit.
}

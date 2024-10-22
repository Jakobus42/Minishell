#ifndef EXECUTOR_H
#define EXECUTOR_H

typedef struct s_exec
{
	int pipe_fd[2][2];
	int filein;
	int fileout;
} t_exec;

#endif // EXECUTOR_H
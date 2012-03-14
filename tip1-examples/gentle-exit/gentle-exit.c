#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void sighandler(int signo)
{
	// exit gentlely to make sure the integration of gcov/gprof result
	exit(1);
}

__attribute__ ((constructor))
void initializer()
{
	struct sigaction sa;
	sa.sa_handler = sighandler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESETHAND;
	if (sigaction(SIGINT, &sa, NULL) == -1 ||
		sigaction(SIGQUIT, &sa, NULL) == -1 ||
		sigaction(SIGTERM, &sa, NULL) == -1) {
		perror("Could not set up signal handler");
	}
}


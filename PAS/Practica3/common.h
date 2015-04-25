#ifndef COMMON_H_
#define COMMON_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <mqueue.h>
#include <time.h>
#include <errno.h>
#include <getopt.h>
#include <string.h>
#include <signal.h>
#include <regex.h>

#define SERVER_QUEUE  "/server_queue"
#define CLIENT_QUEUE  "/client_queue"
#define MAX_SIZE     1024
#define MSG_STOP     "exit"
#define MSG_REGEX_STOP "abort"


#endif /* #ifndef COMMON_H_ */

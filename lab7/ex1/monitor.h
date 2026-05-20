
#ifndef RESOURCE_MONITOR_H
#define RESOURCE_MONITOR_H
#include <pthread.h>

/* --- monitor operations --- */
void initMonitor();
void destroyMonitor();
void put(int value);
int take(int forkId);

#endif

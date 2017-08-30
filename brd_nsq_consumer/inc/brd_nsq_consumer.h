#ifndef __BRD_NSQ_CONSUMER_H__
#define __BRD_NSQ_CONSUMER_H__
#ifdef __cplusplus
extern "C" {
#endif
typedef void (*HANDLER)(const char *topic,const char *msg);
HANDLER callback;

void init_nsq_consumer(const char **topic,const char *channel,const char *nsqlookupdDomain,int nsqlookupdPort,HANDLER handle);

#ifdef __cplusplus
	}
#endif

#endif

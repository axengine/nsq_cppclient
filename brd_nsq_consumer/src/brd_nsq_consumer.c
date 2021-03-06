#include "brd_nsq_consumer.h"
#include "nsq.h"

void message_handler(struct NSQReader *rdr, struct NSQDConnection *conn, struct NSQMessage *msg, void *ctx);

void init_nsq_consumer(const char *topic[],const char *channel,const char *nsqlookupdDomain,int nsqlookupdPort,HANDLER handle)
{
    callback = handle;
    struct NSQReader *rdr;
    struct ev_loop *loop;
    void *ctx = NULL; //(void *)(new TestNsqMsgContext());

    loop = ev_default_loop(0);
	int i = 0;
	while(topics[i]!=NULL){
		rdr = new_nsq_reader(loop, topics[i], channel, (void *)ctx,
			   NULL, NULL, NULL, message_handler);
		nsq_reader_add_nsqlookupd_endpoint(rdr, nsqlookupdDomain, nsqlookupdPort);
		i++;
	}
    nsq_run(loop);
}


void message_handler(struct NSQReader *rdr, struct NSQDConnection *conn, struct NSQMessage *msg, void *ctx)
{
    if(callback!=NULL)
        callback(rdr->topic,msg->body);
    buffer_reset(conn->command_buf);

	nsq_finish(conn->command_buf, msg->id);
   
    buffered_socket_write_buffer(conn->bs, conn->command_buf);

    buffer_reset(conn->command_buf);
    nsq_ready(conn->command_buf, rdr->max_in_flight);
    buffered_socket_write_buffer(conn->bs, conn->command_buf);

    free_nsq_message(msg);
}

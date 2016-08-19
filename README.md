# nsq_cppclient
a nsq client write with cpp,depend on libnsq and libcurl
## compile libnsq
> gcc -o libnsq.so command.c http.c json.c message.c nsqd_connection.c nsqlookupd.c reader.c -fPIC -shared -lev -levbuffsock -lcurl -ljson-c

## compile nsq consumer
> gcc -shared -fPIC -o libnsqconsumer.so brd_nsq_consumer.c -lnsq

## compile nsq producer
> gcc -shared -fPIC -o libnsqproducer.so brd_nsq_producer.c -lcurl

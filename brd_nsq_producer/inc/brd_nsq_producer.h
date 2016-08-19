#ifndef __BRD_NSQ_PRODUCER_H__
#define __BRD_NSQ_PRODUCER_H__
#include <curl/curl.h>

class CNsqProducer{
public:
	CNsqProducer();
	~CNsqProducer();
	//ip:port or domain:port
	void SetNsqdAddr(const char *nsqdAddr);
	void SetNsqTopic(const char *topic);
	void Init();
	int PostData(const char *data);
	int PostData(const char *uri,const char *data);

private:
	char m_szUrl[256];
	
	char m_szNsqdAddr[128];
	char m_szNsqTopic[128];
	CURL* m_curl;
	struct curl_slist* m_httpHeader;

	int initCurl();
	void initHeader();
};
#endif

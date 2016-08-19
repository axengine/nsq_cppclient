#include <string.h>
#include "brd_nsq_producer.h"

CNsqProducer::CNsqProducer()
{
	curl_global_init(CURL_GLOBAL_DEFAULT);
	m_httpHeader = NULL;
	m_curl = curl_easy_init();
}

CNsqProducer::~CNsqProducer()
{
	if(m_httpHeader!=NULL)curl_slist_free_all(m_httpHeader);
	if(m_curl!=NULL)curl_easy_cleanup(m_curl);
	curl_global_cleanup();
}

void CNsqProducer::SetNsqdAddr(const char *nsqdAddr)
{
	if(nsqdAddr==NULL)return;
	memset(m_szNsqdAddr,0x00,sizeof(m_szNsqdAddr));
	strncpy(m_szNsqdAddr,nsqdAddr,sizeof(m_szNsqdAddr));
}

void CNsqProducer::SetNsqTopic(const char *topic)
{
	if(topic==NULL)return;
	memset(m_szNsqTopic,0x00,sizeof(m_szNsqTopic));
	strncpy(m_szNsqTopic,topic,sizeof(m_szNsqTopic));
}

void CNsqProducer::Init()
{
	initHeader();
	initCurl();
}

void CNsqProducer::initHeader()
{
	m_httpHeader = curl_slist_append(m_httpHeader, "Accept: *");
	m_httpHeader = curl_slist_append(m_httpHeader, "Charset: utf-8");
	m_httpHeader = curl_slist_append(m_httpHeader, "User-Agent: curl3");	
}

int CNsqProducer::initCurl()
{
	curl_easy_setopt(m_curl,CURLOPT_POST,1L);
	curl_easy_setopt(m_curl,CURLOPT_HTTPHEADER, m_httpHeader);
	curl_easy_setopt(m_curl,CURLOPT_FOLLOWLOCATION,1L);
	curl_easy_setopt(m_curl,CURLOPT_NOSIGNAL, 1L);
	curl_easy_setopt(m_curl,CURLOPT_TIMEOUT,2L);
	curl_easy_setopt(m_curl,CURLOPT_CONNECTTIMEOUT_MS,500);
	curl_easy_setopt(m_curl,CURLOPT_FORBID_REUSE, 1L);
}

//-1:network error
//0:200 ok
//other:other http code
int CNsqProducer::PostData(const char *data)
{
	char url[256]={0x00};
	sprintf(url,"http://%s/put?topic=%s",m_szNsqdAddr,m_szNsqTopic);
	curl_easy_setopt(m_curl,CURLOPT_URL,url);

	curl_easy_setopt(m_curl,CURLOPT_POSTFIELDS,data);
	CURLcode res = curl_easy_perform(m_curl);
	if (res != CURLE_OK)
	{
		printf("CurlPost error:%s\n",curl_easy_strerror(res));
		return -1;
	}

	long retcode = 0;

	CURLcode code = curl_easy_getinfo(m_curl, CURLINFO_RESPONSE_CODE , &retcode);
	if ( (code == CURLE_OK) && retcode == 200 ){
		retcode = 0;
	}
	return retcode; 
}

//-1:network error
//0:200 ok
//other:other http code
int CNsqProducer::PostData(const char *uri,const char *data)
{
	curl_easy_setopt(m_curl,CURLOPT_URL,uri);
	curl_easy_setopt(m_curl,CURLOPT_POSTFIELDS,data);
	CURLcode res = curl_easy_perform(m_curl);
	if (res != CURLE_OK)
	{
		printf("CurlPost error:%s\n",curl_easy_strerror(res));
		return -1;
	}   

	long retcode = 0;

	CURLcode code = curl_easy_getinfo(m_curl, CURLINFO_RESPONSE_CODE , &retcode);
	if ( (code == CURLE_OK) && retcode == 200 ){
		retcode = 0;
	}
	return retcode; 
}
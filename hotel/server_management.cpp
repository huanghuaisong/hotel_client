#include "c_socket.h"
#include "define.h"
#include "command_process.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "server_management.h"
#include "protocol.h"
#include "server_data.h"
#include "cJSON.h"
#include <unistd.h>
pthread_mutex_t mutex_pool;
pthread_cond_t  cond_pool;
int             connect_sid;

void parse_json_data(msg_t *msg,char *socket_buf){
	plog("");
	cJSON *jsonobject=cJSON_Parse(socket_buf);//�����ַ���������json����
	int message_type=cJSON_GetObjectItem(jsonobject,"messageType")->valueint;
	switch(message_type){
		case USER_REGISTER:
			msg->msg_type=USER_REGISTER;
			plog("");
//			char *account =cJSON_GetObjectItem(jsonobject,"account")->valuestring;
     		char *password=cJSON_GetObjectItem(jsonobject,"password")->valuestring;
			reg_t reg;
			memset(&reg,0,sizeof(reg));
	//		memcpy(reg.usr_name,account,strlen(account));
			memcpy(reg.usr_passwd,password,strlen(password));
			memcpy(msg->msg_buf,&reg,sizeof(reg));	
			plog("");
		break;

		case LOGIN:
			msg->msg_type=LOGIN;
			plog("");
			char *account =cJSON_GetObjectItem(jsonobject,"account")->valuestring;
			char *password=cJSON_GetObjectItem(jsonobject,"password")->valuestring;
			reg_t reg;
			memset(&reg,0,sizeof(reg));
			memcpy(reg.usr_name,account,strlen(account));
			memcpy(reg.usr_passwd,password,strlen(password));
			memcpy(msg->msg_buf,&reg,sizeof(reg));	
			plog("");
		break;
			
	}
}
//�ͻ������߳�
void *client_service_thread(void *arg)
{
	char socket_buf[1024];
	memset(&socket_buf,0,sizeof(socket_buf));
    int c_sid ;//�����߳����Ӻ�
    int i = 0;
    int ret = 0;
    void *p_ret = NULL;
	
    pthread_mutex_lock(&mutex_pool);//��ס
    pthread_cond_wait(&cond_pool,&mutex_pool);//�߳��������ȴ�������������
    c_sid = connect_sid;
    pthread_mutex_unlock(&mutex_pool);
	//�տ�ʼ��֪�����û�������Ϣ�����ĸ��û�
    client_config_t *cli_cfg = NULL;
	plog("client connect,connect id=%d",c_sid);
    while(1)
    {
        i = 0;
        msg_t genmsg;
        memset(&genmsg,0,sizeof(genmsg));
		
        //�ȴ��û���������
        plog("sdasdasd\n");
        //ret = socket_read(c_sid, &genmsg, sizeof(genmsg));		
		ret = read(c_sid, socket_buf, sizeof(socket_buf));
		if(ret == 0)
        {
            plog("close c_sid = %d",c_sid);
            socket_close(c_sid);
            return NULL;
        }
		plog("socket_buf=%s\n",socket_buf);
		parse_json_data(&genmsg,socket_buf);
        plog("c_sid = %d, cmd = %d",c_sid, genmsg.msg_type);
        while(g_cmd_list[i].cmd >= 0)
        {
            //����״̬��
            if(g_cmd_list[i].cmd == genmsg.msg_type)
            {
                //���ݴ���data������
                p_ret = g_cmd_list[i].cmd_handle(c_sid, genmsg.msg_buf, cli_cfg);
                if(g_cmd_list[i].cmd == LOGIN)
                {
                    if(p_ret != NULL)
                    {
                        cli_cfg = (client_config_t *)p_ret;
                    }
                }
            }
            i++;
        }
    }   
    return NULL;
}


//�ͻ������߳�
void *client_listen_thread(void *arg)
{
    int     j;
    int         c_sid;
    pthread_t   c_pid;//�߳�ID

    //�����ͻ������׽���
    server_cfg.client_listen_socket_id = socket_set_server(server_cfg.port, server_cfg.max_client);
    if(server_cfg.client_listen_socket_id < 0)
    {
        perror("server client_listen_thread socket create error\n");
        return NULL;
    }
    for(j=0; j<THREAD_POOL_MAX_NUM; j++)
	//�����̳߳أ�ȫ�������������ȴ�������������
    {
        if(pthread_create(&c_pid, NULL,client_service_thread, NULL) < 0)
        {
            perror("client client_service_thread created failed\n");
            return NULL;
        }
    }
    //���ӿͻ���
    while(1)
    {
        c_sid = socket_accept(server_cfg.client_listen_socket_id);//�ȴ����Ӹö˿ڵĿͻ�������,Ȼ�󷵻�һ����ʱ�����Ӷ˿�
        plog("client_listen_thread  client connect,connect id=%d",c_sid);
        if(c_sid < 0)
        {
        
            perror("client chat sid accept error\n");
            return NULL;
        }
        //���ӳɹ������Ӹÿͻ��˵ķ����߳�,����ͻ������߳�
        pthread_mutex_lock(&mutex_pool);//���Ӽ���������connect_sid�ܹ���ȷ��ֵ
        connect_sid = c_sid;
        pthread_cond_signal(&cond_pool);//�����������������źţ��̵߳�ͨ
        pthread_mutex_unlock(&mutex_pool);
    }

    return NULL;
}


//��ʼ��������
int init_server()
{
	int status;
    memset(&server_cfg,0,sizeof(server_config_t));
	server_cfg.max_client=MAX_NUM;//������ӵĿͻ�����
	server_cfg.port=SERVER_PORT;//�������˿�
//	server_config.server_ip=SERVER_IP;//������IP��ַ

	//�����ͻ������߳�
	if(pthread_create(&server_cfg.client_listen_thread_id, NULL, client_listen_thread, NULL ) != 0)		
    {
        perror("chat listen thread create error\n");
        return -1;
    }
	pthread_join(server_cfg.client_listen_thread_id,(void **)&status);
}

//�رշ�����
int close_server(){}

#ifndef SERVER_DATA_H
#define SERVER_DATA_H
#include "define.h"
//�������������
extern server_config_t server_cfg;

//�û��˺ž�̬ȫ�ֱ���
extern unsigned long register_id ;

//���Դ�ӡ
#define plog(fmt,args...) \
do \
{                  \
    time_t now = time(NULL); \
    tm *cur = localtime(&now);  \
	printf("\n%02d:%02d:%02d->[%s %d]:"fmt"\n",cur->tm_hour,cur->tm_min, \
	cur->tm_sec,__func__,__LINE__,##args);  \
	fflush(0); \
}while(0);

#endif
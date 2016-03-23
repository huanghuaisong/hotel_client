#ifndef _DEFINE_H
#define _DEFINE_H

#include <vector>
#include <sys/types.h>          /* See NOTES */
#include <pthread.h>
#include <stdio.h>
#include <time.h>             
using namespace std;                                                       
/**********************************��Ϣ����****
/*���ӷ�����*/                                    
enum   message_type                     
{
        LOGIN ,             //�����½                                           
        LOGIN_SUCCESS,      //��½�ɹ�1
        USER_NO_EXIST,      //�û�������
        USER_IS_ONLINE,     //�û�����
        USER_NO_ONLINE,     //�û�������                                                                                                                                                                            
        USER_ALREADY_EXIST, //�û��Ѿ�����

        USER_REGISTER,      //ע���˺�6
        REGISTER_SUCCESS,   //ע��ɹ�
        REGISTER_FAILED,    //ע��ʧ��
        CHANGE_PASSWORD,    //�޸�����9
        CHANGE_SUCCESS,     //�޸ĳɹ�
        PASSWORD_ERROR,     //�������
        ORIGIN_PASSWD_ERROR,//ԭʼ�������12

              
        ADD_FRIEND,         //��Ӻ���13
        DEL_FRIEND,         //ɾ������
        ADD_IS_REJECT,      //��ӱ��ܾ�
        DEL_FRIEND_SUCCESS, //ɾ���ɹ�
        ADD_FRIEND_SUCCESS, //��Ӻ��ѳɹ�
        ALREADY_YOUR_FRIEND,//�Ѿ������ĺ���18
        NOT_YOUR_FRIEND,    //�������ĺ���
        AGREE_TO_ADD,       //ͬ�����
        DISAGREE_TO_ADD,    //�ܾ����
        ADD_FRIEND_REP,     //�������߷���������

        JOIN_GROUP,           //����Ⱥ��23
        JOIN_GROUP_REP,           //����Ⱥ���Ӧ
        FOR_ASKER_JOIN_GROUP_REP,//���������Ⱥ���û��Ļظ�
        DELETE_GROUP,        //ɾ��Ⱥ��
        DELETE_GROUP_SUCCESS,//ɾ��Ⱥ��ɹ�
        DELETE_GROUP_FAILURE, //ɾ��Ⱥ��ʧ��
        GROUP_ACCOUNT_UNEXIST,//Ⱥ�˺Ų�����
        NOT_GROUP_OWNER,        //����Ⱥ��30
        EXIT_GROUP,         //�˳�Ⱥ��
        ADD_GROUP_SUCCESS,   //����Ⱥ��ɹ�
        ADD_GROUP_FAILURE,   //����Ⱥ��ʧ��
        AGREE_ADD_GROUP_OR_NOT, //�Ƿ�ͬ�����Ⱥ
        AGREE_ADD_GROUP,        //Ⱥ��ͬ������
        EXIT_GROUP_SUCCESS,  //�˳�Ⱥ�ɹ�
        EXIT_GROUP_FAILURE, //�˳�Ⱥʧ��37
        CREATE_GROUP,          //����Ⱥ
        CREATE_GROUP_SUCCESS,//����Ⱥ�ɹ�
        CREATE_GROUP_FAILURE,//����Ⱥʧ��
        JOIN_GROUP_REJECTED, //���ܾ�����41

        DOWNLOAD_FILE,      //�����ļ�42
        UPLODE_FILE,        //�ϴ��ļ�
        DOWNLOAD_SUCCESS,   //���سɹ�
        ACCEPT_UPLOAD_FILE, //�����ϴ��ļ�
        BEGIN_UPLOAD,         //��ʼ�ϴ�
        UPLOAD_SUCCESS,     //�ϴ��ɹ�
        FILE_NO_EXIST,      //�ļ�������
        RETURN_FILE_SIZE,  //�����ļ���С
        FILE_DOWNLOADING, //�ļ���������
        FILE_UPLOADING, //�ļ������ϴ�
        DOWNLOAD_FAILURE,   //����ʧ��
        UPLOAD_FAILURE,     //�ϴ�ʧ��

        GET_FACE_PICTURE,   //���ձ���53
        SEND_FACE_PICTUER,  //���ͱ���
        P_TO_P_CHAT,        //����
        P_TO_P_CHAT_REP,        //����ʧ�ܵ�ԭ��
        GROUP_CHAT,         //Ⱥ����
        NOTIFY_STATE,       //����״̬
        UPDATE_FRIEND,      //���º���
        USER_DISCONNECT, //�û�Ҫ����
        UPDATE_FRIEND_STATE, //���º��ѵ�״̬60

        INIT_FRIEND_LIST,  //��ʼ�������б�
        FIREND_INITING,   //�����б����ڳ�ʼ��
        FRIEND_INITED,     //�����б��ʼ�����

        INIT_GROUP_LIST,  //��ʼ��Ⱥ�б�
        GROUP_INITING,	//Ⱥ�б����ڳ�ʼ��
        GROUP_INITED, 	//Ⱥ�б��ʼ�����

        INIT_GROUP_MEMBER_LIST,  //��ʼ��Ⱥ�б�
        GROUP_MEMBER_INITING,	//Ⱥ�б����ڳ�ʼ��
        GROUP_MEMBER_INITED, 	//Ⱥ�б��ʼ�����

        UPDATING_FRIEND,  //���ڸ��º���
        UPDATED_FRIEND, //���º������

        UPDATED_GROUP_LIST,
        UPDATEING_GROUP,
        UPDATED_GROUP,

        GET_HEAD_NUM,  //��ȡ�û�ͷ��
        OFFLINE_MSG_SEND,     //����������Ϣһ��ͷ
        SENDING_OFFLINE_MSG,   //ack = ���ڷ���
        SENDED_OFFLINE_MSG,  //ack = �������
        CHANGE_HEAD_NUM,      //����ͷ��
        P_to_P_FILE,
        GROUP_FILE,
};

/*��������*/
#define SERVER_PORT 8887         //��Ե�����˿ں�
#define LOCAL_IP  "127.0.0.1"    //����IP
#define SERVER_IP "127.0.0.1"    //������IP
#define MAX_NUM   2000           //���ͻ�����Ŀ
#define THREAD_POOL_MAX_NUM 20   //����̳߳���


//�û���Ϣ
typedef struct client_info
{
    unsigned long   usr_account;        //�û�ID
    char            passwd[15];         //����
    int 			balance;			//���
	char            register_time[12];  //ע��ʱ�� 
    int             state;              // �û�״̬ 0--->���� 1--->����
} client_info_t;

//������Ϣ
typedef struct room_info
{
    unsigned long   room_ID;        	//����ID
    int 			room_type;			//��������
    int 			bed_number;			//��λ����
	int             window;				//�Ƿ��д���
} room_info_t;

/* ���������û�������Ϣ */
typedef struct client_config
{
    client_info_t                           user;                   //�û���Ϣ
    vector<room_info_t>                     room_list;            //�Ѿ�Ԥ���ķ�������

} client_config_t;

typedef struct server_config
{
	int  port;//�������˿�
   // char server_ip[255];//������IP
    int  max_client;// ��������û���Ŀ
	pthread_t client_listen_socket_id;//�ͻ������׽���ID
	pthread_t client_listen_thread_id;//�ͻ������߳�ID		
}server_config_t;


#endif

#ifndef PROTOCOL_H
#define PROTOCOL_H


///////////////////�Զ���Э��///////////////

//ͨ����Ϣ�ṹ
//һ��Э��

typedef struct tag_msg
{
    //��Ϣ����
    unsigned int msg_type;
    //��Ϣ��������
    char msg_buf[1024];
} msg_t;

////////////����Э��/////////////////

/*********************ע������롢��ʼ���ͻ���************/
//ע������
typedef struct tag_reg
{
    //����
    char usr_passwd[16];
} reg_t;

//ע��Ӧ��
typedef struct tag_reg_rep
{
    // 0---ע��ʧ��
    // 1---ע��ɹ�
    unsigned int ack;
    unsigned int user_account;
} reg_rep_t;

//��������
typedef struct tag_login
{
    //�û�ID�˺�
    unsigned long usr_account;
    //�û�����
    char usr_passwd[15];

} login_t;
//����Ӧ����
typedef struct tag_login_rep
{
    int ack;
    int head_picture_num;
    char   name[15];
} login_rep_t;

//��ʼ�������б�����
typedef struct init_friend
{
    unsigned long  MyAcoount;
} init_friend_request_t;
//��ʼ�������б��Ӧ
typedef struct friend_list_info
{
    int ack;
    int head_num;//ͷ��
    unsigned long friend_account;
    int state;
    char friend_name[15];
} friend_list_info_t;

//��ʼ��Ⱥ�б�����
typedef struct init_community
{
    unsigned long  MyAcoount;
} init_community_t;

//��ʼ��Ⱥ�б��Ӧ
typedef struct group_list_info
{
    int ack;
    unsigned long group_account;
    unsigned long group_owner_account;
    char group_name[15];
} group_list_info_t;

//��ʼ��Ⱥ��Ա�б�����
typedef struct init_group_member
{
    unsigned long group_account;
} init_group_member_t;

//��ʼ��Ⱥ��Ա�б��Ӧ
typedef struct init_group_member_rep
{
    int ack;
    unsigned long       usr_account;
    int     head_picture_num;
    char           usr_name[15];
} init_group_member_rep_t;
/*************************��Ӻ���*******************/
//��Ӻ������� ����(�����߷��͸�������)
typedef struct add_fri
{
    //���ѵ��˺�
    unsigned long   fri_account;
} add_fri_t;

//������Ӻ�������(���������͸���������)
typedef struct  ask_for_add_friend
{
    //�����ߵ�ͷ��
    int head_picture_num;
    //�����ߵ��˺�
    unsigned  long  asker_account;
    //�����ߵ��ǳ�
    char  asker_name[15];
} ask_for_add_friend_t;

//ͬ������Ӧ����(�������߷��͸�������)
typedef struct  ask_for_add_friend_rep
{
    int ack;
    //�������˺�
    unsigned long asker_account;
} ask_for_add_friend_rep_t;


//��Ӻ���Ӧ����(����������������)
typedef struct  tag_add_fri_rep
{
    int ack;
    //���ѵ������˺�ͷ��
    unsigned long  fri_account;
    int fri_head_picture_num;
    char     fri_name[15];
} add_fri_rep_t;


/******************ɾ������*********************/
//ɾ���������� ����(�����߷��͸�������)
typedef struct del_fri
{
    //���ѵ��˺�
    unsigned long   fri_account;
} del_fri_t;

//ɾ������Ӧ��(����������������)
typedef struct del_fri_rep
{
    //ɾ���ɹ����
    int  ack;
} del_fri_rep_t;


/*********************����״̬���޸�����************/


// ͨ�����߻�������
typedef struct notify_user_state
{
    int state;
    //����ID
    unsigned long user_id;
    int  head_num;
} notify_user_state_t;


// ���º����б�
typedef struct update_friend_list
{
    unsigned long user_id;
} up_fri_list_t;

// ���º����б���Ӧ
typedef struct update_friend_list_rep
{
    int  ack;
    //����ͷ��
    int friend_head_picture_num;
    // �û�ID
    unsigned long  user_id;
    // ���û�״̬ 0 ����1
    int  status;
    char name[15];
} update_friend_list_rep_t;


// ����Ⱥ�б�
typedef struct update_group_list
{
    unsigned long user_id;
} up_group_list_t;

// ����Ⱥ�б���Ӧ
typedef struct update_group_list_rep
{
    int  ack;
    unsigned long  group_id;
    unsigned long  owner_id;
    char group_name[15];
} update_group_list_rep_t;

//�޸�����
typedef     struct tag_change_passwd
{
    //�û����˺�
    unsigned long account;
    //ԭʼ����
    char origin_passwd[15];
    //������
    char     new_passwd[15];
} change_passwd_t;

//�޸������Ӧ����
typedef  struct tag_change_passwd_rep
{
    //�޸ĳɹ�
    //�޸�ʧ��
    int ack;
} change_passwd_rep_t;


/*********************��Ե�����************/

//��ȡͷ��
typedef struct get_head
{
    unsigned long friend_account;
} get_head_num_t;

//��ȡͷ��Ӧ��
typedef struct get_head_num
{
    int  head_num;
} get_head_num_rep_t;

// ��Ե�����
typedef struct chat_p2p
{
    // �Լ���ID
    unsigned long            user_id;
    //�����ߵ��ǳ�
    char       asker_name[15];
    // ��������ID
    unsigned long            friend_id;
    // ��������
    char           content[512];
} chat_p2p_t;

// ��Ե�����Ӧ��
typedef struct chat_p2p_rep
{
    // 0---�Է�������
    // 1---���ͳɹ�
    int ack;
} chat_p2p_rep_t;

//����������Ϣ����
typedef struct offline_message_ask
{
	unsigned long myaccount;
}offline_message_ask_t;

//������Ϣ
typedef struct offline_msg
{
	unsigned long  sender;
	unsigned long  recerver;
	char		content[512];
}offline_msg_t;

// ������Ϣ
typedef struct offline_msg_rep
{
	int ack;
      chat_p2p_t  p2p;
}offline_msg_rep_t;

/*********************��Ⱥ�Ĳ���************/

//���봴��Ⱥ
typedef struct  ask_for_creat_group
{
    //�û��˺�-->Ⱥ��
    unsigned long  account;
    //Ⱥ��
    char      group_name[15];
} ask_for_creat_group_t;

//����ȺӦ��
typedef struct ask_for_creat_group_rep
{
    //Ⱥ�˺�
    unsigned  long  group_account;
    // 0---����ʧ��
    // 1---�����ɹ�
    int ack;
} ask_for_creat_group_rep_t;

//����ɾ��Ⱥ
typedef struct  ask_for_del_group
{
    //�û��˺�-->Ⱥ��
    unsigned long  account;
    //Ⱥ�˺�
    unsigned long  group_account;
} ask_for_del_group_t;

//ɾ��ȺӦ��
typedef struct ask_for_del_group_rep
{
    // 0---ɾ��ʧ��
    // 1---ɾ���ɹ�
    int ack;
} ask_for_del_group_rep_t;


//�������Ⱥ
typedef struct  ask_for_join_group
{
    //Ⱥ�˺�
    unsigned  long  group_account;
    //�û��˺�
    unsigned  long  user_account;
} ask_for_join_group_t;


//Ⱥ���Ƿ��Ӧ��Ⱥ
typedef struct  join_group_ok_no
{
    //�����ߵ��˺�
    unsigned long    user_account;
    //��������Ⱥ�˺�
    unsigned long group_accound;
    //��������Ⱥ��
    char        group_name[15];
    //�����ߵ��ǳ�
    char        asker_name[15];
} join_group_ok_no_t;

//����ȺӦ��
typedef struct  ask_for_join_group_rep
{
    // 0---�˺Ų�����
    // 1---�ܾ�����
    // 2---����ɹ�
    int     ack;
    unsigned long group_account;
    unsigned long asker_account;
    char        group_name[15];
    char           asker_name[15];
} ask_for_join_group__rep_t;

//�˳�Ⱥ��
typedef struct  exit_group
{
    //Ⱥ�˺�
    unsigned long   group_account;
    //�û��˺�
    unsigned long user_account;
} exit_group_t;

//�˳�Ⱥ��Ӧ��
typedef struct  exit_group_rep
{
    // 0---�˳�Ⱥ�ɹ�
    // 1---�˳�Ⱥʧ��
    int ack;
} exit_group_rep_t;


//Ⱥ��
typedef struct tag_group_chat
{
    //Ⱥ�˺�
    unsigned  long  group_account;
    //�û��˺�
    unsigned  long  user_account;
    //��������
    char        context[512];
} group_chat_t;

//Ⱥ��������
typedef  struct group_chat_context
{
     //Ⱥ�˺�
    unsigned  long  group_account;
    //Ⱥ��������
    char   context[512];
    //�������˺�
    unsigned  long  sender_account;
    //�������ǳ�
    char   sender_name[15];
} group_chat_context_t;




//�ļ���������
typedef struct file_download
{
    // �����ļ���Ϣ
    // 0--- �����ļ���С
    // 1--- �����ļ�����
    char filename[255];
    int  ack;
    int type;
} file_download_t;

//�ļ�����Ӧ��
typedef struct file_download_rep
{
    // 0 �ļ�������
    // 1 �����ļ���С
    // 2 ������
    // 3 ���ؽ���
    char file_content[512];
    int  ack;
    unsigned long  file_tota_size;
    unsigned long filesize;
    int type;
} file_download_rep_t;

// �ļ��ϴ�����
typedef struct file_upload
{
    //  0 -- ��������
    char       filename[255];
    int        ack;
    unsigned long  file_tota_size;
    int type;
} file_upload_t;

// �ļ��ϴ�������Ӧ
typedef struct file_upload_rep
{
    // 1 -- �����ϴ�����
    // 2 -- �������
    //�������ܾ��ϴ�
    int        ack;
	int type;
} file_upload_rep_t;

//��ʼ�ϴ�
typedef struct file_uploading
{
    //  1 -- �ϴ���
    //  2 -- �ϴ�����
    char       file_content[512];
    int        ack;
	int type;
} file_uploading_t;

typedef  struct change_head_num
{
    int user_account;
    int head_num;
}change_head_num_t;
#endif

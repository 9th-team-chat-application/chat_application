/*
 * @Copyright: School of Computer Science & Technology, BIT
 * @Author: Liao Zhaohe
 * @FileName: DataTransformInterfaces.c
 * @Version: 0.1.0
 * @Date: 2019-09-02 23:26:29
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2019-09-04 06:51:00
 * @Description: This file implements the interfaces descripted in "DBInfotmation.h"
 */
#include "DataTransformInterface.h"

INFO_CODE parseToString(cJSON *json, char *string, char *name)
{
    cJSON *j_str = NULL;
    if ((j_str = cJSON_GetObjectItem(json, name)) == NULL)
        return DB_CJSON_PARSE_ERR;
    strcpy(string, j_str->valuestring);
    return ACCEPTED;
}

INFO_CODE getUsernameFromCJSON(cJSON *json, char *username)
{
    return parseToString(json, username, "user_name");
}

INFO_CODE getTypeFromCJSON(cJSON *json, char *type)
{
    return parseToString(json, type, "type");
}

INFO_CODE getUserIPFromCJSON(cJSON *json, char *user_ip)
{
    return parseToString(json, user_ip, "user_ip");
}

/**
 * @Author: Liao Zhaohe
 * @Description: 
 *      For DataBase     
 *      Parse the username information from cJSON to char*.
 * @Parameters: 
 *      cJSON* login_info: A pointer to the cJson struct passed to database by the 
 *              socket server.
 *      char* user_name: Stores username parsed from cJSON.
 * @Return: 
 *      Return ACCEPTED for parsing info successfully, other info code for Exception. (See in Throw)
 * @Throw: 
 *      DB_CJSON_PARSE_ERR : when passed cJSON has the error structure.
 */
INFO_CODE parseUserName(cJSON *username_json, char *username)
{
    return parseToString(username_json, username, "username");
}

/**
 * @Author: Liao Zhaohe
 * @Description: 
 *      For Database.
 *      Parse the log in information (cJSON formate) to char* that the database uses.
 * @Parameters: 
 *      cJSON* login_info: a pointer to a cJson struct, which is passed to database by the 
 *          socket server.
 *      char* user_name: Provided by DB, stores username parsed from cJSON.
 *      char* user_ip: Provided by DB, stores user_ip parsed from cJSON.
 *      char* password: Provided by DB, stores password parsed from cJSON.
 * @Return: 
 *      Return ACCEPTED for parsing info successfully, other info code for Exception. (See in Throw)
 * @Throw: 
 *      DB_CJSON_PARSE_ERR : when passed cJSON has the error structure.
 */
INFO_CODE parseLoginInfo(cJSON *login_info, char *user_name, char *user_ip, char *password)
{
    INFO_CODE info;
    if ((info = parseToString(login_info, user_name, "user_name")) != ACCEPTED)
        return info;
    if ((info = parseToString(login_info, user_ip, "user_ip")) != ACCEPTED)
        return info;
    if ((info = parseToString(login_info, password, "password")) != ACCEPTED)
        return info;

    return ACCEPTED;
}

/**
 * @Author: Liao Zhaohe
 * @Description: 
 *      For Client.
 *      Encode the log in information (char* formate) to cJSON* that the socket transfers.
 * @Parameters: 
 *      char* user_name: the username of the user who call this function.
 *      char* user_ip: the user's IP address.
 *      char* password: the password user entered.
 *      cJSON* login_info: a pointer to a cJson struct, which stores the previouse information.
 *                         Warning: cJSON pointer must be created by "cJSON_CreateObject" function.
 * @Return: 
 *      Return ACCEPTED for parsing info successfully, other info code for Exception.
 * @Throw: 
 */
INFO_CODE encodeLoginInfo(char *user_name, char *user_ip, char *password, cJSON *login_info)
{
    cJSON_AddStringToObject(login_info, "type", "login_info");
    cJSON_AddStringToObject(login_info, "user_name", user_name);
    cJSON_AddStringToObject(login_info, "passewd", password);
    cJSON_AddStringToObject(login_info, "user_ip", user_ip);

    return ACCEPTED;
}

/**
 * @Author: Liao Zhaohe
 * @Description: For Database
 *               Parse the information from cJSON to char*. This information is used to change
 *               password question.
 * @Parameters: 
 *     cJSON* change_passwd_ques_info: A pointer to the cJson struct passed to database by the 
 *            socket server.
 *     char* user_ip : Stores user ip parsed from cJSON.
 *     char* user_name : Stores user name parsed from cJSON.
 *     char* question : Stores question parsed from cJSON
 *     char* answer : Stores answer parsed from cJSON
 * @Return: 
 *      Return ACCEPTED for parsing info successfully, other info code for Exception. (See in Throw)
 * @Throw: 
 *      DB_CJSON_PARSE_ERR : when passed cJSON has the error structure.
 */
INFO_CODE parseChangePasswdQuestionInfo(
    cJSON *change_passwd_ques_info,
    char *user_ip,
    char *user_name,
    char *question,
    char *answer)
{
    INFO_CODE info;
    if ((info = parseToString(change_passwd_ques_info, user_ip, "user_ip")) != ACCEPTED)
        return info;
    if ((info = parseToString(change_passwd_ques_info, user_name, "user_name")) != ACCEPTED)
        return info;
    if ((info = parseToString(change_passwd_ques_info, question, "question")) != ACCEPTED)
        return info;
    if ((info = parseToString(change_passwd_ques_info, answer, "answer")) != ACCEPTED)
        return info;

    return ACCEPTED;
}

/**
 * @Author: Liao Zhaohe
 * @Description: For Client
 *      Encode the log in information (char* formate) to cJSON* that the socket transfers.
 * @Parameters: 
 *      char *user_ip: the user's IP address.
 *      char *user_name:  the username of the user who call this function.
 *      char *question: the setting password question
 *      char *answer: answer to question
 *      cJSON* change_passwd_ques_info: a pointer to a cJson struct, which stores the previouse information.
 *                         Warning: cJSON pointer must be created by "cJSON_CreateObject" function.
 * @Return: 
 *      Return ACCEPTED for parsing info successfully, other info code for Exception.
 * @Throw: 
 */
INFO_CODE encodeChangePasswdQuestionInfo(
    char *user_ip,
    char *user_name,
    char *question,
    char *answer,
    cJSON *change_passwd_ques_info)
{
    cJSON_AddStringToObject(change_passwd_ques_info, "type", "change_passwd_question");
    cJSON_AddStringToObject(change_passwd_ques_info, "user_ip", user_ip);
    cJSON_AddStringToObject(change_passwd_ques_info, "user_name", user_name);
    cJSON_AddStringToObject(change_passwd_ques_info, "question", question);
    cJSON_AddStringToObject(change_passwd_ques_info, "answer", answer);
    return ACCEPTED;
}

/**
 * @Author: Liao Zhaohe
 * @Description: For Database.
 *               Parse the information from cJSON to char*. This information is used to get
 *               password question.
 * @Parameters: 
 *     cJSON* get_passwd_ques_info: A pointer to the cJson struct passed to database by the 
 *            socket server.
 *     char* user_name : Stores username parsed from cJSON
 * @Return: 
 *      Return ACCEPTED for parsing info successfully, other info code for Exception. (See in Throw)
 * @Throw: 
 *      DB_CJSON_PARSE_ERR : when passed cJSON has the error structure.
 */
INFO_CODE parseGetPasswdQuestionInfo(
    cJSON *get_passwd_ques_info,
    char *user_name)
{
    return parseToString(get_passwd_ques_info, user_name, "user_name");
}

/**
 * @Author: Liao Zhaohe
 * @Description: For Client.
 *               Encode the information from char* to cJSON . This information is used to get
 *               password question.
 * @Parameters: 
 *     char* user_name : Stores username parsed from cJSON
 *     cJSON* get_passwd_ques_info: a pointer to a cJson struct, which stores the previouse information.
 *                         Warning: cJSON pointer must be created by "cJSON_CreateObject" function.
 * @Return: 
 *      Return ACCEPTED for parsing info successfully, other info code for Exception.
 * @Throw: 
 */
INFO_CODE encodeGetPasswdQuestionInfo(
    char *user_name,
    cJSON *get_passwd_ques_info)
{
    cJSON_AddStringToObject(get_passwd_ques_info, "type", "get_passwd_question");
    cJSON_AddStringToObject(get_passwd_ques_info, "user_name", user_name);

    return ACCEPTED;
}

/**
 * @Author: Liao Zhaohe
 * @Description: For Database.
 *               Parse the information from cJSON to char*. This information is used to change
 *               password question.
 * @Parameters: 
 *     cJSON* change_passwd_ques_info: A pointer to the cJson struct passed to database by the 
 *              socket server.
 *     char* user_name: Stores username parsed from cJSON
 *     char* answer: Stores answer parsed from cJSON
 *     cher* passwd: Stores passwd parsed from cJSON
 * @Return: 
 *      Return ACCEPTED for parsing info successfully, other info code for Exception. (See in Throw)
 * @Throw: 
 *      DB_CJSON_PARSE_ERR : when passed cJSON has the error structure.
 */
INFO_CODE parseChangePasswdInfo(
    cJSON *change_passwd_info,
    char *user_name,
    char *answer,
    char *passwd)
{
    INFO_CODE info;
    if ((info = parseToString(change_passwd_info, user_name, "user_name")) != ACCEPTED)
        return info;
    if ((info = parseToString(change_passwd_info, answer, "answer")) != ACCEPTED)
        return info;
    if ((info = parseToString(change_passwd_info, passwd, "passwd")) != ACCEPTED)
        return info;

    return ACCEPTED;
}

/**
 * @Author: Liao Zhaohe
 * @Description: For Client
 *               Parse the information from char* to cJSON. This information is used to change
 *               password question.
 * @Parameters: 
 *      char *user_name:  the username of the user who call this function.
 *      char *answer: answer to question
 *      char *passwd: the setting password
 *      cJSON* change_passwd_ques_info: A pointer to the cJson struct passed to database by the 
 *              socket server.
 * @Return: 
 *      Return ACCEPTED for parsing info successfully, other info code for Exception. (See in Throw)
 * @Throw: 
 */
INFO_CODE encodeChangePasswdInfo(
    char *user_name,
    char *answer,
    char *passwd,
    cJSON *change_passwd_info)
{
    cJSON_AddStringToObject(change_passwd_info, "type", "change_passwd");
    cJSON_AddStringToObject(change_passwd_info, "user_name", user_name);
    cJSON_AddStringToObject(change_passwd_info, "answer", answer);
    cJSON_AddStringToObject(change_passwd_info, "passwd", passwd);

    return ACCEPTED;
}

/**
 * @Author: Liao Zhaohe
 * @Description: For Client
 *               Tansfer the online user list into c-type formate
 * @Parameters: 
 *      online_user_info: cJSON recieved from socket.
 *      online_user_num: The number of user that is online.
 *      online_users: The users' name that is online. Each char* reprecents a online user.
 * @Return: 
 *      Return ACCEPTED for ecoding info successfully, other info code for Exception. (See in Throw)
 * @Throw: 
 */
INFO_CODE parseOnlineUserList(
    cJSON *online_user_info,
    int online_user_num,
    char online_users[][40])
{
    cJSON *j_onine_user_num = NULL;
    if ((j_onine_user_num = cJSON_GetObjectItem(online_user_info, "onine_user_num") == NULL))
        return DB_CJSON_PARSE_ERR;
    online_user_num = j_onine_user_num->valueint;

    int i = 0;
    for (i = 0; i < online_user_num; i++)
    {
        char name[30] = "online_user_name";
        char postfix[5];
        memset(postfix, 0, sizeof(postfix));
        sprintf(postfix, "%d", i);
        strcat(name, postfix);
        INFO_CODE info;
        if ((info = parseToString(online_user_info, online_users[i], name)) != ACCEPTED)
            return info;
    }

    return ACCEPTED;
}

/**
 * @Author: Liao Zhaohe
 * @Description: For Database.
 *               Tansfer the online user list into cJSON formate
 * @Parameters: 
 *      online_user_num: The number of user that is online.
 *      online_users: The users' name that is online. Each char* reprecents a online user.
 *      online_user_info: A cJSON pointer that has been created by cJSON_CreateObject function, 
 *                        in which user information will be stored.
 * @Return: 
 *      Return ACCEPTED for ecoding info successfully, other info code for Exception. (See in Throw)
 * @Throw: 
 *      DB_CJSON_PARSE_ERR : when passed cJSON has the error structure.
 */
INFO_CODE encodeOnlineUserList(
    int online_user_num,
    char online_users[][40],
    cJSON *online_user_info)
{
    cJSON_AddNumberToObject(online_user_info, "online_user_num", online_user_num);
    cJSON_AddStringToObject(online_user_info, "type", "online_user_list");
    int i = 0;
    for (i = 0; i < online_user_num; i++)
    {
        char name[30] = "online_user_name";
        char postfix[5];
        memset(postfix, 0, sizeof(postfix));
        sprintf(postfix, "%d", i);
        strcat(name, postfix);
        cJSON_AddStringToObject(online_user_info, name, online_users[i]);
    }

    return ACCEPTED;
}

/**
 * @Author: Liao Zhaohe
 * @Description: For Database.
 *               Tansform the detail of user information to cJSON.
 * @Parameters: 
 *      char* user_ip: IP adderss of the requested user.
 *      char* user_name: The username of the requested user.
 *      char* user_gender: The gender of the requested user.
 *      char* email_address: The email_address of the requested user.
 *      BOOL  is_online: If the requested user is online.
 *      char* user_detail_info: A cJSON pointer that has been created by cJSON_CreateObject function, 
 *                        in which user information will be stored.
 * @Return: 
 *      Return ACCEPTED for ecoding info successfully, other info code for Exception.
 * @Throw: 
 */
INFO_CODE encodeUserDetail(
    char *user_ip,
    char *user_name,
    char *user_gender,
    char *email_address,
    int is_online,
    cJSON *user_detail_info)
{
    cJSON_AddStringToObject(user_detail_info, "type", "user_details");
    cJSON_AddStringToObject(user_detail_info, "user_ip", user_ip);
    cJSON_AddStringToObject(user_detail_info, "user_name", user_name);
    cJSON_AddStringToObject(user_detail_info, "user_gender", user_gender);
    cJSON_AddStringToObject(user_detail_info, "email_address", email_address);
    if (is_online == TRUE)
        cJSON_AddTrueToObject(user_detail_info, "is_online");
    else
        cJSON_AddFalseToObject(user_detail_info, "is_online");

    return ACCEPTED;
}

/**
 * @Author: Liao Zhaohe
 * @Description: For Client.
 *               Tansform the detail of user information to c-type.
 * @Parameters: 
 *      char* user_detail_info: cJSON recieved from socket
 *      char* user_ip: IP adderss of the requested user.
 *      char* user_name: The username of the requested user.
 *      char* user_gender: The gender of the requested user.
 *      char* email_address: The email_address of the requested user.
 *      BOOL  is_online: If the requested user is online.
 * @Return: 
 *      Return ACCEPTED for ecoding info successfully, other info code for Exception.
 * @Throw: 
 */
INFO_CODE parseUserDetail(
    cJSON *user_detail_info,
    char *user_ip,
    char *user_name,
    char *user_gender,
    char *email_address,
    int is_online)
{
    INFO_CODE info;
    if ((info = parseToString(user_detail_info, user_ip, "user_ip")) != ACCEPTED)
        return DB_CJSON_PARSE_ERR;
    if ((info = parseToString(user_detail_info, user_name, "user_name")) != ACCEPTED)
        return DB_CJSON_PARSE_ERR;
    if ((info = parseToString(user_detail_info, user_gender, "user_gender")) != ACCEPTED)
        return DB_CJSON_PARSE_ERR;
    if ((info = parseToString(user_detail_info, email_address, "email_address")) != ACCEPTED)
        return DB_CJSON_PARSE_ERR;

    cJSON *j_is_online = NULL;
    if ((j_is_online = cJSON_GetObjectItem(user_detail_info, "is_online")) == NULL)
        return DB_CJSON_PARSE_ERR;
    is_online = (j_is_online->valueint == cJSON_True) ? TRUE : FALSE;

    return ACCEPTED;
}

/**
 * @Author: Liao Zhaohe
 * @Description: For Database.
 *               Tansform the detail of user information to cJSON.
 * @Parameters: 
 *      char* sender_name: name of the message sender
 *      char* receiver_name: name of the message receiver
 *      char* message: What did the user send
 *      char* time: When did the user send 
 *      char* user_message: A cJSON pointer that has been created by cJSON_CreateObject function, 
 *                        in which user information will be stored.
 * @Return: 
 *      Return ACCEPTED for ecoding info successfully, other info code for Exception.
 * @Throw: 
 */

INFO_CODE encodeUserMessage(
    char *sender_name,
    char *receiver_name,
    char *message,
    char *time,
    cJSON *user_message)
{
    cJSON_AddStringToObject(user_message, "type", "user_message");
    cJSON_AddStringToObject(user_message, sender_name, "sender_name");
    cJSON_AddStringToObject(user_message, receiver_name, "receiver_name");
    cJSON_AddStringToObject(user_message, message, "message");
    cJSON_AddStringToObject(user_message, time, "time");

    return ACCEPTED;
}

/**
 * @Author: Liao Zhaohe
 * @Description: For Client.
 *               Tansform the detail of user information to c-type.
 * @Parameters: 
 *      char* user_message: cJSON recieved from socket
 *      char* sender_name: name of the message sender
 *      char* receiver_name: name of the message receiver
 *      char* message: What did the user send
 *      char* time: When did the user send 
 * @Return: 
 *      Return ACCEPTED for ecoding info successfully, other info code for Exception.
 * @Throw: 
 */

INFO_CODE parseUserMessage(
    cJSON *user_message,
    char *sender_name,
    char *receiver_name,
    char *message,
    char *time)
{
    INFO_CODE info;
    if ((info = parseToString(user_message, sender_name, "sender_name")) == ACCEPTED)
        return info;
    if ((info = parseToString(user_message, receiver_name, "receiver_name")) == ACCEPTED)
        return info;
    if ((info = parseToString(user_message, message, "message")) == ACCEPTED)
        return info;
    if ((info = parseToString(time, time, "time")) == ACCEPTED)
        return info;

    return ACCEPTED;
}

INFO_CODE parseInfoCode(cJSON *info_code_json, INFO_CODE *info_code)
{
    cJSON *j_code = cJSON_GetObjectItem(info_code_json, "info_code");
    *info_code = (INFO_CODE)j_code->valueint;
    return ACCEPTED;
}

INFO_CODE encodeInfoCode(INFO_CODE *info_code, cJSON *info_code_json)
{
    cJSON_AddStringToObject(info_code_json, "type", "info_code");
    cJSON_AddNumberToObject(info_code_json, "info_code", (int)(*info_code));
}
INFO_CODE parsePasswdQuestion(cJSON *passwd_question, char *question)
{
    return parseToString(passwd_question, question, "question");
}
INFO_CODE encodePasswdQuestion(char *question, cJSON *passwd_question)
{
    cJSON_AddStringToObject(passwd_question, "type", "send_passwd_question");
    cJSON_AddStringToObject(passwd_question, "question", question);
}
INFO_CODE parseFile(
    cJSON *file_json,
    char *file_name,
    char *store_dir,
    char *sender_name,
    char *reciever_name,
    char *sender_ip,
    char *reciever_ip)
{
    INFO_CODE info;
    if ((info = parseToString(file_json, file_name, "file_name") != ACCEPTED))
        return info;
    if ((info = parseToString(file_json, store_dir, "store_dir") != ACCEPTED))
        return info;
    if ((info = parseToString(file_json, sender_name, "sender_name")) != ACCEPTED)
        return info;
    if ((info = parseToString(file_json, reciever_name, "reciever_name")) != ACCEPTED)
        return info;
    if ((info = parseToString(file_json, sender_ip, "sender_ip")) != ACCEPTED)
        return info;
    if ((info = parseToString(file_json, reciever_ip, "reciever_ip")) != ACCEPTED)
        return info;

    return ACCEPTED;
}
INFO_CODE encodeFile(
    char *file_name,
    char *store_dir,
    char *sender_name,
    char *reciever_name,
    char *sender_ip,
    char *reciever_ip,
    cJSON *file_json)
{
    cJSON_AddStringToObject(file_json, "type", "user_file");
    cJSON_AddStringToObject(file_json, "file_name", file_name);
    cJSON_AddStringToObject(file_json, "store_dir", store_dir);
    cJSON_AddStringToObject(file_json, "sender_name", sender_name);
    cJSON_AddStringToObject(file_json, "reiever_name", reciever_name);
    cJSON_AddStringToObject(file_json, "sender_ip", sender_ip);
    cJSON_AddStringToObject(file_json, "reciever_ip", reciever_ip);
}

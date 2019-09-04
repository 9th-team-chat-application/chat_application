#ifndef __DATATRANSFORMINTERFACES_H__
#define __DATATRANSFORMINTERFACES_H__

/*
 * @Copyright: School of Computer Science & Technology, BIT
 * @Author: Liao Zhaohe
 * @FileName: DataTransformInterface.h
 * @Version: 
 * @Date: 2019-09-02 18:21:23
 * @LastEditors: 
 * @LastEditTime: 2019-09-04 06:52:17
 * @Description: This file defines data transform interfaces used in databases and client.
 *              With help of these functions, developers can easily transform data from 
 *              standard C type to cJSON type, which is much more convinient to transfer.
 */
#include "head.h"

INFO_CODE parseToString(cJSON *json, char *string, char *name);
INFO_CODE getUsernameFromCJSON(cJSON *json, char *username);
INFO_CODE getTypeFromCJSON(cJSON *json, char *type);
INFO_CODE getUserIPFromCJSON(cJSON *json, char *user_ip);
INFO_CODE parseUserName(cJSON *username_json, char *username);
INFO_CODE parseLoginInfo(cJSON *login_info, char *user_name, char *user_ip, char *password);
INFO_CODE encodeLoginInfo(char *user_name, char *user_ip, char *password, cJSON *login_info);
INFO_CODE parseChangePasswdQuestionInfo(
    cJSON *change_passwd_ques_info,
    char *user_ip,
    char *user_name,
    char *question,
    char *answer);
INFO_CODE encodeChangePasswdQuestionInfo(
    char *user_ip,
    char *user_name,
    char *question,
    char *answer,
    cJSON *change_passwd_ques_info);
INFO_CODE parseGetPasswdQuestionInfo(
    cJSON *get_passwd_ques_info,
    char *user_name);
INFO_CODE encodeGetPasswdQuestionInfo(
    char *user_name,
    cJSON *get_passwd_ques_info);
INFO_CODE parseChangePasswdInfo(
    cJSON *change_passwd_info,
    char *user_name,
    char *answer,
    char *passwd);
INFO_CODE encodeChangePasswdInfo(
    char *user_name,
    char *answer,
    char *passwd,
    cJSON *change_passwd_info);
INFO_CODE parseOnlineUserList(
    cJSON *online_user_info,
    int online_user_num,
    char online_users[][40]);
INFO_CODE encodeOnlineUserList(
    int online_user_num,
    char online_users[][40],
    cJSON *online_user_info);
INFO_CODE parseUserDetail(
    cJSON *user_detail_info,
    char *user_ip,
    char *user_name,
    char *user_gender,
    char *email_address,
    int is_online);
INFO_CODE encodeUserDetail(
    char *user_ip,
    char *user_name,
    char *user_gender,
    char *email_address,
    int is_online,
    cJSON *user_detail_info);
INFO_CODE parseUserMessage(
    cJSON *user_message,
    char *sender_name,
    char *receiver_name,
    char *message,
    char *time);
INFO_CODE encodeUserMessage(
    char *sender_name,
    char *receiver_name,
    char *message,
    char *time,
    cJSON *user_message);
INFO_CODE parseInfoCode(cJSON *info_code_json, INFO_CODE *info_code);
INFO_CODE encodeInfoCode(INFO_CODE *info_code, cJSON *info_code_json);
INFO_CODE parsePasswdQuestion(cJSON *passwd_question, char *question);
INFO_CODE encodePasswdQuestion(char *question, cJSON *passwd_question);
INFO_CODE parseFile(
    cJSON *file_json,
    char *file_name,
    char *store_dir,
    char *sender_name,
    char *reciever_name,
    char *sender_ip,
    char *reciever_ip);
INFO_CODE encodeFile(
    char *file_name,
    char *store_dir,
    char *sender_name,
    char *reciever_name,
    char *sender_ip,
    char *reciever_ip,
    cJSON *file_json);

#endif //!__DATATRANSFORMINTERFACES_H__
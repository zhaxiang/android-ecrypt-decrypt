//
// Created by 16110988 on 2016/12/16.
//
#include "com_android_suning_jnimode_jnibase_JniUtils.h"
#include <string>
#include <stdio.h>
#include "Utils.h"
#include <android/log.h>
#include "blowfish.h"
#include "md5.h"
#include<vector>
#include "SunningDes.h"
#include "blowfish.h"
using namespace std;

#define  LOG_TAG    "com_android_suning_jnimode_jnibase_JniUtils"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

using std::string;
#ifdef __Cplusplus
extern "C"{
#endif
#define KEY "suning"
#define MODE "md5salt"
#define CONTENT "null"
JNIEXPORT JNICALL jstring Java_com_android_suning_jnimode_jnibase_JniUtils_encryptionString
        (JNIEnv *env, jclass clazz, jstring str, jstring mode, jstring key)
{
    LOGE("Java_com_android_suning_jnimode_jnibase_JniUtils_encryptionString");
    char * contentC = NULL;
    char * modeC = NULL;
    char * keyC = NULL;
    if(key == NULL)
    {
        LOGE("key == NULL");
        keyC = KEY;
    }
    else
    {
        LOGE("key != NULL");
        keyC = Utils::jstringToChar(env, key);
        if(NULL == keyC)
        {
            LOGE("key == null");
            keyC = KEY;
        }
    }
    if(mode == NULL)
    {
        modeC = MODE;
    }
    else
    {
        modeC = Utils::jstringToChar(env, mode);
        if(modeC == NULL)
        {
            modeC = MODE;
        }
    }
    if(str == NULL)
    {
        return Utils::charTojstring(env, CONTENT);
    }
    else
    {
        contentC = Utils::jstringToChar(env, str);
        if(NULL == contentC)
        {
            return Utils::charTojstring(env, CONTENT);
        }
    }

    LOGE("contentC = %s , keyC = %s , modeC = %s", contentC, keyC, modeC);

    string contentS(contentC);
    string keyS(keyC);
    string modeS(modeC);

    LOGE("contentS = %s , keyS = %s , modeS = %s", contentS.c_str(), keyS.c_str(), modeS.c_str());
    jstring returnJstring = str;
    if(strcmp((char *)modeS.c_str(),"des") == 0)
    {

        {
        DES des;
        std::string enS = des.Encrypt(contentS, keyS);
        LOGE("enStr = %s", enS.c_str());

        int size = enS.size();
        char *hex_str = new char[size*2+2];
        Utils::CharStr2HexStr((unsigned char*)enS.c_str(),hex_str,size);
        LOGE("hex_str = %s", hex_str);
        LOGE("iSize = %d", size);
        returnJstring = Utils::charTojstring(env, hex_str);
        delete[] hex_str;
        return returnJstring;

        }




//        char MesHex[16]={0};         // 16个字符数组用于存放 64位16进制的密文
//        char MesHexBack[17]={0};
//        //char MyKey[8]={0};           // 初始密钥 8字节*8
//        //char YourKey[8]={0};         // 输入的解密密钥 8字节*8
//        //char MyMessage[8]={0};       // 初始明文
//
//
//        int keyLength = strlen(keyC);
//        LOGE("keyLength = %d", keyLength);
//        int contentLength = strlen(contentC);
//        LOGE("contentLength = %d", contentLength);
//        Des::SetKey(keyC);
//        Des::PlayDes(MesHex, contentC);
//        int i = 0;
//
//        for(i = 0; i < 16; i++)
//        {
//            MesHexBack[i] = MesHex[i];
//        }
//        MesHexBack[16] = '\0';
//        return Utils::charTojstring(env, MesHexBack);
    }
    else if(strcmp((char *)modeS.c_str(),"blowfish") == 0)
    {
        LOGE("blowfish");
        int keyLength = strlen(keyC);
        LOGE("keyLength = %d", keyLength);
        int contentLength = strlen(contentC);
        LOGE("contentLength = %d", contentLength);


        vector<char > keyVe;
        int i = 0;
        for(i =0; i < keyLength; i++)
        {
        keyVe.push_back(keyC[i]);
        }
        vector<char > contentVe;
        for(i =0; i < contentLength; i++)
        {
        contentVe.push_back(contentC[i]);
        }
        Blowfish blowfish(keyVe);
        vector<char> enVe = blowfish.Encrypt(contentVe);
        for(vector<char>::iterator it  = enVe.begin(); it != enVe.end(); it++)
        {
        LOGE("iterator enVe = %c", *(it));
        }
        std::string enS;
        enS.insert(enS.begin(), enVe.begin(), enVe.end());
        LOGE("enString size= %d", enS.size());
        LOGE("enS = %s enS = %d", enS.c_str(), enS.size());
        int size = enS.size();
        char *hex_str = new char[size*2+2];
        Utils::CharStr2HexStr((unsigned char*)enS.c_str(),hex_str,size);
        LOGE("hex_str = %s", hex_str);
        LOGE("iSize = %d", size);
        returnJstring = Utils::charTojstring(env, hex_str);
        delete[] hex_str;
        return returnJstring;
    }
    else if(strcmp((char *)modeS.c_str(),"md5salt") == 0)
    {

        std::string md5 = MD5(contentS + keyS).toStr();
        LOGE("md5salt md5 = %s", md5.c_str());
        return Utils::charTojstring(env, md5.c_str());
    }
    else
    {
        return returnJstring;
    }
}







JNIEXPORT JNICALL jstring Java_com_android_suning_jnimode_jnibase_JniUtils_decryptionString
        (JNIEnv *env, jclass clazz, jstring str, jstring mode, jstring key) {
    LOGE("Java_com_android_suning_jnimode_jnibase_JniUtils_encryptionString");
    char * contentC = NULL;
    char * modeC = NULL;
    char * keyC = NULL;
    if(key == NULL)
    {
        LOGE("key == NULL");
        keyC = KEY;
    }
    else
    {
        LOGE("key != NULL");
        keyC = Utils::jstringToChar(env, key);
        if(NULL == keyC)
        {
            LOGE("key == null");
            keyC = KEY;
        }
    }
    if(mode == NULL)
    {
        modeC = MODE;
    }
    else
    {
        modeC = Utils::jstringToChar(env, mode);
        if(modeC == NULL)
        {
            modeC = MODE;
        }
    }
    if(str == NULL)
    {
        return Utils::charTojstring(env, CONTENT);
    }
    else
    {
        contentC = Utils::jstringToChar(env, str);
        if(NULL == contentC)
        {
            return Utils::charTojstring(env, CONTENT);
        }
    }

    LOGE("contentC = %s , keyC = %s , modeC = %s", contentC, keyC, modeC);

    string contentS(contentC);
    string keyS(keyC);
    string modeS(modeC);



    LOGE("contentS = %s , keyS = %s , modeS = %s", contentS.c_str(), keyS.c_str(), modeS.c_str());
    jstring returnJstring = str;
    if (strcmp((char *) modeS.c_str(), "des") == 0)
    {
        LOGE("des");
        {
        int size = (strlen(contentC) -2)/2 + 1;
        char *pucCharStr = new char[size];
        Utils::HexStr2CharStr((const char *)contentC, (unsigned char *)pucCharStr, size);
        LOGE("pucCharStr = %s", pucCharStr);
        int pucCharStrLength = strlen(pucCharStr);
        LOGE("pucCharStrLength = %d", pucCharStrLength);
        std::string pucVe(pucCharStr, 0, size);

        DES des;
        std::string deStr = des.Decrypt(pucVe, keyS);
        LOGE("deStr = %s", deStr.c_str());
        returnJstring = Utils::charTojstring(env, deStr.c_str());
        delete[] pucCharStr;
        return returnJstring;
        }

////        char MesHex[16]={0};         // 16个字符数组用于存放 64位16进制的密文
////        char MyKey[8]={0};           // 初始密钥 8字节*8
////        char YourKey[8]={0};         // 输入的解密密钥 8字节*8
//        char MyMessage[8]={0};       // 初始明文
//        char MyMessageBack[9]={0};       // 初始明文
//
//        int keyLength = strlen(keyC);
//        LOGE("keyLength = %d", keyLength);
//        int contentLength = strlen(contentC);
//        LOGE("contentLength = %d", contentLength);
//        Des::SetKey(keyC);
//        Des::KickDes(MyMessage, contentC);
//        std::string  endS(MyMessage);
//
//        int i = 0;
//
//        for(i = 0; i < 8; i++)
//        {
//            MyMessageBack[i] = MyMessage[i];
//        }
//        MyMessageBack[8] = '\0';
//
//        return Utils::charTojstring(env, MyMessageBack);
    }
    else if(strcmp((char *)modeS.c_str(),"blowfish") == 0)
    {
        LOGE("blowfish");
        int keyLength = strlen(keyC);
        LOGE("keyLength = %d", keyLength);
        int contentLength = strlen(contentC);
        LOGE("contentLength = %d", contentLength);


        vector<char > keyVe;
        int i = 0;
        for(i =0; i < keyLength; i++)
        {
        keyVe.push_back(keyC[i]);
        }
        Blowfish blowfish(keyVe);

        LOGE("contentC = %d", strlen(contentC));
        int size = (strlen(contentC) -2)/2 + 1;
        char *pucCharStr = new char[size];
        Utils::HexStr2CharStr((const char *)contentC, (unsigned char *)pucCharStr, size);
        LOGE("pucCharStr = %s", pucCharStr);
        int pucCharStrLength = strlen(pucCharStr);
        LOGE("pucCharStrLength = %d", pucCharStrLength);
        vector<char> pucVe;
        int k = 0;
        for(k = 0; k < size; k++)
        {
        pucVe.push_back(pucCharStr[k]);
        }

        vector<char> DeVe = blowfish.Decrypt(pucVe);
        LOGE("DeVe.size = %d", DeVe.size());
        std::string endS;
        endS.insert(endS.begin(), DeVe.begin(), DeVe.end());
        LOGE("endS = %s", endS.c_str());

        returnJstring = Utils::charTojstring(env, endS.c_str());
        delete[] pucCharStr;
        return returnJstring;
    }
    else
    {
        return returnJstring;
    }
}
#ifdef __Cplusplus
};
#endif
//LOGE("enS = %s enS = %d", enS.c_str(), enS.size());
//char *hex_str = new char[enS.size()*2+2];
//Utils::CharStr2HexStr((unsigned char*)enS.c_str(),hex_str,enS.size());
//LOGE("hex_str = %s", hex_str);
//int iSize = (strlen(hex_str) -2)/2 + 1;
//LOGE("iSize = %d", iSize);
//char *pucCharStr = new char[iSize];
//Utils::HexStr2CharStr((const char *)hex_str, (unsigned char *)pucCharStr, iSize);
//LOGE("pucCharStr = %s", pucCharStr);
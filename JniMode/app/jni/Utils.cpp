//
// Created by 16110988 on 2016/12/19.
//
#include "Utils.h"
#include <android/log.h>
#include <iostream>
#include <fstream>

#define  LOG_TAG    "Utils"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

Utils::Utils() { };

Utils::~Utils() { };
#define BYTE unsigned char
char *Utils::jstringToChar(JNIEnv *env, jstring jstr) {
    LOGE("jstringToChar %d", __LINE__);
    char* rtn = NULL;
    jclass clsstring = env->FindClass("java/lang/String");
    jstring strencode = env->NewStringUTF("UTF-8");
    jmethodID mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
    jbyteArray barr= (jbyteArray)env->CallObjectMethod(jstr, mid, strencode);
    jsize alen = env->GetArrayLength(barr);
    jbyte* ba = env->GetByteArrayElements(barr, JNI_FALSE);
    if (alen > 0)
    {
        rtn = (char*)malloc(alen + 1);

        memcpy(rtn, ba, alen);
        rtn[alen] = 0;
    }
    env->ReleaseByteArrayElements(barr, ba, 0);

    return rtn;



//    const char *dname = NULL;
//    dname = env->GetStringUTFChars(jstr, 0);
//    return (char *) dname;
}

// 由于jvm和c++对中文的编码不一样，因此需要转码。gb2312转换成utf8/16
jstring Utils::charTojstring(JNIEnv *env, const char *pat) {
    LOGE("charTojstring line pat =%s", pat);
    jclass strClass = env->FindClass("java/lang/String");
    jmethodID ctorID = env->GetMethodID(strClass, "<init>", "([BLjava/lang/String;)V");
    jbyteArray bytes = env->NewByteArray(strlen(pat));
    env->SetByteArrayRegion(bytes, 0, strlen(pat), (jbyte *) pat);
    jstring encoding = env->NewStringUTF("utf-8");
    return (jstring) env->NewObject(strClass, ctorID, bytes, encoding);
}



int Utils::strToHex(char *ch, char *hex)
{
    int high,low;
    int tmp = 0;
    if(ch == NULL || hex == NULL){
        return -1;
    }

    if(strlen(ch) == 0){
        return -2;
    }

    while(*ch){
        tmp = (int)*ch;
        high = tmp >> 4;
        low = tmp & 15;
        *hex++ = valueToHexCh(high); //先写高字节
        *hex++ = valueToHexCh(low); //其次写低字节
        ch++;
    }
    *hex = '\0';
    return 0;
}

int Utils::hexToStr(char *hex, char *ch)
{
    int high,low;
    int tmp = 0;
    if(hex == NULL || ch == NULL){
        return -1;
    }

    if(strlen(hex) %2 == 1){
        return -2;
    }

    while(*hex){
        high = hexCharToValue(*hex);
        if(high < 0){
            *ch = '\0';
            return -3;
        }
        hex++; //指针移动到下一个字符上
        low = hexCharToValue(*hex);
        if(low < 0){
            *ch = '\0';
            return -3;
        }
        tmp = (high << 4) + low;
        *ch++ = (char)tmp;
        hex++;
    }
    *ch = '\0';
    return 0;
}

int Utils::hexCharToValue(const char ch){
    int result = 0;
    //获取16进制的高字节位数据
    if(ch >= '0' && ch <= '9'){
        result = (int)(ch - '0');
    }
    else if(ch >= 'a' && ch <= 'z'){
        result = (int)(ch - 'a') + 10;
    }
    else if(ch >= 'A' && ch <= 'Z'){
        result = (int)(ch - 'A') + 10;
    }
    else{
        result = -1;
    }
    return result;
}

char Utils::valueToHexCh(const int value)
{
    char result = '\0';
    if(value >= 0 && value <= 9){
        result = (char)(value + 48); //48为ascii编码的‘0’字符编码值
    }
    else if(value >= 10 && value <= 15){
        result = (char)(value - 10 + 65); //减去10则找出其在16进制的偏移量，65为ascii的'A'的字符编码值
    }
    else{
        ;
    }

    return result;
}



void Utils::Char2Hex(const unsigned char ch, char* szHex)
{
    unsigned char byte[2];
    byte[0] = ch/16;
    byte[1] = ch%16;
    for(int i=0; i<2; i++)
    {
        if(byte[i] >= 0 && byte[i] <= 9)
            szHex[i] = '0' + byte[i];
        else
            szHex[i] = 'A' + byte[i] - 10;
    }
    szHex[2] = 0;
}

//Function to convert string of length 2 to unsigned char
void Utils::Hex2Char(const char* szHex, unsigned char& rch)
{
    rch = 0;
    for(int i=0; i<2; i++)
    {
        if(*(szHex + i) >='0' && *(szHex + i) <= '9')
            rch = (rch << 4) + (*(szHex + i) - '0');
        else if(*(szHex + i) >='A' && *(szHex + i) <= 'F')
            rch = (rch << 4) + (*(szHex + i) - 'A' + 10);
        else
            break;
    }
}

//Function to convert string of unsigned chars to string of chars
void Utils::CharStr2HexStr(const unsigned char* pucCharStr, char* pszHexStr, int iSize)
{
    int i;
    char szHex[3];
    pszHexStr[0] = 0;
    for(i=0; i<iSize; i++)
    {
        Char2Hex(pucCharStr[i], szHex);
        strcat(pszHexStr, szHex);
    }
}

//Function to convert string of chars to string of unsigned chars
void Utils::HexStr2CharStr(const char* pszHexStr, unsigned char* pucCharStr, int iSize)
{
    int i;
    unsigned char ch;
    for(i=0; i<iSize; i++)
    {
        Hex2Char(pszHexStr+2*i, ch);
        pucCharStr[i] = ch;
    }
}

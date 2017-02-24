//
// Created by 16110988 on 2016/12/19.
//
#include <wchar.h>
#include <string>
#include <jni.h>

#ifndef TESTAPPLICATION_UTILS_H
#define TESTAPPLICATION_UTILS_H

class Utils {
    // 由于jvm和c++对中文的编码不一样，因此需要转码。 utf8/16转换成gb2312
public:
    Utils();

    ~Utils();

    static char *jstringToChar(JNIEnv *env, jstring jstr);

// 由于jvm和c++对中文的编码不一样，因此需要转码。gb2312转换成utf8/16
    static jstring charTojstring(JNIEnv *env, const char *str);


    static int strToHex(char *ch, char *hex);
    static int hexToStr(char *hex, char *ch);
    static int hexCharToValue(const char ch);
    static char valueToHexCh(const int value);

    static void Char2Hex(const unsigned char ch, char* szHex);
    static void Hex2Char(const char* szHex, unsigned char& rch);
    static void CharStr2HexStr(const unsigned char* pucCharStr, char* pszHexStr, int iSize);
    static void HexStr2CharStr(const char* pszHexStr, unsigned char* pucCharStr, int iSize);
};

#endif //TESTAPPLICATION_UTILS_H

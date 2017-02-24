package com.android.suning.jnimode.jnibase;

/**
 * Created by 16110988 on 2016/12/16.
 */

public class JniUtils {
    public static final String DES_MODULE = "des";
    public static final String BF_MODULE = "blowfish";
    public static final String MS_MODULE = "md5salt";

   public static String encryptionString(String str)
   {
       return encryptionString(str, null, null);
   }

    public static String encryptionString(String str, String module)
    {
        return encryptionString(str, module, null);
    }

    public static String decryptionString(String str)
    {
        return encryptionString(str, null, null);
    }

    public static String decryptionString(String str, String module)
    {
        return encryptionString(str, module, null);
    }

    public static native String encryptionString(String str, String module, String key);
    public static native String decryptionString(String str, String module, String key);

}

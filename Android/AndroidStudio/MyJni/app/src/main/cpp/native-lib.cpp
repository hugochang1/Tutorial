//JNI Tutorial https://www3.ntu.edu.sg/home/ehchua/programming/java/JavaNativeInterface.html
// JNI memory leakage summary: https://amazontzy.iteye.com/blog/1962367
//-------------------------------------------------------------------------------------------------------------------------------------------
#include <jni.h>
#include <string>
#include <android/log.h>

#define LOGD(...) __android_log_print(ANDROID_LOG_INFO, "hugo_app", __VA_ARGS__)

//-------------------------------------------------------------------------------------------------------------------------------------------
void class_set_bool(JNIEnv* env, jobject o, jclass c, const char* name, jboolean value) {
    jfieldID id = env->GetFieldID(c, name, "Z");
    env->SetBooleanField(o, id, value);
}

void class_set_byte(JNIEnv* env, jobject o, jclass c, const char* name, jbyte value) {
    jfieldID id = env->GetFieldID(c, name, "B");
    env->SetByteField(o, id, value);
}

void class_set_short(JNIEnv* env, jobject o, jclass c, const char* name, jshort value) {
    jfieldID id = env->GetFieldID(c, name, "S");
    env->SetShortField(o, id, value);
}

void class_set_int(JNIEnv* env, jobject o, jclass c, const char* name, jint value) {
    jfieldID id = env->GetFieldID(c, name, "I");
    env->SetIntField(o, id, value);
}

void class_set_long(JNIEnv* env, jobject o, jclass c, const char* name, jlong value) {
    jfieldID id = env->GetFieldID(c, name, "J");
    env->SetLongField(o, id, value);
}

void class_set_float(JNIEnv* env, jobject o, jclass c, const char* name, jfloat value) {
    jfieldID id = env->GetFieldID(c, name, "F");
    env->SetFloatField(o, id, value);
}

void class_set_double(JNIEnv* env, jobject o, jclass c, const char* name, jdouble value) {
    jfieldID id = env->GetFieldID(c, name, "D");
    env->SetDoubleField(o, id, value);
}

void class_set_string(JNIEnv* env, jobject o, jclass c, const char* name, const char* value) {
    jfieldID id = env->GetFieldID(c, name, "Ljava/lang/String;");
    if(value == NULL) {
        env->SetObjectField(o, id, NULL);
    } else {
        jstring str = env->NewStringUTF(value);
        env->SetObjectField(o, id, str);
        env->DeleteLocalRef(str);
    }
}

void class_set_byteArray(JNIEnv* env, jobject o, jclass c, const char* name, jbyte* data, int data_length) {
    jfieldID id = env->GetFieldID(c, name, "[B");
    if(data == NULL) {
        env->SetObjectField(o, id, NULL);
    } else {
        jbyteArray arr = env->NewByteArray(data_length);
        env->SetByteArrayRegion(arr, 0, data_length, data);
        env->SetObjectField(o, id, arr);
        env->DeleteLocalRef(arr);
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------
jint jni_get_byteArray(JNIEnv* env, jbyteArray in, char* output, int output_size) {
    if(in == NULL) {
        return 0;
    }
    jsize length = env->GetArrayLength(in);
    jbyte* byteArray = env->GetByteArrayElements(in, NULL);

    if(length > output_size) {
        length = output_size;
    }
    memcpy(output, byteArray, length);

    env->ReleaseByteArrayElements(in, byteArray, 0);
    return length;
}

jint jni_get_string(JNIEnv* env, jstring in, char* output, int output_size) {
    if(in == NULL) {
        return 0;
    }
    const char* str = env->GetStringUTFChars(in, NULL);

    int length = strlen(str);
    if(length > (output_size - 1)) {
        length = output_size - 1;
    }
    strncpy(output, str, length);

    env->ReleaseStringUTFChars(in, str);
    return length;
}

jboolean class_get_bool(JNIEnv* env, jobject o, jclass c, const char* name) {
    jfieldID id = env->GetFieldID(c, name, "Z");
    return env->GetBooleanField(o, id);
}

jbyte class_get_byte(JNIEnv* env, jobject o, jclass c, const char* name) {
    jfieldID id = env->GetFieldID(c, name, "B");
    return env->GetByteField(o, id);
}

jshort class_get_short(JNIEnv* env, jobject o, jclass c, const char* name) {
    jfieldID id = env->GetFieldID(c, name, "S");
    return env->GetShortField(o, id);
}

jint class_get_int(JNIEnv* env, jobject o, jclass c, const char* name) {
    jfieldID id = env->GetFieldID(c, name, "I");
    return env->GetIntField(o, id);
}

jlong class_get_long(JNIEnv* env, jobject o, jclass c, const char* name) {
    jfieldID id = env->GetFieldID(c, name, "J");
    return env->GetLongField(o, id);
}

jfloat class_get_float(JNIEnv* env, jobject o, jclass c, const char* name) {
    jfieldID id = env->GetFieldID(c, name, "F");
    return env->GetFloatField(o, id);
}

jdouble class_get_double(JNIEnv* env, jobject o, jclass c, const char* name) {
    jfieldID id = env->GetFieldID(c, name, "D");
    return env->GetDoubleField(o, id);
}

jobject class_get_class(JNIEnv* env, jobject o, jclass c, const char* name, const char* className) {
    jfieldID id = env->GetFieldID(c, name, className);
    return env->GetObjectField(o, id);
}

jint class_get_string(JNIEnv* env, jobject o, jclass c, const char* name, char* output, int output_size) {
    jfieldID id = env->GetFieldID(c, name, "Ljava/lang/String;");
    jstring str = (jstring)env->GetObjectField(o, id);
    jint len = jni_get_string(env, str, output, output_size);
    env->DeleteLocalRef(str);
    return len;
}

jint class_get_byteArray(JNIEnv* env, jobject o, jclass c, const char* name, char* output, int output_size) {
    jfieldID id = env->GetFieldID(c, name, "[B");
    jbyteArray arr = (jbyteArray)env->GetObjectField(o, id);
    jint len = jni_get_byteArray(env, arr, output, output_size);
     env->DeleteLocalRef(arr);
    return len;
}

//-------------------------------------------------------------------------------------------------------------------------------------------
jobject newMyClass(JNIEnv* env) {
    // get class
    jclass c = env->FindClass("com/example/hugo/myjni/MainActivity$MyClass");
    // get constructor
    jmethodID mid = env->GetMethodID(c, "<init>", "()V");
    // new object
    jobject o = env->NewObject(c, mid);

    //assign values
    class_set_bool(env, o, c, "boo", true);
    class_set_byte(env, o, c, "b", 1);
    class_set_short(env, o, c, "s", 2);
    class_set_int(env, o, c, "i", 3);
    class_set_long(env, o, c, "l", 4);
    class_set_float(env, o, c, "f", 5.1f);
    class_set_double(env, o, c, "d", 6.1);
    class_set_string(env, o, c, "str", "Good!!!!!!!!!!!!");
    jbyte data[] = {3,2,1,0};
    class_set_byteArray(env, o, c, "ba", data, sizeof(data));

    // new MyClass2
    jclass c2 = env->FindClass("com/example/hugo/myjni/MainActivity$MyClass2");
    jmethodID mid2 = env->GetMethodID(c2, "<init>", "()V");
    jobject o2 = env->NewObject(c2, mid2);

    // assign to MyClass.c
    jfieldID id = env->GetFieldID(c, "c", "Lcom.example.hugo.myjni.MainActivity$MyClass2;");
    env->SetObjectField(o, id, o2);

    class_set_int(env, o2, c2, "i2", 7);

    // delete
    env->DeleteLocalRef(c);
    env->DeleteLocalRef(c2);
    env->DeleteLocalRef(o2);
    return o;
}

void dumpMyClass(JNIEnv* env, jobject o1) {
    if(o1 == NULL) {
        LOGD("MyClass is NULL");
        return;
    }
    jclass c = env->GetObjectClass(o1);
    LOGD("  boo=%d", class_get_bool(env, o1, c, "boo"));
    LOGD("  b=%d", class_get_byte(env, o1, c, "b"));
    LOGD("  s=%d", class_get_short(env, o1, c, "s"));
    LOGD("  i=%d", class_get_int(env, o1, c, "i"));
    LOGD("  l=%ld", class_get_long(env, o1, c, "l"));
    LOGD("  f=%f", class_get_float(env, o1, c, "f"));
    LOGD("  d=%lf", class_get_double(env, o1, c, "d"));
    int len = 0;
    char buff[128] = {0};
    len = class_get_string(env, o1, c, "str", buff, sizeof(buff));
    LOGD("  str len=%d str=[%s]", len, buff);
    len = class_get_byteArray(env, o1, c, "ba", buff, sizeof(buff));
    LOGD("  ba len=%d", len);
    for(int i = 0; i < len; i++) {
        LOGD("    i=%d data=%d", i, buff[i]);
    }

    jobject o2 = class_get_class(env, o1, c, "c", "Lcom.example.hugo.myjni.MainActivity$MyClass2;");
    if(o2 == NULL) {
        LOGD("c is NULL");
        return;
    }
    jclass c2 = env->GetObjectClass(o2);
    LOGD("  i2=%d", class_get_int(env, o2, c2, "i2"));

    //delete jclass
    env->DeleteLocalRef(c);
    env->DeleteLocalRef(c2);
    env->DeleteLocalRef(o2);
}

//-------------------------------------------------------------------------------------------------------------------------------------------
extern "C" JNIEXPORT void JNICALL
Java_com_example_hugo_myjni_MainActivity_nativeVoid(
        JNIEnv* env,
        jobject thisObj) {
    LOGD("nativeVoid");
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_hugo_myjni_MainActivity_nativeReturnString(
        JNIEnv* env,
        jobject thisObj) {
    std::string hello = "nativeString";
    return env->NewStringUTF(hello.c_str());
}

extern "C" JNIEXPORT jint JNICALL
Java_com_example_hugo_myjni_MainActivity_nativeReturnInt(
        JNIEnv* env,
        jobject /* this */) {
    return 456;
}

extern "C" JNIEXPORT jobject JNICALL
Java_com_example_hugo_myjni_MainActivity_nativeReturnClass(
        JNIEnv* env,
        jobject thisObj) {
    LOGD("nativeReturnClass");
    return newMyClass(env);
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_hugo_myjni_MainActivity_nativeInputPrimitive(
        JNIEnv* env,
        jobject thisObj,
        jboolean boo, jbyte b, jshort s, jint i, jlong l, jfloat f, jdouble d) {
    LOGD("nativeInputPrimitive boo=%d b=%d s=%d i=%d l=%ld f=%f d=%lf", boo, b, s, i, l, f, d);
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_hugo_myjni_MainActivity_nativeInputByteArray(
        JNIEnv* env,
        jobject thisObj,
        jbyteArray o) {
    LOGD("nativeInputByteArray data=%p", o);
    int len;
    char buff[128] = {0};
    len = jni_get_byteArray(env, o, buff, sizeof(buff));
    LOGD("  len=%d", len);
    for(int i = 0; i < len; i++) {
        LOGD("  i=%d data=%d", i, buff[i]);
    }
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_hugo_myjni_MainActivity_nativeInputString(
        JNIEnv* env,
        jobject thisObj,
        jstring o) {
    LOGD("nativeInputString in=%p", o);

    int len;
    char str[128] = {0};
    len = jni_get_string(env, o, str, sizeof(str));
    LOGD("  len=%d str=[%s]", len, str);
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_hugo_myjni_MainActivity_nativeInputClass(
        JNIEnv* env,
        jobject thisObj,
        jobject o) {
    LOGD("nativeInputClass c=%p", o);
    dumpMyClass(env, o);
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_hugo_myjni_MainActivity_nativeInputClassArray(
        JNIEnv* env,
        jobject thisObj,
        jobjectArray o) {
    LOGD("nativeInputClassArray c=%p", o);
    if(o == NULL) {
        return;
    }
    jsize length = env->GetArrayLength(o);
    LOGD("  length=%d", length);
    for(int i = 0; i < length; i++) {
        jobject o2 = env->GetObjectArrayElement(o, i);
        LOGD("    i=%d obj=%p", i, o2);
        if(o2 != NULL) {
            dumpMyClass(env, o2);
        }
        //delete jobject
        env->DeleteLocalRef(o2);
    }
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_hugo_myjni_MainActivity_nativeModifyClass(
        JNIEnv* env,
        jobject thisObj,
        jobject o1) {
    LOGD("nativeModifyClass c=%p", o1);
    if(o1 == NULL) {
        return;
    }
    jclass c1 = env->GetObjectClass(o1);

    class_set_bool(env, o1, c1, "boo", false);
    class_set_byte(env, o1, c1, "b", 11);
    class_set_short(env, o1, c1, "s", 22);
    class_set_int(env, o1, c1, "i", 33);
    class_set_long(env, o1, c1, "l", 44);
    class_set_float(env, o1, c1, "f", 12.34f);
    class_set_double(env, o1, c1, "d", 43.21);
    class_set_string(env, o1, c1, "str", "world");

    class_set_byteArray(env, o1, c1, "ba", NULL, 0);
    jbyte data[] = {11,22,33,0,44,55};
    class_set_byteArray(env, o1, c1, "ba", data, sizeof(data));

    jobject o2 = class_get_class(env, o1, c1, "c", "Lcom.example.hugo.myjni.MainActivity$MyClass2;");
    if(o2 == NULL) {
        LOGD("c is NULL");
        return;
    }
    jclass c2 = env->GetObjectClass(o2);
    class_set_int(env, o2, c2, "i2", 55);

    //delete jclass
    env->DeleteLocalRef(o2);
    env->DeleteLocalRef(c1);
    env->DeleteLocalRef(c2);
}


extern "C" JNIEXPORT void JNICALL
Java_com_example_hugo_myjni_MainActivity_nativeCallbacks(
        JNIEnv* env,
        jobject thisObj) {
    LOGD("nativeCallbacks");

    jmethodID mid;
    jclass c1 = env->GetObjectClass(thisObj);

    mid = env->GetMethodID(c1, "callback", "()V");
    env->CallVoidMethod(thisObj, mid);

    mid = env->GetMethodID(c1, "callbackReturnBool", "()Z");
    LOGD("CallBooleanMethod=%d", env->CallBooleanMethod(thisObj, mid));

    mid = env->GetMethodID(c1, "callbackReturnByte", "()B");
    LOGD("CallByteMethod=%d", env->CallByteMethod(thisObj, mid));

    mid = env->GetMethodID(c1, "callbackReturnShort", "()S");
    LOGD("CallShortMethod=%d", env->CallShortMethod(thisObj, mid));

    mid = env->GetMethodID(c1, "callbackReturnInt", "()I");
    LOGD("CallIntMethod=%d", env->CallIntMethod(thisObj, mid));

    mid = env->GetMethodID(c1, "callbackReturnLong", "()J");
    LOGD("CallLongMethod=%ld", env->CallLongMethod(thisObj, mid));

    mid = env->GetMethodID(c1, "callbackReturnFloat", "()F");
    LOGD("CallFloatMethod=%f", env->CallFloatMethod(thisObj, mid));

    mid = env->GetMethodID(c1, "callbackReturnDouble", "()D");
    LOGD("CallDoubleMethod=%f", env->CallDoubleMethod(thisObj, mid));

    mid = env->GetMethodID(c1, "callbackReturnString", "()Ljava/lang/String;");
    jstring jstr = (jstring) env->CallObjectMethod(thisObj, mid);
    char str[32] = {0};
    int str_len = jni_get_string(env, jstr, str, sizeof(str));
    LOGD("str_len=%d str=[%s]", str_len, str);

    mid = env->GetMethodID(c1, "callbackReturnByteArray", "()[B");
    jbyteArray jarray = (jbyteArray) env->CallObjectMethod(thisObj, mid);
    char buff[32] = {0};
    int len = jni_get_byteArray(env, jarray, buff, sizeof(buff));
    LOGD("len=%d data=%02x %02x %02x %02x ", len, buff[0], buff[1], buff[2], buff[3]);

    mid = env->GetMethodID(c1, "callbackInputs", "(ZBSIJFD)V");
    env->CallVoidMethod(thisObj, mid, true, 1, 2, 3, 4, 5.5f, 6.6);

    jstring str2 = env->NewStringUTF("hello world");
    mid = env->GetMethodID(c1, "callbackInputString", "(Ljava/lang/String;)V");
    env->CallVoidMethod(thisObj, mid, NULL);
    env->CallVoidMethod(thisObj, mid, str2);

    char buff2[] = {1, 2, 3, 4, 5, 0};
    jbyteArray arr = env->NewByteArray(sizeof(buff2));
    env->SetByteArrayRegion(arr, 0, sizeof(buff2), (jbyte*)buff2);
    mid = env->GetMethodID(c1, "callbackInputByteArray", "([B)V");
    env->CallVoidMethod(thisObj, mid, NULL);
    env->CallVoidMethod(thisObj, mid, arr);

    mid = env->GetMethodID(c1, "callbackInputClass", "(Lcom/example/hugo/myjni/MainActivity$MyClass;)V");
    env->CallVoidMethod(thisObj, mid, NULL);

    jclass c2 = env->FindClass("com/example/hugo/myjni/MainActivity$MyClass");
    jmethodID mid2 = env->GetMethodID(c2, "<init>", "()V");
    jobject o2 = env->NewObject(c2, mid2);
    class_set_bool(env, o2, c2, "boo", true);
    class_set_byte(env, o2, c2, "b", 1);
    class_set_short(env, o2, c2, "s", 2);
    class_set_int(env, o2, c2, "i", 3);
    class_set_long(env, o2, c2, "l", 4);
    class_set_float(env, o2, c2, "f", 5.1f);
    class_set_double(env, o2, c2, "d", 6.1);
    class_set_string(env, o2, c2, "str", "Good!!!!!!!!!!!!");
    jbyte data[] = {3,2,1,0};
    class_set_byteArray(env, o2, c2, "ba", data, sizeof(data));

    jclass c3 = env->FindClass("com/example/hugo/myjni/MainActivity$MyClass2");
    jmethodID mid3 = env->GetMethodID(c3, "<init>", "()V");
    jobject o3 = env->NewObject(c3, mid3);

    jfieldID id = env->GetFieldID(c2, "c", "Lcom.example.hugo.myjni.MainActivity$MyClass2;");
    env->SetObjectField(o2, id, o3);
    class_set_int(env, o3, c3, "i2", 7);

    env->CallVoidMethod(thisObj, mid, o2);

    // delete
    env->DeleteLocalRef(o2);
    env->DeleteLocalRef(o3);
    env->DeleteLocalRef(c1);
    env->DeleteLocalRef(c2);
    env->DeleteLocalRef(c3);
}


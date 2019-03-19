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


extern "C" JNIEXPORT void JNICALL
Java_com_example_hugo_myjni_MainActivity_nativeVoid(
        JNIEnv* env,
        jobject /* this */) {
    LOGD("nativeVoid");
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_hugo_myjni_MainActivity_nativeReturnString(
        JNIEnv* env,
        jobject /* this */) {
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
        jobject /* this */) {
    LOGD("nativeReturnClass");

    // get class
    jclass cls = env->FindClass("com/example/hugo/myjni/MainActivity$MyClass");
    // get constructor
    jmethodID method = env->GetMethodID(cls, "<init>", "()V");
    // new object
    jobject obj = env->NewObject(cls, method);

    //assign values
    class_set_bool(env, obj, cls, "boo", true);
    class_set_byte(env, obj, cls, "b", 1);
    class_set_short(env, obj, cls, "s", 2);
    class_set_int(env, obj, cls, "i", 3);
    class_set_long(env, obj, cls, "l", 4);
    class_set_float(env, obj, cls, "f", 5.1f);
    class_set_double(env, obj, cls, "d", 6.1);
    class_set_string(env, obj, cls, "str", "Good!!!!!!!!!!!!");
    jbyte data[] = {3,2,1,0};
    class_set_byteArray(env, obj, cls, "ba", data, sizeof(data));

    // new MyClass2
    jclass cls2 = env->FindClass("com/example/hugo/myjni/MainActivity$MyClass2");
    jmethodID method2 = env->GetMethodID(cls2, "<init>", "()V");
    jobject obj2 = env->NewObject(cls2, method);

    // assign to MyClass.c
    jfieldID id = env->GetFieldID(cls, "c", "Lcom.example.hugo.myjni.MainActivity$MyClass2;");
    env->SetObjectField(obj, id, obj2);

    class_set_int(env, obj2, cls2, "i2", 7);

    // delete
    env->DeleteLocalRef(cls);
    env->DeleteLocalRef(cls2);
    return obj;
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_hugo_myjni_MainActivity_nativeInputPrimitive(
        JNIEnv* env,
        jobject /* this */,
        jboolean boo, jbyte b, jshort s, jint i, jlong l, jfloat f, jdouble d) {
    LOGD("nativeInputPrimitive boo=%d b=%d s=%d i=%d l=%ld f=%f d=%lf", boo, b, s, i, l, f, d);
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_hugo_myjni_MainActivity_nativeInputByteArray(
        JNIEnv* env,
        jobject /* this */,
        jbyteArray obj1) {
    LOGD("nativeInputByteArray data=%p", obj1);

    int len;
    char buff[128] = {0};
    len = jni_get_byteArray(env, obj1, buff, sizeof(buff));
    LOGD("  len=%d", len);
    for(int i = 0; i < len; i++) {
        LOGD("  i=%d data=%d", i, buff[i]);
    }
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_hugo_myjni_MainActivity_nativeInputString(
        JNIEnv* env,
        jobject /* this */,
        jstring obj1) {
    LOGD("nativeInputString in=%p", obj1);

    int len;
    char str[128] = {0};
    len = jni_get_string(env, obj1, str, sizeof(str));
    LOGD("  len=%d str=[%s]", len, str);
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_hugo_myjni_MainActivity_nativeInputClass(
        JNIEnv* env,
        jobject /* this */,
        jobject obj1) {
    LOGD("nativeInputClass c=%p", obj1);
    if(obj1 == NULL) {
        return;
    }
    jclass c = env->GetObjectClass(obj1);
    LOGD("  boo=%d", class_get_bool(env, obj1, c, "boo"));
    LOGD("  b=%d", class_get_byte(env, obj1, c, "b"));
    LOGD("  s=%d", class_get_short(env, obj1, c, "s"));
    LOGD("  i=%d", class_get_int(env, obj1, c, "i"));
    LOGD("  l=%ld", class_get_long(env, obj1, c, "l"));
    LOGD("  f=%f", class_get_float(env, obj1, c, "f"));
    LOGD("  d=%lf", class_get_double(env, obj1, c, "d"));
    int len = 0;
    char buff[128] = {0};
    len = class_get_string(env, obj1, c, "str", buff, sizeof(buff));
    LOGD("  str len=%d str=[%s]", len, buff);
    len = class_get_byteArray(env, obj1, c, "ba", buff, sizeof(buff));
    LOGD("  ba len=%d", len);
    for(int i = 0; i < len; i++) {
        LOGD("    i=%d data=%d", i, buff[i]);
    }

    jobject obj = class_get_class(env, obj1, c, "c", "Lcom.example.hugo.myjni.MainActivity$MyClass2;");
    if(obj == NULL) {
        LOGD("c is NULL");
        return;
    }
    jclass c2 = env->GetObjectClass(obj);
    LOGD("  i2=%d", class_get_int(env, obj, c2, "i2"));

    //delete jclass
    env->DeleteLocalRef(obj);
    env->DeleteLocalRef(c);
    env->DeleteLocalRef(c2);
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_hugo_myjni_MainActivity_nativeInputClassArray(
        JNIEnv* env,
        jobject /* this */,
        jobjectArray obj1) {
    LOGD("nativeInputClassArray c=%p", obj1);
    if(obj1 == NULL) {
        return;
    }
    jsize length = env->GetArrayLength(obj1);
    LOGD("  lenght=%d", length);
    for(int i = 0; i < length; i++) {
        jobject obj = env->GetObjectArrayElement(obj1, i);
        LOGD("    i=%d obj=%p", i, obj);
        if(obj != NULL) {
            jclass c = env->GetObjectClass(obj);
            LOGD("      i=%d", class_get_int(env, obj, c, "i"));
            LOGD("      l=%ld", class_get_long(env, obj, c, "l"));
            //delete jclass
            env->DeleteLocalRef(c);
        }
        //delete jobject
        env->DeleteLocalRef(obj);
    }
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_hugo_myjni_MainActivity_nativeModifyClass(
        JNIEnv* env,
        jobject /* this */,
        jobject obj1) {
    LOGD("nativeModifyClass c=%p", obj1);
    if(obj1 == NULL) {
        return;
    }
    jclass cls1 = env->GetObjectClass(obj1);

    class_set_bool(env, obj1, cls1, "boo", false);
    class_set_byte(env, obj1, cls1, "b", 11);
    class_set_short(env, obj1, cls1, "s", 22);
    class_set_int(env, obj1, cls1, "i", 33);
    class_set_long(env, obj1, cls1, "l", 44);
    class_set_float(env, obj1, cls1, "f", 12.34f);
    class_set_double(env, obj1, cls1, "d", 43.21);
    class_set_string(env, obj1, cls1, "str", "world");

    class_set_byteArray(env, obj1, cls1, "ba", NULL, 0);
    jbyte data[] = {11,22,33,0,44,55};
    class_set_byteArray(env, obj1, cls1, "ba", data, sizeof(data));

    jobject obj2 = class_get_class(env, obj1, cls1, "c", "Lcom.example.hugo.myjni.MainActivity$MyClass2;");
    if(obj2 == NULL) {
        LOGD("c is NULL");
        return;
    }
    jclass cls2 = env->GetObjectClass(obj2);
    class_set_int(env, obj2, cls2, "i2", 55);

    //delete jclass
    env->DeleteLocalRef(obj2);
    env->DeleteLocalRef(cls1);
    env->DeleteLocalRef(cls2);
}


extern "C" JNIEXPORT void JNICALL
Java_com_example_hugo_myjni_MainActivity_nativeCallbacks(
        JNIEnv* env,
        jobject obj) {
    LOGD("nativeCallbacks");

    jmethodID mid;
    jclass cls = env->GetObjectClass(obj);

    mid = env->GetMethodID(cls, "callback", "()V");
    env->CallVoidMethod(obj, mid);

    mid = env->GetMethodID(cls, "callbackReturnBool", "()Z");
    LOGD("CallBooleanMethod=%d", env->CallBooleanMethod(obj, mid));

    mid = env->GetMethodID(cls, "callbackReturnByte", "()B");
    LOGD("CallByteMethod=%d", env->CallByteMethod(obj, mid));

    mid = env->GetMethodID(cls, "callbackReturnShort", "()S");
    LOGD("CallShortMethod=%d", env->CallShortMethod(obj, mid));

    mid = env->GetMethodID(cls, "callbackReturnInt", "()I");
    LOGD("CallIntMethod=%d", env->CallIntMethod(obj, mid));

    mid = env->GetMethodID(cls, "callbackReturnLong", "()J");
    LOGD("CallLongMethod=%ld", env->CallLongMethod(obj, mid));

    mid = env->GetMethodID(cls, "callbackReturnFloat", "()F");
    LOGD("CallFloatMethod=%f", env->CallFloatMethod(obj, mid));

    mid = env->GetMethodID(cls, "callbackReturnDouble", "()D");
    LOGD("CallDoubleMethod=%f", env->CallDoubleMethod(obj, mid));

    mid = env->GetMethodID(cls, "callbackReturnString", "()Ljava/lang/String;");
    jstring jstr = (jstring) env->CallObjectMethod(obj, mid);
    char str[32] = {0};
    int str_len = jni_get_string(env, jstr, str, sizeof(str));
    LOGD("str_len=%d str=[%s]", str_len, str);

    mid = env->GetMethodID(cls, "callbackReturnByteArray", "()[B");
    jbyteArray jarray = (jbyteArray) env->CallObjectMethod(obj, mid);
    char buff[32] = {0};
    int len = jni_get_byteArray(env, jarray, buff, sizeof(buff));
    LOGD("len=%d data=%02x %02x %02x %02x ", len, buff[0], buff[1], buff[2], buff[3]);

    mid = env->GetMethodID(cls, "callbackInputs", "(ZBSIJFD)V");
    env->CallVoidMethod(obj, mid, true, 1, 2, 3, 4, 5.5f, 6.6);

    jstring str2 = env->NewStringUTF("hello world");
    mid = env->GetMethodID(cls, "callbackInputString", "(Ljava/lang/String;)V");
    env->CallVoidMethod(obj, mid, NULL);
    env->CallVoidMethod(obj, mid, str2);

    char buff2[] = {1, 2, 3, 4, 5, 0};
    jbyteArray arr = env->NewByteArray(sizeof(buff2));
    env->SetByteArrayRegion(arr, 0, sizeof(buff2), (jbyte*)buff2);
    mid = env->GetMethodID(cls, "callbackInputByteArray", "([B)V");
    env->CallVoidMethod(obj, mid, NULL);
    env->CallVoidMethod(obj, mid, arr);

    mid = env->GetMethodID(cls, "callbackInputClass", "(Lcom/example/hugo/myjni/MainActivity$MyClass;)V");
    env->CallVoidMethod(obj, mid, NULL);

    jclass cls2 = env->FindClass("com/example/hugo/myjni/MainActivity$MyClass");
    jmethodID mid2 = env->GetMethodID(cls2, "<init>", "()V");
    jobject obj2 = env->NewObject(cls2, mid2);
    class_set_bool(env, obj2, cls2, "boo", true);
    class_set_byte(env, obj2, cls2, "b", 1);
    class_set_short(env, obj2, cls2, "s", 2);
    class_set_int(env, obj2, cls2, "i", 3);
    class_set_long(env, obj2, cls2, "l", 4);
    class_set_float(env, obj2, cls2, "f", 5.1f);
    class_set_double(env, obj2, cls2, "d", 6.1);
    class_set_string(env, obj2, cls2, "str", "Good!!!!!!!!!!!!");
    jbyte data[] = {3,2,1,0};
    class_set_byteArray(env, obj2, cls2, "ba", data, sizeof(data));

    jclass cls3 = env->FindClass("com/example/hugo/myjni/MainActivity$MyClass2");
    jmethodID mid3 = env->GetMethodID(cls3, "<init>", "()V");
    jobject obj3 = env->NewObject(cls3, mid3);

    jfieldID id = env->GetFieldID(cls2, "c", "Lcom.example.hugo.myjni.MainActivity$MyClass2;");
    env->SetObjectField(obj2, id, obj3);
    class_set_int(env, obj3, cls3, "i2", 7);

    env->CallVoidMethod(obj, mid, obj2);

    // delete
    env->DeleteLocalRef(obj2);
    env->DeleteLocalRef(obj3);
    env->DeleteLocalRef(cls2);
    env->DeleteLocalRef(cls3);
}


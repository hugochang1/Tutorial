#include <jni.h>
#include <string>
#include <android/log.h>

#define LOGD(...) __android_log_print(ANDROID_LOG_INFO, "hugo_app", __VA_ARGS__)

jint        jni_get_string(JNIEnv* env, jstring in, char* output, int output_size);
jint        jni_get_byteArray(JNIEnv* env, jbyteArray in, char* output, int output_size);

jboolean    class_get_bool(JNIEnv* env, jobject o, jclass c, const char* name);
jbyte       class_get_byte(JNIEnv* env, jobject o, jclass c, const char* name);
jshort      class_get_short(JNIEnv* env, jobject o, jclass c, const char* name);
jint        class_get_int(JNIEnv* env, jobject o, jclass c, const char* name);
jlong       class_get_long(JNIEnv* env, jobject o, jclass c, const char* name);
jfloat      class_get_float(JNIEnv* env, jobject o, jclass c, const char* name);
jdouble     class_get_double(JNIEnv* env, jobject o, jclass c, const char* name);
jint        class_get_string(JNIEnv* env, jobject o, jclass c, const char* name, char* output, int output_size);
jint        class_get_byteArray(JNIEnv* env, jobject o, jclass c, const char* name, char* output, int output_size);

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
        jbyteArray in) {
    LOGD("nativeInputByteArray data=%p", in);

    int len;
    char buff[128] = {0};
    len = jni_get_byteArray(env, in, buff, sizeof(buff));
    LOGD("  len=%d", len);
    for(int i = 0; i < len; i++) {
        LOGD("  i=%d data=%d", i, buff[i]);
    }
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_hugo_myjni_MainActivity_nativeInputString(
        JNIEnv* env,
        jobject /* this */,
        jstring in) {
    LOGD("nativeInputString in=%p", in);

    int len;
    char str[128] = {0};
    len = jni_get_string(env, in, str, sizeof(str));
    LOGD("  len=%d str=[%s]", len, str);
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_hugo_myjni_MainActivity_nativeInputClass(
        JNIEnv* env,
        jobject /* this */,
        jobject in) {
    LOGD("nativeInputClass c=%p", in);
    if(in == NULL) {
        return;
    }
    jclass c = env->GetObjectClass(in);
    LOGD("  boo=%d", class_get_bool(env, in, c, "boo"));
    LOGD("  b=%d", class_get_byte(env, in, c, "b"));
    LOGD("  s=%d", class_get_short(env, in, c, "s"));
    LOGD("  i=%d", class_get_int(env, in, c, "i"));
    LOGD("  l=%ld", class_get_long(env, in, c, "l"));
    LOGD("  f=%f", class_get_float(env, in, c, "f"));
    LOGD("  d=%lf", class_get_double(env, in, c, "d"));
    int len = 0;
    char buff[128] = {0};
    len = class_get_string(env, in, c, "str", buff, sizeof(buff));
    LOGD("  str len=%d str=[%s]", len, buff);
    //TODO
    len = class_get_byteArray(env, in, c, "ba", buff, sizeof(buff));
    LOGD("  ba len=%d", len);
    for(int i = 0; i < len; i++) {
        LOGD("    i=%d data=%d", i, buff[i]);
    }
}

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

jint class_get_string(JNIEnv* env, jobject o, jclass c, const char* name, char* output, int output_size) {
    jfieldID id = env->GetFieldID(c, name, "Ljava/lang/String;");
    jstring str = (jstring)env->GetObjectField(o, id);
    return jni_get_string(env, str, output, output_size);
}

jint class_get_byteArray(JNIEnv* env, jobject o, jclass c, const char* name, char* output, int output_size) {
    jfieldID id = env->GetFieldID(c, name, "[B");
    jbyteArray arr = (jbyteArray)env->GetObjectField(o, id);
    return jni_get_byteArray(env, arr, output, output_size);
}

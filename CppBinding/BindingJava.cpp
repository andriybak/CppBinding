#include "jni.h"

#include "BindingJava.h"
#include "export_functions.h"
#include "map.hpp"

//Variables that are used to store intermidiate variables to handle java request for callback.
//This could be expanced to a class instead of using variables. For this small assigment do not see the point in extending things.
namespace
{
    JNIEnv* InternalEnv = nullptr;
    jobject* InternalObject = nullptr;
    jstring CallbackName;
}

static void RenderFunction()
{
    if (InternalEnv && InternalObject)
    {
        jclass ThisClass = InternalEnv->GetObjectClass(*InternalObject);

        const char* CallbackChars = InternalEnv->GetStringUTFChars(CallbackName, NULL);
        jmethodID MethodId = InternalEnv->GetMethodID(ThisClass, CallbackChars, "()V");
        if(MethodId > 0)
        {
            InternalEnv->CallVoidMethod(*InternalObject, MethodId);
        }

        InternalEnv->ReleaseStringUTFChars(CallbackName, CallbackChars);
    }
}

/*
 * Class:     BindingJava
 * Method:    CreateStyleOptionsInstance
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_BindingJava_CreateStyleOptionsInstance(JNIEnv* env, jobject thisObj)
{
    return (jlong)CreateStyleOptionsInstance();
}

/*
 * Class:     BindingJava
 * Method:    CreateStyleWithStyleURL
 * Signature: (JLjava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_BindingJava_CreateStyleWithStyleURL(JNIEnv* env, jobject thisObj, jlong StyleInstanceAddr, jstring StyleUrlString)
{
    StyleOptions* Options = reinterpret_cast<StyleOptions*>(StyleInstanceAddr);
    const char *StyleUrl = env->GetStringUTFChars(StyleUrlString, NULL);
    jlong Result = (jlong)CreateStyleWithStyleURL((void*)Options, StyleUrl);

    env->ReleaseStringUTFChars(StyleUrlString, StyleUrl);

    return Result;
}

/*
 * Class:     BindingJava
 * Method:    DestroyStyleOptionsInstance
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_BindingJava_DestroyStyleOptionsInstance(JNIEnv* env, jobject thisObj, jlong StyleInstance)
{
    DestroyStyleOptionsInstance((void*)StyleInstance);
}

/*
 * Class:     BindingJava
 * Method:    CreateMapInstance
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_BindingJava_CreateMapInstance(JNIEnv* env, jobject thisObj)
{
    return (jlong)CreateMapInstance();
}

/*
 * Class:     BindingJava
 * Method:    SetMapStyle
 * Signature: (JJ)J
 */
JNIEXPORT jlong JNICALL Java_BindingJava_SetMapStyle(JNIEnv* env, jobject thisObj, jlong MapInstance, jlong StyleOptionInstance)
{
    StyledMap* Map = reinterpret_cast<StyledMap*>(MapInstance);
    StyleOptions* Options = reinterpret_cast<StyleOptions*>(StyleOptionInstance);

    return (jlong)SetMapStyle((void*)MapInstance, (void*)StyleOptionInstance);
}

inline ::jclass JavaErrorClass(JNIEnv& env)
{
    return env.FindClass("java/lang/Error");
}

/*
 * Class:     BindingJava
 * Method:    RenderMap
 * Signature: (JLjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_BindingJava_RenderMap(JNIEnv* env, jobject thisObj, jlong MapInstance, jstring FunctionName)
{
    InternalEnv = env;
    InternalObject = &thisObj;
    CallbackName = std::move(FunctionName);

    try
    {
        RenderMap((void*)MapInstance, RenderFunction);
    }
    catch(const std::exception &ex)
    {
        jclass ErrorClass = JavaErrorClass(*env);
        if(ErrorClass != NULL)
        {
            env->ThrowNew(ErrorClass, ex.what());
        }
    }

    InternalEnv = nullptr;
    InternalObject = nullptr;
    CallbackName = jstring();
}

/*
 * Class:     BindingJava
 * Method:    DestroyMapInstance
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_BindingJava_DestroyMapInstance(JNIEnv* env, jobject thisObj, jlong MapInstance)
{
    DestroyMapInstance((void*)MapInstance);
}

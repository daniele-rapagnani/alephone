//
// Created by Daniele on 2019-08-03.
//

#include "android_assets.h"

#include <android/asset_manager_jni.h>

namespace android_assets {

AAssetManager* asset_manager = nullptr;

JNIEXPORT
void JNICALL Java_com_marathon_alephone_MainActivity_setAssetManager(
    JNIEnv* env,
    jclass c,
    jobject am
)
{
    asset_manager = AAssetManager_fromJava(env, am);
}

} // namespace android_assets

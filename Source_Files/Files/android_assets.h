//
// Created by Daniele on 2019-08-03.
//

#ifndef ALEPHONE_ANDROID_ASSETS_H
#define ALEPHONE_ANDROID_ASSETS_H

#include <jni.h>
#include <android/asset_manager.h>

namespace android_assets {

extern AAssetManager* asset_manager;

extern "C" {

JNIEXPORT
void JNICALL Java_com_marathon_alephone_MainActivity_setAssetManager(JNIEnv *, jclass, jobject);

}

} // android_assets

#endif //ALEPHONE_ANDROID_ASSETS_H

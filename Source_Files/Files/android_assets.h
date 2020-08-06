//
// Created by Daniele on 2019-08-03.
//

#ifndef ALEPHONE_ANDROID_ASSETS_H
#define ALEPHONE_ANDROID_ASSETS_H

#include <jni.h>
#include <android/asset_manager.h>
#include <string>

namespace android_assets {

extern AAssetManager* asset_manager;

extern "C" {

JNIEXPORT
void JNICALL Java_com_marathon_alephone_MainActivity_setAssetManager(JNIEnv *, jclass, jobject);

}

bool install_to_internal_storage(
    const std::string& path,
    const std::string& toPath = ""
);

} // android_assets

#endif //ALEPHONE_ANDROID_ASSETS_H

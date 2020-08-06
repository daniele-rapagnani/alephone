//
// Created by Daniele on 2019-08-03.
//

#include "android_assets.h"
#include "FileHandler.h"

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

bool install_to_internal_storage(
    const std::string& path,
    const std::string& toPath /* = "" */
)
{
    std::string dstPath = toPath.empty() ? path : toPath;

    FileSpecifier srcFs(path);
    FileSpecifier dstFs;
    dstFs.SetToLocalDataDir();
    dstFs += dstPath;

    if (dstFs.Exists())
    {
        return true;
    }

    return dstFs.CopyContents(srcFs);
}

} // namespace android_assets

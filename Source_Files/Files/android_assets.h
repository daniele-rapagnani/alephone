//
// Created by Daniele Rapagnani on 2019-08-03.
//

#ifndef ALEPHONE_ANDROID_ASSETS_H
#define ALEPHONE_ANDROID_ASSETS_H

#ifdef __ANDROID__

#include <jni.h>
#include <android/asset_manager.h>
#include <string>
#include <vector>
#include <cstdint>
#include <unordered_map>

namespace android_assets {

extern AAssetManager* asset_manager;

extern "C" {

JNIEXPORT
void JNICALL Java_com_marathon_alephone_AlephOneActivity_setAssetManager(JNIEnv *, jclass, jobject);

JNIEXPORT
void JNICALL Java_com_marathon_alephone_AlephOneActivity_setScenarioPath(
    JNIEnv* env,
    jclass c,
    jstring path
);

}

bool install_to_internal_storage(
    const std::string& path,
    const std::string& toPath = ""
);

bool get_scenario_datapath(std::string& path);

class BakedFilesystem
{
public:
    struct Node
    {
        std::vector<const Node*> get_children() const;

        const char* path;
        const char* name;
        size_t size;
        size_t pathDepth;
        bool directory;
        const struct Node* childrenStart = nullptr;
        const struct Node* childrenEnd = nullptr;
    };

public:
    static BakedFilesystem& instance();

private:
    BakedFilesystem() = default;
    ~BakedFilesystem();

public:
    bool load(const std::string& bakedListFile);
    const Node* get_file(const std::string& path) const;

private:
    char* bakedList = nullptr;
    size_t bakedListSize = 0;

    std::vector<Node> nodes;
    std::unordered_map<std::string, const Node*> tree;
};

} // android_assets

#endif // __ANDROID__

#endif //ALEPHONE_ANDROID_ASSETS_H

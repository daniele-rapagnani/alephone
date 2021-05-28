//
// Created by Daniele Rapagnani on 2019-08-03.
//

#ifdef __ANDROID__

#include "android_assets.h"
#include "FileHandler.h"

#include <android/asset_manager_jni.h>
#include <cstdlib>
#include <cassert>
#include <stack>

#include <boost/algorithm/string.hpp>

namespace android_assets {

AAssetManager* asset_manager = nullptr;

JNIEXPORT
void JNICALL Java_com_marathon_alephone_AlephOneActivity_setAssetManager(
    JNIEnv* env,
    jclass c,
    jobject am
)
{
    asset_manager = AAssetManager_fromJava(env, am);
}

namespace {

std::string scenarioPath = {};
bool hasScenarioPath = false;

}

JNIEXPORT void JNICALL Java_com_marathon_alephone_AlephOneActivity_setScenarioPath(
    JNIEnv* env,
    jclass c,
    jstring path
)
{
    const char* cpath = env->GetStringUTFChars(path, nullptr);

    if (!cpath)
    {
        return;
    }

    scenarioPath.assign(cpath);
    hasScenarioPath = true;

    env->ReleaseStringUTFChars(path, cpath);
}

bool get_scenario_datapath(std::string& path)
{
    if (!hasScenarioPath)
    {
        return false;
    }

    path = scenarioPath;
    return true;
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


BakedFilesystem& BakedFilesystem::instance()
{
    static BakedFilesystem bfs = {};
    return bfs;
}

BakedFilesystem::~BakedFilesystem()
{
    if (this->bakedList)
    {
        delete[] this->bakedList;
        this->bakedList = nullptr;
    }
}

namespace {

size_t get_path_comps_count(const char* path, const char** last)
{
    size_t count = 0;
    for (; *path != '\0'; path++)
    {
        if (*path == '/')
        {
            *last = path;
            count++;
        }
    }

    return count;
}

struct Parser
{
    Parser(char* data, size_t size)
        : data(data), cur(data), size(size)
    { }

    bool parse_int(size_t& v)
    {
        if (done())
        {
            return false;

        }

        char* end = nullptr;
        v = strtol(this->cur, &end, 0);

        bool read = end > this->cur;
        this->cur = end;

        return read;
    }

    bool parse_string(const char*& v)
    {
        if (done())
        {
            return false;
        }

        v = this->cur;

        if (!read_until_char('\n'))
        {
            return false;
        }

        set('\0');

        return true;
    }

    bool parse_node(BakedFilesystem::Node& node)
    {
        if (!parse_string(node.path))
        {
            return false;
        }

        const char* lastComp = nullptr;
        node.pathDepth = get_path_comps_count(node.path, &lastComp) + 1;
        node.name = lastComp + 1;

         // The null char
        if (!next())
        {
            return false;
        }

        if (done())
        {
            return false;
        }

        char type = pop();

        if (done())
        {
            return false;
        }

        pop();  // The space char
        node.directory = type == 'D';

        if (!parse_int(node.size))
        {
            return false;
        }

        if (!next())
        {
            return false;
        }

        return true;
    }

    bool read_until_char(char c)
    {
        while (!done() && get() != c)
        {
            next();
        }

        return !done();
    }

    bool done() const
    {
        return (this->cur - this->data) >= this->size;
    }

    char get() const
    {
        return *this->cur;
    }

    void set(char c)
    {
        *this->cur = c;
    }

    bool next()
    {
        if (done())
        {
            return false;
        }

        this->cur++;
        return !this->done();
    }

    char pop()
    {
        char c = get();
        next();
        return c;
    }

    size_t size = 0;
    char* cur = nullptr;
    char* data = nullptr;
};

}

std::vector<const BakedFilesystem::Node*> BakedFilesystem::Node::get_children() const
{
    std::vector<const BakedFilesystem::Node*> children;

    if (!this->childrenStart || !this->childrenEnd)
    {
        return children;
    }

    for (const Node* it = this->childrenStart; it <= this->childrenEnd; ++it)
    {
        if (it->pathDepth == this->pathDepth + 1)
        {
            children.push_back(it);
        }
    }

    return children;
}

bool BakedFilesystem::load(const std::string& bakedListFile)
{
    FileSpecifier bakedListFs(bakedListFile);

    if (!bakedListFs.Exists())
    {
        return false;
    }

    OpenedFile bakedListOf;

    if (!bakedListFs.Open(bakedListOf))
    {
        return false;
    }

    int32 size = 0;

    if (!bakedListOf.GetLength(size))
    {
        return false;
    }

    this->bakedListSize = size;
    this->bakedList = new char[size + 1];

    if (!bakedListOf.Read(size, this->bakedList))
    {
        return false;
    }

    Parser p(this->bakedList, size);

    size_t nodesCount = 0;

    if (!p.parse_int(nodesCount))
    {
        return false;
    }

    if (!p.next())
    {
        return false;
    }

    this->nodes.resize(nodesCount + 1);

    std::stack<Node*> dirsStack;
    dirsStack.push(&this->nodes[0]);

    dirsStack.top()->path = ".";
    dirsStack.top()->pathDepth = 1;
    dirsStack.top()->directory = true;
    dirsStack.top()->size = 0;

    this->tree["."] = dirsStack.top();

    for (size_t i = 1; i < nodesCount; i++)
    {
        Node& n = this->nodes[i];

        if (!p.parse_node(n))
        {
            return false;
        }

        this->tree[std::string { n.path }] = &n;

        while (n.pathDepth <= dirsStack.top()->pathDepth)
        {
            dirsStack.pop();
        }

        assert(!dirsStack.empty());

        if (n.pathDepth > dirsStack.top()->pathDepth)
        {
            dirsStack.top()->childrenEnd = &n;
        }

        if (n.directory)
        {
            n.childrenStart = n.childrenEnd = &n;

            dirsStack.push(&n);
            continue;
        }
    }

    assert(!dirsStack.empty());

    if (this->nodes.size() > 1)
    {
        dirsStack.top()->childrenStart =  &(this->nodes[1]);
        dirsStack.top()->childrenEnd = &(this->nodes.back());
    }

    return true;
}

const BakedFilesystem::Node* BakedFilesystem::get_file(const std::string& path) const
{
    std::string realPath = path;

    if (realPath.empty())
    {
        realPath = "/";
    }
    else if (
        (realPath.size() == 1 && realPath[0] != '.' && realPath[0] != '/')
        || (realPath.size() > 1 && (realPath[0] != '/' && realPath.substr(0, 2) != "./"))
    )
    {
        realPath = "./" + realPath;
    }

    if (this->tree.find(realPath) == this->tree.end())
    {
        return nullptr;
    }

    return this->tree.at(realPath);
}

} // namespace android_assets

#endif // __ANDROID__
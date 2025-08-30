
#include "SDK/amx/amx.h"
#include "SDK/plugincommon.h"
#include <string>
#include <unordered_map>
#include <iostream>
class CNatives
{
public:
    struct NativeInfo
    {
        std::string name;
        AMX_NATIVE func;
    };
    std::vector<AMX_NATIVE_INFO> dynamicNatives;
    std::unordered_map<std::string, AMX_NATIVE> nativeMap;

    void AddNative(const char* name, AMX_NATIVE func)
    {
        nativeMap[name] = func;
    }
    void BuildNativeList()
    {
        dynamicNatives.clear();
        dynamicNatives.reserve(nativeMap.size() + 1);

        for (const auto& pair : nativeMap)
        {
            AMX_NATIVE_INFO info;
            info.name = pair.first.c_str();
            info.func = pair.second;
            dynamicNatives.push_back(info);
        }

        AMX_NATIVE_INFO terminator = { 0, 0 };
        dynamicNatives.push_back(terminator);
    }
    AMX_NATIVE_INFO* GetNativeList()
    {
        return dynamicNatives.data();
    }
    static cell AMX_NATIVE_CALL n_GetPluginVersion(AMX* amx, cell* params)
    {
        return 100; // Версия 1.00
    }
};
const auto Natives = std::make_unique<CNatives>();
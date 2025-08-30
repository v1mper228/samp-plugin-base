#include "natives.hpp"
extern void *pAMXFunctions;
void *(*logprintf)(const char *fmt, ...);

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()
{
	return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData)
{
	pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
	logprintf = (void *(*)(const char *fmt, ...))ppData[PLUGIN_DATA_LOGPRINTF];
	
	if (NULL == pAMXFunctions || NULL == logprintf)
		return false;
	Natives->AddNative("GetPluginVersion", CNatives::n_GetPluginVersion);
	Natives->BuildNativeList();
	logprintf("  clear plugin loaded..");
	return true;
}
PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX* amx)
{
	return amx_Register(amx, Natives->GetNativeList(), -1);
}
PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX* amx)
{
	return AMX_ERR_NONE;
}
PLUGIN_EXPORT void PLUGIN_CALL Unload()
{
	logprintf("  clear plugin unloaded..");
}
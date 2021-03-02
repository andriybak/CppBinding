#pragma once

#define DLL_EXPORT __declspec(dllexport)

#ifdef __cplusplus
extern "C" {
#endif

    DLL_EXPORT void* CreateStyleOptionsInstance();
    DLL_EXPORT void* CreateStyleWithStyleURL(void* StylePtr, const char* StyleUrl);
    DLL_EXPORT void DestroyStyleOptionsInstance(void* StyleInstance);

    DLL_EXPORT void* CreateMapInstance();
    DLL_EXPORT void* SetMapStyle(void* MapInstance, void* StyleOptionsInstance);
    DLL_EXPORT void RenderMap(void* MapInstance, void (*FunctionInstance) ()) noexcept(false);
    DLL_EXPORT void DestroyMapInstance(void* MapInstance);

#ifdef __cplusplus
}
#endif

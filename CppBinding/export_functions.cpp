#include "export_functions.h"
#include "map.hpp"

void* CreateStyleOptionsInstance()
{
    return new(std::nothrow) StyleOptions();
}

void* CreateStyleWithStyleURL(void* StylePtr, const char* StyleUrl)
{
    StyleOptions* Options = reinterpret_cast<StyleOptions*>(StylePtr);
    if (Options)
    {
        const std::string UrlString = std::string(StyleUrl);

        return &Options->withStyleURL(UrlString);
    }

    return nullptr;
}

void DestroyStyleOptionsInstance(void* StyleInstance)
{
    StyleOptions* Options = reinterpret_cast<StyleOptions*>(StyleInstance);
    if(Options)
    {
        delete Options;
    }
}

void* CreateMapInstance()
{
    return new(std::nothrow) StyledMap();
}

void* SetMapStyle(void* MapInstance, void* StyleOptionsInstance)
{
    StyledMap* Map = reinterpret_cast<StyledMap*>(MapInstance);
    StyleOptions* Options = reinterpret_cast<StyleOptions*>(StyleOptionsInstance);
    if (Map && Options)
    {
        Map->setStyle(Style::createStyle(*Options));
    }

    return Map;
}

void RenderMap(void* MapInstance, void (*FunctionInstance) ()) noexcept(false)
{
    StyledMap* Map = reinterpret_cast<StyledMap*>(MapInstance);
    if (Map)
    {
        try
        {
            Map->render(*FunctionInstance);
        }
        catch(std::exception ex)
        {
            throw ex;
        }
    }
}

void DestroyMapInstance(void* MapInstance)
{
    StyledMap* Map = reinterpret_cast<StyledMap*>(MapInstance);
    if(Map)
    {
        delete Map;
    }
}

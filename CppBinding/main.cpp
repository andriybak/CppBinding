#include "map.hpp"

void RenderFunction()
{
    printf("map rendered!\n");
}

int main()
{
    StyleOptions styleOptions;
    styleOptions.withStyleURL("https://www.test.com");

    std::unique_ptr<Style> stylePointer = Style::createStyle(std::move(styleOptions));

    StyledMap map;
    map.setStyle(std::move(stylePointer));
    map.render(RenderFunction);

    return 0;
}

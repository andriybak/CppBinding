#include "map.hpp"
#include "export_functions.h"

StyleOptions& StyleOptions::withStyleURL(const std::string& url_)
{
    url = url_;
    return *this;
}

std::unique_ptr<Style> Style::createStyle(std::optional<StyleOptions>&& options_)
{
    return std::make_unique<Style>(Style(std::move(options_)));
}

Style::Style(std::optional<StyleOptions>&& options_): options(std::move(options_)) {}

bool Style::isValid() const
{
    return options &&
        !options->url.empty();
}

void StyledMap::setStyle(std::unique_ptr<Style>&& style_)
{
    style = std::move(style_);
}

void StyledMap::render(MapRenderedCallback&& callback)
{
    if(style && style->isValid())
    {
        callback();
    }
    else
    {
        throw std::runtime_error("no valid style is set");
    }
}

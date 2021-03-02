#pragma once

#include <functional>
#include <memory>
#include <string>
#include <optional>
#include <stdexcept>

class StyleOptions
{
public:
    StyleOptions() = default;
    StyleOptions& withStyleURL(const std::string&);

    std::string url;
};

class Style
{
public:
    static std::unique_ptr<Style> createStyle(std::optional<StyleOptions>&&);
    bool isValid() const;

protected:
    Style(std::optional<StyleOptions>&&);

private:
    std::optional<StyleOptions> options;
};

class MapInterface
{
public:
    using MapRenderedCallback = std::function<void()>;
    virtual void render(MapRenderedCallback&&) = 0;

protected:
    MapInterface() = default;
};

class StyledMap : public MapInterface
{
public:
    StyledMap() = default;
    void setStyle(std::unique_ptr<Style>&&);

    // throws std::runtime_error if no valid style is set.
    void render(MapRenderedCallback&&) final;

private:
    std::unique_ptr<Style> style;
};

#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <array>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

struct SpriteData {
    int x;
    int y;
    int w;
    int h;
};

struct Sprite {
    std::string filename;
    SpriteData data;
};

int main(int argc, char** argv)
{
    if (argc != 3) {
        std::cerr
            << "Usage: generate_sprites <input.json> <output.hpp>\n";
        return 1;
    }

    const std::string input_path = argv[1];
    const std::string output_path = argv[2];

    std::ifstream input(input_path);
    if (!input) {
        std::cerr << "Failed to open: " << input_path << '\n';
        return 1;
    }

    json sheet;

    try {
        input >> sheet;
    }
    catch (const json::exception& e) {
        std::cerr << "Failed to parse JSON: " << e.what() << '\n';
        return 1;
    }

    std::ofstream output(output_path);
    if (!output) {
        std::cerr << "Failed to open: " << output_path << '\n';
        return 1;
    }

    std::vector<Sprite> sprites;

    for (const auto& item : sheet) {
        if (!item.contains("filename") ||
            !item.contains("frame")) {
            continue;
        }

        const auto& frame = item["frame"];

        if (!frame.contains("x") ||
            !frame.contains("y") ||
            !frame.contains("w") ||
            !frame.contains("h")) {
            std::cerr
                << "Invalid sprite entry: "
                << item["filename"] << '\n';
            return 1;
        }

        sprites.push_back({
            item["filename"].get<std::string>(),
            {
                frame["x"].get<int>(),
                frame["y"].get<int>(),
                frame["w"].get<int>(),
                frame["h"].get<int>()
            }
        });
    }

    output << R"(#pragma once


struct GeneratedSpriteData {
    int x;
    int y;
    int w;
    int h;
};

)";

    output << "inline constexpr std::array generated_sprites{\n";

    for (const auto& sprite : sprites) {
        output << "    GeneratedSpriteData{"
               << sprite.data.x << ", "
               << sprite.data.y << ", "
               << sprite.data.w << ", "
               << sprite.data.h << "}, "
               << "// " << sprite.filename << '\n';
    }

    output << "};\n";

    std::cout
        << "Generated "
        << sprites.size()
        << " sprites -> "
        << output_path
        << '\n';

    return 0;
}


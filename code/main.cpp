#include <core/entity.hpp>
#include <core/memory.hpp>
#include <core/memory_control.hpp>
#include <cstdint>
#include <render/texture.hpp>
#include <render/window.hpp>
#include <render/camera.hpp>
#include <render/draw.hpp>

int main()
{
	initWindow() ?: printf("Init failed.");

	loadMedia();		
}

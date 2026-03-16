#include <world/world.hpp>
#include <core/memory.hpp>
#include <render/window.hpp>
#include <render/texture.hpp>
#include <ui/state.hpp>
#include <simulation/world_gen.hpp>
#include <world/tile/database.hpp>

int main() {
	init() ? : printf("Init failed.");

        loadMedia();

	GameOptions go = selectGameOptions();

	//NOTE: right now Ws uses regions while world does chunks, but the same width and height is used for both.
        WorldSpawner *ws = new WorldSpawner(go.width / 2, go.height / 2);
        ws->generateWorld();

	Arena chunkArena = new Arena();
        World *world = new World(&chunkArena, go.width, go.height);
        world->loadChunkData(*ws);

        Arena tileArena = new Arena();
        TileDatabase *tileDB = new TileDatabase(&tileArena, *ws, *world);

        gSpriteSheetTexture.loadFromFile("sprite_sheet.png");

        Arena animalArena = new Arena();
	AnimalDatabase *animalDB = new AnimalDatabase();
	
	drawEntities(tileDB->tiles, Array<Time> &animalAges, Array<Frame> &animalFrames, Array<AnimalStatus> &animalStates, Array<Frame> &unitFrames, Array<Time> &unitAges, Array<ActState> &unitStates, SearchGrid &sg)
}

// GAME OPTIONS STATE

struct GameOptions
{
	int width;
	int height;
};

GameOptions select_game_options()
{
	GameOptions go;
	go.width = 200;
	go.height = 200;
	return go;
}

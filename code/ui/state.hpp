// GAME OPTIONS STATE

struct GameOptions {
        int width;
        int height;
	
};

GameOptions selectGameOptions() {
  GameOptions go;
  go.width = 200;
  go.height = 200;
	return go;
}

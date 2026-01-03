#include <chrono>

using Time = std::chrono::duration<float>;

class GameClock {
private:
    Time currentTime{};
public:
    void advance(Time delta) { currentTime += delta; }
    Time now() const { return currentTime; }

    GameClock() = default;
    GameClock(const GameClock&) = delete;
    GameClock& operator=(const GameClock&) = delete;
};

inline GameClock gameClock;

Time now() {
    return gameClock.now();
}


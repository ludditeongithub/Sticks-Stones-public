#include <random>
#include <array>

    static std::random_device rd;
    static std::mt19937 gen(rd());


inline int rbin() {

    return dist(gen);
}

inline bool rbool() {
    if (rbin() == 0) return false;
    return true;
}

inline bool rchance(double chance) {
    std::bernoulli_distribution dist(chance);
    return dist(gen);
}

inline double rnormal() {
    double u, v, s;
    do {
        u = 2.0 * (double)rand() / RAND_MAX - 1.0;
        v = 2.0 * (double)rand() / RAND_MAX - 1.0;
        s = u*u + v*v;
    } while(s >= 1.0 || s == 0.0);
    return u * sqrt(-2.0 * log(s) / s);
}


template<typename E>
E random_enum()
{
    using U = std::underlying_type_t<E>;
    std::uniform_int_distribution<U> dist(
        static_cast<U>(E::NONE) + 1,
        static_cast<U>(E::MAX) - 1
    );
    return static_cast<E>(dist(gen));
}

int randomBoolCurrent = 0;
int randomPropFracCurrent = 0;

constexpr int RANDOM_BATCH_SIZE = 5000;
std::vector<bool> randomBools(RANDOM_BATCH_SIZE);
std::array<float, RANDOM_BATCH_SIZE> randomPropFracs;

void generateRandomBools() {
  static std::uniform_int_distribution<int> dist(0, 1);
  for (auto i = 0; i < RANDOM_BATCH_SIZE; i++) {
    int r = dist(gen);
    if (r) randomBools[i] = true;
    else randomBools[i] = false;
  }
}

float nextRandomPropFrac() {
  randomPropFracCurrent++;
  if (randomPropFracCurrent > RANDOM_BATCH_SIZE) randomBoolCurrent = 
}

void nextRandomInt();

bool nextRandomBool() {
  
}

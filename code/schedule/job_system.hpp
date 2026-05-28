#include <cstdint>
#include <vector>
#include <queue>
#include <mutex>
#include <thread>
#include <condition_variable>

struct Job {
    void (*func)(uint32_t start, uint32_t end, void* data);
    uint32_t start;
    uint32_t end;
    void* data;
};

class JobSystem {
public:
    std::vector<std::thread> workers;
    std::queue<Job> jobQueue;
    std::mutex queueMutex;
    std::condition_variable cv;
    bool stop = false;

    void workerThread() {
        while (true) {
            Job job;
            {
                std::unique_lock lock(queueMutex);
                cv.wait(lock, [&] { return stop || !jobQueue.empty(); });
                if (stop && jobQueue.empty()) return;
                job = jobQueue.front();
                jobQueue.pop();
            }
            job.func(job.start, job.end, job.data);
        }
    }
};

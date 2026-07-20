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
    std::queue<Job> job_queue;
    std::mutex queue_mutex;
    std::condition_variable cv;
    bool stop = false;

    void worker_thread() {
        while (true) {
            Job job;
            {
                std::unique_lock lock(queue_mutex);
                cv.wait(lock, [&] { return stop || !job_queue.empty(); });
                if (stop && job_queue.empty()) return;
                job = job_queue.front();
                job_queue.pop();
            }
            job.func(job.start, job.end, job.data);
        }
    }
};

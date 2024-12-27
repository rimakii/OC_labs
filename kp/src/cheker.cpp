#include <iostream>
#include <INIReader.h>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <functional>


struct Job {
    int name;                        
    std::string command;             
    std::vector<int> depends_on;     
    std::string mutex_name;
};

std::vector<Job> parseJobs(const std::string& filename) {
    INIReader reader(filename);
    if (reader.ParseError() != 0) {
        std::cerr << "Cannot parse INI file: " << filename << std::endl;
        exit(EXIT_FAILURE);
    }

    std::vector<std::string> sections;
    {
        int idx = 1;
        while (true) {
            std::string sec = "job" + std::to_string(idx++);
            if (!reader.HasSection(sec)) {
                break;
            }
            sections.push_back(sec);
        }
    }

    std::vector<Job> jobs;
    for (const auto& section : sections) {
        Job job;
        try {
            job.name = std::stoi(section.substr(3));
        } catch (const std::invalid_argument& e) {
            std::cerr << "Invalid job name in section: " << section << std::endl;
            exit(EXIT_FAILURE);
        }

        job.command = reader.Get(section, "command", "");
        job.mutex_name = reader.Get(section, "mutex", "");

        std::string depends_on = reader.Get(section, "depends_on", "");
        if (!depends_on.empty()) {
            std::istringstream ss(depends_on);
            int dep;
            while (ss >> dep) {
                job.depends_on.push_back(dep);
            }
        }
        jobs.push_back(job);
    }

    return jobs;
}

bool checkDAG(const std::vector<Job>& jobs) {
    std::map<int, std::vector<int>> adj;
    std::set<int> allJobs;

    for (auto& j : jobs) {
        allJobs.insert(j.name);
        for (int dep : j.depends_on) {
            adj[dep].push_back(j.name);
        }
        if (!adj.count(j.name)) {
            adj[j.name] = {};
        }
    }

    std::map<int, int> inDegree;
    for (auto j : allJobs) {
        inDegree[j] = 0;
    }
    for (auto& pair : adj) {
        for (auto v : pair.second) {
            inDegree[v]++;
        }
    }

    std::queue<int> q;
    for (auto& kv : inDegree) {
        if (kv.second == 0) {
            q.push(kv.first);
        }
    }

    int countVisited = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        countVisited++;

        for (auto v : adj[u]) {
            inDegree[v]--;
            if (inDegree[v] == 0) {
                q.push(v);
            }
        }
    }
    if (countVisited != (int)allJobs.size()) {
        std::cerr << "Cycle detected! DAG check failed." << std::endl;
        return false;
    }


    std::map<int, std::vector<int>> undirected;
    for (auto& pair : adj) {
        int u = pair.first;
        for (auto v : pair.second) {
            undirected[u].push_back(v);
            undirected[v].push_back(u);
        }
        if (!undirected.count(u)) {
            undirected[u] = {};
        }
    }

    std::set<int> visited;
    std::function<void(int)> dfs = [&](int node) {
        visited.insert(node);
        for (auto nxt : undirected[node]) {
            if (!visited.count(nxt)) {
                dfs(nxt);
            }
        }
    };
    int start = *allJobs.begin();
    dfs(start);
    if (visited.size() != allJobs.size()) {
        std::cerr << "Multiple connected components! DAG check failed." << std::endl;
        return false;
    }

    bool hasStart = false, hasEnd = false;
    for (auto& j : jobs) {
        if (j.depends_on.empty()) {
            hasStart = true;
        }
        if (adj[j.name].empty()) {
            hasEnd = true;
        }
        if (hasStart && hasEnd) break;
    }
    if (!hasStart) {
        std::cerr << "No start jobs found!" << std::endl;
        return false;
    }
    if (!hasEnd) {
        std::cerr << "No end jobs found!" << std::endl;
        return false;
    }

    return true;
}

bool executeJob(const Job& job) {
    std::cout << "[START] Job " << job.name << ": " << job.command << std::endl;
    int ret = system(job.command.c_str());
    if (ret != 0) {
        std::cerr << "[ERROR] Job " << job.name << " failed! Return code: " << ret << std::endl;
        return false;
    }
    std::cout << "[FINISH] Job " << job.name << " done." << std::endl;
    return true;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <path_to_ini_file>" << std::endl;
        return EXIT_FAILURE;
    }

    std::string iniFilePath = argv[1];
    std::vector<Job> jobs = parseJobs(iniFilePath);

    if (!checkDAG(jobs)) {
        std::cerr << "DAG check failed. Exiting." << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << "DAG is valid.\n";

    std::map<int, std::vector<int>> adj;
    std::map<int, int> inDegree;
    std::map<int, Job> jobMap;

    for (auto& job : jobs) {
        jobMap[job.name] = job;
        for (auto d : job.depends_on) {
            adj[d].push_back(job.name);
        }
        if (!inDegree.count(job.name)) {
            inDegree[job.name] = 0;
        }
    }
    for (auto& p : adj) {
        for (auto v : p.second) {
            inDegree[v]++;
        }
    }

    std::queue<int> ready;
    for (auto& kv : inDegree) {
        if (kv.second == 0) {
            ready.push(kv.first);
        }
    }

    while (!ready.empty()) {
        int jobName = ready.front();
        ready.pop();

        if (!executeJob(jobMap[jobName])) {
            std::cerr << "Execution stopped due to an error." << std::endl;
            return EXIT_FAILURE;
        }

        for (auto nxt : adj[jobName]) {
            inDegree[nxt]--;
            if (inDegree[nxt] == 0) {
                ready.push(nxt);
            }
        }
    }

    std::cout << "All jobs completed successfully!\n";
    return 0;
}
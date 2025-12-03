#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <csignal>
#include <algorithm>
#include <dirent.h>
#include <fstream>
#include <sstream>

void killById(pid_t pid)
{
    if (kill(pid, SIGKILL) == 0)
    {
        std::cout << "[killer] : process " << pid << " successfully killed!" << std::endl;
    }
    else
    {
        std::cerr << "[killer] : process " << pid << " failed to kill the process!" << std::endl;
    }
}

bool isNumeric(const std::string &str)
{
    return !str.empty() && std::all_of(str.begin(), str.end(), [](unsigned char c)
                                       { return std::isdigit(c); });
}

void killByName(const std::string &name)
{
    DIR *directory = opendir("/proc");

    if (!directory)
    {
        std::cerr << "[killer] : failed to open /proc directry :(" << std::endl;
        return;
    }

    struct dirent *entry;

    while ((entry = readdir(directory)))
    {
        std::string pidString = entry->d_name;

        if (!isNumeric(pidString))
        {
            continue;
        }

        std::string commPath = "/proc/" + pidString + "/comm";

        std::ifstream commFile(commPath);
        if (commFile.is_open())
        {
            std::string currentName;

            if (commFile >> currentName)
            {
                if (name == currentName && !name.empty())
                {
                    std::cout << "[killer] : found the neeed process " << name << " with pid " << pidString << std::endl;
                    pid_t pid = std::stoi(pidString);
                    killById(pid);
                }
            }
        }
    }
    closedir(directory);
}

void killByEnvVar()
{
    const char *envVar = getenv("PROC_TO_KILL");
    if (envVar)
    {
        const std::string envVarStr = envVar;
        std::stringstream ss(envVarStr);
        std::string name;

        while (std::getline(ss, name, ','))
        {
            if (!name.empty())
            {
                killByName(name);
            }
        }
    }
}


int main(int argc, char* argv[]) {
    if (argc >= 3) {
        std::string argType = argv[1];
        std::string argValue = argv[2];

        if (argType == "--id") {
            pid_t pid = std::stoi(argValue);
            killById(pid);
        } else if (argType == "--name") {
            killByName(argValue);
        }
    }

    killByEnvVar();

    return 0;
}
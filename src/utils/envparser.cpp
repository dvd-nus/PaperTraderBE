#include <fstream>
#include <string>
#include <cstdlib>
#include <stdexcept>
#include <iostream>

void loadEnvFile(const std::string& envFilePath) {
    std::ifstream envFile(envFilePath);
    if (!envFile.is_open()) {
        throw std::runtime_error("Failed to open .env file: " + envFilePath);
    }

    std::string line;
    while (std::getline(envFile, line)) {
        // Ignore empty lines and comments
        if (line.empty() || line[0] == '#') continue;

        // Find the position of the '=' character
        size_t delimiterPos = line.find('=');
        if (delimiterPos == std::string::npos) continue;  // Skip malformed lines

        // Extract the key and value
        std::string key = line.substr(0, delimiterPos);
        std::string value = line.substr(delimiterPos + 1);

        // Trim spaces around the key and value (optional)
        key.erase(key.find_last_not_of(" \t") + 1);
        key.erase(0, key.find_first_not_of(" \t"));
        value.erase(value.find_last_not_of(" \t") + 1);
        value.erase(0, value.find_first_not_of(" \t"));

        // Set the environment variable
        _putenv_s(key.c_str(), value.c_str());
    }

    envFile.close();
}

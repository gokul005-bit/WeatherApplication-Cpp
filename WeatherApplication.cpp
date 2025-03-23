﻿#define CURL_STATICLIB
#include <iostream>
#include <algorithm> // for std::replace
#include <curl/curl.h>
#include <windows.h>

// Callback function for handling API response
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

// Function to format city name (Title Case)
std::string toTitleCase(std::string str) {
    if (str.empty()) return str;
    str[0] = toupper(str[0]);
    for (size_t i = 1; i < str.size(); i++) {
        str[i] = tolower(str[i]);
    }
    return str;
}

// Function to fetch weather data
void cleanResponse(std::string& str) {
    // Remove non-ASCII characters
    str.erase(std::remove_if(str.begin(), str.end(), [](unsigned char c) {
        return c > 127;  // Remove characters outside standard ASCII range
        }), str.end());
}

void getWeather(const std::string& city) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl) {
        std::string url = "http://wttr.in/" + city + "?format=%C+%t+%h+%w";  // Added humidity + wind speed
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);  // ✅ Follow redirects

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "cURL Error: " << curl_easy_strerror(res) << std::endl;
        }
        else {
            // ✅ Clean unwanted characters from response
            cleanResponse(readBuffer);
            std::cout << "Weather in " << city << ": " << readBuffer << std::endl;
        }

        curl_easy_cleanup(curl);
    }
}


int main() {
    SetConsoleOutputCP(CP_UTF8);  // ✅ Enable UTF-8 output in Windows console

    std::string city;
    std::cout << "Enter city name: ";
    std::cin >> city;

    getWeather(city);
    return 0;
}
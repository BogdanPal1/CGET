#include <iostream>
#include <cstring>
#include <string>
#include <curl/curl.h>

char* makePath(char* filename)
{
    std::string dir = "your_directory";
    std::string path = dir + filename;

    char *chrpath = new char[path.length() + 1];
    strcpy(chrpath, path.c_str());

    return chrpath;
}

int main(int argc, char *argv[])
{
    CURL *curl;
    FILE *file;
    CURLcode result;

    file = fopen(makePath(argv[2]), "wb");

    curl = curl_easy_init();

    curl_easy_setopt(curl, CURLOPT_URL, argv[1]);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
    curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L);

    result = curl_easy_perform(curl);

    if (result == CURLE_OK)
        std::cout << "Download successful!" << std::endl;
    else 
        std::cout << "ERROR: " << curl_easy_strerror(result) << std::endl;
    
    fclose(file);
    curl_easy_cleanup(curl);
    
    return 0;
}
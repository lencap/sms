// helper.c

#include "smsclic.h"

// Graceful exit
void Die(int code, char *msg)
{
    if (msg[0] != '\0') {
        fprintf(stdout, "%s\n", msg);
    }
    exit(code);
}


// Set up global variables as per values in configuration file
void ProcessConfigFile(void)
{
    char buf[256];
    char cfgfile[256];

    // Read config file
    sprintf(cfgfile, "%s/.%s", getenv("HOME"), "smsclirc");
    ini_t *config = ini_load(cfgfile);
    if (config == '\0') {
        sprintf(buf, "Error. Missing %s file. Run %s -y to create a new one.", cfgfile, prgname);
        Die(1, buf);
    }

    const char *value;  // Temp string value

    value = ini_get(config, "global", "svcurl");
    if (value[0] == '\0') {
        sprintf(buf, "Error. svcurl not defined in %s", cfgfile);
        Die(1, buf);
    }
    strcpy(svcurl, value);

    value = ini_get(config, "global", "svckey");
    if (value[0] == '\0') {
        sprintf(buf, "Error. svckey not defined in %s", cfgfile);
        Die(1, buf);
    }
    strcpy(svckey, value);

    ini_free(config);  // Frees all used memory, including tmp var
}


// Create a skeleton configuration file with default hard-coded values
void CreateSkeletonConfigFile(void)
{
    char buf[256];
    char cfgfile[256];
    FILE * fp;

    sprintf(cfgfile, "%s/.%src", getenv("HOME"), prgname);
    // https://stackoverflow.com/questions/230062/whats-the-best-way-to-check-if-a-file-exists-in-c
    if (access(cfgfile, F_OK) != -1) {
        sprintf(buf, "Error. File %s already exist!", cfgfile);
        Die(1, buf);
    }
    fp = fopen(cfgfile, "w");
    if (fp == NULL) {
        sprintf(buf, "Error creating file %s!\n", cfgfile);
        Die(1, buf);
    }
    fprintf(fp, "# Edit below values accordingly\n");
    fprintf(fp, "[global]\n");
    fprintf(fp, "svcurl = %s\n", svcurl);
    fprintf(fp, "svckey = %s\n", svckey);
    fclose (fp);
}


// Do HTTP POST
void CURLPostData(char * url, char * data)
{
    CURL     *curl;
    CURLcode res;
  
    curl_global_init(CURL_GLOBAL_ALL);    // In windows, this will init the winsock stuff
    curl = curl_easy_init();              // get a curl handle 
    if (curl) {
        //curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl");
        curl_easy_setopt(curl, CURLOPT_URL, url);                 // URL about to receive POST
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);         // Now specify the POST data 
        res = curl_easy_perform(curl);                            // Perform the request
        if (res != CURLE_OK) {
            fprintf(stderr, "%s: %s\n", prgname, curl_easy_strerror(res));
        }
        curl_easy_cleanup(curl);            // Always cleanup
        printf("\n");
    }
    curl_global_cleanup();  
}

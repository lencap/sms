// smsclic.c

#include "smsclic.h"
 
// Global constants and variables initialization
const char prgname[64] = "smsclic";
const char prgver[16]  = "1.1.0";
char cfgfile[64] = "";  
char svcurl[256] = "https://textbelt.com/text";
char svckey[256] = "textbelt";


int main(int argc, char *argv[])
{
  char buf[256];
  char tel[32];
  char msg[4096];
  char data[6000];

  // Print usage if less than 1 or more than 2 arguments
  if (argc < 2 || argc > 3) {
    PrintUsage();
  }

  // If the only one argument is "-y", try creating a skeleton file
  if (argc == 2) {
    if (!strcmp(argv[1], "-y")) {
      CreateSkeletonConfigFile();
      Die(0,"");
    }
    PrintUsage();
  }

  // We'll assume that the 2 arguments are tel and msg
  strcpy(tel, argv[1]);
  strcpy(msg, argv[2]);
  if (strlen(tel) > 10) {
    Die(1, "Error. CellPhoneNum cannot be greater than 10 chars.");
  }
  if (strlen(msg) > 4095) {
    Die(1, "Error. Message cannot be greater than 4096 chars.");
  }
  // Needs more error checking

  ProcessConfigFile();    // Get URL and Key

  // DEBUG
  //printf("URL : [%s]\nKEY : [%s]\nTEL : [%s]\nMSG : [%s]\n", svcurl, svckey, tel, msg);

  // Build data values
  strcpy(data, "key=");     strcat(data, svckey);  strcat(data, "&");
  strcat(data, "phone=");   strcat(data, tel);     strcat(data, "&");
  strcat(data, "message="); strcat(data, msg);
  //printf("DATA: [%s]\n", data);     // DEBUG

  CURLPostData(svcurl, data);

  Die(0, "");
}

// Usage
void PrintUsage(void)
{
  fprintf(stdout, "SMS CLI utility %s\n", prgver);
  fprintf(stdout, "%s <CellPhoneNum> <Message>\n", prgname);
  fprintf(stdout, "%s -y Create skeleton ~/.%src file\n", prgname, prgname);
  fprintf(stdout, "Visit https://textbelt.com for more info.\n");
  Die(0, "");
}

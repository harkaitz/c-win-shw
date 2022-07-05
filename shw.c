// hflycheck:cc: x86_64-w64-mingw32-gcc
#include <windows.h>
#include <string.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <process.h>

#define USE_ANSICON 0
#define DEBUG       0
#define USE_SPAWNVP 1
#define USE_EXECVP  0

static bool FileExists(LPCTSTR szPath);

int main (int _argc, const char *_argv[]) {

    char           shell[MAX_PATH]       = {0};
#   if USE_ANSICON
    char           launcher[MAX_PATH]    = {0};
#   endif
    char           tmpfile [MAX_PATH]    = {0};
    char           tmpdir  [MAX_PATH]    = {0};
    const char    *command[_argc+20];
    size_t         commandsz             = 0;   
    char           directory_b[MAX_PATH] = {0};
    char          *directory;
    int            i;
    bool           is_c;
    FILE          *fp;
    
    strncpy(directory_b, _argv[0], sizeof(directory_b)-1);
    directory = dirname(directory_b);

    if (_argc == 1) {
#       if USE_ANSICON
        sprintf(launcher, "%s\\ansicon.exe", directory);
        if (FileExists(launcher)) {
            command[commandsz++] = launcher;
        }
#       endif
    }
    
    if (FileExists(({sprintf(shell, "%s\\busybox.exe", directory); shell;}))) {
        command[commandsz++] = shell;
        command[commandsz++] = "sh";
        command[commandsz++] = "-l";
    } else {
        shell[0] = '\0';
    }
    
    if (!shell[0]) {
        fprintf(stderr, "No shell found: busybox.exe\n");
        return 1;
    }
    
    for (i=1, is_c = false; i<_argc; i++) {
        if (!strcmp(_argv[i], "-c")) {
            is_c = true;
            continue;
        }
        if (is_c) {
            GetTempPath(MAX_PATH, tmpdir);
            GetTempFileName(tmpdir, TEXT("wsh"), 0, tmpfile);
            fp = fopen(tmpfile, "wb");
            fputs(_argv[i], fp);
            fclose(fp);
            command[commandsz++] = tmpfile;
            is_c = false;
        } else {
            command[commandsz++] = _argv[i];
        }
        
    }
    command[commandsz++] = NULL;
    
    /* Execute the shell. */
#   if DEBUG
    for (i=0; command[i]; i++) {
        fprintf(stderr, "I: %s\n", command[i]);
    }
#   endif
#   if USE_SPAWNVP
    return _spawnvp(_P_WAIT, command[0], command);
#   endif
#   if USE_EXECVP
    return _execvp(command[0], command);
#   endif
}

static bool FileExists(LPCTSTR szPath) {
    DWORD dwAttrib = GetFileAttributes(szPath);
    return (dwAttrib != INVALID_FILE_ATTRIBUTES && 
            !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

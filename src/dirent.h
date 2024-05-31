#ifndef _DIRENT_H
#define _DIRENT_H

#include <sys/types.h>

// Structure for directory entries
struct dirent {
    ino_t   d_ino;              // inode number
    off_t   d_off;              // offset to the next dirent
    unsigned short d_reclen;    // length of this record
    unsigned char  d_type;      // type of file
    char    d_name[256];        // filename
};

// Directory stream type
typedef struct DIR {
    // Implementation-specific data
} DIR;

// Function declarations
extern DIR *opendir(const char *dirname);
extern struct dirent *readdir(DIR *dirp);
extern int closedir(DIR *dirp);
extern void rewinddir(DIR *dirp);

#endif /* _DIRENT_H */
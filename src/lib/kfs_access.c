#include "kfs_access.h"

int kfs_access(const char* path, int mask) {
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    int res = access(fpath, mask);
    if (res == -1) {
        return -errno;
    }

    return 0;
}
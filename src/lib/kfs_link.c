#include "kfs_link.h"

int kfs_link(const char* source_path, const char* target_path) {
    char fs_source_path[PATH_MAX];
    char fs_target_path[PATH_MAX];
    fullpath(fs_source_path, source_path);
    fullpath(fs_target_path, target_path);
    int res = link(fs_source_path, fs_target_path);
    if (res == -1) {
        return -errno;
    }
    res = xglfs_link(source_path, target_path);
    if (res == -1) {
        return -errno;
    }
    return 0;
}
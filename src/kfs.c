#include "kfs.h"

struct fuse_operations kfs_ops = {
                .getattr    = kfs_getattr,
                .access     = kfs_access,
                .open       = kfs_open,
                .read       = kfs_read,
                .write      = kfs_write,
                .truncate   = kfs_truncate,
                .release    = kfs_release,
                .readdir    = kfs_readdir,
                .unlink     = kfs_unlink,
                .rename     = kfs_rename,
                .mkdir      = kfs_mkdir,
                .rmdir      = kfs_rmdir,
                .create     = kfs_create,
                .mknod      = kfs_mknod,
                .chmod      = kfs_chmod,
                .link       = kfs_link,
                .symlink    = kfs_symlink,
                .flush      = kfs_flush,
                .ftruncate  = kfs_ftruncate,
                .readlink   = kfs_readlink
};

int main(int argc, char *argv[]) {
    getcwd(LOCAL_DISC_CACHE_PATH, sizeof(LOCAL_DISC_CACHE_PATH));
    return fuse_main(argc, argv, &kfs_ops, NULL);
}
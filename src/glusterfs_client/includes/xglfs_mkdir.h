#ifndef KFS_XGLFS_MKDIR_H
#define KFS_XGLFS_MKDIR_H

#include <errno.h>
#include <glusterfs/api/glfs.h>

#include "xglfs.h"

#pragma once

int xglfs_mkdir(const char* _path, mode_t _mode);

#endif //KFS_XGLFS_MKDIR_H

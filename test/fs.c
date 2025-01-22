#include <linux/vfs/fs.h>

#include "test.h"
#include <linux/vfs/api.h>

#include <stdio.h>
#include <linux/vfs/dirent.h>

void test_fs_mkdir(void)
{

    vfs_mkdirat_api(&filedesc1, AT_FDCWD, "/d2", 0);
}

void test_fs_mknod(void)
{
    vfs_mknodat_api(&filedesc1, AT_FDCWD, "/n1", S_IFREG, 0);
}

void test_fs_open(void)
{
    vfs_openat_api(&filedesc1, AT_FDCWD, "/n1", O_RDWR, 0);
}

void test_fs_symlink(void)
{
    vfs_symlinkat_api(&filedesc1, "/n1", AT_FDCWD, "/s1");
}

void test_fs_opendir(void)
{
    vfs_openat_api(&filedesc1, AT_FDCWD, "/d2", O_RDWR | O_DIRECTORY, 0);
}

void test_fs_mount(void)
{
    vfs_mount_api(&filedesc1, NULL, "/d2", "cramfs", 0, NULL);
}

void test_fs_opensym(void)
{
    vfs_openat_api(&filedesc1, AT_FDCWD, "/s1", O_RDWR, 0);
}

void test_fs_mount_fat(void)
{
    vfs_mkdirat_api(&filedesc1, AT_FDCWD, "/mnt", 0);
    vfs_mount_api(&filedesc1, "/dev/sda1", "/mnt", "vfat", 0, NULL);
}

void test_fs_creat(void)
{
    vfs_openat_api(&filedesc1, AT_FDCWD, "/cf1", O_RDWR | O_CREAT, 0);
}

void test_fs_readdir(const char *path, struct test_msgshow *ctx)
{
    int fd;
    struct dirent d;
    int ret;

    fd = vfs_openat_api(&filedesc1, AT_FDCWD, path, O_RDWR | O_DIRECTORY, 0);
    if (fd >= 0)
    {
        while (1)
        {
            ret = vfs_getdents_api(&filedesc1, fd, &d, sizeof(d));
            if (ret <= 0)
                break;

            for (int i = 0; i < ret; i++)
            {
                struct dirent *entry = (char*)&d + i;

                if (ctx)
                    ctx->print(ctx, "%s\n", entry->d_name);

                i += (entry->d_reclen - 1);
            }
        }

        vfs_close_api(&filedesc1, fd);
    }
}

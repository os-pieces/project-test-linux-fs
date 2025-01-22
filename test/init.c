#include <linux/vfs/fs.h>
#include <linux/vfs/path.h>
#include "test.h"

extern int shmem_init_fs_context(struct fs_context *fc);

static int rootfs_init_fs_context(struct fs_context *fc)
{
    return shmem_init_fs_context(fc);
}

struct file_system_type rootfs_fs_type = {
	.name		= "rootfs",
	.init_fs_context = rootfs_init_fs_context,
	.kill_sb	= kill_litter_super,
};

extern struct vfsmount *vfs_kern_mount(struct file_system_type *type,
								int flags, const char *name,
								void *data);

filedesc_t filedesc1;

extern int vfs_init(void);


static void fs_init(void)
{
    extern int tmpfs_init(void);

    tmpfs_init();
}

int test_fs_init(void)
{
    struct vfsmount *mt;
    struct path root;

    vfs_init();

    filedesc_init(&filedesc1, false);

    fs_init();

    mt = vfs_kern_mount(&rootfs_fs_type, 0, "rootfs", 0);

    root.mnt = mt;
    root.dentry = mt->mnt_root;

    set_fs_pwd(&filedesc1, &root);
    set_fs_root(&filedesc1, &root);

    return 0;
}

#include <linux/vfs/api.h>
#include <linux/vfs/fcntl.h>
#include <sys/stat.h>
#include <linux/kdev_t.h>

#include <stdio.h>

#include "test.h"

#include <QString>
#include <QStringList>
#include <QMap>

static void msgprint(struct test_msgshow *ctx, const char *msg, ...)
{
    QString *s = (QString *)ctx->priv;
    va_list args;

    va_start(args, msg);
    s->append(QString::vasprintf(msg, args));
    va_end(args);
}

QMap<QString, int> apimap = {
    {"mknod", 4 | 1 << 8},
    {"ls", 1 | 2 << 8},
    {"mkdir", 1 | 3 << 8},
    {"mount", 1 | 4 << 8},
    {"open", 1 | 5 << 8},
    {"write", 2 | 6 << 8},
    {"kfifo", 0 | 7 << 8},
};

static void __cmd_exec(QString cmd, QString &msg)
{
    QStringList args;
    int api;
    struct test_msgshow show;

    show.priv = &msg;
    show.print = msgprint;

    args = cmd.split(" ");

    api = apimap[args.at(0)];
    if ((args.count() - 1) >= (api & 0xff))
    {
        switch (api >> 8)
        {
        case 1:
        {
            int mode = S_IFREG;
            int dev = 0;

            if (args.at(2) == "c")
                mode = S_IFCHR;

            dev = MKDEV(args.at(3).toInt(), args.at(4).toInt());

            vfs_mknodat_api(&filedesc1, AT_FDCWD, args.at(1).toStdString().c_str(), mode, dev);
        }
        break;
        case 2:
        {
            test_fs_readdir(args.at(1).toStdString().c_str(), &show);
        }
        break;
        case 3:
        {
            vfs_mkdirat_api(&filedesc1, AT_FDCWD, args.at(1).toStdString().c_str(), 0);
        }
        break;
        case 4:
        {
            vfs_mount_api(&filedesc1, NULL, "/d1", "devpts", 0, NULL);
        }
        break;
        case 5:
        {
            vfs_openat_api(&filedesc1, AT_FDCWD, args.at(1).toStdString().c_str(), O_RDWR, 0);
        }
        break;
        case 6:
        {
            int fd;

            fd = vfs_openat_api(&filedesc1, AT_FDCWD, args.at(1).toStdString().c_str(), O_RDWR, 0);
            if (fd >= 0)
            {
                vfs_write_api(&filedesc1, fd, args.at(2).toStdString().c_str(), args.at(2).toStdString().length());
            }
        }
        break;
        case 7:
        {
            test_lib_kfifo();
        }
        break;
        }
    }
}

void test_fs_cmd_exec(QString &s, QString &msg)
{
    QStringList args;

    args = s.split(";");
    for (int i = 0; i < args.count(); i++)
    {
        __cmd_exec(args.at(i), msg);
    }
}

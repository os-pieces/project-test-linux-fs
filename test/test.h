#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <linux/filedesc.h>

extern filedesc_t filedesc1;

struct test_msgshow
{
    void *priv;
    void (*print)(struct test_msgshow *ctx, const char *msg, ...);
};

int test_fs_init(void);

void test_fs_readdir(const char *path, struct test_msgshow *ctx);

void test_lib_kfifo(void);

#ifdef __cplusplus
}
#endif

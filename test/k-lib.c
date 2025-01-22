#include "test.h"

#include <linux/kfifo.h>

void test_lib_kfifo(void)
{
    struct __kfifo kfifo;
    char buf[64] = {0};
    char out[12] = {0};
    int ret;

    __kfifo_init(&kfifo, buf, sizeof(buf), 1);

    for (int i = 0; i < 15; i++) 
    {
        ret = __kfifo_in(&kfifo, "123456789", 9);

        ret = __kfifo_out(&kfifo, out, 5);
    }
}

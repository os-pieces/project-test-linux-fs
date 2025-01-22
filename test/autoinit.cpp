#include "test.h"

class autoinit
{
public:
    autoinit();
};

autoinit::autoinit()
{
    test_fs_init();
}

autoinit init;

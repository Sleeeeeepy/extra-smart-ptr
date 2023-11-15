#include <stdio.h>
#include "sptr.h"

int main(int argc, char **argv) {
    smart int *foo = make_shared((int *)malloc(10));
    smart int *bar = make_shared((int *)malloc(20));
    smart int *foo_ref = ref(foo);
    foo[0] = 10;
    bar[0] = 20;
    printf("%d\n", foo[0]);
    printf("%d\n", bar[0]);
    printf("%d\n", foo_ref[0]);
    return 0;
}
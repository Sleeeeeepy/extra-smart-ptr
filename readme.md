# Simple Smart Pointer Implementation in C

## 소개
GCC의 cleanup attribute를 이용한 간단한 스마트 포인터 구현 예제입니다.

## 예제

``` c 
#include <stdio.h>
#include "sptr.h"

void func(int *p) {
    smart int* p_ref = ref(p);
    printf("p in func(): %d\n", *p_ref);
}

int main(int argc, char **argv) {
    smart int *foo = make_shared((int *)malloc(10));
    smart int *bar = make_shared((int *)malloc(20));
    smart int *foo_ref = ref(foo);
    foo[0] = 10;
    bar[0] = 20;
    printf("%d\n", foo[0]);
    printf("%d\n", bar[0]);
    printf("%d\n", foo_ref[0]);
    func(foo_ref);
    return 0;
}
```

## 주의사항
1. 실제로 사용하지 마세요.
2. thread-safe하지 않습니다.
3. 배열에는 적용되지 않습니다.
4. 연결 리스트를 이용해 관리하기 때문에 성능이 좋지 않습니다.
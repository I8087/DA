# DA
Dynamic array library written in C.


## Getting Started
Here's an example to get you going!

```c
#include <stdio.h>
#include "da.h"

int main(int argc, char *argv[]) {
    DA mylist;
    DA_qinit(&mylist);
    for (int i = 0; i < 10; i++) DA_append(&mylist, i);
    DA_print(&mylist);
    DA_deinit(&mylist);
    return 0;
}
```

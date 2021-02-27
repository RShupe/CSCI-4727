#include <iostream>

int main() {
    int* ptr = (int*)malloc(100 * sizeof (int));

    for(int i = 0; i < 99; i ++)
    {
        ptr[i]=1;
    }

    //ptr[100] = 0;
    free(ptr);

    ptr[50] = 5;

    printf("%d\n", ptr[50]);
    return 0;
}

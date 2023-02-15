// inspired by BINKY
//
//  https://www.youtube.com/watch?v=5VnDaHBi8dM
//

int main(void)
{
    int *x;
    int *y;

    x = malloc(sizeof(int));

    *x = 42;
    // garbage value or segmentation fault
    *y = 13; // error because we never allocated memory for Y

    y = x;

    *y = 13;
}
#include <stdio.h>

#include <time.h>

#define LEN_1D 32000
#define LEN_2D 256
#define ITERS 1000


extern int dummy(float a[LEN_1D], float b[LEN_1D], float c[LEN_1D], float d[LEN_1D], float e[LEN_1D], float aa[LEN_2D][LEN_2D], float bb[LEN_2D][LEN_2D], float cc[LEN_2D][LEN_2D], float result);

void  init_1d(float* arr, unsigned int len, float val) {
    for (unsigned int i = 0; i < len; i++)
    arr[i] = val;
}

void  init_2d(float arr[LEN_2D][LEN_2D], float val) {
    for (unsigned int i = 0; i < LEN_2D; i++)
    init_1d(arr[i], LEN_2D, val);
}

void init_arrays(float a[LEN_1D], float b[LEN_1D], float c[LEN_1D], float d[LEN_1D], float e[LEN_1D], float aa[LEN_2D][LEN_2D], float bb[LEN_2D][LEN_2D], float cc[LEN_2D][LEN_2D]) {
    init_1d(a, LEN_1D, 1);
    init_1d(b, LEN_1D, 1);
    init_1d(c, LEN_1D, 1);
    init_2d(aa, 1);
    init_2d(bb, 1);
}

int test_main(float a[LEN_1D], float b[LEN_1D], float c[LEN_1D], float d[LEN_1D], float e[LEN_1D], float aa[LEN_2D][LEN_2D], float bb[LEN_2D][LEN_2D], float cc[LEN_2D][LEN_2D]) {
    for (int i = 0; i < LEN_2D; i++) {
        a[i] += b[i] * c[i];
        for (int j = 1; j < LEN_2D; j++) {
            aa[j][i] = aa[j-1][i] + bb[j][i] * a[i];
        }
        dummy(a, b, c, d, e, aa, bb, cc, 0.);
    }

    // for (int i = 0; i < LEN_2D; i++) {
    //     a[i] += b[i] * c[i];
    // }
    // for (int j = 1; j < LEN_2D; j++) {
    //     for (int i = 0; i < LEN_2D; i++) {
    //         aa[j][i] = aa[j-1][i] + bb[j][i] * a[i];
    //     }
    //     dummy(a, b, c, d, e, aa, bb, cc, 0.);
    // }

    return 0;
}



int main()
{
    float __attribute__((aligned(64))) a1[LEN_1D];
    float __attribute__((aligned(64))) b1[LEN_1D];
    float __attribute__((aligned(64))) c1[LEN_1D];
    float __attribute__((aligned(64))) d1[LEN_1D];
    float __attribute__((aligned(64))) e1[LEN_1D];
    float __attribute__((aligned(64))) aa1[LEN_2D][LEN_2D];
    float __attribute__((aligned(64))) bb1[LEN_2D][LEN_2D];
    float __attribute__((aligned(64))) cc1[LEN_2D][LEN_2D];

    float* __restrict a = (float*)__builtin_assume_aligned(a1, 64);
    float* __restrict b = (float*)__builtin_assume_aligned(b1, 64);
    float* __restrict c = (float*)__builtin_assume_aligned(c1, 64);
    float* __restrict d = (float*)__builtin_assume_aligned(d1, 64);
    float* __restrict e = (float*)__builtin_assume_aligned(e1, 64);

    float (*__restrict bb)[LEN_2D] = (float (*)[LEN_2D])__builtin_assume_aligned(bb1, 64);
    float (*__restrict aa)[LEN_2D] = (float (*)[LEN_2D])__builtin_assume_aligned(aa1, 64);
    float (*__restrict cc)[LEN_2D] = (float (*)[LEN_2D])__builtin_assume_aligned(cc1, 64);


    init_arrays(a,b,c,d,e,aa,bb,cc);

    clock_t begin = clock();
    test_main(a, b, c, d, e, aa, bb, cc);
    clock_t end = clock();


    printf("Time: %f\n", (double)(end - begin));

    return 0;
}

#include <stdio.h>
#include <limits.h>
int main()
{
    unsigned char uc = 0;
    signed char sc = 127;
    unsigned short int usi = 0;
    signed short int ssi = 32767;
    unsigned int ui = 0;
    signed int si = 32767;
    unsigned long int uli = 0;
    signed long int sli = 2147483647;

    printf("            Obliczona:            <limits.h>\tTyp\n");
    printf("%22u%22u \tunsigned char min\n",uc, 0U);
    printf("%22u%22u \tunsigned char max\n",--uc, UCHAR_MAX);

    while (sc > 0)
        ++sc;
    printf("%22d%22d \tsigned char min\n",sc, SCHAR_MIN);
    printf("%22d%22d \tsigned char max\n",--sc, SCHAR_MAX);

    printf("%22u%22u \tunsigned short int min\n",usi, 0U);
    printf("%22u%22u \tunsigned short int max\n",--usi, USHRT_MAX);

    while (ssi > 0)
        ++ssi;
    printf("%22d%22d \tsigned short int min\n",ssi, SHRT_MIN);
    printf("%22d%22d \tsigned short int max\n",--ssi, SHRT_MAX);

    printf("%22u%22u \tunsigned int min\n",ui, 0U);
    printf("%22u%22u \tunsigned int max\n",--ui, UINT_MAX);
    
    while (si > 0)
        ++si;
    printf("%22d%22d \tsigned int min\n",si, INT_MIN);
    printf("%22d%22d \tsigned int max\n",--si, INT_MAX);

    printf("%22lu%22lu \tunsigned long int min\n",uli, 0UL);
    printf("%22lu%22lu \tunsigned long int max\n",--uli, ULONG_MAX);
    
    sli = uli / 2;
    while (sli > 0)
        ++sli;
    printf("%22ld%22ld \tsigned long int min\n",sli, LONG_MIN);
    printf("%22ld%22ld \tsigned long int max\n",--sli, LONG_MAX);

    return 0;
}

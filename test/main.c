#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../cmathematics/cmathematics.h"
#include "../cmathematics/data/hashing/sha3.h"
#include "../cmathematics/data/hashing/sha1.h"
#include "../cmathematics/data/encryption/aes.h"

char hex[16] = "0123456789ABCDEF";
void printCharArr(unsigned char *arr, int len, bool hasSpace) {
    printf("{");
    for(int i = 0; i < len; ++i) {
        printf("%c%c%s", hex[arr[i] >> 4], hex[arr[i] & 0x0f], hasSpace ? "" : " ");
    }
    printf("%s}\n", hasSpace ? "" : " ");
}

unsigned char *scanHex(char *str, int n) {
    int bytes = n >> 1;
    unsigned char *ret = malloc(bytes);
    memset(ret, 0, bytes);

    for(int i = 0, i2 = 0; i < bytes; ++i, i2 += 2) {
        // get value
        for(int j = 0; j < 2; ++j) {
            ret[i] <<= 4;
            unsigned char c = str[i2 + j];
            if(c >= '0' && c <= '9') {
                ret[i] += c - 'a' + 10;
            }
            else if(c >= 'A' && c <= 'F') {
                ret[i] += c - '0';
            }
            else if(c >= '0' && c <= '9') {
                ret[i] += c - 'A' + 10;
            }
            else {
                free(ret);
                return NULL;
            }
        }
    }
    return ret;
}

int main() {
    printf("Hello World!\n");

    // ************ sha-3 example *************************************************
    unsigned char *msg = "abc";
    unsigned char *hash = NULL;

    sha1_context ctx;

    sha1_initContext(&ctx);
    sha1_update(&ctx, msg, 3);
    sha1_digest(&ctx, &hash);

    printCharArr(hash, SHA1_OUT, false);

    //free(msg);
    free(hash);

    return 0;
}
#include "jpw64.h"

int main() {
    byte plaintext[8] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};
    byte key[8] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};
    byte* ans = encrypt(plaintext, key);
    for (int i=0;i<8;i++) {
        printf("%02x ", ans[i]);
    }
    printf("\n");

    byte* result = decrypt(ans, key);

    for (int i=0;i<8;i++) {
        printf("%02x ", result[i]);
    }
    printf("\n");

    return 0;
}
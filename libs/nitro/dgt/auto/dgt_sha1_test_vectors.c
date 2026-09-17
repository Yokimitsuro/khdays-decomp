/* The prebuilt DGT (SHA-1 digest) library's .data, 0x020422cc-0x020423e8: the SHA-1 known-answer test
 * table -- the block transform, the expected digests and the messages of the FIPS 180-1 vectors
 * ("abc", the 56-character string, one million 'a', "01234567" x 8 ten times) -- read by the
 * update / final routines 0200b79c and 0200b8f0.
 */
typedef unsigned char u8;
typedef unsigned int u32;

extern void func_0200bd4c(void);   /* the SHA-1 block transform */
extern u8 data_02042338[24], data_02042350[24], data_02042308[24], data_02042320[24];
extern char data_02042304[4], data_02042368[60], data_020423a4[68];

char data_020422cc[4] = "a";

struct {
    void (*transform)(void);      /* 0x00 */
    const u8 *digestAbc;          /* 0x04: SHA-1("abc") */
    const u8 *digest56;           /* 0x08: SHA-1 of the 56-character message */
    const u8 *digestMillionA;     /* 0x0c: SHA-1 of one million 'a' */
    const u8 *digest0123;         /* 0x10: SHA-1 of "01234567" x 8 repeated ten times */
    const char *msgAbc;           /* 0x14 */
    const char *msg56;            /* 0x18 */
    const char *msgA;             /* 0x1c */
    const char *msg0123;          /* 0x20 */
    u32 repeatAbc;                /* 0x24 */
    u32 repeat56;                 /* 0x28 */
    u32 repeatA;                  /* 0x2c */
    u32 repeat0123;               /* 0x30 */
} data_020422d0 = {
    func_0200bd4c,
    data_02042338, data_02042350, data_02042308, data_02042320,
    data_02042304, data_02042368, data_020422cc, data_020423a4,
    1, 1, 1000000, 10,
};

char data_02042304[4] = "abc";

/* The expected digests (20 bytes each, padded to 24). */
u8 data_02042308[24] = { 0x34, 0xaa, 0x97, 0x3c, 0xd4, 0xc4, 0xda, 0xa4, 0xf6, 0x1e, 0xeb, 0x2b, 0xdb, 0xad, 0x27, 0x31, 0x65, 0x34, 0x01, 0x6f, 0x00, 0x00, 0x00, 0x00 };
u8 data_02042320[24] = { 0xde, 0xa3, 0x56, 0xa2, 0xcd, 0xdd, 0x90, 0xc7, 0xa7, 0xec, 0xed, 0xc5, 0xeb, 0xb5, 0x63, 0x93, 0x4f, 0x46, 0x04, 0x52, 0x00, 0x00, 0x00, 0x00 };
u8 data_02042338[24] = { 0xa9, 0x99, 0x3e, 0x36, 0x47, 0x06, 0x81, 0x6a, 0xba, 0x3e, 0x25, 0x71, 0x78, 0x50, 0xc2, 0x6c, 0x9c, 0xd0, 0xd8, 0x9d, 0x00, 0x00, 0x00, 0x00 };
u8 data_02042350[24] = { 0x84, 0x98, 0x3e, 0x44, 0x1c, 0x3b, 0xd2, 0x6e, 0xba, 0xae, 0x4a, 0xa1, 0xf9, 0x51, 0x29, 0xe5, 0xe5, 0x46, 0x70, 0xf1, 0x00, 0x00, 0x00, 0x00 };

char data_02042368[60] = "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq";
char data_020423a4[68] = "0123456701234567012345670123456701234567012345670123456701234567";

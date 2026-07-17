/* Apply a transform message (x3: ov212/266/267). Only message type 5 carries one.
 * The position arrives as three 24-bit BIG-ENDIAN signed values: each is rebuilt by
 * dropping its bytes into the top 3 of a 4-byte scratch word and arithmetic-shifting
 * right by 8, which sign-extends and discards the untouched low byte. Sub-op 0xb sets
 * the transform (position + the quaternion at msg+4), 0xc clears it. Either way the
 * message continues to the generic handler.
 *
 * Frame layout is load-bearing: the scratch words sit at sp+0 and the decoded vector
 * at sp+0xc, and mwcc gives the FIRST-declared local the HIGHEST address -- so `pos`
 * must be declared before the scratch array. */
typedef struct { int x, y, z; } VecFx32;
typedef struct { int x, y, z, w; } Quaternion;

extern void func_ov267_020d5468(int *ctx, const VecFx32 *v, const Quaternion *q);
extern void func_ov267_020d54cc(int *ctx);
extern int func_ov107_020c7500(int a, int b, int c);

union W { unsigned char b[4]; int w; };

void func_ov267_020d4860(int param_1, unsigned char *msg, int param_3) {
    VecFx32 pos;
    union W t[3];

    if (msg[2] == 5) {
        t[0].b[3] = msg[0x14];
        t[0].b[2] = msg[0x15];
        t[0].b[1] = msg[0x16];
        pos.x = t[0].w >> 8;
        t[1].b[3] = msg[0x17];
        t[1].b[2] = msg[0x18];
        t[1].b[1] = msg[0x19];
        pos.y = t[1].w >> 8;
        t[2].b[3] = msg[0x1a];
        t[2].b[2] = msg[0x1b];
        t[2].b[1] = msg[0x1c];
        pos.z = t[2].w >> 8;
        switch (msg[3]) {
        case 0xb:
            func_ov267_020d5468(*(int **)(param_1 + 0x390), &pos, (const Quaternion *)(msg + 4));
            break;
        case 0xc:
            func_ov267_020d54cc(*(int **)(param_1 + 0x390));
            break;
        }
    }
    func_ov107_020c7500(param_1, (int)msg, param_3);
}

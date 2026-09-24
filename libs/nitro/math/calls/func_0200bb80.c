/* func_0200bb80 -- HMAC-style keyed hash: fold the key into an ipad/opad pair
 * through a caller-supplied hash-op table, then run two passes (inner hash
 * over ipad+message, outer hash over opad+innerDigest) to produce the final
 * digest in `out`.
 *
 * If the key is longer than the hash's block size, it is hashed down first
 * (reset/update/finish) and the digest used as the effective key; otherwise
 * the key itself is used directly, matching the disassembly's fall-through
 * (no reload of key length / pointer) when keyLen <= ops->blockSize.
 */

typedef struct {
    int digestSize;   /* +0x00 */
    int blockSize;    /* +0x04 */
    void *self;       /* +0x08 */
    void *digestBuf;  /* +0x0c */
    void (*reset)(void *self);
    void (*update)(void *self, const void *data, int len);
    void (*finish)(void *self, void *out);
} HashOps;

void func_0200bb80(void *out, const void *msg, int msgLen, const void *key, int keyLen, HashOps *ops) {
    unsigned char keyBuf[0x40];
    unsigned char ipad[0x40];
    unsigned char opad[0x40];
    int i;

    if (out && msg && msgLen && key && keyLen && ops) {
        const unsigned char *kp = key;
        int klen = keyLen;

        if (keyLen > ops->blockSize) {
            ops->reset(ops->self);
            ops->update(ops->self, key, keyLen);
            ops->finish(ops->self, keyBuf);
            kp = keyBuf;
            klen = ops->digestSize;
        }

        for (i = 0; i < klen; i++) {
            ipad[i] = kp[i] ^ 0x36;
        }
        for (; i < ops->blockSize; i++) {
            ipad[i] = 0x36;
        }

        ops->reset(ops->self);
        ops->update(ops->self, ipad, ops->blockSize);
        ops->update(ops->self, msg, msgLen);
        ops->finish(ops->self, ops->digestBuf);

        for (i = 0; i < klen; i++) {
            opad[i] = kp[i] ^ 0x5c;
        }
        for (; i < ops->blockSize; i++) {
            opad[i] = 0x5c;
        }

        ops->reset(ops->self);
        ops->update(ops->self, opad, ops->blockSize);
        ops->update(ops->self, ops->digestBuf, ops->digestSize);
        ops->finish(ops->self, out);
    }
}

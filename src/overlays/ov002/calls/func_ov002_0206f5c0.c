typedef struct {
    unsigned char pad0000[0x10];
    unsigned int nStartMs;
} Ov002TimingConfig;

extern Ov002TimingConfig *data_ov002_0207fa08;
extern int func_ov002_0206f578(void);

unsigned long long func_ov002_0206f5c0(void)
{
    Ov002TimingConfig *ctx = data_ov002_0207fa08;

    if (func_ov002_0206f578() == 0) {
        return 0;
    }

    return ((unsigned long long)ctx->nStartMs * 33514) >> 6;
}

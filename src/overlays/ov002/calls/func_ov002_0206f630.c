typedef struct {
    unsigned char pad0000[0x14];
    unsigned int nEndMs;
} Ov002TimingConfig;

extern Ov002TimingConfig *data_ov002_0207fa08;
extern int func_ov002_0206f578(void);

unsigned long long func_ov002_0206f630(void)
{
    Ov002TimingConfig *ctx = data_ov002_0207fa08;

    if (func_ov002_0206f578() == 0) {
        return 0;
    }

    return ((unsigned long long)ctx->nEndMs * 33514) >> 6;
}

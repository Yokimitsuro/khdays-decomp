extern int FX_Inv(int a, int b);

struct hdr_020afd78 {
    unsigned char kind : 4;
    unsigned char rest : 4;
};

int func_ov022_020afd78(int param_1) {
    int iVar2 = -0x1000;
    if (*(int **)(param_1 + 0x500) == 0) {
        return iVar2;
    }
    {
        unsigned char *pbVar5 = (unsigned char *)**(int **)(param_1 + 0x500);
        switch (((struct hdr_020afd78 *)pbVar5)->kind) {
        case 0:
            return *(int *)(pbVar5 + 0x74);
        case 1:
            iVar2 = FX_Inv(*(int *)(pbVar5 + 0x90), 0x2000);
            return FX_Inv(*(int *)(pbVar5 + 0x94) + iVar2, 0x2000);
        case 2: {
            int iVar4 = 0;
            do {
                iVar2 = iVar2 + ((int *)pbVar5)[iVar4 + 0x31];
                iVar4 = iVar4 + 1;
            } while (iVar4 < 3);
            return FX_Inv(iVar2, 0x6000);
        }
        case 3:
            break;
        }
    }
    return 0x2000;
}

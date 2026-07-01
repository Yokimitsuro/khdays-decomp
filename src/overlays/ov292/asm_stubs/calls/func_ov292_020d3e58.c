extern void VEC_Subtract(void);
extern void VEC_DotProduct(void);
extern void func_01ff8d18(void);
extern void func_01ffa724(void);
extern void func_01fffd70(void);
extern void func_01fffd8c(void);
extern void func_020050b4(void);
extern void func_02020400(void);
extern void func_0202f188(void);
extern void func_0202f384(void);
extern int data_02042258;
extern int data_02042264;

asm void func_ov292_020d3e58(void)
{
    dcd     0xe92d4078
    dcd     0xe24dd024
    dcd     0xe1a04000
    dcd     0xe5941008
    dcd     0xe28d2018
    dcd     0xe284001c
    dcd     0xe5945000
    bl      VEC_Subtract
    dcd     0xe28d0018
    dcd     0xe1a01000
    bl      func_01ff8d18
    dcd     0xe59d0018
    dcd     0xe59d1020
    bl      func_020050b4
    dcd     0xe1a02000
    dcd     0xe59f118c
    dcd     0xe2840048
    bl      func_0202f188
    dcd     0xe5941000
    dcd     0xe59f2180
    dcd     0xe28d000c
    dcd     0xe28110a0
    bl      func_0202f384
    dcd     0xe2850c02
    dcd     0xe1d011f8
    dcd     0xe3a05d1e
    dcd     0xe3510000
    dcd     0x0a000004
    dcd     0xe1d021fa
    dcd     0xe3a00c05
    dcd     0xe1600082
    bl      func_02020400
    dcd     0xe0455000
    dcd     0xe28d0018
    dcd     0xe28d100c
    bl      VEC_DotProduct
    dcd     0xe1a00080
    dcd     0xe3500a01
    dcd     0xc3a00a01
    dcd     0xca000001
    dcd     0xe3500c02
    dcd     0xb3a00c02
    dcd     0xe0c01095
    dcd     0xe2912b02
    dcd     0xe2a01000
    dcd     0xe1a02622
    dcd     0xe5940030
    dcd     0xe1822a01
    dcd     0xe0c01092
    dcd     0xe2911b02
    dcd     0xe1a05621
    dcd     0xe2a00000
    dcd     0xe1855a00
    dcd     0xe3550d0f
    dcd     0xb3a05d0f
    dcd     0xe28d1018
    dcd     0xe1a00005
    dcd     0xe2842010
    bl      func_01ffa724
    dcd     0xe5940030
    dcd     0xe28000c0
    dcd     0xe3500a01
    dcd     0xc3a00a01
    dcd     0xca000001
    dcd     0xe3500000
    dcd     0xb3a00000
    dcd     0xe5840030
    dcd     0xe5940000
    dcd     0xe59003b4
    dcd     0xe3500000
    dcd     0x028dd024
    dcd     0x08bd8078
    dcd     0xe5941008
    dcd     0xe28d2000
    dcd     0xe284001c
    bl      VEC_Subtract
    dcd     0xe28d0000
    dcd     0xe3a02000
    dcd     0xe1a01000
    dcd     0xe58d2004
    bl      func_01ff8d18
    dcd     0xe1500005
    dcd     0xa28dd024
    dcd     0xa8bd8078
    dcd     0xe5941008
    dcd     0xe284001c
    dcd     0xe2842010
    bl      VEC_Subtract
    dcd     0xe5940000
    dcd     0xe5942034
    dcd     0xe59013b4
    dcd     0xe2820001
    bl      func_02020400
    dcd     0xe5841034
    dcd     0xe5940000
    dcd     0xe2800fe5
    bl      func_01fffd70
    dcd     0xe3500000
    dcd     0xe3a06000
    dcd     0x028dd024
    dcd     0x08bd8078
    dcd     0xe284501c
    dcd     0xe8900007
    dcd     0xe8850007
    dcd     0xe5940034
    dcd     0xe1560000
    dcd     0xa28dd024
    dcd     0xa8bd8078
    dcd     0xe5940000
    dcd     0xe2800fe5
    bl      func_01fffd8c
    dcd     0xe3500000
    dcd     0xe2866001
    dcd     0x1afffff3
    dcd     0xe28dd024
    dcd     0xe8bd8078
    dcd     data_02042264
    dcd     data_02042258
}

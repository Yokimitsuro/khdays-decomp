extern void MTX_RotY33_(void);
extern void func_020307f4(void);
extern void MTX_MultVec33(void);
extern void func_01ffa724(void);
extern void VEC_Add(void);
extern void func_0203084c(void);
extern void func_ov064_020b6ed0(void);
extern void func_ov064_020b6e30(void);
extern char data_ov064_020b72ac[];
extern char data_0203d210[];

asm void func_ov064_020b6c84(void)
{
    dcd     0xe92d4070
    dcd     0xe24dd0f0
    dcd     0xe1a06000
    dcd     0xe2860edf
    dcd     0xe2804a02
    dcd     0xe5940110
    dcd     0xe0400001
    dcd     0xe3500000
    dcd     0xc28dd0f0
    dcd     0xe5840110
    dcd     0xc8bd8070
    dcd     0xe594110c
    dcd     0xe59f0164
    dcd     0xe59fe164
    dcd     0xe0000091
    dcd     0xe2700a06
    dcd     0x43a00000
    dcd     0xe2800a06
    dcd     0xe5840110
    dcd     0xe594010c
    dcd     0xe28dc030
    dcd     0xe2800001
    dcd     0xe584010c
    dcd     0xe3a0500c
    dcd     0xe8be000f
    dcd     0xe8ac000f
    dcd     0xe2555001
    dcd     0x1afffffb
    dcd     0xe5940114
    dcd     0xe59f2128
    dcd     0xe3500000
    dcd     0xe5960020
    dcd     0xe3a05010
    dcd     0xe1d018b0
    dcd     0x02455006
    dcd     0xe28d0000
    dcd     0xe2411902
    dcd     0xe1a01801
    dcd     0xe1a01821
    dcd     0xe1a01241
    dcd     0xe1a03081
    dcd     0xe2831001
    dcd     0xe1a03083
    dcd     0xe1a01081
    dcd     0xe19230f3
    dcd     0xe19220f1
    dcd     0xe2631000
    dcd     0xe2622000
    bl      MTX_RotY33_
    dcd     0xe1a00005
    bl      func_020307f4
    dcd     0xe28d2030
    dcd     0xe3a0100c
    dcd     0xe0202091
    dcd     0xe28d1000
    dcd     0xe28d2024
    bl      MTX_MultVec33
    dcd     0xe28d1024
    dcd     0xe3a00a05
    dcd     0xe1a02001
    bl      func_01ffa724
    dcd     0xe286008c
    dcd     0xe28d1024
    dcd     0xe2800b01
    dcd     0xe1a02001
    bl      VEC_Add
    bl      func_0203084c
    dcd     0xe240cb02
    dcd     0xe59f0090
    dcd     0xe1a01fcc
    dcd     0xe082309c
    dcd     0xe0222091
    dcd     0xe2931b02
    dcd     0xe59d5024
    dcd     0xe2a20000
    dcd     0xe1a01621
    dcd     0xe1811a00
    dcd     0xe0850001
    dcd     0xe58d0024
    dcd     0xe5960490
    dcd     0xe58d0028
    bl      func_0203084c
    dcd     0xe240eb02
    dcd     0xe59f1054
    dcd     0xe1a02fce
    dcd     0xe083519e
    dcd     0xe0233192
    dcd     0xe2952b02
    dcd     0xe59dc02c
    dcd     0xe2a31000
    dcd     0xe1a02622
    dcd     0xe1822a01
    dcd     0xe08c1002
    dcd     0xe28d0024
    dcd     0xe58d102c
    dcd     0xe1a01000
    bl      func_ov064_020b6ed0
    dcd     0xe1a00006
    dcd     0xe1a01004
    dcd     0xe28d2024
    bl      func_ov064_020b6e30
    dcd     0xe28dd0f0
    dcd     0xe8bd8070
    dcd     0x000004cd
    dcd     data_ov064_020b72ac
    dcd     data_0203d210
    dcd     0x0000019a
}

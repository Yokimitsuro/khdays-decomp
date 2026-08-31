typedef unsigned char u8;
typedef struct Ov005Context {void *resultArchive,*localizedResultArchive;char pad8[0x4bdc];void *rowBuffers[3];char pad4bf0[0x22];char inputHeader[26];char pad4c2c[0x5d550];char menuText[12];} Ov005Context;
extern Ov005Context *data_ov005_0205b80c;
extern unsigned short data_ov005_0205b334[];
extern char data_ov005_0205b520[],data_ov005_0205b534[],data_ov005_0205b544[];
extern void *NNS_FndAllocFromDefaultExpHeapEx(unsigned int,int);
extern void MIi_CpuClear16(unsigned short,void *,unsigned int);
extern void func_ov005_02052a7c(void);
extern void func_ov005_0204e4c0(void *,const char *);
extern void *func_02024ee8(const char *,int);
extern void func_0201e374(int);
extern int func_02036298(void *,short *);
void func_ov005_02052ba8(void) {
    short limits[2];
    u8 i;
    limits[1]=data_ov005_0205b334[2];
    limits[0]=data_ov005_0205b334[1];
    for(i=0;i<3;i++) {
        data_ov005_0205b80c->rowBuffers[i]=NNS_FndAllocFromDefaultExpHeapEx(0x600,32);
        MIi_CpuClear16(0,data_ov005_0205b80c->rowBuffers[i],0x600);
    }
    func_ov005_02052a7c();
    func_ov005_0204e4c0(data_ov005_0205b80c->menuText,data_ov005_0205b520);
    data_ov005_0205b80c->resultArchive=func_02024ee8(data_ov005_0205b534,14);
    data_ov005_0205b80c->localizedResultArchive=func_02024ee8(data_ov005_0205b544,14);
    func_0201e374(-16);
    func_02036298(data_ov005_0205b80c->inputHeader,limits);
}

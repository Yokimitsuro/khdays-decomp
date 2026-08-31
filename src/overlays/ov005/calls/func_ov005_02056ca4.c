typedef unsigned short u16;
typedef unsigned int u32;
typedef void *(*Ov005ResultState)(void);
typedef struct Ov005Config {u16 sceneId;char unknown02[8];u16 resultLabelIndex,rewardMode;} Ov005Config;
typedef struct Ov005ResultContext {char unknown00[0x4c4c];int gaugeMaximum,gaugeValue;char unknown4c54[16];} Ov005ResultContext;
typedef struct Ov005ResultGaugeRequest {int firstTileId;short column;u16 row;int maximum,value,widthPixels;} Ov005ResultGaugeRequest;
extern Ov005Config data_ov005_0205b85c;
extern Ov005ResultContext *data_ov005_0205b810;
extern Ov005ResultContext *NNSi_FndGetCurrentRootHeap(void);
extern void MI_CpuFill8(void *,unsigned char,u32);
extern void func_ov005_020564a4(void),func_ov005_020560e8(void),func_ov005_0205660c(void),func_ov005_02056690(void),func_ov005_02056b54(void);
extern void func_ov005_02056314(u32),func_ov005_020555e4(Ov005ResultGaugeRequest *),func_ov005_020563b0(void);
extern void *func_ov005_02056f1c(void);
Ov005ResultState func_ov005_02056ca4(void) {
    Ov005Config *config=&data_ov005_0205b85c;
    Ov005ResultGaugeRequest gauge;
    data_ov005_0205b810=NNSi_FndGetCurrentRootHeap();
    MI_CpuFill8(data_ov005_0205b810,0,sizeof(Ov005ResultContext));
    func_ov005_020564a4();
    func_ov005_020560e8();
    func_ov005_0205660c();
    func_ov005_02056690();
    func_ov005_02056b54();
    func_ov005_02056314(0x3e9);
    switch(config->sceneId) {
    case 0x547:func_ov005_02056314(0x40f);break;
    case 0x548:func_ov005_02056314(0x410);break;
    case 0x514:case 0x515:func_ov005_02056314(0x412);break;
    case 0x54a:
    default:func_ov005_02056314(config->resultLabelIndex+0x403);break;
    }
    if(config->rewardMode!=255 && config->rewardMode!=2)func_ov005_02056314(0x3ea);
    gauge.firstTileId=0x3fb;
    gauge.column=3;
    gauge.row=21;
    if(data_ov005_0205b810->gaugeMaximum==0) gauge.maximum=gauge.value=100;
    else {
        gauge.maximum=data_ov005_0205b810->gaugeMaximum;
        gauge.value=data_ov005_0205b810->gaugeValue;
    }
    gauge.widthPixels=144;
    func_ov005_020555e4(&gauge);
    func_ov005_020563b0();
    return func_ov005_02056f1c;
}

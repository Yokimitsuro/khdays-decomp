/* Ov002_ScriptOpenChoicePanel: decode script text and submit a choice request. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct ScriptVmOperand {u16 nType,pad2;u32 nValue;} ScriptVmOperand;
typedef struct Ov002PanelChoiceFields {u16 *pTitle,*apChoices[3];int nFlags,nSelection,nMode;} Ov002PanelChoiceFields;
typedef union Ov002PanelRequestPayload {int aWords[7];Ov002PanelChoiceFields choice;} Ov002PanelRequestPayload;
typedef struct Ov002PanelRequest {Ov002PanelRequestPayload payload;int nRequestType,nReserved;} Ov002PanelRequest;
extern char *func_02021948(void *,ScriptVmOperand *);
extern int func_02021980(void *,ScriptVmOperand *);
extern int func_ov002_0206b78c(void);
extern u8 data_0204c240;
extern void func_0202fcb8(char *,u16 *);
extern void func_ov002_0206d3ec(int,int);
extern void func_ov002_0205f594(void);
extern int func_ov002_02057300(Ov002PanelRequest *,int);
extern void func_ov002_02075460(void);
extern void func_020235e8(int,int,int);
int func_ov002_02075730(void *pVm,ScriptVmOperand *pOperands)
{
    u16 aTitleText[256],aChoiceText0[256],aChoiceText1[256],aChoiceText2[256];
    Ov002PanelRequest request;
    int aSeatFlags[3];
    char *apChoiceText[3];
    int i;
    char *pTitle;
    int nMode,nChoices;
    ScriptVmOperand *pCurrent;
    pTitle=func_02021948(pVm,pOperands);
    nMode=func_02021980(pVm,pOperands+1);
    pCurrent=pOperands+2;
    pOperands+=3;
    nChoices=func_02021980(pVm,pCurrent);
    if(func_ov002_0206b78c()==1 && (data_0204c240&4))return 1;
    for(i=0;i<nChoices;i++){
        apChoiceText[i]=func_02021948(pVm,pOperands);
        pCurrent=pOperands+1;
        pOperands+=2;
        aSeatFlags[i]=func_02021980(pVm,pCurrent);
    }
    func_0202fcb8(pTitle,aTitleText);
    request.payload.choice.pTitle=aTitleText;
    request.payload.choice.apChoices[0]=request.payload.choice.apChoices[1]=request.payload.choice.apChoices[2]=0;
    request.payload.choice.nFlags=0;
    request.payload.choice.nSelection=-1;
    request.payload.choice.nMode=nMode;
    if(nChoices>0){func_0202fcb8(apChoiceText[0],aChoiceText0);request.payload.choice.apChoices[0]=aChoiceText0;}
    if(nChoices>1){func_0202fcb8(apChoiceText[1],aChoiceText1);request.payload.choice.apChoices[1]=aChoiceText1;}
    if(nChoices>2){func_0202fcb8(apChoiceText[2],aChoiceText2);request.payload.choice.apChoices[2]=aChoiceText2;}
    func_ov002_0206d3ec(0,aSeatFlags[0]);
    func_ov002_0206d3ec(1,aSeatFlags[1]);
    func_ov002_0206d3ec(2,aSeatFlags[2]);
    func_ov002_0205f594();
    func_ov002_02057300(&request,0);
    func_ov002_02075460();
    func_020235e8(0x20ef,1,1);
    return 0;
}

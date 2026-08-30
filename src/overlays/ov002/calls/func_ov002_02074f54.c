/* Ov002_ScriptBuildBindingPayload: expand tagged script operands into binding words. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct ScriptVmOperand {u16 nType,pad2;u32 nValue;} ScriptVmOperand;
extern int func_02021980(void *,ScriptVmOperand *);
extern int func_02021994(void *,ScriptVmOperand *);
extern u32 func_ov002_0207679c(u8,u16);
extern void func_ov002_02073f50(int,int,u32 *,int);
extern int func_ov002_02074414(int,void *);
extern int func_ov002_02074440(int);
int func_ov002_02074f54(void *pVm,ScriptVmOperand *pOperands)
{
    u32 aPayloadWords[128];
    int nComponent,nId,nArg,nOperandCount,nWords,nOperand; ScriptVmOperand *pValues;
    nId=func_02021980(pVm,pOperands);
    nArg=func_02021980(pVm,pOperands+1);
    nOperandCount=func_02021980(pVm,pOperands+2);
    nWords=0;
    nOperand=0;
    pValues=pOperands+3;
    while(nOperand<nOperandCount){
        switch(func_02021980(pVm,pValues+nOperand++)){
        case 0:
            for(nComponent=0;nComponent<3;nComponent++){aPayloadWords[nWords]=func_02021994(pVm,pValues+nOperand++);nWords++;}
            break;
        case 1:{
            int nTable=func_02021980(pVm,pValues+nOperand++);
            int nIndex=func_02021980(pVm,pValues+nOperand++);
            if(nTable==-1 && nIndex==-1)aPayloadWords[nWords]=0;
            else aPayloadWords[nWords]=func_ov002_0207679c((u8)nTable,(u16)nIndex);
            nWords++;
            break;
        }
        case 2:aPayloadWords[nWords]=func_02021980(pVm,pValues+nOperand++);nWords++;break;
        case 3:aPayloadWords[nWords]=func_02021994(pVm,pValues+nOperand++);nWords++;break;
        case 4:((int (**)(int,void *))aPayloadWords)[nWords]=func_ov002_02074414;nWords++;break;
        case 5:((int (**)(int))aPayloadWords)[nWords]=func_ov002_02074440;nWords++;break;
        }
    }
    for(nOperand=0;nOperand<nWords;nOperand++){}
    func_ov002_02073f50(nId,nArg,aPayloadWords,nOperand*4);
    return 1;
}

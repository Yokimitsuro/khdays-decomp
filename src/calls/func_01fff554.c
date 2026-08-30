/* Downward ray intersection with the upper spherical object cap.
 * The hardware divider is drained on every path after the asynchronous start. */
typedef signed int s32;
typedef unsigned int u32;
typedef signed long long s64;
typedef unsigned long long u64;
typedef unsigned short u16;
typedef unsigned char u8;
typedef struct VecFx32 { s32 x,y,z; } VecFx32;
typedef struct CollisionObject { u8 pad00[0x2c]; VecFx32 position2c; s32 radius38,height3c; } CollisionObject;
typedef struct CollCastState {
 u8 pad00[0x10]; VecFx32 vRayStart,vDir;
 u8 pad28[0x44-0x28]; VecFx32 vUnitDir; s32 nDirLength;
 VecFx32 vRayEnd;
 u8 pad60[0x74-0x60]; s32 nRadius,nNearestHit;
} CollCastState;
extern void VEC_Subtract(const VecFx32*,const VecFx32*,VecFx32*);
extern s32 VEC_DotProduct(const VecFx32*,const VecFx32*);
extern s32 FX_Sqrt(s32);
extern s64 func_01ff8ab0(void);
#define MUL(a,b) ((s32)(((s64)(a)*(b)+0x800)>>12))
static inline void WaitDivider(void) { while(*(volatile u16*)0x04000280&0x8000) {} }
static inline void StartDivide(s32 numerator,s32 denominator) {
 *(u64*)0x04000290=(u64)(u32)numerator<<32;
 *(u64*)0x04000298=(u32)denominator;
}
s32 func_01fff554(CollisionObject *object,CollCastState *query)
{
 VecFx32 relativeStart;
 s32 startY,endY,top,dot,radius,discriminant,distance,length,fraction;
 startY=query->vRayStart.y;
 endY=query->vRayEnd.y;
 top=object->position2c.y+object->height3c;
 if(startY<=endY) return -4096;
 if(startY-top < -128 || endY-(top+object->radius38)>128) return -4096;
 VEC_Subtract(&query->vRayStart,&object->position2c,&relativeStart);
 relativeStart.y-=object->height3c;
 dot=VEC_DotProduct(&query->vUnitDir,&relativeStart);
 radius=object->radius38;
 discriminant=MUL(radius,radius)+(MUL(dot,dot)-VEC_DotProduct(&relativeStart,&relativeStart));
 if(discriminant<0) return -4096;
 if(dot>=0) distance=FX_Sqrt(discriminant)-dot;
 else distance=-FX_Sqrt(discriminant)-dot;
 length=query->nDirLength;
 StartDivide(distance,length);
 if(distance>=(s32)(((s64)query->nNearestHit*length)>>27)) { WaitDivider(); return -4096; }
 if(distance<0) {
  relativeStart.y=query->vRayStart.y;
  fraction=0;
  WaitDivider();
 } else if(distance>=query->nDirLength) {
  relativeStart.y=query->vRayEnd.y;
  fraction=1<<27;
  WaitDivider();
 } else {
  relativeStart.y=query->vRayStart.y+MUL(distance,query->vUnitDir.y);
  fraction=(s32)(func_01ff8ab0()>>5);
 }
 if(relativeStart.y<=object->position2c.y+object->height3c) return -4096;
 query->nNearestHit=fraction;
 return fraction;
}

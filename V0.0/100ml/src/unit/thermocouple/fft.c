/*********************************************************************
                         快速福利叶变换C函数
函数简介：此函数是通用的快速傅里叶变换C语言函数，移植性强，以下部分不依
          赖硬件。此函数采用联合体的形式表示一个复数，输入为自然顺序的复
          数（输入实数是可令复数虚部为0），输出为经过FFT变换的自然顺序的
          复数
使用说明：使用此函数只需更改宏定义FFT_N的值即可实现点数的改变，FFT_N的
          应该为2的N次方，不满足此条件时应在后面补0
函数调用：FFT(s);
时    间：2010-2-20
版    本：Ver1.0
参考文献：    
      
**********************************************************************/
#include<math.h>

#define PI 3.1415926535897932384626433832795028841971               //定义圆周率值
#define FFT_N 64                                                   //定义福利叶变换的点数

struct compx {float real,imag;};                                    //定义一个复数结构
struct compx s[FFT_N];                                              //FFT输入和输出：从S[1]开始存放，根据大小自己定义


/*******************************************************************
函数原型：struct compx EE(struct compx b1,struct compx b2)  
函数功能：对两个复数进行乘法运算
输入参数：两个以联合体定义的复数a,b
输出参数：a和b的乘积，以联合体的形式输出
*******************************************************************/
struct compx EE(struct compx a,struct compx b)      
{
 struct compx c;
 c.real=a.real*b.real-a.imag*b.imag;
 c.imag=a.real*b.imag+a.imag*b.real;
 return(c);
}

/*****************************************************************
函数原型：void FFT(struct compx *xin,int N)
函数功能：对输入的复数组进行快速傅里叶变换（FFT）
输入参数：*xin复数结构体组的首地址指针，struct型
*****************************************************************/
void FFT(struct compx *xin)
{
  int f,m,nv2,nm1,i,k,l,j=1;
  struct compx u,w,t;
   
   nv2=FFT_N/2;                  //变址运算，即把自然顺序变成倒位序，采用雷德算法
   nm1=FFT_N-1;  
   for(i=0;i<nm1;i++)        
   {
    if(i<j)                    //如果i<j,即进行变址
     {
      t=xin[j];           
      xin[j]=xin[i];
      xin[i]=t;
     }
    k=nv2;                    //求j的下一个倒位序
    while(k<=j && k > 0)               //如果k<=j,表示j的最高位为1
     {           
      j=j-k;                 //把最高位变成0
      k=k/2;                 //k/2，比较次高位，依次类推，逐个比较，直到某个位为0
     }
   j=j+k;                   //把0改为1
  }
                         
  {
   int le,lei,ip;                            //FFT运算核，使用蝶形运算完成FFT运算
    f=FFT_N;
   for(l=1;(f=f/2)!=1;l++)                  //计算l的值，即计算蝶形级数
           ;
  for(m=1;m<=l;m++)                         // 控制蝶形结级数
   {                                        //m表示第m级蝶形，l为蝶形级总数l=log（2）N
    le=2<<(m-1);                            //le蝶形结距离，即第m级蝶形的蝶形结相距le点
    lei=le/2;                               //同一蝶形结中参加运算的两点的距离
    u.real=1.0;                             //u为蝶形结运算系数，初始值为1
    u.imag=0.0;
    w.real=cos(PI/lei);                     //w为系数商，即当前系数与前一个系数的商
    w.imag=-sin(PI/lei);
    for(j=0;j<=lei-1;j++)                   //控制计算不同种蝶形结，即计算系数不同的蝶形结
     {
      for(i=j;i<=FFT_N-1;i=i+le)            //控制同一蝶形结运算，即计算系数相同蝶形结
       {
        ip=i+lei;                           //i，ip分别表示参加蝶形运算的两个节点
        t=EE(xin[ip],u);                    //蝶形运算，详见公式
        xin[ip].real=xin[i].real-t.real;
        xin[ip].imag=xin[i].imag-t.imag;
        xin[i].real=xin[i].real+t.real;
        xin[i].imag=xin[i].imag+t.imag;
       }
      u=EE(u,w);                           //改变系数，进行下一个蝶形运算
     }
   }
  }
  
}



short int getFFT(short int *a)
{
	int i;
	for(i = 0; i < FFT_N; ++i) {
		s[i].real = (float)a[i];
		s[i].imag = 0;
	}
	FFT(s);
	return s[0].real/FFT_N;
}

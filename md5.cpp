﻿#include <QApplication>
#include<QDebug>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "md5.h"
typedef   unsigned   char   *POINTER;
typedef   unsigned   short   int   UINT2;
typedef   unsigned   long   int   UINT4;

typedef   struct
{
  UINT4   state[4];
  UINT4   count[2];
  unsigned   char   buffer[64];
}   MD5_CTX;

void   MD5Init(MD5_CTX   *);
void   MD5Update(MD5_CTX   *,   unsigned   char   *,   unsigned   int);
void   MD5Final(unsigned   char   [16],   MD5_CTX   *);
bool getRandStr(char * randStr);
#define   S11   7
#define   S12   12
#define   S13   17
#define   S14   22
#define   S21   5
#define   S22   9
#define   S23   14
#define   S24   20
#define   S31   4
#define   S32   11
#define   S33   16
#define   S34   23
#define   S41   6
#define   S42   10
#define   S43   15
#define   S44   21

static   unsigned   char   PADDING[64]   =   {
  0x80,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0
};

#define   F(x,   y,   z)   (((x)   &   (y))   |   ((~x)   &   (z)))
#define   G(x,   y,   z)   (((x)   &   (z))   |   ((y)   &   (~z)))
#define   H(x,   y,   z)   ((x)   ^   (y)   ^   (z))
#define   I(x,   y,   z)   ((y)   ^   ((x)   |   (~z)))

#define   ROTATE_LEFT(x,   n)   (((x)   <<   (n))   |   ((x)   >>   (32-(n))))

#define   FF(a,   b,   c,   d,   x,   s,   ac)   {     (a)   +=   F   ((b),   (c),   (d))   +   (x)   +   (UINT4)(ac);     (a)   =   ROTATE_LEFT   ((a),   (s));     (a)   +=   (b);       }
#define   GG(a,   b,   c,   d,   x,   s,   ac)   {     (a)   +=   G   ((b),   (c),   (d))   +   (x)   +   (UINT4)(ac);     (a)   =   ROTATE_LEFT   ((a),   (s));     (a)   +=   (b);       }
#define   HH(a,   b,   c,   d,   x,   s,   ac)   {     (a)   +=   H   ((b),   (c),   (d))   +   (x)   +   (UINT4)(ac);     (a)   =   ROTATE_LEFT   ((a),   (s));     (a)   +=   (b);       }
#define   II(a,   b,   c,   d,   x,   s,   ac)   {     (a)   +=   I   ((b),   (c),   (d))   +   (x)   +   (UINT4)(ac);     (a)   =   ROTATE_LEFT   ((a),   (s));     (a)   +=   (b);   }


inline   void   Encode(unsigned   char   *output,   UINT4   *input,   unsigned   int   len)
{
  unsigned   int   i,   j;

  for   (i   =   0,   j   =   0;   j   <   len;   i++,   j   +=   4)   {
    output[j]   =   (unsigned   char)(input[i]   &   0xff);
    output[j+1]   =   (unsigned   char)((input[i]   >>   8)   &   0xff);
    output[j+2]   =   (unsigned   char)((input[i]   >>   16)   &   0xff);
    output[j+3]   =   (unsigned   char)((input[i]   >>   24)   &   0xff);
  }
}

inline   void   Decode(UINT4   *output,   unsigned   char   *input,   unsigned   int   len)
{
  unsigned   int   i,   j;

  for   (i   =   0,   j   =   0;   j   <   len;   i++,   j   +=   4)
    output[i]   =   ((UINT4)input[j])   |   (((UINT4)input[j+1])   <<   8)   |
  (((UINT4)input[j+2])   <<   16)   |   (((UINT4)input[j+3])   <<   24);
}

inline   void   MD5Transform   (UINT4   state[4],   unsigned   char   block[64])
{
  UINT4   a   =   state[0],   b   =   state[1],   c   =   state[2],   d   =   state[3],   x[16];
  Decode   (x,   block,   64);
  FF   (a,   b,   c,   d,   x[   0],   S11,   0xd76aa478);
  FF   (d,   a,   b,   c,   x[   1],   S12,   0xe8c7b756);
  FF   (c,   d,   a,   b,   x[   2],   S13,   0x242070db);
  FF   (b,   c,   d,   a,   x[   3],   S14,   0xc1bdceee);
  FF   (a,   b,   c,   d,   x[   4],   S11,   0xf57c0faf);
  FF   (d,   a,   b,   c,   x[   5],   S12,   0x4787c62a);
  FF   (c,   d,   a,   b,   x[   6],   S13,   0xa8304613);
  FF   (b,   c,   d,   a,   x[   7],   S14,   0xfd469501);
  FF   (a,   b,   c,   d,   x[   8],   S11,   0x698098d8);
  FF   (d,   a,   b,   c,   x[   9],   S12,   0x8b44f7af);
  FF   (c,   d,   a,   b,   x[10],   S13,   0xffff5bb1);
  FF   (b,   c,   d,   a,   x[11],   S14,   0x895cd7be);
  FF   (a,   b,   c,   d,   x[12],   S11,   0x6b901122);
  FF   (d,   a,   b,   c,   x[13],   S12,   0xfd987193);
  FF   (c,   d,   a,   b,   x[14],   S13,   0xa679438e);
  FF   (b,   c,   d,   a,   x[15],   S14,   0x49b40821);
  GG   (a,   b,   c,   d,   x[   1],   S21,   0xf61e2562);
  GG   (d,   a,   b,   c,   x[   6],   S22,   0xc040b340);
  GG   (c,   d,   a,   b,   x[11],   S23,   0x265e5a51);
  GG   (b,   c,   d,   a,   x[   0],   S24,   0xe9b6c7aa);
  GG   (a,   b,   c,   d,   x[   5],   S21,   0xd62f105d);
  GG   (d,   a,   b,   c,   x[10],   S22,     0x2441453);
  GG   (c,   d,   a,   b,   x[15],   S23,   0xd8a1e681);
  GG   (b,   c,   d,   a,   x[   4],   S24,   0xe7d3fbc8);
  GG   (a,   b,   c,   d,   x[   9],   S21,   0x21e1cde6);
  GG   (d,   a,   b,   c,   x[14],   S22,   0xc33707d6);
  GG   (c,   d,   a,   b,   x[   3],   S23,   0xf4d50d87);
  GG   (b,   c,   d,   a,   x[   8],   S24,   0x455a14ed);
  GG   (a,   b,   c,   d,   x[13],   S21,   0xa9e3e905);
  GG   (d,   a,   b,   c,   x[   2],   S22,   0xfcefa3f8);
  GG   (c,   d,   a,   b,   x[   7],   S23,   0x676f02d9);
  GG   (b,   c,   d,   a,   x[12],   S24,   0x8d2a4c8a);
  HH   (a,   b,   c,   d,   x[   5],   S31,   0xfffa3942);
  HH   (d,   a,   b,   c,   x[   8],   S32,   0x8771f681);
  HH   (c,   d,   a,   b,   x[11],   S33,   0x6d9d6122);
  HH   (b,   c,   d,   a,   x[14],   S34,   0xfde5380c);
  HH   (a,   b,   c,   d,   x[   1],   S31,   0xa4beea44);
  HH   (d,   a,   b,   c,   x[   4],   S32,   0x4bdecfa9);
  HH   (c,   d,   a,   b,   x[   7],   S33,   0xf6bb4b60);
  HH   (b,   c,   d,   a,   x[10],   S34,   0xbebfbc70);
  HH   (a,   b,   c,   d,   x[13],   S31,   0x289b7ec6);
  HH   (d,   a,   b,   c,   x[   0],   S32,   0xeaa127fa);
  HH   (c,   d,   a,   b,   x[   3],   S33,   0xd4ef3085);
  HH   (b,   c,   d,   a,   x[   6],   S34,     0x4881d05);
  HH   (a,   b,   c,   d,   x[   9],   S31,   0xd9d4d039);
  HH   (d,   a,   b,   c,   x[12],   S32,   0xe6db99e5);
  HH   (c,   d,   a,   b,   x[15],   S33,   0x1fa27cf8);
  HH   (b,   c,   d,   a,   x[   2],   S34,   0xc4ac5665);
  II   (a,   b,   c,   d,   x[   0],   S41,   0xf4292244);
  II   (d,   a,   b,   c,   x[   7],   S42,   0x432aff97);
  II   (c,   d,   a,   b,   x[14],   S43,   0xab9423a7);
  II   (b,   c,   d,   a,   x[   5],   S44,   0xfc93a039);
  II   (a,   b,   c,   d,   x[12],   S41,   0x655b59c3);
  II   (d,   a,   b,   c,   x[   3],   S42,   0x8f0ccc92);
  II   (c,   d,   a,   b,   x[10],   S43,   0xffeff47d);
  II   (b,   c,   d,   a,   x[   1],   S44,   0x85845dd1);
  II   (a,   b,   c,   d,   x[   8],   S41,   0x6fa87e4f);
  II   (d,   a,   b,   c,   x[15],   S42,   0xfe2ce6e0);
  II   (c,   d,   a,   b,   x[   6],   S43,   0xa3014314);
  II   (b,   c,   d,   a,   x[13],   S44,   0x4e0811a1);
  II   (a,   b,   c,   d,   x[   4],   S41,   0xf7537e82);
  II   (d,   a,   b,   c,   x[11],   S42,   0xbd3af235);
  II   (c,   d,   a,   b,   x[   2],   S43,   0x2ad7d2bb);
  II   (b,   c,   d,   a,   x[   9],   S44,   0xeb86d391);
  state[0]   +=   a;
  state[1]   +=   b;
  state[2]   +=   c;
  state[3]   +=   d;
  memset   ((POINTER)x,   0,   sizeof   (x));
  }
//初始化
inline   void   MD5Init(MD5_CTX   *context)
{
  context->count[0]   =   context->count[1]   =   0;
  context->state[0]   =   0x67452301;
  context->state[1]   =   0xefcdab89;
  context->state[2]   =   0x98badcfe;
  context->state[3]   =   0x10325476;
}
inline   void   MD5Update(MD5_CTX   *context,   unsigned   char   *input,   unsigned   int   inputLen)
{
  unsigned   int   i,   index,   partLen;

  index   =   (unsigned   int)((context->count[0]   >>   3)   &   0x3F);
  if   ((context->count[0]   +=   ((UINT4)inputLen   <<   3))
    <   ((UINT4)inputLen   <<   3))
    context->count[1]++;
  context->count[1]   +=   ((UINT4)inputLen   >>   29);

  partLen   =   64   -   index;

  if   (inputLen   >=   partLen)   {
    memcpy((POINTER)&context->buffer[index],   (POINTER)input,   partLen);
    MD5Transform(context->state,   context->buffer);

    for   (i   =   partLen;   i   +   63   <   inputLen;   i   +=   64)
      MD5Transform   (context->state,   &input[i]);
    index   =   0;
  }
  else
    i   =   0;

  memcpy((POINTER)&context->buffer[index],   (POINTER)&input[i],   inputLen-i);
}

inline   void   MD5Final(unsigned   char   digest[16],   MD5_CTX   *context)
{
  unsigned   char   bits[8];
  unsigned   int   index,   padLen;

  Encode   (bits,   context->count,   8);
  index   =   (unsigned   int)((context->count[0]   >>   3)   &   0x3f);
  padLen   =   (index   <   56)   ?   (56   -   index)   :   (120   -   index);
  MD5Update   (context,   PADDING,   padLen);
  MD5Update   (context,   bits,   8);
  Encode   (digest,   context->state,   16);
  memset   ((POINTER)context,   0,   sizeof   (*context));
  }

void   MD5Digest(char   *pszInput,   unsigned   long   nInputSize,   char   *pszOutPut)
{
  MD5_CTX   context;
  unsigned   int   len   =   strlen   (pszInput);

  MD5Init   (&context);
  MD5Update   (&context,   (unsigned   char   *)pszInput,   len);
  MD5Final   ((unsigned   char   *)pszOutPut,   &context);
}
//生成一个随机字符串
bool getRandStr(char * randStr,int length){
    srand(time(0));                         //产生随机化种子
    int k=rand()%length+1;                  //随机生成一个字符串的长度，50以内
    printf("\nSalt String:");
    for(int i=0;i<=k-1;i++)
    {
        int x,s;                        //x表示这个字符的ascii码 ，s表示这个字符的大小写
        s=rand()%2;                     //随机使s为1或0，为1就是大写，为0就是小写
        if(s==1)                        //如果s=1
            x=rand()%('Z'-'A'+1)+'A';       //将x赋为大写字母的ascii码
        else
            x=rand()%('z'-'a'+1)+'a';       //如果s=0，x赋为小写字母的ascii码
        *(randStr+i)=x;
        printf("%c",x);                 //将x转换为字符输出
    }
    printf("\n");
    return true;
}



QByteArray MD5Process(QByteArray SALT, QByteArray PASSWD)
{
    QByteArray MessageDigest;


    char *user_key;
     user_key  = PASSWD.data();
    char *salt;
    salt = SALT.data();
    qDebug()<<"SALT"<<SALT.data();
    printf("\nsalt");

    for (int i=0;salt[i];i++)
    {
        printf("%02X",(unsigned char)salt[i]);
    }
//    qDebug()<<"SALT"<<SALT;
//    qDebug()<<"PASSWD"<<PASSWD<<"PASSWD.len"<<PASSWD.size();
//    qDebug()<<strlen(user_key);


 //说明：每次登陆需要发送salt（明文）、用户名（明文）、两次MD5后的消息摘要（md5(md5(密码明文)+salt)）
    char szDigest[20]={0};//消息摘要为128bits，共16字节，赋初值0
    char user_key_temp[80]={0};//缓存密码加密结果和salt,首先要赋初值0，不然会编码错误
    //第一步，用户密码加密MD5
    MD5Digest(user_key,strlen(user_key),user_key_temp);
    int i;

    //第二步，生成一个随机字符串，a-z,A-Z
    //第三步，将用户密码MD5加密后的结果和随机字符串连接
    strcat(user_key_temp,salt);

    //第四步，将连接后的数据进行MD5加密
    MD5Digest(user_key_temp,strlen(user_key_temp),szDigest);
     printf("\nEncoded msg:");
    for (i=0;i<16;i++)
    {
        printf("%02X",(unsigned char)szDigest[i]);
    }
    printf("\n");
    MessageDigest = QByteArray(szDigest,16).toHex();
    qDebug()<<"MessageDigest"<<MessageDigest;
    return MessageDigest;
}
/*
int main(int argc, char *argv[])
{
    //说明：每次登陆需要发送salt（明文）、用户名（明文）、两次MD5后的消息摘要（md5(md5(密码明文)+salt)）


    char szDigest[20]={0};//消息摘要为128bits，共16字节，赋初值0
    char user_key_temp[80]={0};//缓存密码加密结果和salt,首先要赋初值0，不然会编码错误
    char user_key[200] = "sono";//密码
    char salt[60] = {0};//salt 长度不超过50
    //第一步，用户密码加密MD5
    MD5Digest(user_key,strlen(user_key),user_key_temp);
    int i;
    printf("Md5 Key:");
    for (i=0;i<16;i++)
    {
        printf("%02X",(unsigned char)user_key_temp[i]);
    }
    //第二步，生成一个随机字符串，a-z,A-Z
    getRandStr(salt,50);
    printf("salt:");
    for (i=0;salt[i];i++)
    {
        printf("%02X",(unsigned char)salt[i]);
    }
    printf("\n");
    //第三步，将用户密码MD5加密后的结果和随机字符串连接
    strcat(user_key_temp,salt);
    printf("Md5 Key+salt:");
    for (i=0;user_key_temp[i];i++)
    {
        printf("%02X",(unsigned char)user_key_temp[i]);
    }
    //第四步，将连接后的数据进行MD5加密
    MD5Digest(user_key_temp,strlen(user_key_temp),szDigest);

    printf("\nEncoded msg:");
    for (i=0;i<16;i++)
    {
        printf("%02X",(unsigned char)szDigest[i]);
    }
    return 0;
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

//    return a.exec();
}
*/

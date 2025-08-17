#include <stdio.h>
#include <string.h>
 
#define REVERSE(a) (((a) & 0xff) << 24 | ((a) & 0xff00) << 8 | ((a) & 0xff0000) >> 8 | ((a) & 0xff000000) >> 24)
//32位数据四个字节大小端转换
typedef struct {
    char *para;
    int value;
} MyStruct;

MyStruct cmd[] = 
{
    {"Set", 0}, 
    {"Get", 1}
};

MyStruct para[] = 
{
    {"VID", 0}, 
    {"PID", 1}, 
    {"SN", 2}
};
 
int findValueByName(MyStruct arr[], int size, const char* searchName) 
{
    for (int i = 0; i < size; i++) {
        if (strcmp(arr[i].para, searchName) == 0) {
            return arr[i].value; // 返回找到的value
        }
    }
    return -1; // 如果没有找到，返回-1或适当的错误码
}


int HexToAscii(unsigned char *pHexStr,unsigned char *pAscStr,int Len)
{
  char Nibble[2];
  unsigned char Buffer[2048];
  int i = 0;
  int j = 0;

  for(i=0;i<Len;i++)
  {
    Nibble[0]=pHexStr[i] >> 4 & 0X0F;
    Nibble[1]=pHexStr[i] & 0x0F;
    for(j=0;j<2;j++)
    {
      if(Nibble[j]<10)
      {
        Nibble[j]=Nibble[j]+0x30;
      }
      else if(Nibble[j]<16)
      {
        Nibble[j]=Nibble[j]-10+'A';
      }
      else
      {
        return 0;
      }
    }
    memcpy(Buffer+i*2,Nibble,2);
  }
  Buffer[2*Len]=0x00;
  memcpy(pAscStr,Buffer,2*Len);
  pAscStr[2*Len]=0x00;
  return 1;

}

char  AsciiToHex(unsigned char * pAscii, unsigned char * pHex, int nLen)
{
  int nHexLen = nLen / 2;
  unsigned char Nibble[2] = {0};
  int i = 0;
  int j = 0;

  if (nLen%2)
  {
    return 1;
  }

  for (i = 0; i < nHexLen; i ++)
  {
    Nibble[0] = *pAscii ++;   
    Nibble[1] = *pAscii ++;
    for (j = 0; j < 2; j ++)
    {
      if (Nibble[j] <= 'F' && Nibble[j] >= 'A')
        Nibble[j] = Nibble[j] - 'A' + 10;
      else if (Nibble[j] <= 'f' && Nibble[j] >= 'a')
        Nibble[j] = Nibble[j] - 'a' + 10;
      else if (Nibble[j] >= '0' && Nibble[j] <= '9')
        Nibble [j] = Nibble[j] - '0';
      else
        return 1;//Nibble[j] = Nibble[j] - 'a' + 10;
      
    } // for (int j = ...)
    pHex[i] = Nibble[0] << 4; // Set the high nibble
    pHex[i] |= Nibble[1]; //Set the low nibble
  } // for (int i = ...)
  return 0;
}

char  AsciiToDec(unsigned char * pAscii, unsigned char * pHex, int nLen)
{
  int nHexLen = nLen / 2;
  unsigned char Nibble[2] = {0};
  int i = 0;
  int j = 0;

  if (nLen%2)
  {
    return 1;
  }

  for (i = 0; i < nHexLen; i ++)
  {
    Nibble[0] = *pAscii ++;   
    Nibble[1] = *pAscii ++;
    for (j = 0; j < 2; j ++)
    {
      Nibble [j] = Nibble[j] - '0';
    } // for (int j = ...)
  
    pHex[i] = Nibble[0] * 10; // Set the high nibble
    pHex[i] += Nibble[1]; //Set the low nibble
  } // for (int i = ...)
  return 0;
}

int main() {
    char target[100];
    int size = sizeof(cmd) / sizeof(cmd[0]);
    int value = findValueByName(cmd, size, "Set");
    if (value != -1) {
        printf("Value for %s: %d\n",cmd[value].para, value);
    } else {
        printf("Name not found.\n");
    }
    sprintf(target, "<%s-%d>", cmd[value].para, value);
    printf("%s\n",target);
    

    // 1. 准备输入数据（原始二进制）
    unsigned char hexData[] = {0x12, 0xAB, 0x5F};
    
    // 2. 计算输入数据长度
    int inputLen = sizeof(hexData) / sizeof(hexData[0]);
    
    // 3. 准备输出缓冲区（大小为 2*Len+1）
    unsigned char asciiStr[2 * inputLen + 1];
    
    // 4. 调用转换函数
    int success = HexToAscii(hexData, asciiStr, inputLen);
    
    if (success) {
        printf("HexToAscii: %s\n", asciiStr); // 输出: "12AB5F"
    } else {
        printf("转换失败！\n");
    }

    
    // 1. 准备输入数据（ASCII十六进制字符串）
    unsigned char asciiStr1[] = "12AB5F";  // 有效输入
    
    // 2. 计算输入字符串长度（不包括终止符）
    int inputLen1 = strlen((char*)asciiStr1);
    
    // 3. 检查长度是否为偶数
    if (inputLen1 % 2 != 0) {
        printf("错误：输入长度必须是偶数！\n");
        return -1;
    }
    
    // 4. 准备输出缓冲区（大小为输入长度的一半）
    int outputLen1 = inputLen1 / 2;
    unsigned char hexData1[outputLen1];
    
    // 5. 调用转换函数
    char result = AsciiToHex(asciiStr1, hexData1, inputLen1);
    
    // 6. 检查结果
    if (result == 0) {
        printf("AsciiToHex:");
        // 打印转换结果
        for (int i = 0; i < outputLen1; i++) {
            printf("0x%02X ", hexData1[i]); // 输出：0x12 0xAB 0x5F
        }
        printf("\n");
    } else {
        printf("转换失败：输入包含非法字符或长度错误！\n");
    }



 // 1. 准备输入数据（ASCII数字字符串）
    unsigned char asciiStr2[] = "12345678";  // 必须为偶数长度
    
    // 2. 计算输入字符串长度
    int inputLen2 = strlen((char*)asciiStr2);
    
    // 3. 检查长度是否为偶数
    if (inputLen2 % 2 != 0) {
        printf("错误：输入长度必须是偶数！当前长度：%d\n", inputLen2);
        return -1;
    }
    
    // 4. 准备输出缓冲区
    int outputLen2 = inputLen2 / 2;
    unsigned char decData2[outputLen2];
    
    // 5. 调用转换函数
    char result2 = AsciiToDec(asciiStr2, decData2, inputLen2);
    
    // 6. 检查结果
    if (result2 == 0) {
        printf("转换成功！\n");
        printf("原始字符串: %s\n", asciiStr2);
        printf("转换结果: ");
        for (int i = 0; i < outputLen2; i++) {
            printf("%02X ", decData2[i]); // 输出十六进制表示
        }
        printf("\n");
        
        // 解释转换结果
        printf("AsciiToDec: ");
        for (int i = 0; i < outputLen2; i++) {
            printf("%d ", decData2[i]); // 输出十进制值
        }
    } else {
        printf("转换失败：输入长度非偶数！\n");
    }



    return 0;
}



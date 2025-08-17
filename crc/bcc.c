#include "bcc.h"
/**
 * funBccCreate: 异或校验，计算校验码
 * @p[IN]: 字符串指针
 * @len[IN]: 字符串长度
 * @bcc[OUT]: bcc校验码
 * return: 0 成功 , -1 失败
 */
int funBccCreate(unsigned char *p, unsigned int len, unsigned char *bcc)
{   
    if((NULL == p) || (0 == len) || (NULL == bcc))
    {
		return -1;
    }
    *bcc = 0;
    for(; len > 0; len--)
    {
		*bcc^=*p++;
    }
	
    return 0;
}


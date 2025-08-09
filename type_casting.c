#include <stdio.h>
#include <string.h>

int main() {
    float f1 = 59.622f;
    float f2 = 92.6327f;

    char buf[4];  // 存两个 short
    short s1, s2;

    // 1. 选一个缩放因子，减少小数损失
    float scale = 350.0f; 
    //  short的范围是-32768~32768，计算得出最大缩放范围
    s1 = (short)(f1 * scale);
    s2 = (short)(f2 * scale);
    printf("原始值: %.6f, %.6f\n", f1, f2);
    // 2. 用 memcpy 压入缓冲区
    memcpy(buf, &s1, sizeof(short));
    memcpy(buf + sizeof(short), &s2, sizeof(short));
    printf ("扩大后存储的值： ");
    for (int i=0;i<4;i++)
    {
        printf ("buf[%d] = %u \n",i,(unsigned char)buf[i]);
    }
    // 3. 从缓冲区提取
    short rs1, rs2;
    memcpy(&rs1, buf, sizeof(short));
    memcpy(&rs2, buf + sizeof(short), sizeof(short));

    // 4. 还原成 float
    float rf1 = rs1 / scale;
    float rf2 = rs2 / scale;

   
    printf("还原值: %.6f, %.6f\n", rf1, rf2);
    printf("误差:    %.6f, %.6f\n", f1 - rf1, f2 - rf2);

    return 0;
}

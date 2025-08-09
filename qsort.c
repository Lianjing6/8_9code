#include <stdio.h>
#include <stdlib.h>


//比较函数
int compareFloat(const void *a,const void *b)
{
    float fa = *(const float*)a;
    float fb = *(const float*)b;
    if (fa < fb) return -1;
    else if (fa >fb) return 1;
    else return 0;
}


int main (void)
{
    float *arr = NULL;//动态数组
    int count = 0;//用于计算已输入元素的个数
    float temp;

    printf("请输入任意数量的浮点数（非数字输入结束）：\n");

    //循环输入，遇回车结束
    while (scanf ("%f",&temp)==1){
        //定义新指针用于接收realloc返回值，避免丢失原指针
        float *newarr = realloc (arr,(count+1)*sizeof(float));
        //如果malloc分配失败，会返回NULL
        if (!newarr){
            printf("内存分配失败！！\n");
            free (arr);
            return 1;
        }
        arr = newarr;//分配成功，将新指针赋给arr
        arr[count]= temp;//把读入的temp写入arr末尾
        count++;
    }
    if (count==0){
        printf("没有数据！！\n");
        return 0;
    }

    //排序
    qsort(arr,count,sizeof(float),compareFloat);
    
    //输出结果
    printf("\n从小到大排序的结果是：\n");
    for (int i=0;i<count;i++){
        printf("%.2f ",arr[i]);
    }
    printf("\n");
    free(arr);
    return 0;
}
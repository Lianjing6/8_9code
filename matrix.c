#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//矩阵结构体定义
typedef struct MParam
{
    uint8_t row;
    uint8_t column;
    float **data;
} *Matrix;

//矩阵库函数
Matrix createMatrix(uint8_t row,uint8_t column)
{
    //为矩阵m分配内存
    Matrix m = (Matrix)malloc(sizeof(struct MParam));
    if (!m)
    return NULL;
    //赋值
    m -> row = row;//行
    m -> column = column;//列

    //分配行指针
    m->data = malloc((size_t)row * sizeof (float*));
    if(!m->data)
    {
       free (m);
       return NULL;
    }
    //为每一行分配列
    for (uint8_t i=0;i<row ;i++)
    {
        m->data[i] = (float*)malloc((size_t)column * sizeof(float));
        if (!m->data[i]){
          for (size_t k= 0;k<i;k++)
          free (m->data[k]);
          free (m->data);
          return NULL;
        }
    }
    return m;
}
//释放矩阵内存
void freeMatrix (Matrix m){
    if (!m)
    return;
    //释放每一行的内存
    for (uint8_t i=0;i<m->row;i++)
    {
        free (m->data[i]);
    }
    //释放行指针数组本身
    free (m->data);
    free(m);//释放结构体m
}
//从键盘输入矩阵
void inputMatrix(Matrix m){
    printf("请输入 %d × %d 矩阵元素：\n",m->row,m->column);
    for (uint8_t i = 0;i < m->row ; i++){
        for (uint8_t j = 0;j < m->column;j++){
            scanf ("%f",&m->data[i][j]);
        }
    }
}
//打印矩阵
void printMatrix(Matrix m)
{
     for (uint8_t i = 0;i < m->row ; i++){
        for (uint8_t j = 0;j < m->column;j++){
            printf("%f ",m->data[i][j]);
        }
        printf("\n");
    }
}
//矩阵转置
Matrix transposeMatrix(Matrix m){
    Matrix t = createMatrix(m->column,m->row);
    for (uint8_t i= 0;i<m->row;i++){
        for (uint8_t j = 0;j<m->column;j++){
            t->data[j][i] = m->data[i][j];
        }
    } 
    return t;
}

//矩阵乘法
Matrix multiplyMatrix (Matrix a,Matrix b){
    if (a->column != b->row){
        printf ("两矩阵无法进行乘法运算！！");
        exit (1);
    }
    Matrix result = createMatrix(a->row,b->column);
    for (uint8_t i = 0;i< a->row;i++){
        for (uint8_t j=0;j<b->column;j++){
            float sum = 0;
            for (uint8_t k = 0;k<a->column;k++){
                sum += a->data[i][k]*b->data[k][j];
            }
            result->data[i][j]=sum;
        }
    }
    return result;
}
//主程序
int main (void){
    int row,column;
    printf ("请输入矩阵的行数和列数：");
    scanf ("%d %d",&row,&column);

    //创建输入A矩阵
    Matrix A = createMatrix(row,column);
    inputMatrix(A);


    //创建A转置矩阵
    Matrix AT = transposeMatrix(A);

    //矩阵乘法
    Matrix result = multiplyMatrix(A,AT);

    
    //打印A、AT矩阵以及两者相乘结果
    printf ("\n原矩阵A:\n");
    printMatrix(A);

    printf("\n转置矩阵AT；\n");
    printMatrix(AT);

    printf("\n原矩阵A × 转置矩阵AT = \n");
    printMatrix(result);

    //释放内存
    freeMatrix(A);
    freeMatrix(AT);
    freeMatrix(result);

    return 0;
}
/*
说明:
part1实现分数相关计算
part2实现矩阵输入
part3实现矩阵化简
part4实现矩阵输出
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
int gcd(int a,int b)//最大公约数算法
{
    int temp=1;
    while(b)
    {
        temp = b;
        b = a%b;
        a = temp;
    }
    return a;
}


typedef struct//定义分数结构体
{
    int numerator;//分子
    int denominator;//分母
} fraction;
void simplify_fraction(fraction *f)//约分算法
{   
    if(f->denominator == 0)//分母为0报错并退出
    {
        printf("denominator cannot be zero!");
        exit(1);//程序异常终止并且退出,stdlib.h库中方法
    }
    if(f->denominator < 0)//确保负号在分子上
    {
        f->denominator = -f->denominator;
        f->numerator = -f->numerator;
    }
    //约分
    int greatest_common_divisor=abs(gcd(f->denominator,f->numerator));
    f->denominator /= greatest_common_divisor;
    f->numerator /= greatest_common_divisor;
}
fraction print_fraction(fraction a)//标准化输出
{   
    if(a.denominator == 0)
    {
        printf("invalid input!");
        exit(1);
    }
    if(a.denominator == 1)
    {
        printf("%d",a.numerator);
    }else{
        printf("%d/%d",a.numerator,a.denominator);
    }
}
fraction create_fraction(int numerator,int denominator)//创建分数
{
    fraction f;
    f.numerator = numerator;
    f.denominator = denominator;
    return f;
}
fraction add_fraction(fraction a,fraction b)//分数加法
{
    fraction result={0,1};
    result.numerator=a.numerator*b.denominator+a.denominator*b.numerator;
    result.denominator=a.denominator*b.denominator;
    //e.g. 1/2+1/3 = (1*3+1*2)/2*3 = 5/6
    simplify_fraction(&result);
    return result;
}
fraction subtract_fraction(fraction a,fraction b)//分数减法
{
    fraction result={0,1};
    result.numerator=a.numerator*b.denominator-a.denominator*b.numerator;
    result.denominator=a.denominator*b.denominator;
    //e.g. 1/2-1/3 = (1*3-1*2)/2*3 = 1/6
    simplify_fraction(&result);
    return result;
}
fraction multiple_fraction(fraction a,fraction b)//分数乘法
{
    fraction result={0,1};
    result.numerator=a.numerator*b.numerator;
    result.denominator=a.denominator*b.denominator;
    //e.g. 1/2*1/3 = 1*1/2*3 = 1/6
    simplify_fraction(&result);
    return result;
}
fraction divide_fraction(fraction a,fraction b)//分数除法
{
    fraction result={0,1};
    result.numerator=a.numerator*b.denominator;
    result.denominator=a.denominator*b.numerator;
    //e.g. 1/2 / 1/3 = 1*3/2*1 = 1/6
    simplify_fraction(&result);
    return result;
}
int is_one_fraction(fraction frac)// 判断分数是否为1
{
    return frac.numerator == frac.denominator && frac.numerator != 0;
}
int is_zero_fraction(fraction frac)// 判断分数是否为0
{
    return frac.numerator == 0;
}


typedef struct //定义矩阵
{
    int rows;//行数
    int cols;//列数
    fraction** data;//二维数组指针
} matrix;
matrix create_matrix(int rows,int cols)//创建矩阵
{
    matrix mat;
    mat.rows = rows;
    mat.cols = cols;
    
    //分配内存
    mat.data = (fraction**)malloc(rows * sizeof(fraction*));//创建 rows 个指针，每个指针将指向一行数据
    if (mat.data == NULL) {
        // 错误处理
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    for(int i = 0;i < rows;i++)
    {
        mat.data[i] = (fraction*)malloc(cols * sizeof(fraction));//为每一行分配 cols 个 Fraction 结构体的空间
        if (mat.data == NULL) {
        // 错误处理
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
        //初始化
        for(int j = 0;j < cols; j++)
        {
            mat.data[i][j] = create_fraction(0,1);
        }
    }
    return mat;
}
void free_matrix(matrix* mat)//释放内存
{
    for(int i = 0; i < mat->rows; i++)
    {
        free(mat->data[i]);//释放每一行的内存
    }
    free(mat->data);//释放行指针数组的内存
}
// fraction matrix_input(int rows,char a[])//处理输入部分(第一版)
// {
//     /*规定输入格式为[1,3/4,-2.5,10.7,-15],参考数组写法,定义两个flag确定数据位置,使用循环遍历字符判断输入类型,再根据不同的类型进行存储*/
//     int flag1 = 0;//前起止位
//     int flag2 = 1;//后起止位
//     int op = 1;//符号位
//     for(int i = 0;i <= strlen(a);i++)
//     {
//         if(a[i] == '/')//分数
//         {
//             op = i;
//             for(int j = i;j <= strlen(a);j++)//定位,或者[]
//             {
//                 if(a[j] == ',' || a[j] == ']')
//                 {
//                     flag2 = j;
//                     break;
//                 }
//             }
//             int temp_denominator=0;
//             int temp_numerator=0;
//             for(int j = flag2 - 1;j >= op + 1;j--)//分母处理
//             {
//                 temp_denominator = temp_denominator*10 + (int)(a[j]-'0');
//             }
//             for(int j = op-1;j >= flag1 + 1;j--)//分子处理
//             {
//                 temp_numerator = temp_numerator*10 + (int)(a[j]-'0');
//             }
//             for(int j = flag2-1;j >= op + 1;j--)//分母处理
//             {
//                 temp_denominator = temp_denominator*10 + (int)(a[j]-'0');
//             }
//         }else if(a[i] == '.'){
//             //小数
//         }
//         //整数   
//     }
// }
fraction float_to_fraction(double decimal)// 浮点数转分数
{
    const int max_denominator = 10000;
    double tolerance = 1e-10;
    
    // 处理符号
    int sign = (decimal < 0) ? -1 : 1;
    decimal = fabs(decimal);
    
    // 分离整数和小数部分
    int integer_part = (int)decimal;
    double fractional_part = decimal - integer_part;
    
    // 寻找最佳分数近似
    int best_num = 0, best_den = 1;
    double min_error = 1.0;
    
    for (int denom = 1; denom <= max_denominator; denom++) {
        int numer = (int)round(fractional_part * denom);
        double error = fabs(fractional_part - (double)numer / denom);
        
        if (error < min_error) {
            min_error = error;
            best_num = numer;
            best_den = denom;
            if (error < tolerance) break;
        }
    }
    
    // 合并整数部分
    int numerator = sign * (integer_part * best_den + best_num);
    int denominator = best_den;
    
    return create_fraction(numerator, denominator);
}
fraction parse_fraction_input(const char* input)// 解析输入
{
    char buffer[100];
    strcpy(buffer, input);
    
    // 去除前后空格
    char* start = buffer;
    while (isspace(*start)) start++;
    char* end = start + strlen(start) - 1;
    while (end > start && isspace(*end)) end--;
    *(end + 1) = '\0';
    
    // 检查空字符串
    if (strlen(start) == 0) {
        return create_fraction(0, 1);
    }
    
    // 检查分数格式 (a/b)
    char* slash = strchr(start, '/');
    if (slash != NULL) {
        *slash = '\0';
        char* numerator_str = start;
        char* denominator_str = slash + 1;
        
        int numerator = atoi(numerator_str);
        int denominator = atoi(denominator_str);
        
        if (denominator == 0) {
            printf("错误: 分母不能为零!\n");
            return create_fraction(0, 1);
        }
        
        return create_fraction(numerator, denominator);
    }
    
    // 检查小数格式
    char* dot = strchr(start, '.');
    if (dot != NULL) {
        double decimal_value = atof(start);
        return float_to_fraction(decimal_value);
    }
    
    // 整数格式
    int integer_value = atoi(start);
    return create_fraction(integer_value, 1);
}
void input_matrix(matrix* mat)// 输入矩阵
{
    printf("请输入 %d*%d 矩阵的元素:\n", mat->rows, mat->cols);
    printf("支持格式: 整数(3), 分数(2/3), 小数(2.5)\n");
    
    char input[100];
    for (int i = 0; i < mat->rows; i++) {
        printf("第 %d 行 (用空格分隔 %d 个元素): ", i + 1, mat->cols);
        
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("输入错误!\n");
            return;
        }
        
        // 分割输入
        char* token = strtok(input, " \t\n");
        int j = 0;
        
        while (token != NULL && j < mat->cols) {
            mat->data[i][j] = parse_fraction_input(token);
            token = strtok(NULL, " \t\n");
            j++;
        }
        
        if (j < mat->cols) {
            printf("警告: 只输入了 %d 个元素,剩余元素设为0\n", j);
        }
    }
}
void print_matrix(matrix* mat)//打印矩阵
{
    for(int i = 0;i < mat->rows;i++)
    {
        printf("[");
        for(int j = 0;j < mat->cols;j++)
        {  
            print_fraction(mat->data[i][j]);
            printf(" ");
        }
        printf("]\n");
    }
}


void swap_rows(matrix* mat,int row1,int row2)//交换两行
{
    if(row1 == row2)return;

    fraction* temp = mat->data[row1];
    mat->data[row1] = mat->data[row2];
    mat->data[row2] = temp;
}
void multiple_row(matrix* mat,fraction f,int row)//倍乘某行
{
    for(int i = 0;i <= mat->cols;i++)   
    {
        mat->data[row][i] = multiple_fraction(mat->data[row][i],f);
    }
}
void add_scaled_row(matrix* mat,int row1,int row2,fraction f)// 行加法：row1 = row1 + scalar * row2
{
    for (int j = 0; j < mat->cols; j++) {
        fraction product = multiple_fraction(f, mat->data[row2][j]);
        mat->data[row1][j] = add_fraction(mat->data[row1][j], product);
    }
}
// matrix simplify_matrix(matrix* mat)//化为最简阶梯矩阵(第一版)
// {
//     //创建副本
//     matrix result = create_matrix(mat->rows,mat->cols);
//     for(int i = 0;i < mat->rows;i++)
//     {
//         for(int j = 0;j < mat->cols;j++){
//             result.data[i][j] = mat->data[i][j];
//         }
//     }
//     //化简
//     for(int i = 0;i < result.cols;i++)//主元一定在(i,i)位置上
//     {
//         for(int j = 0;j < result.rows;j++)
//         {
//             if(result.data[i][j].numerator != 0)
//             {
//                 swap_rows(&result,i,j);
//             }
//         }
//         for(int j = i;j < result.rows;j++)
//         {
//             fraction temp = divide_fraction(result.data[i][j],result.data[i][i]);
//             add_scaled_row(&result,j,i,temp);
//         }
//     }
//     return result;
// }
matrix simplify_matrix(matrix* mat)//化为最简阶梯矩阵
{
    // 创建副本
    matrix result = create_matrix(mat->rows, mat->cols);
    for(int i = 0; i < mat->rows; i++)
    {
        for(int j = 0; j < mat->cols; j++) {
            result.data[i][j] = mat->data[i][j];
        }
    }
    
    int lead = 0; // 主元列
    
    // 前向消元：化为行阶梯形
    for(int r = 0; r < result.rows; r++)
    {
        if (lead >= result.cols) break;
        
        // 在当前列寻找主元
        int i = r;
        while (i < result.rows && is_zero_fraction(result.data[i][lead])) {
            i++;
        }
        
        if (i >= result.rows) {
            // 当前列找不到主元，移动到下一列
            lead++;
            r--; // 保持当前行不变
            continue;
        }
        
        // 交换主元行到当前行
        if (i != r) {
            swap_rows(&result, r, i);
        }
        
        // 消去当前列下方元素
        fraction pivot = result.data[r][lead];
        for (int j = r + 1; j < result.rows; j++) {
            if (!is_zero_fraction(result.data[j][lead])) {
                fraction factor = divide_fraction(result.data[j][lead], pivot);
                factor = multiple_fraction(factor, create_fraction(-1, 1)); // 取负号
                add_scaled_row(&result, j, r, factor);
            }
        }
        
        lead++;
    }
    
    // 后向消元：化为行最简形
    for(int r = result.rows - 1; r >= 0; r--)
    {
        // 找到主元列
        int pivot_col = -1;
        for(int j = 0; j < result.cols; j++) {
            if (!is_zero_fraction(result.data[r][j])) {
                pivot_col = j;
                break;
            }
        }
        
        if (pivot_col == -1) continue; // 零行，跳过
        
        // 标准化主元为1
        fraction pivot = result.data[r][pivot_col];
        if (!is_one_fraction(pivot)) {
            multiple_row(&result,create_fraction(pivot.denominator, pivot.numerator),r);
        }
        
        // 消去上方行的主元列元素
        for(int i = 0; i < r; i++) {
            if (!is_zero_fraction(result.data[i][pivot_col])) {
                fraction factor = multiple_fraction(result.data[i][pivot_col], create_fraction(-1, 1));
                add_scaled_row(&result, i, r, factor);
            }
        }
    }
    
    return result;
}
void user_interaction()//交互界面
{
    printf("----------矩阵计算化简程序v0.1----------\n");
    int flag = 0;
    while(1)
    {   
        printf("请输入数字进入对应操作:\n1.创建矩阵\n2.查看当前矩阵\n3.输出化简结果\n4.退出程序\n");
        int a = 0;
        matrix mat;
        scanf("%d",&a);
        if(a == 1){
            flag = 1;
            int m=0,n=0;
            //输入大小
            printf("请输入矩阵的大小:(格式为m*n)\n");
            scanf("%d*%d",&m,&n);
            getchar();
            //创建矩阵
            mat = create_matrix(m,n);
            input_matrix(&mat);
            printf("\n");
        }else if(a == 2){
            if(flag == 0){
                printf("无效!请先创建矩阵\n\n");
            }else{
                //输出矩阵
                printf("输入的矩阵:\n");
                print_matrix(&mat);
                printf("\n");
            }
        }else if(a == 3){
            if(flag == 0){
                printf("无效!请先创建矩阵\n\n");
            }else{
                //输出化简结果
                printf("化简结果:\n");
                matrix result = simplify_matrix(&mat);
                print_matrix(&result);
                printf("\n");
            }
        }else if(a == 4){
            printf("退出程序!\n");
            if(a == 1)
                free_matrix(&mat);
            break;
        }else{
            printf("无效的输入!请重试\n");
        }
    }
    
}
int main(){
    // fraction f1,f2;
    // f1.denominator=2;
    // f1.numerator=1;
    // f2.denominator=-4;
    // f2.numerator=3;
    // printf("%d/%d + %d/%d = %d/%d",f1.numerator,f1.denominator,f2.numerator,f2.denominator,divide_fraction(f1,f2).numerator,divide_fraction(f1,f2).denominator);
    //getchar();getchar();
    user_interaction();
    return 0;
}
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
void print_fraction(fraction a)//标准化输出
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
matrix create_matrix(int rows,int cols)//创建矩阵并且初始化
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
//在user_interaction()中已经强制检查是否能够进行运算
matrix add_matrix(matrix* mat1,matrix* mat2)//矩阵加法
{
    matrix result;
    result = create_matrix(mat1->rows,mat1->cols);//创建矩阵并且初始化
    if(mat1->cols == mat2->cols && mat1->rows == mat2->rows){//判断矩阵大小是否相同
        for(int i = 0;i < mat1->rows;i++)
        {
            for(int j = 0;j < mat1->cols;j++)
            {
                result.data[i][j] = add_fraction(mat1->data[i][j],mat2->data[i][j]);
            }
        }
        return result;
    }else{
        printf("矩阵大小不合法!invalid input!");
        return result;
    }
}
matrix subtract_matrix(matrix* mat1,matrix* mat2)//矩阵减法
{
    matrix result;
    result = create_matrix(mat1->rows,mat1->cols);//创建矩阵并且初始化
    if(mat1->cols == mat2->cols && mat1->rows == mat2->rows){//判断矩阵大小是否相同
        for(int i = 0;i < mat1->rows;i++)
        {
            for(int j = 0;j < mat1->cols;j++)
            {
                result.data[i][j] = subtract_fraction(mat1->data[i][j],mat2->data[i][j]);
            }
        }
        return result;
    }else{
        printf("矩阵大小不合法!invalid input!");
        return result;
    }
}
matrix multiple_matrix(matrix* mat1,matrix* mat2)//矩阵乘法
{
    matrix result;
    //m*n 矩阵与 n*k 矩阵才能相乘 结果矩阵大小为 m*k
    //即检查mat1.cols == mat2.rows
    result = create_matrix(mat1->rows,mat2->cols);//创建矩阵并且初始化
    if(mat1->cols == mat2->rows){//判断能否相乘
        for(int i = 0;i < mat1->rows;i++)//遍历mat1.rows即mat1的行数
        {
            for(int j = 0;j < mat2->cols;j++)//mat2的列数
            {
                for(int k = 0;k < mat1->cols;k++)
                {
                    result.data[i][j] = add_fraction(result.data[i][j],multiple_fraction(mat1->data[i][k],mat2->data[k][j]));
                }
            }
        }
        return result;
    }else{
        printf("矩阵大小不合法!invalid input!");
        return result;
    }
}
matrix transpose_matrix(matrix* mat1)//矩阵的转置
{
    matrix result = create_matrix(mat1->cols,mat1->rows);
    for(int i = 0;i < mat1->rows;i++)
    {
        for(int j = 0;j < mat1->cols;j++)
        {
            result.data[j][i] = mat1->data[i][j];
        }
    }
    return result;
}
fraction determinant_matrix(matrix* mat1)//求方阵的>>>>值<<<<!!!!
{
    matrix result;
    result = create_matrix(mat1->rows,mat1->cols);

    if(mat1->rows == mat1->cols)//只有方阵才能求值
    {
        //储存副本
        for(int i = 0;i < mat1->rows;i++)
        {
            for(int j = 0;j < mat1->cols;j++)
            {
                result.data[i][j] = mat1->data[i][j];
            }
        }

        //化为阶梯型矩阵

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
        
        //累乘,行阶梯方阵的值是对角线所有值的乘积
        fraction sum = create_fraction(1,1);
        for(int i = 0;i < result.rows;i++)
        {
            sum = multiple_fraction(sum,result.data[i][i]);
        }
        return sum;
    }else{
        printf("矩阵大小不合法!\n");
        return create_fraction(1,1);
    }
}
matrix solutions_of_equations(matrix* mat1)//求解n元线性方程组
{
    matrix result = create_matrix(mat1->rows,mat1->cols);
    if(mat1->rows == mat1->cols - 1){
        //克拉默法则:对于一个n*n的线性方程组,它的解可以表示为det(Ai)/det(A),其中Ai表示第i列被B替换后的矩阵;
        //高斯消元法:化为最简行阶梯矩阵即可求解
        //实际计算不会使用克拉默法则;
        //result = simplify_matrix(mat1);
        return result;
    }else{
        printf("输入的增广矩阵大小不合法!\n");
        return result;
    }
}
matrix inverse_matrix(matrix* mat1)//矩阵的逆
{
    matrix temp,result;
    temp = create_matrix(mat1->rows,mat1->cols*2);
    result = create_matrix(mat1->rows,mat1->cols);
    for(int i = 0;i < mat1->rows;i++)//分段赋值,(A:I)前半段赋值mat1
    {
        for(int j = 0;j < mat1->cols;j++)
        {
            temp.data[i][j] = mat1->data[i][j];
        }
    }
    for(int i = 0;i < mat1->rows;i++)//后半段赋值I
    {
        temp.data[i][i+mat1->rows] = create_fraction(1,1);
    }
    
    return result;
}
void user_interaction()//交互界面
{

    printf("----------矩阵计算化简程序v0.1----------\n");
    int flag1 = 0,flag2 = 0;
    matrix mat1,mat2;
    while(1)
    {   
        printf("请输入数字进入对应操作:\n1.创建矩阵1\n2.创建矩阵2\n3.查看矩阵1的值\n4.查看矩阵2的值\n5.计算矩阵加法(覆盖矩阵1的值)\n6.计算矩阵减法(覆盖矩阵1的值)\n7.计算矩阵乘法(覆盖矩阵1的值)\n8.输出矩阵1的转置矩阵(覆盖矩阵1的值)\n9.输出矩阵1的最简行阶梯矩阵\n10.输出矩阵1的逆矩阵(覆盖矩阵1的值)\n11.求矩阵1的值(方阵)\n12.求解线性方程组(请输入增广矩阵)\n0.退出程序(请输入0)\n");
        int a = 0;
        scanf("%d",&a);
        if(a == 1){//创建矩阵1
            flag1 = 1;
            int m=0,n=0;
            //输入大小
            printf("请输入矩阵1的大小:(格式为m*n)\n");
            scanf("%d*%d",&m,&n);
            getchar();
            //创建矩阵
            mat1 = create_matrix(m,n);
            input_matrix(&mat1);
            printf("\n");
        }else if(a == 2){//创建矩阵2
            flag2 = 1;
            int m=0,n=0;
            //输入大小
            printf("请输入矩阵2的大小:(格式为m*n)\n");
            scanf("%d*%d",&m,&n);
            getchar();
            //创建矩阵
            mat2 = create_matrix(m,n);
            input_matrix(&mat2);
            printf("\n");
        }else if(a == 3){//输出矩阵1
            if(flag1 == 0){
                printf("无效!请先创建矩阵\n\n");
            }else{
                //输出矩阵
                printf("输入的矩阵1:\n");
                print_matrix(&mat1);
                printf("\n");
            }
        }else if(a == 4){//输出矩阵2
            if(flag2 == 0){
                printf("无效!请先创建矩阵\n\n");
            }else{
                //输出矩阵
                printf("输入的矩阵2:\n");
                print_matrix(&mat2);
                printf("\n");
            }
        }else if(a == 5){//计算矩阵加法并覆写结果到矩阵1
            if(flag1 == 0 || flag2 == 0)
            {
                printf("请先创建矩阵!\n\n");
            }else if(mat1.cols == mat2.cols && mat1.rows == mat2.rows){
                matrix result;
                result = create_matrix(mat1.rows,mat1.cols);
                result = add_matrix(&mat1,&mat2);
                printf("\n");
                print_matrix(&result);
                printf("\n");
                //赋值并且释放内存...
                for(int i = 0;i < mat1.rows;i++)
                {
                    for(int j = 0;j < mat1.cols;j++)
                    {
                        mat1.data[i][j] = result.data[i][j];
                    }
                }
                free_matrix(&result);
            }else{
                printf("矩阵大小不合法!\n");
            }
        }else if(a == 6){//计算矩阵减法并覆写结果到矩阵1
            if(flag1 == 0 || flag2 == 0)
            {
                printf("请先创建矩阵!\n\n");
            }else if(mat1.cols == mat2.cols && mat1.rows == mat2.rows){
                matrix result;
                result = create_matrix(mat1.rows,mat1.cols);
                result = subtract_matrix(&mat1,&mat2);
                printf("\n");
                print_matrix(&result);
                printf("\n");
                //赋值并且释放内存...
                for(int i = 0;i < mat1.rows;i++)
                {
                    for(int j = 0;j < mat1.cols;j++)
                    {
                        mat1.data[i][j] = result.data[i][j];
                    }
                }
                free_matrix(&result);
            }else{
                printf("矩阵大小不合法!\n");
            }
        }else if(a == 7){//计算矩阵乘法并覆写结果到矩阵1
            if(flag1 == 0 || flag2 == 0)
            {
                printf("请先创建矩阵!\n\n");
            }else if(mat1.cols == mat2.rows){
                matrix result;
                result = create_matrix(mat1.rows,mat2.cols);
                result = multiple_matrix(&mat1,&mat2);
                printf("\n");
                print_matrix(&result);
                printf("\n");
                //赋值并且释放内存...
                mat1.cols = mat2.cols;
                for(int i = 0;i < mat1.rows;i++)
                {
                    for(int j = 0;j < mat2.cols;j++)
                    {
                        mat1.data[i][j] = result.data[i][j];
                    }
                }
                free_matrix(&result);
            }else{
                printf("矩阵大小不合法!\n");
            }
        }else if(a == 8){//输出矩阵1的转置矩阵并覆写结果到矩阵1
            if(flag1 == 0){
                printf("请先创建矩阵!\n\n");
            }else{
                matrix result;
                result = create_matrix(mat1.cols,mat1.rows);
                result = transpose_matrix(&mat1);
                mat1 = create_matrix(result.rows,result.cols);
                for(int i = 0;i < mat1.rows;i++)
                {
                    for(int j = 0;j < mat1.cols;j++)
                    {
                        mat1.data[i][j] = result.data[i][j];
                    }
                }
                free_matrix(&result);
                printf("矩阵1的转置:\n");
                print_matrix(&mat1);
                printf("\n");
            }
        }else if(a == 9){//将矩阵1化为最简阶梯行列式
            if(flag1 == 0){
                printf("请先创建矩阵!\n\n");
            }else{
                //输出化简结果
                printf("化简结果:\n");
                matrix result = simplify_matrix(&mat1);
                print_matrix(&result);
                printf("\n");
            }
        }else if(a == 10){//求矩阵1的逆矩阵并覆写结果到矩阵1
            if(flag1 == 0){
                printf("请先创建矩阵!\n\n");
            }else{
                matrix result = inverse_matrix(&mat1);
            }
        }else if(a == 11){
            if(flag1 == 0)
            {
                printf("请先创建矩阵!\n\n");
            }else if(mat1.rows == mat1.cols){
                fraction sum = create_fraction(1,1);
                sum = determinant_matrix(&mat1);
                printf("矩阵1的值为:");
                print_fraction(sum);
                printf("\n");
            }else{
                printf("矩阵大小错误!只有方阵才能求值!\n\n");
            }
        }else if(a == 12){
            if(flag1 == 0)
            {
                printf("请先创建矩阵!\n\n");
            }else if(mat1.rows == mat1.cols){

            }else{
                printf("矩阵大小错误!\n\n");
            }
        }else if(a == 0){//退出程序并释放内存
            printf("退出程序!\n");
            if(flag1 == 1)
                free_matrix(&mat1);
            if(flag2 ==1)
                free_matrix(&mat2);
            break;
        }else{//处理不合法的输入
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
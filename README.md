### 接口说明

---

1. 创建变量

    ```
    create typename(optional) VariableName
    ```

    * 实数：R
    * 矩阵：matrix(row,column)
    * 方阵：square matrix(order)
    * 线性方程组：equations(row, column)    here you should enter the augmented matrix
    * 二次型：quadratic form(order)

2. 输出计算结果

    ```
    print expressions
    ```

    * 四则运算
    * 矩阵求逆： `A^(-1)`
    * 矩阵转置： `A^(T)`
    * 乘方用`^`，开方用`^(1/n)`
    * `det()` 为行列式
    * `rank()`为矩阵的秩
    * 支持直接输入数字或输入变量名

3. 输出分析结果

    ```
    operationName(VariableName)
    ```

    * solve() 解线性方程组
    * analyse() 输出二次型的标准型、规范型以及相应的过渡矩阵
    * QR()直接输出QR分解的结果；QRq()返回QR分解中的Q，QRr()返回QR分解中的R
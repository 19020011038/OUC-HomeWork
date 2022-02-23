`timescale 1ns / 1ps
//*************************************************************************
//   > 文件名: multiply.v
//   > 描述  ：乘法器模块，低效率的迭代乘法算法，使用两个乘数绝对值参与运算
//   > 作者  : LOONGSON
//   > 日期  : 2016-04-14
//*************************************************************************
module multiply(              // 乘法器
    input         clk,        // 时钟
    input         mult_begin, // 乘法开始信号
    input  [31:0] mult_op1,   // 乘法源操作数1
    input  [31:0] mult_op2,   // 乘法源操作数2
    output [63:0] product,    // 乘积
    output        mult_end    // 乘法结束信号
);

    //乘法正在运算信号和结束信号
    reg mult_valid;
    assign mult_end = mult_valid & ~(|multiplier); //乘法结束信号：乘数全0
    always @(posedge clk)
    begin
        if (!mult_begin || mult_end)
        begin
            mult_valid <= 1'b0;
        end
        else
        begin
            mult_valid <= 1'b1;
        end
    end

    //两个源操作取绝对值，正数的绝对值为其本身，负数的绝对值为取反加1
    wire        op1_sign;      //操作数1的符号位
    wire        op2_sign;      //操作数2的符号位
    wire [31:0] op1_absolute;  //操作数1的绝对值
    wire [31:0] op2_absolute;  //操作数2的绝对值
    assign op1_sign = mult_op1[31];
    assign op2_sign = mult_op2[31];
    assign op1_absolute = op1_sign ? (~mult_op1+1) : mult_op1;
    assign op2_absolute = op2_sign ? (~mult_op2+1) : mult_op2;

    //加载被乘数，运算时每次左移一位
    reg  [63:0] multiplicand;
    always @ (posedge clk)
    begin
        if (mult_valid)
        begin    // 如果正在进行乘法，则被乘数每时钟左移一位
            multiplicand <= {multiplicand[62:0],1'b0};
        end
        else if (mult_begin) 
        begin   // 乘法开始，加载被乘数，为乘数1的绝对值
            multiplicand <= {32'd0,op1_absolute};
        end
    end

    //加载乘数，运算时每次右移一位
    reg  [31:0] multiplier;
    //请自行补充
    always @ (posedge clk)  
    begin
    if(mult_valid)
    begin       //如果正在进行乘法，则乘数每时钟右移一位
         multiplier <= {1'b0,multiplier[31:1]}; //相当于乘数y右移一位
    end
    else if(mult_begin)
    begin   //乘法开始，将乘数2的绝对值作为乘数
        multiplier <= op2_absolute;
        end
    end
    
    // 部分积：乘数末位为1，由被乘数左移得到；乘数末位为0，部分积为0
    wire [63:0] partial_product;
    //请自行补充
    assign partial_product = multiplier[0] ? multiplicand:64'd0;      
    //若此时y的最低位为1，则把x赋值给部分积，否则把0赋值给部分积
    
    //累加器
    reg [63:0] product_temp;
    //请自行补充
     always @ (posedge clk)  //clk信号从0变为1时，激发此段语句的执行，但语句的执行需要时间
    begin
        if (mult_valid)
        begin  //如果正在进行乘法，累加器中的值加上部分积
            product_temp <= product_temp + partial_product;
        end      
        else if (mult_begin)
        begin  //乘法开始时，加载全0进累加器
        product_temp <= 64'd0;
        end
     end

    //乘法结果的符号位和乘法结果
    reg product_sign;
    always @ (posedge clk)  // 乘积
    begin
        if (mult_valid)
        begin
              product_sign <= op1_sign ^ op2_sign;
        end
    end 
    //若乘法结果为负数，则需要对结果取反+1
    assign product = product_sign ? (~product_temp+1) : product_temp;
endmodule

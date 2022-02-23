`timescale 1ns / 1ps
//*************************************************************************
//   > 文件名: alu.v
//   > 描述  ：ALU模块，可做12种操作
//   > 作者  : LOONGSON
//   > 日期  : 2016-04-14
//*************************************************************************
module alu(
    input  [11:0] alu_control, 
    input  [31:0] alu_src1, 
    input  [31:0] alu_src2,
    output   [31:0] alu_result 
    );
    reg [31:0] alu_result;
    wire alu_add;   //加法
    wire alu_sub;   //减法
    wire alu_slt;   //有符号比较，小于置位
    wire alu_sltu;  //无符号比较，小于置位
    wire alu_and;   //按位与
    wire alu_nor;   //按位或非
    wire alu_or;    //按位或 
    wire alu_xor;   //按位异或
    wire alu_sll;   //逻辑左移
    wire alu_srl;   //逻辑右移
    wire alu_sra;   //算数右移
    wire alu_lui;   //高位加载

    assign alu_add  = alu_control[11];
    assign alu_sub  = alu_control[10];
    assign alu_slt  = alu_control[ 9];
    assign alu_sltu = alu_control[ 8];
    assign alu_and  = alu_control[ 7];
    assign alu_nor  = alu_control[ 6];
    assign alu_or   = alu_control[ 5];
    assign alu_xor  = alu_control[ 4];
    assign alu_sll  = alu_control[ 3];
    assign alu_srl  = alu_control[ 2];
    assign alu_sra  = alu_control[ 1];
    assign alu_lui  = alu_control[ 0];

    wire [31:0] add_sub_result; //加减结果，减法用加法来实现
    wire [31:0] slt_result;     //
    wire [31:0] sltu_result;    //
    wire [31:0] and_result;
    wire [31:0] nor_result;
    wire [31:0] or_result;
    wire [31:0] xor_result;
    wire [31:0] sll_result;
    wire [31:0] srl_result;
    wire [31:0] sra_result;     //
    wire [31:0] lui_result;

    wire signed [31:0] temp_src1;   //带符号数的临时变量
    assign temp_src1 = alu_src1;    //方便后面对alu_src1进行算数右移
    
    assign and_result = alu_src1 & alu_src2;        //按位与
    assign or_result  = alu_src1 | alu_src2;        //按位或
    assign nor_result = ~or_result;                 //或非
    assign xor_result = alu_src1 ^ alu_src2;        //异或
    assign lui_result = {alu_src2[15:0], 16'd0};    //高位加载，第二个操作数的低十六位加载到高十六位上
    assign sll_result = alu_src1 << alu_src2;       //逻辑左移
    assign srl_result = alu_src1 >> alu_src2;       //逻辑右移
    assign slt_result = adder_result[31] ? 1'b1 : 1'b0;   // 带符号数小于置位
    assign sltu_result = adder_cout ? 1'b0 : 1'b1;     //无符号数小于置位
    assign sra_result = temp_src1 >>> alu_src2;     //算数右移

    wire [31:0] adder_operand1;
    wire [31:0] adder_operand2;
    wire        adder_cin     ;
    wire [31:0] adder_result  ;
    wire        adder_cout    ;
    assign adder_operand1 = alu_src1; 
    assign adder_operand2 = alu_add ? alu_src2 : ~alu_src2;     //默认进行减法，为slt和sltu服务
    assign adder_cin      = ~alu_add;  //巧妙到我都以为代码有bug
    adder adder_module(     //调用加法模块
    .operand1(adder_operand1),
    .operand2(adder_operand2),
    .cin     (adder_cin     ),
    .result  (adder_result  ),
    .cout    (adder_cout    )
    );
    
    
assign add_sub_result = adder_result;

	always@(*)
	begin

        if(alu_add | alu_sub)  //如果是加法或者减法操作，则把加减法结果add_sub_result放入alu最终的运算结果alu_result中
            alu_result <= add_sub_result;
            else if(alu_slt)  //如果是有符号比较，则把有符号比较结果slt_result放入alu最终的运算结果alu_result中
            alu_result <= slt_result;
            else if(alu_sltu)  //如果是无符号比较，则把无符号比较结果sltu_result放入alu最终的运算结果alu_result中
            alu_result <= sltu_result;
            else if(alu_and)  //如果是按位与操作，则把按位与操作结果and_result放入alu最终的运算结果alu_result中
            alu_result <= and_result;
            else if(alu_nor)  //如果是按位或非操作，则把按位或非操作结果nor_result放入alu最终的运算结果alu_result中
            alu_result <= nor_result;
            else if(alu_or)  //如果是按位或操作，则把按位或操作结果or_result放入alu最终的运算结果alu_result中
            alu_result <= or_result;
            else if(alu_xor)  //如果是按位异或操作，则把按位异或操作结果xor_result放入alu最终的运算结果alu_result中
            alu_result <= xor_result;
            else if(alu_sll)  //如果是逻辑左移操作，则把逻辑左移的结果alu_sll放入alu最终的运算结果alu_result中
            alu_result <= sll_result;
            else if(alu_srl)  //如果是逻辑右移操作，则把逻辑右移的结果alu_srl放入alu最终的运算结果alu_result中
            alu_result <= srl_result;
            else if(alu_sra)  //如果是算术右移操作，则把算术右移的结果alu_sra放入alu最终的运算结果alu_result中
            alu_result <= sra_result;
            else if(alu_lui)  //如果是高位加载操作，则把高位加载操作的结果lui_result放入alu最终的运算结果alu_result中
            alu_result <= lui_result;
         
	end
	
	
endmodule

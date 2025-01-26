`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: Istanbul Technical University Computer Engineering Department 
// Engineer(s):
// Yusuf Sahin
// Mustafa Can Caliskan 
// 
// Create Date: 03/15/2024 09:01:26 PM
// Design Name: ALU System
// Project Name: BLG 222E Project 1
// 
//////////////////////////////////////////////////////////////////////////////////

module RegisterFile(
    input wire Clock,
    input wire [15:0] I,
    input wire [2:0] OutASel,
    input wire [2:0] OutBSel,
    input wire [2:0] FunSel,
    input wire [3:0] RegSel,
    input wire [3:0] ScrSel,
    output reg [15:0] OutA,
    output reg [15:0] OutB
);

    wire [15:0] R1_Out, R2_Out, R3_Out, R4_Out, S1_Out, S2_Out, S3_Out, S4_Out;
    wire R1_Enable, R2_Enable, R3_Enable, R4_Enable, S1_Enable, S2_Enable, S3_Enable, S4_Enable;
    
	assign R1_Enable = ~RegSel[3];
	assign R2_Enable = ~RegSel[2];
	assign R3_Enable = ~RegSel[1];
	assign R4_Enable = ~RegSel[0];
	assign S1_Enable = ~ScrSel[3];
	assign S2_Enable = ~ScrSel[2];
	assign S3_Enable = ~ScrSel[1];
	assign S4_Enable = ~ScrSel[0];
	
	
	Register R1(.Clock(Clock), .I(I), .Q(R1_Out), .FunSel(FunSel), .E(R1_Enable));
    Register R2(.Clock(Clock), .I(I), .Q(R2_Out), .FunSel(FunSel), .E(R2_Enable));
    Register R3(.Clock(Clock), .I(I), .Q(R3_Out), .FunSel(FunSel), .E(R3_Enable));
    Register R4(.Clock(Clock), .I(I), .Q(R4_Out), .FunSel(FunSel), .E(R4_Enable));
    
    Register S1(.Clock(Clock), .I(I), .Q(S1_Out), .FunSel(FunSel), .E(S1_Enable));
    Register S2(.Clock(Clock), .I(I), .Q(S2_Out), .FunSel(FunSel), .E(S2_Enable));
    Register S3(.Clock(Clock), .I(I), .Q(S3_Out), .FunSel(FunSel), .E(S3_Enable));
    Register S4(.Clock(Clock), .I(I), .Q(S4_Out), .FunSel(FunSel), .E(S4_Enable));

    always @(*) begin        
        case (OutASel)
            3'b000: OutA <= R1_Out;
            3'b001: OutA <= R2_Out;
            3'b010: OutA <= R3_Out;
            3'b011: OutA <= R4_Out;
            3'b100: OutA <= S1_Out;
            3'b101: OutA <= S2_Out;
            3'b110: OutA <= S3_Out;
            3'b111: OutA <= S4_Out;
        endcase
        
        case (OutBSel)
            3'b000: OutB <= R1_Out;
            3'b001: OutB <= R2_Out;
            3'b010: OutB <= R3_Out;
            3'b011: OutB <= R4_Out;
            3'b100: OutB <= S1_Out;
            3'b101: OutB <= S2_Out;
            3'b110: OutB <= S3_Out;
            3'b111: OutB <= S4_Out;
        endcase
    end

endmodule

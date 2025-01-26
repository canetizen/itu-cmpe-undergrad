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

module AddressRegisterFile(
	input wire Clock,
	input wire [15:0] I,
	input wire [1:0] OutCSel,
	input wire [1:0] OutDSel,
	input wire [2:0] FunSel,
	input wire [2:0] RegSel,
	output reg [15:0] OutC,
	output reg [15:0] OutD
);

	wire [15:0] PC_Out, AR_Out, SP_Out;
    wire PC_Enable, AR_Enable, SP_Enable;
	
	assign PC_Enable = ~RegSel[2];
	assign AR_Enable = ~RegSel[1];
	assign SP_Enable = ~RegSel[0];
    
    Register PC(.Clock(Clock), .I(I), .Q(PC_Out), .FunSel(FunSel), .E(PC_Enable));
    Register AR(.Clock(Clock), .I(I), .Q(AR_Out), .FunSel(FunSel), .E(AR_Enable));
    Register SP(.Clock(Clock), .I(I), .Q(SP_Out), .FunSel(FunSel), .E(SP_Enable));

	always @(*) begin
		case (OutCSel)
			2'b00: OutC <= PC_Out;
			2'b01: OutC <= PC_Out;
			2'b10: OutC <= AR_Out;
			2'b11: OutC <= SP_Out;
		endcase
		
		case (OutDSel)
			2'b00: OutD <= PC_Out;
			2'b01: OutD <= PC_Out;
			2'b10: OutD <= AR_Out;
			2'b11: OutD <= SP_Out;
		endcase
	end
	
endmodule
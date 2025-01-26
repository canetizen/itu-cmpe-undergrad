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

module ArithmeticLogicUnit(
	input wire Clock,
	input wire [15:0] A,
	input wire [15:0] B,
	input wire [4:0] FunSel,
	input wire WF,
	output reg [15:0] ALUOut,
	output reg [3:0] FlagsOut
);
	reg CarryFlagInput;
	
	always @(*) begin
		case (FunSel) // Zeroing 15:8 bits of ALUOut for 8-bit operations.
			5'h0, 5'h1, 5'h2, 5'h3, 5'h4, 5'h5, 5'h6, 5'h7, 5'h8, 5'h9, 5'ha, 5'hb, 5'hc, 5'hd, 5'he, 5'hf: ALUOut[15:8] <= 8'b0;
		endcase
	end
	
	always @(*) begin
		case (FunSel)
			// 8-bit Operations
			5'h0: ALUOut[7:0] <= A[7:0];
			5'h1: ALUOut[7:0] <= B[7:0];
			5'h2: ALUOut[7:0] <= ~A[7:0];
			5'h3: ALUOut[7:0] <= ~B[7:0];
			5'h4: {CarryFlagInput, ALUOut[7:0]} <= A[7:0] + B[7:0];
			5'h5: {CarryFlagInput, ALUOut[7:0]} = A[7:0] + B[7:0] + FlagsOut[2];
			5'h6: {CarryFlagInput, ALUOut[7:0]} = A[7:0] + ~B[7:0] + 8'h1;
			5'h7: ALUOut[7:0] <= A[7:0] & B[7:0];
			5'h8: ALUOut[7:0] <= A[7:0] | B[7:0];
			5'h9: ALUOut[7:0] <= A[7:0] ^ B[7:0];
			5'ha: ALUOut[7:0] <= ~(A[7:0] & B[7:0]);
			5'hb: {CarryFlagInput, ALUOut[7:0]} <= {A[7:0], 1'b0};
			5'hc: {ALUOut[7:0], CarryFlagInput} <= {1'b0, A[7:0]};
			5'hd: {ALUOut[7:0], CarryFlagInput} <= {A[7], A[7:0]};
			5'he: {CarryFlagInput, ALUOut[7:0]} <= {A[7:0], FlagsOut[2]};
			5'hf: {ALUOut[7:0], CarryFlagInput} <= {FlagsOut[2], A[7:0]};
			
			// 16-bit Operations
			5'h10: ALUOut <= A;		
			5'h11: ALUOut <= B;
			5'h12: ALUOut <= ~A;
			5'h13: ALUOut <= ~B;
			5'h14: {CarryFlagInput, ALUOut} <= A + B;
			5'h15: {CarryFlagInput, ALUOut} = A + B + FlagsOut[2];
			5'h16: {CarryFlagInput, ALUOut} = A + ~B + 16'h1;
			5'h17: ALUOut <= A & B;
			5'h18: ALUOut <= A | B;
			5'h19: ALUOut <= A ^ B;
			5'h1a: ALUOut <= ~(A & B);
			5'h1b: {CarryFlagInput, ALUOut} <= {A, 1'b0};
			5'h1c: {ALUOut, CarryFlagInput} <= {1'b0, A};
			5'h1d: {ALUOut, CarryFlagInput} <= {A[15], A};
			5'h1e: {CarryFlagInput, ALUOut} <= {A, FlagsOut[2]};
			5'h1f: {ALUOut, CarryFlagInput} <= {FlagsOut[2], A};
		endcase
	end
	
	always @(posedge Clock) begin
		if (WF) begin
			case (FunSel) // Z
				5'h0, 5'h1, 5'h2, 5'h3, 5'h4, 5'h5, 5'h6, 5'h7, 5'h8, 5'h9, 5'ha, 5'hb, 5'hc, 5'hd, 5'he, 5'hf: FlagsOut[3] <= (ALUOut[7:0] == 8'h0);
				5'h10, 5'h11, 5'h12, 5'h13, 5'h14, 5'h15, 5'h16, 5'h17, 5'h18, 5'h19, 5'h1a, 5'h1b, 5'h1c, 5'h1d, 5'h1e, 5'h1f: FlagsOut[3] <= (ALUOut == 16'h0);
			endcase
		
			case (FunSel) // C
				5'h4, 5'h5, 5'h6, 5'hb, 5'hc, 5'hd, 5'he, 5'hf, 5'h14, 5'h15, 5'h16, 5'h1b, 5'h1c, 5'h1d, 5'h1e, 5'h1f: FlagsOut[2] <= CarryFlagInput;
			endcase
			
			case (FunSel) // N
				5'h0, 5'h1, 5'h2, 5'h3, 5'h4, 5'h5, 5'h6, 5'h7, 5'h8, 5'h9, 5'ha, 5'hb, 5'hc, 5'he, 5'hf: FlagsOut[1] <= ALUOut[7];
				5'h10, 5'h11, 5'h12, 5'h13, 5'h14, 5'h15, 5'h16, 5'h17, 5'h18, 5'h19, 5'h1a, 5'h1b, 5'h1c, 5'h1e, 5'h1f: FlagsOut[1] <= ALUOut[15];
			endcase
			
			case (FunSel) // O
				// For addition
				5'h4, 5'h5: FlagsOut[0] <= ((A[7] & B[7] & ~ALUOut[7]) | (~A[7] & ~B[7] & ALUOut[7]));
				5'h14, 5'h15: FlagsOut[0] <= ((A[15] & B[15] & ~ALUOut[15]) | (~A[15] & ~B[15] & ALUOut[15]));
				
				// For subtraction
				5'h6: FlagsOut[0] <= ((A[7] & ~B[7] & ~ALUOut[7]) | (~A[7] & B[7] & ALUOut[7]));
				5'h16: FlagsOut[0] <= ((A[15] & ~B[15] & ~ALUOut[15]) | (~A[15] & B[15] & ALUOut[15]));
			endcase
		end
	end
	
endmodule
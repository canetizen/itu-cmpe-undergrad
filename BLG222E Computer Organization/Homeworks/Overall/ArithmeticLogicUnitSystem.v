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

module ArithmeticLogicUnitSystem(
	input wire Clock,
	input wire [2:0] RF_OutASel,
	input wire [2:0] RF_OutBSel,		
	input wire [2:0] RF_FunSel,
	input wire [3:0] RF_RegSel,
	input wire [3:0] RF_ScrSel,
	input wire [4:0] ALU_FunSel,
	input wire ALU_WF,
	input wire [1:0] ARF_OutCSel,
	input wire [1:0] ARF_OutDSel,
	input wire [2:0] ARF_FunSel,
	input wire [2:0] ARF_RegSel,
	input wire IR_LH,
	input wire IR_Write,
	input wire Mem_WR,
	input wire Mem_CS,
	input wire [1:0] MuxASel,
	input wire [1:0] MuxBSel,
	input wire MuxCSel
);
	reg [15:0] MuxAOut;
	reg [15:0] MuxBOut;
	reg [7:0] MuxCOut;
	wire [7:0] MemOut;
	wire [15:0] OutA;
	wire [15:0] OutB;
	wire [15:0] OutC;
	wire [15:0] ALUOut;
	wire [3:0] ALU_FlagsOut;
	wire [15:0] IROut;
	wire [15:0] Address;
	
	
	always @(*) begin
		case (MuxASel)
			2'b00: MuxAOut <= ALUOut;
			2'b01: MuxAOut <= OutC;
			2'b10: MuxAOut <= {8'b0, MemOut};
			2'b11: MuxAOut <= {8'b0, IROut[7:0]};
		endcase
		
		case (MuxBSel)
			2'b00: MuxBOut <= ALUOut;
			2'b01: MuxBOut <= OutC;
			2'b10: MuxBOut <= {8'b0, MemOut};
			2'b11: MuxBOut <= {8'b0, IROut[7:0]};
		endcase

		case (MuxCSel)
			1'b0: MuxCOut <= ALUOut[7:0];
			1'b1: MuxCOut <= ALUOut[15:8];
		endcase
	end	
	
    RegisterFile RF(.I(MuxAOut), .OutASel(RF_OutASel), .OutBSel(RF_OutBSel), .FunSel(RF_FunSel), .RegSel(RF_RegSel), .ScrSel(RF_ScrSel), .Clock(Clock), .OutA(OutA), .OutB(OutB));
					
	AddressRegisterFile ARF(.I(MuxBOut), .OutCSel(ARF_OutCSel), .OutDSel(ARF_OutDSel), .FunSel(ARF_FunSel), .RegSel(ARF_RegSel), .Clock(Clock), .OutC(OutC), .OutD(Address));
				
	InstructionRegister IR(.I(MemOut), .Write(IR_Write), .LH(IR_LH), .Clock(Clock), .IROut(IROut));
						
    ArithmeticLogicUnit ALU(.A(OutA), .B(OutB), .FunSel(ALU_FunSel), .WF(ALU_WF), .Clock(Clock), .ALUOut(ALUOut), .FlagsOut(ALU_FlagsOut));

	Memory MEM(.Address(Address), .Data(MuxCOut), .WR(Mem_WR), .CS(Mem_CS), .Clock(Clock), .MemOut(MemOut));

endmodule

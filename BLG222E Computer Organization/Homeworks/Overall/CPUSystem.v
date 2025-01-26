`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: Istanbul Technical University Computer Engineering Department 
// Engineer(s):
// Mustafa Can Caliskan
// Yusuf Sahin
// 
// Create Date: 04/22/2024 21:00:00 PM
// Design Name: CPU System
// Project Name: BLG 222E Project 2
// 
//////////////////////////////////////////////////////////////////////////////////

module TDecoder(
    input wire [2:0] Input,
    output reg [7:0] Output
);
    always @(*) begin
        Output = 8'b00000000;
        Output[Input] = 1'b1;
    end
endmodule

module DDecoder(
    input wire [5:0] Input,
    output reg [33:0] Output
);
    always @(*) begin
        Output = 34'b0;
        Output[Input] = 1'b1;
    end
endmodule

module TCounter(
	input wire Clock,
	input wire Reset,
    output reg[2:0] Output
);
    always @(posedge Clock) begin
		if(Reset) 
			Output <= 3'b0;
		else
			Output <= Output + 1'b1;
    end
endmodule

module ControlUnit(
	input wire[15:0] IROut,
	input wire[7:0] T,
	input wire Clock,
	input wire Reset,
    output reg[2:0] ARF_FunSel, ARF_RegSel,												
    output reg[2:0] RF_OutASel, RF_OutBSel, RF_FunSel,
    output reg[3:0] RF_RegSel, RF_ScrSel,
    output reg[4:0] ALU_FunSel,
    output reg IR_LH, IR_Write, Mem_WR, Mem_CS, ALU_WF, MuxCSel, TCounter_Reset,
    output reg[1:0] MuxASel, MuxBSel, ARF_OutCSel, ARF_OutDSel
);
	
	/*
		The term "Indicator" determines the type of register specified in the given instruction. 
		For example, the DREG_R1_Indicator will be logic 1 if the register specified as DREG in the given instruction is R1.
	*/								
	wire DREG_AR_Indicator = ~IROut[8] & IROut[7] & IROut[6];
	
	wire DREG_PC_Indicator = (~IROut[8] & ~IROut[7] & ~IROut[6])
							| (~IROut[8] & ~IROut[7] & IROut[6]);
							
	wire DREG_R1_Indicator = IROut[8] & ~IROut[7] & ~IROut[6];
	wire DREG_R2_Indicator = IROut[8] & ~IROut[7] & IROut[6];
	wire DREG_R3_Indicator = IROut[8] & IROut[7] & ~IROut[6];
	
	wire DREG_R4_Indicator = IROut[8] & IROut[7] & IROut[6];
	wire DREG_RF_Indicator = IROut[8]; 
	wire DREG_SP_Indicator = ~IROut[8] & IROut[7] & ~IROut[6];
	wire Rx_R1_Indicator = ~IROut[9] & ~IROut[8];
	
	wire Rx_R2_Indicator = ~IROut[9] & IROut[8];
	wire Rx_R3_Indicator = IROut[9] & ~IROut[8];
	
	wire Rx_R4_Indicator = IROut[9] & IROut[8];
	wire SREG1_AR_Indicator = ~IROut[5] & IROut[4] & IROut[3];
	
	wire SREG1_PC_Indicator = (~IROut[5] & ~IROut[4] & ~IROut[3])
							| (~IROut[5] & ~IROut[4] & IROut[3]);
							
	wire SREG1_R1_Indicator = IROut[5] & ~IROut[4] & ~IROut[3];
	wire SREG1_R2_Indicator = IROut[5] & ~IROut[4] & IROut[3];
	wire SREG1_R3_Indicator = IROut[5] & IROut[4] & ~IROut[3];
	
	wire SREG1_R4_Indicator = IROut[5] & IROut[4] & IROut[3];
	wire SREG1_RF_Indicator = IROut[5];
	
	wire SREG1_SP_Indicator = ~IROut[5] & IROut[4] & ~IROut[3];
	wire SREG2_AR_Indicator = ~IROut[2] & IROut[1] & IROut[0];
	
	wire SREG2_PC_Indicator = (~IROut[2] & ~IROut[1] & ~IROut[0])
							| (~IROut[2] & ~IROut[1] & IROut[0]);
							
	wire SREG2_R1_Indicator = IROut[2] & ~IROut[1] & ~IROut[0];
	wire SREG2_R2_Indicator = IROut[2] & ~IROut[1] & IROut[0];
	wire SREG2_R3_Indicator = IROut[2] & IROut[1] & ~IROut[0];
	
	wire SREG2_R4_Indicator = IROut[2] & IROut[1] & IROut[0];
	wire SREG2_RF_Indicator = IROut[2];
	
	wire SREG2_SP_Indicator = ~IROut[2] & IROut[1] & ~IROut[0];
	
	wire WF_Change_Indicator = IROut[9];
	wire Zero_Flag_Indicator = _ALUSystem.ALU.FlagsOut[3];			
		
	wire[2:0] TCounter_Output;

	wire[33:0] D;
	
	TCounter SC(.Clock(Clock), .Reset(TCounter_Reset), .Output(TCounter_Output));
	TDecoder SD(.Input(TCounter_Output), .Output(T));
	DDecoder OD(.Input(IROut[15:10]), .Output(D));
	
	/*
		Computer initialization conditions: 
			*) All PC and RF registers are reset to zero. 
			*) T is reset. 
			*) ALU_WF is disabled.
			*) Memory chip and IR are disabled.
	*/
	always @(posedge Reset) begin
		ALU_WF <= 1'b0;
		ARF_FunSel <= 3'b011;
		ARF_RegSel <= 3'b011;
		IR_Write <= 1'b0;
		Mem_CS <= 1'b1;
		RF_FunSel <= 3'b011;
		RF_RegSel <= 4'b0000;
		RF_ScrSel <= 4'b0000;
		TCounter_Reset <= 1'b1;
	end
	
	always @(T) begin
		// ################ Reset Selects ################									 
		if (T[0])									
			TCounter_Reset <= 1'b0; // T will continue counting. 
			
		else if (
			(D[0] & T[4]) 
			| (D[1] & T[2] & Zero_Flag_Indicator) 
			| (D[1] & T[4] & ~Zero_Flag_Indicator) 
			| (D[2] & T[2] & ~Zero_Flag_Indicator) 
			| (D[2] & T[4] & Zero_Flag_Indicator) 
			| ((D[5] | D[6]) & T[3])
			| ((D[7] | D[8] | D[9] | D[10] | D[11] | D[14] | D[24]) & T[3] & ~SREG1_RF_Indicator & ~DREG_RF_Indicator) 
			| ((D[7] | D[8] | D[9] | D[10] | D[11] | D[14] | D[24]) & T[3] & ~SREG1_RF_Indicator & DREG_RF_Indicator)
			| ((D[7] | D[8] | D[9] | D[10] | D[11] | D[14] | D[24]) & T[2] & SREG1_RF_Indicator & DREG_RF_Indicator) 
			| ((D[7] | D[8] | D[9] | D[10] | D[11] | D[14] | D[24]) & T[2] & SREG1_RF_Indicator & ~DREG_RF_Indicator)
			| ((D[12] | D[13] | D[15] | D[16] | D[21] | D[22] | D[23] | D[25] | D[26] | D[27] | D[28] | D[29]) & T[4])
			| (D[32] & T[2])
			| (D[18] & T[3])
			| (D[19] & T[3])
			| (D[31] & T[5])
			| (D[30] & T[5])
			| (D[33] & T[6])
			| (D[3] & T[3])
			| (D[4] & T[4])
			| ((D[17] | D[20]) & T[2])
		)
			TCounter_Reset <= 1'b1; // T will be reset.
		// #############################################
		
		// ################ RF Selects ################
		if (
			((D[5] | D[6]) & T[2] & SREG1_RF_Indicator & DREG_RF_Indicator & SREG1_R1_Indicator) 
			| ((D[5] | D[6]) & T[2] & SREG1_RF_Indicator & ~DREG_RF_Indicator & SREG1_R1_Indicator) 
			| ((D[7] | D[8] | D[9] | D[10] | D[11] | D[14] | D[24]) & T[2] & SREG1_RF_Indicator & DREG_RF_Indicator & SREG1_R1_Indicator)
			| ((D[7] | D[8] | D[9] | D[10] | D[11] | D[14] | D[24]) & T[2] & SREG1_RF_Indicator & ~DREG_RF_Indicator & SREG1_R1_Indicator)
			| ((D[12] | D[13] | D[15] | D[16] | D[21] | D[22] | D[23] | D[25] | D[26] | D[27] | D[28] | D[29]) & T[2] & SREG1_RF_Indicator & SREG1_R1_Indicator)
			| ((D[12] | D[13] | D[15] | D[16] | D[21] | D[22] | D[23] | D[25] | D[26] | D[27] | D[28] | D[29]) & T[3] & SREG2_RF_Indicator & SREG2_R1_Indicator)
			| (D[19] & T[2] & Rx_R1_Indicator)
			| (D[30] & T[5] & Rx_R1_Indicator)
			| (D[33] & T[5] & Rx_R1_Indicator)
			| (D[4] & T[2] & Rx_R1_Indicator)
		)
			RF_OutASel <= 3'b000; // R1 goes to ALU through A.
			
		else if (
			((D[5] | D[6]) & T[2] & SREG1_RF_Indicator & DREG_RF_Indicator & SREG1_R2_Indicator) 
			| ((D[5] | D[6]) & T[2] & SREG1_RF_Indicator & ~DREG_RF_Indicator & SREG1_R2_Indicator) 
			| ((D[7] | D[8] | D[9] | D[10] | D[11] | D[14] | D[24]) & T[2] & SREG1_RF_Indicator & DREG_RF_Indicator & SREG1_R2_Indicator)
			| ((D[7] | D[8] | D[9] | D[10] | D[11] | D[14] | D[24]) & T[2] & SREG1_RF_Indicator & ~DREG_RF_Indicator & SREG1_R2_Indicator)
			| ((D[12] | D[13] | D[15] | D[16] | D[21] | D[22] | D[23] | D[25] | D[26] | D[27] | D[28] | D[29]) & T[2] & SREG1_RF_Indicator & SREG1_R2_Indicator)
			| ((D[12] | D[13] | D[15] | D[16] | D[21] | D[22] | D[23] | D[25] | D[26] | D[27] | D[28] | D[29]) & T[3] & SREG2_RF_Indicator & SREG2_R2_Indicator)
			| (D[19] & T[2] & Rx_R2_Indicator)
			| (D[30] & T[5] & Rx_R2_Indicator)
			| (D[33] & T[5] & Rx_R2_Indicator)
			| (D[4] & T[2] & Rx_R2_Indicator)

		)
			RF_OutASel <= 3'b001; // R2 goes to ALU through A.
			
		else if (
			((D[5] | D[6]) & T[2] & SREG1_RF_Indicator & DREG_RF_Indicator & SREG1_R3_Indicator) 
			| ((D[5] | D[6]) & T[2] & SREG1_RF_Indicator & ~DREG_RF_Indicator & SREG1_R3_Indicator) 
			| ((D[7] | D[8] | D[9] | D[10] | D[11] | D[14] | D[24]) & T[2] & SREG1_RF_Indicator & DREG_RF_Indicator & SREG1_R3_Indicator)
			| ((D[7] | D[8] | D[9] | D[10] | D[11] | D[14] | D[24]) & T[2] & SREG1_RF_Indicator & ~DREG_RF_Indicator & SREG1_R3_Indicator)
			| ((D[12] | D[13] | D[15] | D[16] | D[21] | D[22] | D[23] | D[25] | D[26] | D[27] | D[28] | D[29]) & T[2] & SREG1_RF_Indicator & SREG1_R3_Indicator)
			| ((D[12] | D[13] | D[15] | D[16] | D[21] | D[22] | D[23] | D[25] | D[26] | D[27] | D[28] | D[29]) & T[3] & SREG2_RF_Indicator & SREG2_R3_Indicator)
			| (D[19] & T[2] & Rx_R3_Indicator)
			| (D[30] & T[5] & Rx_R3_Indicator)
			| (D[33] & T[5] & Rx_R3_Indicator)
			| (D[4] & T[2] & Rx_R3_Indicator)
		)
			RF_OutASel <= 3'b010; // R3 goes to ALU through A.	
			
		else if (
			((D[5] | D[6]) & T[2] & SREG1_RF_Indicator & DREG_RF_Indicator & SREG1_R4_Indicator) 
			| ((D[5] | D[6]) & T[2] & SREG1_RF_Indicator & ~DREG_RF_Indicator & SREG1_R4_Indicator) 
			| ((D[7] | D[8] | D[9] | D[10] | D[11] | D[14] | D[24]) & T[2] & SREG1_RF_Indicator & DREG_RF_Indicator & SREG1_R4_Indicator)
			| ((D[7] | D[8] | D[9] | D[10] | D[11] | D[14] | D[24]) & T[2] & SREG1_RF_Indicator & ~DREG_RF_Indicator & SREG1_R4_Indicator)
			| ((D[12] | D[13] | D[15] | D[16] | D[21] | D[22] | D[23] | D[25] | D[26] | D[27] | D[28] | D[29]) & T[2] & SREG1_RF_Indicator & SREG1_R4_Indicator)
			| ((D[12] | D[13] | D[15] | D[16] | D[21] | D[22] | D[23] | D[25] | D[26] | D[27] | D[28] | D[29]) & T[3] & SREG2_RF_Indicator & SREG2_R4_Indicator)
			| (D[19] & T[2] & Rx_R4_Indicator)
			| (D[30] & T[5] & Rx_R4_Indicator)
			| (D[33] & T[5] & Rx_R4_Indicator)
			| (D[4] & T[2] & Rx_R4_Indicator)
		)
			RF_OutASel <= 3'b011; // R4 goes to ALU through A.

		else if (
			T[1] 
			| (D[0] & T[4]) 
			| (D[1] & T[4] & ~Zero_Flag_Indicator) 
			| (D[2] & T[4] & Zero_Flag_Indicator) 
			| ((D[5] | D[6]) & T[3] & SREG1_RF_Indicator & DREG_RF_Indicator) 
			| ((D[5] | D[6]) & T[3] & SREG1_RF_Indicator & ~DREG_RF_Indicator) 
			| ((D[7] | D[8] | D[9] | D[10] | D[11] | D[14] | D[24]) & T[3] & ~SREG1_RF_Indicator & ~DREG_RF_Indicator)
			| ((D[7] | D[8] | D[9] | D[10] | D[11] | D[14] | D[24]) & T[3] & ~SREG1_RF_Indicator & DREG_RF_Indicator)
			| ((D[12] | D[13] | D[15] | D[16] | D[21] | D[22] | D[23] | D[25] | D[26] | D[27] | D[28] | D[29]) & T[4] & ~DREG_RF_Indicator)
			| ((D[12] | D[13] | D[15] | D[16] | D[21] | D[22] | D[23] | D[25] | D[26] | D[27] | D[28] | D[29]) & T[4] & DREG_RF_Indicator)
			| (D[30] & T[3])
			| (D[33] & T[4])
		)
			RF_OutASel <= 3'b100; // S1 goes to ALU through A.
	
		if (
			(D[0] & T[4]) 
			| (D[1] & T[4] & ~Zero_Flag_Indicator) 
			| (D[2] & T[4] & Zero_Flag_Indicator)
			| ((D[12] | D[13] | D[15] | D[16] | D[21] | D[22] | D[23] | D[25] | D[26] | D[27] | D[28] | D[29]) & T[4] & ~DREG_RF_Indicator)
			| ((D[12] | D[13] | D[15] | D[16] | D[21] | D[22] | D[23] | D[25] | D[26] | D[27] | D[28] | D[29]) & T[4] & DREG_RF_Indicator)
			| (D[33] & T[4])
		)
			RF_OutBSel <= 3'b101; // S2 goes to ALU through B.
			
		if (
			(D[0] & T[4]) 
			| (D[1] & T[4] & ~Zero_Flag_Indicator) 
			| (D[2] & T[4] & Zero_Flag_Indicator) 
			| T[0]				
		)
			RF_ScrSel <= 4'b0000; // ALL S registers in RF are enabled.
			
		else if (
			(D[0] & T[2]) 
			| (D[1] & T[2] & ~Zero_Flag_Indicator) 
			| (D[2] & T[2] & Zero_Flag_Indicator) 
			| ((D[7] | D[8] | D[9] | D[10] | D[11] | D[14] | D[24]) & T[2] & ~SREG1_RF_Indicator & ~DREG_RF_Indicator) 
			| ((D[7] | D[8] | D[9] | D[10] | D[11] | D[14] | D[24]) & T[2] & ~SREG1_RF_Indicator & DREG_RF_Indicator)
			| ((D[12] | D[13] | D[15] | D[16] | D[21] | D[22] | D[23] | D[25] | D[26] | D[27] | D[28] | D[29]) & T[2] & ~SREG1_RF_Indicator)
			| ((D[12] | D[13] | D[15] | D[16] | D[21] | D[22] | D[23] | D[25] | D[26] | D[27] | D[28] | D[29]) & T[2] & SREG1_RF_Indicator)
			| (D[30] & T[2])
			| (D[33] & T[2])
		)
			RF_ScrSel <= 4'b0111; // S1 in RF is enabled.
			
		else if (
			(D[0] & T[3]) 
			| (D[1] & T[3] & ~Zero_Flag_Indicator) 
			| (D[2] & T[3] & Zero_Flag_Indicator)
			| ((D[12] | D[13] | D[15] | D[16] | D[21] | D[22] | D[23] | D[25] | D[26] | D[27] | D[28] | D[29]) & T[3] & ~SREG2_RF_Indicator)
			| ((D[12] | D[13] | D[15] | D[16] | D[21] | D[22] | D[23] | D[25] | D[26] | D[27] | D[28] | D[29]) & T[3] & SREG2_RF_Indicator)
			| (D[33] & T[3])
		)
			RF_ScrSel <= 4'b1011; // S2 in RF is enabled.
			
		else if (
			T[1]
			| ((D[12] | D[13] | D[15] | D[16] | D[21] | D[22] | D[23] | D[25] | D[26] | D[27] | D[28] | D[29]) & T[4] & ~SREG1_RF_Indicator)
			| ((D[12] | D[13] | D[15] | D[16] | D[21] | D[22] | D[23] | D[25] | D[26] | D[27] | D[28] | D[29]) & T[4] & SREG1_RF_Indicator)
			
		)
			RF_ScrSel <= 4'b1111; // ALL S registers in RF are disabled.
			
		if (
			(D[6] & T[3] & ~SREG1_RF_Indicator & DREG_RF_Indicator) 
			| (D[6] & T[3] & SREG1_RF_Indicator & DREG_RF_Indicator)
		)
			RF_FunSel <= 3'b000; // Decrement operation for enabled RF registers.
			
		else if (
			(D[5] & T[3] & ~SREG1_RF_Indicator & DREG_RF_Indicator) 
			| (D[5] & T[3] & SREG1_RF_Indicator & DREG_RF_Indicator)
		)
			RF_FunSel <= 3'b001; // Increment operation for enabled RF registers.

		else if (
			(D[0] & T[2]) 
			| (D[0] & T[3]) 
			| (D[1] & T[2] & ~Zero_Flag_Indicator) 
			| (D[1] & T[3] & ~Zero_Flag_Indicator) 
			| (D[2] & T[2] & Zero_Flag_Indicator) 
			| (D[2] & T[3] & Zero_Flag_Indicator) 
			| ((D[5] | D[6]) & T[2] & ~SREG1_RF_Indicator & DREG_RF_Indicator) 
			| ((D[5] | D[6]) & T[2] & SREG1_RF_Indicator & DREG_RF_Indicator)
			| ((D[7] | D[8] | D[9] | D[10] | D[11] | D[14] | D[24]) & T[2] & ~SREG1_RF_Indicator & ~DREG_RF_Indicator) 
			| ((D[7] | D[8] | D[9] | D[10] | D[11] | D[14] | D[24]) & T[2] & ~SREG1_RF_Indicator & DREG_RF_Indicator) 
			| ((D[7] | D[8] | D[9] | D[10] | D[11] | D[14] | D[24]) & T[2] & SREG1_RF_Indicator & DREG_RF_Indicator)
			| ((D[12] | D[13] | D[15] | D[16] | D[21] | D[22] | D[23] | D[25] | D[26] | D[27] | D[28] | D[29]) & T[2] & ~SREG1_RF_Indicator)
			| ((D[12] | D[13] | D[15] | D[16] | D[21] | D[22] | D[23] | D[25] | D[26] | D[27] | D[28] | D[29]) & T[3] & ~SREG2_RF_Indicator)
			| ((D[12] | D[13] | D[15] | D[16] | D[21] | D[22] | D[23] | D[25] | D[26] | D[27] | D[28] | D[29]) & T[2] & SREG1_RF_Indicator)
			| ((D[12] | D[13] | D[15] | D[16] | D[21] | D[22] | D[23] | D[25] | D[26] | D[27] | D[28] | D[29]) & T[3] & SREG2_RF_Indicator)
			| ((D[12] | D[13] | D[15] | D[16] | D[21] | D[22] | D[23] | D[25] | D[26] | D[27] | D[28] | D[29]) & T[4] & DREG_RF_Indicator)
			| (D[32] & T[2])
			| (D[30] & T[2])	
			| (D[33] & T[2])
			| (D[33] & T[3])		
		)
			RF_FunSel <= 3'b010; // Load operation for enabled RF registers.
				
		else if (
			(D[0] & T[4]) 
			| (D[1] & T[4] & ~Zero_Flag_Indicator) 
			| (D[2] & T[4] & Zero_Flag_Indicator) 
			| ((D[7] | D[8] | D[9] | D[10] | D[11] | D[14] | D[24]) & T[3] & ~SREG1_RF_Indicator & ~DREG_RF_Indicator) 
			| T[0]
		)
			RF_FunSel <= 3'b011; // Clear operation for enabled RF registers.

		else if (
			(D[20] & T[2])
			| (D[18] & T[2])
			| (D[3] & T[2])
		)
			RF_FunSel <= 3'b101; // Only write low (7-0) operation for enabled RF registers.
			
		else if (
			(D[17] & T[2])
			| (D[18] & T[3])
			| (D[3] & T[3])
		)
			RF_FunSel <= 3'b110; // Only write high (15-8) operation for enabled RF registers

		if (T[0])
			RF_RegSel <= 4'b1111; // ALL R in RF are disabled.
			
		if (
			((D[5] | D[6]) & T[2] & ~SREG1_RF_Indicator & DREG_RF_Indicator & DREG_R1_Indicator) 
			| ((D[5] | D[6]) & T[2] & SREG1_RF_Indicator & DREG_RF_Indicator & DREG_R1_Indicator) 
			| ((D[7] | D[8] | D[9] | D[10] | D[11] | D[14] | D[24]) & T[3] & ~SREG1_RF_Indicator & DREG_RF_Indicator & DREG_R1_Indicator)
			| ((D[7] | D[8] | D[9] | D[10] | D[11] | D[14] | D[24]) & T[2] & SREG1_RF_Indicator & DREG_RF_Indicator & DREG_R1_Indicator)
			| ((D[12] | D[13] | D[15] | D[16] | D[21] | D[22] | D[23] | D[25] | D[26] | D[27] | D[28] | D[29]) & T[4] & DREG_RF_Indicator & DREG_R1_Indicator)
			| (D[32] & T[2] & Rx_R1_Indicator)
			| (D[18] & T[2] & Rx_R1_Indicator)
			| (D[3] & T[2] & Rx_R1_Indicator)
			| ((D[17] | D[20]) & T[2] & Rx_R1_Indicator)
		)
			RF_RegSel <= 4'b0111; // R1 in RF is enabled.
			
		else if (
			((D[5] | D[6]) & T[2] & ~SREG1_RF_Indicator & DREG_RF_Indicator & DREG_R2_Indicator) 
			| ((D[5] | D[6]) & T[2] & SREG1_RF_Indicator & DREG_RF_Indicator & DREG_R2_Indicator) 
			| ((D[7] | D[8] | D[9] | D[10] | D[11] | D[14] | D[24]) & T[3] & ~SREG1_RF_Indicator & DREG_RF_Indicator & DREG_R2_Indicator)
			| ((D[7] | D[8] | D[9] | D[10] | D[11] | D[14] | D[24]) & T[2] & SREG1_RF_Indicator & DREG_RF_Indicator & DREG_R2_Indicator)
			| ((D[12] | D[13] | D[15] | D[16] | D[21] | D[22] | D[23] | D[25] | D[26] | D[27] | D[28] | D[29]) & T[4] & DREG_RF_Indicator & DREG_R2_Indicator)
			| (D[32] & T[2] & Rx_R2_Indicator)
			| (D[18] & T[2] & Rx_R2_Indicator)
			| (D[3] & T[2] & Rx_R2_Indicator)
			| ((D[17] | D[20]) & T[2] & Rx_R2_Indicator)
		)
			RF_RegSel <= 4'b1011; // R2 in RF is enabled.
			
		else if (
			((D[5] | D[6]) & T[2] & ~SREG1_RF_Indicator & DREG_RF_Indicator & DREG_R3_Indicator) 
			| ((D[5] | D[6]) & T[2] & SREG1_RF_Indicator & DREG_RF_Indicator & DREG_R3_Indicator)
			| ((D[7] | D[8] | D[9] | D[10] | D[11] | D[14] | D[24]) & T[3] & ~SREG1_RF_Indicator & DREG_RF_Indicator & DREG_R3_Indicator) 
			| ((D[7] | D[8] | D[9] | D[10] | D[11] | D[14] | D[24]) & T[2] & SREG1_RF_Indicator & DREG_RF_Indicator & DREG_R3_Indicator)
			| ((D[12] | D[13] | D[15] | D[16] | D[21] | D[22] | D[23] | D[25] | D[26] | D[27] | D[28] | D[29]) & T[4] & DREG_RF_Indicator & DREG_R3_Indicator)
			| (D[32] & T[2] & Rx_R3_Indicator)
			| (D[18] & T[2] & Rx_R3_Indicator)
			| (D[3] & T[2] & Rx_R3_Indicator)
			| ((D[17] | D[20]) & T[2] & Rx_R3_Indicator)
		)
			RF_RegSel <= 4'b1101; // R3 in RF is enabled.
			
		else if (
			((D[5] | D[6]) & T[2] & ~SREG1_RF_Indicator & DREG_RF_Indicator & DREG_R4_Indicator) 
			| ((D[5] | D[6]) & T[2] & SREG1_RF_Indicator & DREG_RF_Indicator & DREG_R4_Indicator)
			| ((D[7] | D[8] | D[9] | D[10] | D[11] | D[14] | D[24]) & T[3] & ~SREG1_RF_Indicator & DREG_RF_Indicator & DREG_R4_Indicator) 
			| ((D[7] | D[8] | D[9] | D[10] | D[11] | D[14] | D[24]) & T[2] & SREG1_RF_Indicator & DREG_RF_Indicator & DREG_R4_Indicator)
			| ((D[12] | D[13] | D[15] | D[16] | D[21] | D[22] | D[23] | D[25] | D[26] | D[27] | D[28] | D[29]) & T[4] & DREG_RF_Indicator & DREG_R4_Indicator)
			| (D[32] & T[2] & Rx_R4_Indicator)
			| (D[18] & T[2] & Rx_R4_Indicator)
			| (D[3] & T[2] & Rx_R4_Indicator)
			| ((D[17] | D[20]) & T[2] & Rx_R4_Indicator)
		)
			RF_RegSel <= 4'b1110; // R4 in RF is enabled.
		// #############################################
		
		// ################ ARF Selects ################
		if (
			(D[0] & T[3]) 
			| (D[1] & T[3] & ~Zero_Flag_Indicator) 
			| (D[2] & T[3] & Zero_Flag_Indicator) 
			| ((D[5] | D[6]) & T[2] & ~SREG1_RF_Indicator & ~DREG_RF_Indicator & SREG1_PC_Indicator) 
			| ((D[5] | D[6]) & T[2] & ~SREG1_RF_Indicator & DREG_RF_Indicator & SREG1_PC_Indicator)
			| ((D[7] | D[8] | D[9] | D[10] | D[11] | D[14] | D[24]) & T[2] & ~SREG1_RF_Indicator & ~DREG_RF_Indicator & SREG1_PC_Indicator) 
			| ((D[7] | D[8] | D[9] | D[10] | D[11] | D[14] | D[24]) & T[2] & ~SREG1_RF_Indicator & DREG_RF_Indicator & SREG1_PC_Indicator)
			| ((D[12] | D[13] | D[15] | D[16] | D[21] | D[22] | D[23] | D[25] | D[26] | D[27] | D[28] | D[29]) & T[2] & ~SREG1_RF_Indicator & SREG1_PC_Indicator)
			| ((D[12] | D[13] | D[15] | D[16] | D[21] | D[22] | D[23] | D[25] | D[26] | D[27] | D[28] | D[29]) & T[3] & ~SREG2_RF_Indicator & SREG2_PC_Indicator)
			| (D[30] & T[2])
		)				
			ARF_OutCSel <= 2'b00; // PC goes to MuxA and MuxB through OutC.
			
		else if (
			((D[5] | D[6]) & T[2] & ~SREG1_RF_Indicator & ~DREG_RF_Indicator & SREG1_AR_Indicator) 
			| ((D[5] | D[6]) & T[2] & ~SREG1_RF_Indicator & DREG_RF_Indicator & SREG1_AR_Indicator)
			| ((D[7] | D[8] | D[9] | D[10] | D[11] | D[14] | D[24]) & T[2] & ~SREG1_RF_Indicator & ~DREG_RF_Indicator & SREG1_AR_Indicator) 
			| ((D[7] | D[8] | D[9] | D[10] | D[11] | D[14] | D[24]) & T[2] & ~SREG1_RF_Indicator & DREG_RF_Indicator & SREG1_AR_Indicator)
			| ((D[12] | D[13] | D[15] | D[16] | D[21] | D[22] | D[23] | D[25] | D[26] | D[27] | D[28] | D[29]) & T[2] & ~SREG1_RF_Indicator & SREG1_AR_Indicator)
			| ((D[12] | D[13] | D[15] | D[16] | D[21] | D[22] | D[23] | D[25] | D[26] | D[27] | D[28] | D[29]) & T[3] & ~SREG2_RF_Indicator & SREG2_AR_Indicator)
			| (D[33] & T[2])
		)
			ARF_OutCSel <= 2'b10; // AR goes to MuxA and MuxB through OutC.
			
		else if (
			((D[5] | D[6]) & T[2] & ~SREG1_RF_Indicator & ~DREG_RF_Indicator & SREG1_SP_Indicator) 
			| ((D[5] | D[6]) & T[2] & ~SREG1_RF_Indicator & DREG_RF_Indicator & SREG1_SP_Indicator) 
			| ((D[7] | D[8] | D[9] | D[10] | D[11] | D[14] | D[24]) & T[2] & ~SREG1_RF_Indicator & DREG_RF_Indicator & SREG1_SP_Indicator)
			| ((D[7] | D[8] | D[9] | D[10] | D[11] | D[14] | D[24]) & T[2] & ~SREG1_RF_Indicator & ~DREG_RF_Indicator & SREG1_SP_Indicator)
			| ((D[12] | D[13] | D[15] | D[16] | D[21] | D[22] | D[23] | D[25] | D[26] | D[27] | D[28] | D[29]) & T[2] & ~SREG1_RF_Indicator & SREG1_SP_Indicator)
			| ((D[12] | D[13] | D[15] | D[16] | D[21] | D[22] | D[23] | D[25] | D[26] | D[27] | D[28] | D[29]) & T[3] & ~SREG2_RF_Indicator & SREG2_SP_Indicator)
		)
			ARF_OutCSel <= 2'b11; // SP goes to MuxA and MuxB through OutC.
	
		if (
			T[0] 
			| T[1]
		)
			ARF_OutDSel <= 2'b00; // PC goes to address select of memory chip through OutD.
			
		else if (
			(D[31] & T[2])
			| (D[30] & T[3])
			| (D[3] & T[2])
			| (D[4] & T[2])
		)
			ARF_OutDSel <= 2'b11; // SP goes to address select of memory chip through OutD.
			
		else if (
			(D[18] & T[2])
			| (D[19] & T[2])
			| (D[33] & T[5])
		)
			ARF_OutDSel <= 2'b10; // AR goes to address select of memory chip through OutD.
		
		/*
			At time T[2], the default behavior is to disable ARF to stop the PC increment from previous clock pulses. 
			However, there are cases where other registers in ARF are enabled at time T[2]. 
			Therefore, we NAND these situations with the default behavior of T[2].
		*/		
		if (
			(T[2] 
			& ~((D[5] | D[6]) & T[2] & ~SREG1_RF_Indicator & ~DREG_RF_Indicator) 
			& ~((D[5] | D[6]) & T[2] & SREG1_RF_Indicator & ~DREG_RF_Indicator) 
			& ~((D[7] | D[8] | D[9] | D[10] | D[11] | D[14] | D[24]) & T[2] & SREG1_RF_Indicator & ~DREG_RF_Indicator)
			& ~(D[18] & T[2])
			& ~(D[19] & T[2])
			& ~(D[31] & T[2])
			& ~(D[3] & T[2])
			& ~(D[4] & T[2]))
		)									
			ARF_RegSel <= 3'b111; // ALL registers in ARF are disabled.		
			
		else if (
			T[0] 
			| T[1] 
			| (D[0] & T[4]) 
			| (D[1] & T[4] & ~Zero_Flag_Indicator) 
			| (D[2] & T[4] & Zero_Flag_Indicator) 
			| ((D[5] | D[6]) & T[2] & ~SREG1_RF_Indicator & ~DREG_RF_Indicator & DREG_PC_Indicator) 
			| ((D[5] | D[6]) & T[2] & SREG1_RF_Indicator & ~DREG_RF_Indicator & DREG_PC_Indicator) 
			| ((D[7] | D[8] | D[9] | D[10] | D[11] | D[14] | D[24]) & T[3] & ~SREG1_RF_Indicator & ~DREG_RF_Indicator & DREG_PC_Indicator)
			| ((D[7] | D[8] | D[9] | D[10] | D[11] | D[14] | D[24]) & T[2] & SREG1_RF_Indicator & ~DREG_RF_Indicator & DREG_PC_Indicator)
			| ((D[12] | D[13] | D[15] | D[16] | D[21] | D[22] | D[23] | D[25] | D[26] | D[27] | D[28] | D[29]) & T[4] & ~DREG_RF_Indicator & DREG_PC_Indicator)
			| (D[31] & T[2])
			| (D[31] & T[4])
			| (D[30] & T[5])
		)
			ARF_RegSel <= 3'b011; // PC is enabled.
			
		else if (
			((D[5] | D[6]) & T[2] & ~SREG1_RF_Indicator & ~DREG_RF_Indicator & DREG_AR_Indicator)
			| ((D[5] | D[6]) & T[2] & SREG1_RF_Indicator & ~DREG_RF_Indicator & DREG_AR_Indicator)  
			| ((D[7] | D[8] | D[9] | D[10] | D[11] | D[14] | D[24]) & T[3] & ~SREG1_RF_Indicator & ~DREG_RF_Indicator & DREG_AR_Indicator)
			| ((D[7] | D[8] | D[9] | D[10] | D[11] | D[14] | D[24]) & T[2] & SREG1_RF_Indicator & ~DREG_RF_Indicator & DREG_AR_Indicator)
			| ((D[12] | D[13] | D[15] | D[16] | D[21] | D[22] | D[23] | D[25] | D[26] | D[27] | D[28] | D[29]) & T[4] & ~DREG_RF_Indicator & DREG_AR_Indicator)
			| (D[18] & T[2])
			| (D[19] & T[2])
			| (D[33] & T[4])
		)
			ARF_RegSel <= 3'b101; // AR is enabled.
			
		else if (
			((D[5] | D[6]) & T[2] & ~SREG1_RF_Indicator & ~DREG_RF_Indicator & DREG_SP_Indicator)
			| ((D[5] | D[6]) & T[2] & SREG1_RF_Indicator & ~DREG_RF_Indicator & DREG_SP_Indicator) 
			| ((D[7] | D[8] | D[9] | D[10] | D[11] | D[14] | D[24]) & T[3] & ~SREG1_RF_Indicator & ~DREG_RF_Indicator & DREG_SP_Indicator)
			| ((D[7] | D[8] | D[9] | D[10] | D[11] | D[14] | D[24]) & T[2] & SREG1_RF_Indicator & ~DREG_RF_Indicator & DREG_SP_Indicator)
			| ((D[12] | D[13] | D[15] | D[16] | D[21] | D[22] | D[23] | D[25] | D[26] | D[27] | D[28] | D[29]) & T[4] & ~DREG_RF_Indicator & DREG_SP_Indicator)
			| (D[31] & T[3])
			| (D[30] & T[3])
			| (D[3] & T[2])
			| (D[4] & T[2])
			| (D[31] & T[5])
		)
			ARF_RegSel <= 3'b110; // SP is enabled.
			
		if (
			(D[6] & T[3] & ~SREG1_RF_Indicator & ~DREG_RF_Indicator) 
			| (D[6] & T[3] & SREG1_RF_Indicator & ~DREG_RF_Indicator)
			| (D[4] & T[3])
			| (D[18] & T[3])
			| (D[19] & T[3])
			| (D[33] & T[6])
		)
			ARF_FunSel <= 3'b000; // Decrement operation for enabled ARF registers.

		else if (
			T[0] 
			| T[1] 
			| (D[5] & T[3] & ~SREG1_RF_Indicator & ~DREG_RF_Indicator) 
			| (D[5] & T[3] & SREG1_RF_Indicator & ~DREG_RF_Indicator)
			| (D[18] & T[2])
			| (D[19] & T[2])
			| (D[31] & T[3])
			| (D[30] & T[3])
			| (D[33] & T[5])
			| (D[3] & T[2])		
			| (D[4] & T[2])
			| (D[31] & T[5])			
		)
			ARF_FunSel <= 3'b001; // Increment operation for enabled ARF registers.
			
		else if (
			(D[0] & T[4]) 
			| (D[1] & T[4] & ~Zero_Flag_Indicator) 
			| (D[2] & T[4] & Zero_Flag_Indicator) 
			| ((D[5] | D[6]) & T[2] & ~SREG1_RF_Indicator & ~DREG_RF_Indicator)
			| ((D[5] | D[6]) & T[2] & SREG1_RF_Indicator & ~DREG_RF_Indicator) 
			| ((D[7] | D[8] | D[9] | D[10] | D[11] | D[14] | D[24]) & T[3] & ~SREG1_RF_Indicator & ~DREG_RF_Indicator)
			| ((D[7] | D[8] | D[9] | D[10] | D[11] | D[14] | D[24]) & T[2] & SREG1_RF_Indicator & ~DREG_RF_Indicator)
			| ((D[12] | D[13] | D[15] | D[16] | D[21] | D[22] | D[23] | D[25] | D[26] | D[27] | D[28] | D[29]) & T[4] & ~DREG_RF_Indicator)
			| (D[30] & T[5])
			| (D[33] & T[4])			
		)
			ARF_FunSel <= 3'b010; // Load operation for enabled ARF registers.
			
		else if (
			(D[31] & T[2])			
		)
			ARF_FunSel <= 3'b101; // Only write low (7-0) operation for enabled ARF registers.
			
		else if (
			(D[31] & T[4])
		)
			ARF_FunSel <= 3'b110; // Only write low (15-8) operation for enabled ARF registers.
			
		// #############################################
		
		// ################ ALU Selects ################
		if (
			T[1] 
			| ((D[5] | D[6]) & T[2] & SREG1_RF_Indicator & DREG_RF_Indicator) 
			| ((D[5] | D[6]) & T[2] & SREG1_RF_Indicator & ~DREG_RF_Indicator)
			| ((D[12] | D[13] | D[15] | D[16] | D[21] | D[22] | D[23] | D[25] | D[26] | D[27] | D[28] | D[29]) & T[2] & SREG1_RF_Indicator)
			| ((D[12] | D[13] | D[15] | D[16] | D[21] | D[22] | D[23] | D[25] | D[26] | D[27] | D[28] | D[29]) & T[3] & SREG2_RF_Indicator)
			| (D[19] & T[2])
			| (D[30] & T[3])
			| (D[33] & T[5])
			| (D[4] & T[2])
		)
			ALU_FunSel <= 5'b10000; // A
			
		else if (
			(D[0] & T[4]) 
			| (D[1] & T[4] & ~Zero_Flag_Indicator) 
			| (D[2] & T[4] & Zero_Flag_Indicator)
			| (D[33] & T[4])
			| (D[21] & T[4] & ~DREG_RF_Indicator)
			| (D[21] & T[4] & DREG_RF_Indicator)
			| (D[25] & T[4] & ~DREG_RF_Indicator)
			| (D[25] & T[4] & DREG_RF_Indicator)
		)
			ALU_FunSel <= 5'b10100; // A + B
			
		else if (
			(D[22] & T[4] & ~DREG_RF_Indicator)
			| (D[22] & T[4] & DREG_RF_Indicator)
		)
			ALU_FunSel <= 5'b10101; // A + B + Carry
			
		else if (
			(D[23] & T[4] & ~DREG_RF_Indicator)
			| (D[23] & T[4] & DREG_RF_Indicator)
			| (D[26] & T[4] & ~DREG_RF_Indicator)
			| (D[26] & T[4] & DREG_RF_Indicator)
		)
			ALU_FunSel <= 5'b10110; // A - B
			
		else if (
			(D[7] & T[3] & ~SREG1_RF_Indicator & ~DREG_RF_Indicator) 
			| (D[7] & T[3] & ~SREG1_RF_Indicator & DREG_RF_Indicator) 
			| (D[7] & T[2] & SREG1_RF_Indicator & DREG_RF_Indicator) 
			| (D[7] & T[2] & SREG1_RF_Indicator & ~DREG_RF_Indicator)
		)
			ALU_FunSel <= 5'b11011; // lSL A
			
		else if (
			(D[8] & T[3] & ~SREG1_RF_Indicator & ~DREG_RF_Indicator) 
			| (D[8] & T[3] & ~SREG1_RF_Indicator & DREG_RF_Indicator) 
			| (D[8] & T[2] & SREG1_RF_Indicator & DREG_RF_Indicator) 
			| (D[8] & T[2] & SREG1_RF_Indicator & ~DREG_RF_Indicator)
		)
			ALU_FunSel <= 5'b11100; // LSR A
			
		else if (
			(D[9] & T[3] & ~SREG1_RF_Indicator & ~DREG_RF_Indicator) 
			| (D[9] & T[3] & ~SREG1_RF_Indicator & DREG_RF_Indicator) 
			| (D[9] & T[2] & SREG1_RF_Indicator & DREG_RF_Indicator) 
			| (D[9] & T[2] & SREG1_RF_Indicator & ~DREG_RF_Indicator)
		)
			ALU_FunSel <= 5'b11101; // ASR A
			
		else if (
			(D[10] & T[3] & ~SREG1_RF_Indicator & ~DREG_RF_Indicator) 
			| (D[10] & T[3] & ~SREG1_RF_Indicator & DREG_RF_Indicator) 
			| (D[10] & T[2] & SREG1_RF_Indicator & DREG_RF_Indicator) 
			| (D[10] & T[2] & SREG1_RF_Indicator & ~DREG_RF_Indicator)
		)
			ALU_FunSel <= 5'b11110; // CSL A
			
		else if (
			(D[11] & T[3] & ~SREG1_RF_Indicator & ~DREG_RF_Indicator) 
			| (D[11] & T[3] & ~SREG1_RF_Indicator & DREG_RF_Indicator) 
			| (D[11] & T[2] & SREG1_RF_Indicator & DREG_RF_Indicator) 
			| (D[11] & T[2] & SREG1_RF_Indicator & ~DREG_RF_Indicator)
		)
			ALU_FunSel <= 5'b11111; // CSR A
			
		else if (
			(D[14] & T[3] & ~SREG1_RF_Indicator & ~DREG_RF_Indicator) 
			| (D[14] & T[3] & ~SREG1_RF_Indicator & DREG_RF_Indicator) 
			| (D[14] & T[2] & SREG1_RF_Indicator & DREG_RF_Indicator) 
			| (D[14] & T[2] & SREG1_RF_Indicator & ~DREG_RF_Indicator)
		)
			ALU_FunSel <= 5'b10010; // NOT A
			
		else if (
			(D[12] & T[4] & ~DREG_RF_Indicator)
			| (D[12] & T[4] & DREG_RF_Indicator)
			| (D[27] & T[4] & ~DREG_RF_Indicator)
			| (D[27] & T[4] & DREG_RF_Indicator)
		)
			ALU_FunSel <= 5'b10111; // AND A
			
		else if (
			(D[13] & T[4] & ~DREG_RF_Indicator)
			| (D[13] & T[4] & DREG_RF_Indicator)
			| (D[28] & T[4] & ~DREG_RF_Indicator)
			| (D[28] & T[4] & DREG_RF_Indicator)
		)
			ALU_FunSel <= 5'b11000; // OR A
			
		else if (
			(D[15] & T[4] & ~DREG_RF_Indicator)
			| (D[15] & T[4] & DREG_RF_Indicator)
			| (D[29] & T[4] & ~DREG_RF_Indicator)
			| (D[29] & T[4] & DREG_RF_Indicator)
		)
			ALU_FunSel <= 5'b11001; // XOR A
			
		else if (
			(D[16] & T[4] & ~DREG_RF_Indicator)
			| (D[16] & T[4] & DREG_RF_Indicator)
		)
			ALU_FunSel <= 5'b11010; // NAND A

		if (
			T[0]
		)
			ALU_WF <= 1'b0; // ALU Write Flag is disabled.
		else if (
			((D[25] | D[26] | D[27] | D[28] | D[29]) & T[4] & WF_Change_Indicator)
			| (D[24] & T[3] & ~SREG1_RF_Indicator & WF_Change_Indicator)
			| (D[24] & T[2] & SREG1_RF_Indicator & WF_Change_Indicator)
		)
			ALU_WF <= 1'b1; // ALU Write Flag is enabled.
		// #############################################
		
		// ################ MUX Selects ################
		if (
			((D[5] | D[6]) & T[2] & SREG1_RF_Indicator & DREG_RF_Indicator) 
			| ((D[7] | D[8] | D[9] | D[10] | D[11] | D[14] | D[24]) & T[3] & ~SREG1_RF_Indicator & DREG_RF_Indicator) 
			| ((D[7] | D[8] | D[9] | D[10] | D[11] | D[14] | D[24]) & T[2] & SREG1_RF_Indicator & DREG_RF_Indicator)
			| ((D[12] | D[13] | D[15] | D[16] | D[21] | D[22] | D[23] | D[25] | D[26] | D[27] | D[28] | D[29]) & T[2] & SREG1_RF_Indicator)
			| ((D[12] | D[13] | D[15] | D[16] | D[21] | D[22] | D[23] | D[25] | D[26] | D[27] | D[28] | D[29]) & T[3] & SREG2_RF_Indicator)
			| ((D[12] | D[13] | D[15] | D[16] | D[21] | D[22] | D[23] | D[25] | D[26] | D[27] | D[28] | D[29]) & T[4] & DREG_RF_Indicator)
		)
			MuxASel <= 2'b00; // ALUOut goes to RF through MuxA.		
			
		else if (
			(D[0] & T[3]) 
			| (D[1] & T[3] & ~Zero_Flag_Indicator) 
			| (D[2] & T[3] & Zero_Flag_Indicator) 
			| ((D[5] | D[6]) & T[2] & ~SREG1_RF_Indicator & DREG_RF_Indicator)
			| ((D[7] | D[8] | D[9] | D[10] | D[11] | D[14] | D[24]) & T[2] & ~SREG1_RF_Indicator & ~DREG_RF_Indicator) 
			| ((D[7] | D[8] | D[9] | D[10] | D[11] | D[14] | D[24]) & T[2] & ~SREG1_RF_Indicator & DREG_RF_Indicator)
			| ((D[12] | D[13] | D[15] | D[16] | D[21] | D[22] | D[23] | D[25] | D[26] | D[27] | D[28] | D[29]) & T[2] & ~SREG1_RF_Indicator)
			| ((D[12] | D[13] | D[15] | D[16] | D[21] | D[22] | D[23] | D[25] | D[26] | D[27] | D[28] | D[29]) & T[3] & ~SREG2_RF_Indicator)
			| (D[30] & T[2])
			| (D[33] & T[2])
		)
			MuxASel <= 2'b01; // ARF OutC goes to RF through MuxA.
			
		else if (
			(D[18] & T[2])
			| (D[3] & T[2])
		)
			MuxASel <= 2'b10; // Memory Output goes to RF through MuxA.
			
		else if (
			(D[0] & T[2]) 
			| (D[1] & T[2] & ~Zero_Flag_Indicator) 
			| (D[2] & T[2] & Zero_Flag_Indicator)
			| (D[32] & T[2])
			| (D[33] & T[3])
			| ((D[17] | D[20]) & T[2])
		)
			MuxASel <= 2'b11; // IR(7-0) goes to RF through MuxA.
											
		if (
			(D[0] & T[4]) 
			| (D[1] & T[4] & ~Zero_Flag_Indicator) 
			| (D[2] & T[4] & Zero_Flag_Indicator) 
			| ((D[5] | D[6]) & T[2] & SREG1_RF_Indicator & ~DREG_RF_Indicator) 
			| ((D[7] | D[8] | D[9] | D[10] | D[11] | D[14] | D[24]) & T[3] & ~SREG1_RF_Indicator & ~DREG_RF_Indicator) 
			| ((D[7] | D[8] | D[9] | D[10] | D[11] | D[14] | D[24]) & T[2] & SREG1_RF_Indicator & ~DREG_RF_Indicator)
			| ((D[12] | D[13] | D[15] | D[16] | D[21] | D[22] | D[23] | D[25] | D[26] | D[27] | D[28] | D[29]) & T[4] & ~DREG_RF_Indicator)
			| (D[30] & T[5])
			| (D[33] & T[4])
		)
			MuxBSel <= 2'b00; // ALUOut goes to ARF through MuxB.
			
		else if (
			((D[5] | D[6]) & T[2] & ~SREG1_RF_Indicator & ~DREG_RF_Indicator)
		)
			MuxBSel <= 2'b01; // ARF OutC goes to ARF through MuxB.
			
		else if (
			(D[31] & T[2])
		)
			MuxBSel <= 2'b10; // Memory Output goes to ARF through MuxB.
									
		if (
			(D[19] & T[2])
			| (D[30] & T[3])
			| (D[33] & T[5])
			| (D[4] & T[2])
		)						
			MuxCSel <= 1'b0; // ALUOut(7-0) will be loaded to memory through MuxC.
			
		else if (
			(D[19] & T[3])
			| (D[30] & T[4])
			| (D[33] & T[6])
			| (D[4] & T[3])
		)
			MuxCSel <= 1'b1; // ALUOut(15-8) will be loaded to memory through MuxC.
		// #############################################
		
		// ################ MEM Selects ################
		if (		
			T[0] 
			| T[1]
			| (D[18] & T[2])
			| (D[19] & T[2])
			| (D[31] & T[2])
			| (D[30] & T[3])
			| (D[33] & T[5])
			| (D[3] & T[2])
			| (D[4] & T[2])
		)
			Mem_CS <= 1'b0; // Memory chip is enabled.
			
		/*
			The default behavior is to disable the memory chip from time T[2] onwards to stop any input/output from the memory (since most instructions do not use the memory). 
			However, there are situations at time T[2] where data exchange with the memory is required. 
			Therefore, we NAND these situations with the default behavior of T[2].
		*/		
		else if (
			(T[2]
			& ~(D[18] & T[2])
			& ~(D[19] & T[2])
			& ~(D[31] & T[2])
			& ~(D[3] & T[2])
			& ~(D[4] & T[2]))
			| (D[30] & T[5])
			| (D[4] & T[4])
			
		)
			Mem_CS <= 1'b1; // Memory chip is disabled.
			
		if (
			T[0] 
			| T[1]
			| (D[18] & T[2])
			| (D[31] & T[2])
			| (D[3] & T[2])
		)
			Mem_WR <= 1'b0; // Memory is in Read mode. 
			
		if (
			(D[19] & T[2])		
			| (D[30] & T[3])
			| (D[33] & T[5])
			| (D[4] & T[2])			
		)
			Mem_WR <= 1'b1;// Memory is in write mode.
		// #############################################
		
		// ################ IR Selects ################		
		if (T[0] | T[1])
			IR_Write <= 1'b1; // IR register is enabled.
			
		else if (T[2])
			IR_Write <= 1'b0; // IR register is disabled.
		
		if (T[0])
			IR_LH <= 1'b0; // Memory Output(7:0) will be loaded to IR.
			
		else if (T[1])
			IR_LH <= 1'b1; // Memory Output(15:8) will be loaded to IR.
		// #############################################
	end
endmodule
	 
module CPUSystem(
    input wire Clock,
	input wire Reset,
	input wire[7:0] T 
);
    wire[2:0] ARF_FunSel, ARF_RegSel;																
    wire[2:0] RF_OutASel, RF_OutBSel, RF_FunSel;
    wire[3:0] RF_RegSel, RF_ScrSel;
    wire[4:0] ALU_FunSel;
    wire IR_LH, IR_Write, Mem_WR, Mem_CS, ALU_WF, MuxCSel, TCounter_Reset;
    wire[1:0] MuxASel, MuxBSel, ARF_OutCSel, ARF_OutDSel;
	
    ArithmeticLogicUnitSystem _ALUSystem(
        .RF_OutASel(RF_OutASel),   .RF_OutBSel(RF_OutBSel), 
        .RF_FunSel(RF_FunSel),     .RF_RegSel(RF_RegSel),
        .RF_ScrSel(RF_ScrSel),     .ALU_FunSel(ALU_FunSel),
        .ALU_WF(ALU_WF),           .ARF_OutCSel(ARF_OutCSel), 
        .ARF_OutDSel(ARF_OutDSel), .ARF_FunSel(ARF_FunSel),
        .ARF_RegSel(ARF_RegSel),   .IR_LH(IR_LH),
        .IR_Write(IR_Write),       .Mem_WR(Mem_WR),
        .Mem_CS(Mem_CS),           .MuxASel(MuxASel),
        .MuxBSel(MuxBSel),         .MuxCSel(MuxCSel),
        .Clock(Clock)
	);
	
    ControlUnit _ControlUnit(
		.T(T),
        .Clock(Clock),
        .Reset(Reset),
        .ARF_FunSel(ARF_FunSel),
        .ARF_RegSel(ARF_RegSel),
        .RF_OutASel(RF_OutASel),
        .RF_OutBSel(RF_OutBSel),
        .RF_FunSel(RF_FunSel),
        .RF_RegSel(RF_RegSel),
        .RF_ScrSel(RF_ScrSel),
        .ALU_FunSel(ALU_FunSel),
        .IR_LH(IR_LH),
        .IR_Write(IR_Write),
        .Mem_WR(Mem_WR),
        .Mem_CS(Mem_CS),
        .ALU_WF(ALU_WF),
        .MuxCSel(MuxCSel),
        .TCounter_Reset(TCounter_Reset),
        .MuxASel(MuxASel),
        .MuxBSel(MuxBSel),
        .ARF_OutCSel(ARF_OutCSel),
        .ARF_OutDSel(ARF_OutDSel),
	.IROut(_ALUSystem.IR.IROut)
    );
endmodule

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

module InstructionRegister(
    input wire Clock,
    input wire [7:0] I,
    input wire LH,
    input wire Write,
    output reg [15:0] IROut
);

    always @(posedge Clock) begin
        if (Write) begin
            case (LH)
                1'b0: IROut[7:0] <= I; 
                1'b1: IROut[15:8] <= I;
            endcase
        end
    end

endmodule
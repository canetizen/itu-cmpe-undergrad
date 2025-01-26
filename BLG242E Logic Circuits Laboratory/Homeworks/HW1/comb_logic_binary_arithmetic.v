`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// BLG242E Logic Lab HW1
// Mustafa Can Caliskan 150200097
// Ahmet Emre Buz 150200010
//////////////////////////////////////////////////////////////////////////////////

module and_gate(input a, input b, output c);
    assign c = a & b;
endmodule
module or_gate(input a, input b, output c);
    assign c = a | b;
endmodule
module not_gate(input a, output b);
    assign b = ~a;
endmodule
module xor_gate(input a, input b, output c);
    assign c = a ^ b;
endmodule

module xor_gate_8bit(input[7:0] a, input b, output[7:0] out);
    xor_gate x0(a[0], b, out[0]);
    xor_gate x1(a[1], b, out[1]);
    xor_gate x2(a[2], b, out[2]);
    xor_gate x3(a[3], b, out[3]);
    xor_gate x4(a[4], b, out[4]);
    xor_gate x5(a[5], b, out[5]);
    xor_gate x6(a[6], b, out[6]);
    xor_gate x7(a[7], b, out[7]);
endmodule

module two_input_nand_gate(input a, input b, output c);
    assign c = ~(a & b);
endmodule
module three_input_nand_gate(input a, input b, input c, output out);
    assign out = ~(a & b & c);
endmodule
module mux_8to1(input [7:0] in, input [2:0] sel, output out);
    assign out = (sel == 3'b000) ? in[0] :
                (sel == 3'b001) ? in[1] :
                (sel == 3'b010) ? in[2] :
                (sel == 3'b011) ? in[3] :
                (sel == 3'b100) ? in[4] :
                (sel == 3'b101) ? in[5] :
                (sel == 3'b110) ? in[6] :
                (sel == 3'b111) ? in[7] : 1'b0;
endmodule

module decoder_3to8(input [2:0] in, output wire [7:0] out);

    assign out = (in == 3'b000) ? 8'b00000001 :
                 (in == 3'b001) ? 8'b00000010 :
                 (in == 3'b010) ? 8'b00000100 :
                 (in == 3'b011) ? 8'b00001000 :
                 (in == 3'b100) ? 8'b00010000 :
                 (in == 3'b101) ? 8'b00100000 :
                 (in == 3'b110) ? 8'b01000000 :
                 (in == 3'b111) ? 8'b10000000 : 8'b00000000;

endmodule

module part2(input a, input b, input c, input d, output out);
    wire notA;
    wire notB;
    wire notD;
    wire firstAnd;
    wire secondAnd;
    wire out1;
    wire out2;
    wire out3;
    wire tempOut;
    and_gate a0(a, c, firstAnd);
    and_gate a1(d, firstAnd, out1);
    not_gate n0(a, notA);
    and_gate a2(notA, b, secondAnd);
    and_gate a3(secondAnd, c, out2);
    not_gate n1(b, notB);
    not_gate n2(d, notD);
    and_gate a4(notB, notD,out3);
    or_gate o0(out1, out2, tempOut);
    or_gate o1(tempOut, out3, out);
endmodule

module part3(input a, input b, input c, input d, output out);
    wire a0out;
    wire notA;
    wire a2out;
    wire notB;
    wire notD;
    wire a5out;
    three_input_nand_gate a0(a, c, d, a0out);
    two_input_nand_gate a1(a, a, notA);
    three_input_nand_gate a2(notA, b, c, a2out);
    two_input_nand_gate a3(b, b, notB);
    two_input_nand_gate a4(d, d, notD);
    two_input_nand_gate a5(notB, notD, a5out);
    three_input_nand_gate a6(a0out, a2out, a5out, out);
endmodule

module part4(input a, input b, input c, input d, output out);
    reg [7:0]in = 8'b11011000;
    wire [2:0]sel;
    wire out1;
    wire out2;
    wire notB;
    wire notD;
    assign sel[0] = a;
    assign sel[1] = d;
    assign sel[2] = b;
    mux_8to1 m(in, sel, muxOut);
    and_gate a0(c, muxOut, out1);
    not_gate n0(b, notB);
    not_gate n1(d, notD);
    and_gate a1(notB, notD, out2);
    or_gate o0(out1, out2, out);
endmodule


module part5a(input a, input b, input c, output out);
    wire [7:0] decOut;
    wire [2:0] decIn;
    assign decIn[0] = c;
    assign decIn[1] = b;
    assign decIn[2] = a;
    decoder_3to8 d0(decIn, decOut);
    or_gate o0(decOut[3], decOut[5], out);
endmodule

module part5b(input a, input b, input c, output out);
    wire [7:0] decOut;
    wire [2:0] decIn;
    assign decIn[0] = c;
    assign decIn[1] = b;
    assign decIn[2] = a;
    decoder_3to8 d0(decIn, decOut);
    or_gate o0(decOut[6], decOut[7], out);
endmodule


module half_adder(input a, input b, output sum, output carry);
    and_gate a0 (a, b, carry);
    xor_gate x0 (a, b, sum);
endmodule

module full_adder(input a, input b, input cIn, output sum, output cOut);
    wire inner_sum;
    wire inner_carry;
    half_adder ha0(a, b, inner_sum, inner_carry);
    half_adder ha1(cIn, inner_sum, sum, outer_carry);
    or_gate o0(outer_carry, inner_carry, cOut);
endmodule

module full_adder_4bit(input [3:0]a, input [3:0]b, input carryIn, output [3:0] sum, output carryOut);
    full_adder bit0(a[0], b[0], carryIn, sum[0], c1);
    full_adder bit1(a[1], b[1], c1, sum[1], c2);
    full_adder bit2(a[2], b[2], c2, sum[2], c3);
    full_adder bit3(a[3], b[3], c3, sum[3], carryOut);
endmodule

module full_adder_8bit(input[7:0]a, input [7:0]b, input carryIn, output [7:0] sum, output carryOut);
    full_adder bit0(a[0], b[0], carryIn, sum[0], c1);
    full_adder bit1(a[1], b[1], c1, sum[1], c2);
    full_adder bit2(a[2], b[2], c2, sum[2], c3);
    full_adder bit3(a[3], b[3], c3, sum[3], c4);
    full_adder bit4(a[4], b[4], c4, sum[4], c5);
    full_adder bit5(a[5], b[5], c5, sum[5], c6);
    full_adder bit6(a[6], b[6], c6, sum[6], c7);
    full_adder bit7(a[7], b[7], c7, sum[7], carryOut);
endmodule

module adder_subtractor_16bit(input[15:0] a, input[15:0] b, input carryIn, output[15:0] result, output carryOut);
    wire inner_carry;
    wire[7:0] b_xor0;
    wire[7:0] b_xor1;
    xor_gate_8bit x0(b[7:0], carryIn, b_xor0);
    full_adder_8bit fa8b0(a[7:0], b_xor0, carryIn, result[7:0], inner_carry);
    xor_gate_8bit x1(b[15:8], carryIn, b_xor1);
    full_adder_8bit fa8b1(a[15:8], b_xor1, inner_carry, result[15:8], carryOut);
endmodule

module b_minus_2a(input[15:0] a, input[15:0] b, output[15:0] result, output carryOut);
    wire[15:0] a_plus_a;
    wire inner_output_carry;
    adder_subtractor_16bit a_plus_a_(a, a, 1'b0, a_plus_a, inner_output_carry);
    adder_subtractor_16bit b_minus_2a_(b, a_plus_a, 1'b1, result, carryOut);
endmodule

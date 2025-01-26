`timescale 1ns / 1ps

//////////////////////////////////////////////////////////////////////////////////
// BLG242E Logic Lab HW1
// Mustafa Can Caliskan 150200097
// Ahmet Emre Buz 150200010
//////////////////////////////////////////////////////////////////////////////////

module nand_gate_test();
  reg A;
  reg B;
  wire C;

  nand_gate uut(A, B, C);

  initial begin
    A = 1'b0; B = 1'b0; #250;
    A = 1'b0; B = 1'b1; #250;
    A = 1'b1; B = 1'b0; #250;
    A = 1'b1; B = 1'b1; #250;
  end
endmodule

module not_gate_test();
    reg A;
    wire C;
    
    not_gate uut(A, C);
    
    initial begin
        A = 1'b0; #250;
        A = 1'b1; #250;
     end
endmodule

module or_gate_test();
    reg A;
    reg B;
    wire C;
    
    or_gate uut(A, B, C);
    
    initial begin
        A = 1'b0; B = 1'b0; #250;
        A = 1'b1; B = 1'b0; #250;
        A = 1'b0; B = 1'b1; #250;
        A = 1'b1; B = 1'b1; #250;
     end
endmodule

module part2_test();
    reg a;
    reg b;
    reg c;
    reg d;
    wire out;
    
    part2 uut(a, b, c, d, out);
    
    initial begin
    a = 1'b0; b = 1'b0; c = 1'b0; d = 1'b0; #60;
    a = 1'b0; b = 1'b0; c = 1'b0; d = 1'b1; #60;
    a = 1'b0; b = 1'b0; c = 1'b1; d = 1'b0; #60;
    a = 1'b0; b = 1'b0; c = 1'b1; d = 1'b1; #60;
    a = 1'b0; b = 1'b1; c = 1'b0; d = 1'b0; #60;
    a = 1'b0; b = 1'b1; c = 1'b0; d = 1'b1; #60;
    a = 1'b0; b = 1'b1; c = 1'b1; d = 1'b0; #60;
    a = 1'b0; b = 1'b1; c = 1'b1; d = 1'b1; #60;
    a = 1'b1; b = 1'b0; c = 1'b0; d = 1'b0; #60;
    a = 1'b1; b = 1'b0; c = 1'b0; d = 1'b1; #60;
    a = 1'b1; b = 1'b0; c = 1'b1; d = 1'b0; #60;
    a = 1'b1; b = 1'b0; c = 1'b1; d = 1'b1; #60;
    a = 1'b1; b = 1'b1; c = 1'b0; d = 1'b0; #60;
    a = 1'b1; b = 1'b1; c = 1'b0; d = 1'b1; #60;
    a = 1'b1; b = 1'b1; c = 1'b1; d = 1'b0; #60;
    a = 1'b1; b = 1'b1; c = 1'b1; d = 1'b1; #60;
    end
endmodule

module part3_test(); 
    reg a;
    reg b;
    reg c;
    reg d;
    wire out;
    
    part3 uut(a, b, c, d, out);
    
    initial begin
    a = 1'b0; b = 1'b0; c = 1'b0; d = 1'b0; #60;
    a = 1'b0; b = 1'b0; c = 1'b0; d = 1'b1; #60;
    a = 1'b0; b = 1'b0; c = 1'b1; d = 1'b0; #60;
    a = 1'b0; b = 1'b0; c = 1'b1; d = 1'b1; #60;
    a = 1'b0; b = 1'b1; c = 1'b0; d = 1'b0; #60;
    a = 1'b0; b = 1'b1; c = 1'b0; d = 1'b1; #60;
    a = 1'b0; b = 1'b1; c = 1'b1; d = 1'b0; #60;
    a = 1'b0; b = 1'b1; c = 1'b1; d = 1'b1; #60;
    a = 1'b1; b = 1'b0; c = 1'b0; d = 1'b0; #60;
    a = 1'b1; b = 1'b0; c = 1'b0; d = 1'b1; #60;
    a = 1'b1; b = 1'b0; c = 1'b1; d = 1'b0; #60;
    a = 1'b1; b = 1'b0; c = 1'b1; d = 1'b1; #60;
    a = 1'b1; b = 1'b1; c = 1'b0; d = 1'b0; #60;
    a = 1'b1; b = 1'b1; c = 1'b0; d = 1'b1; #60;
    a = 1'b1; b = 1'b1; c = 1'b1; d = 1'b0; #60;
    a = 1'b1; b = 1'b1; c = 1'b1; d = 1'b1; #60;
    end
endmodule

module part4_test(); 
    reg a;
    reg b;
    reg c;
    reg d;
    wire out;
    
    part4 uut(a, b, c, d, out);
    
    initial begin
    a = 1'b0; b = 1'b0; c = 1'b0; d = 1'b0; #60;
    a = 1'b0; b = 1'b0; c = 1'b0; d = 1'b1; #60;
    a = 1'b0; b = 1'b0; c = 1'b1; d = 1'b0; #60;
    a = 1'b0; b = 1'b0; c = 1'b1; d = 1'b1; #60;
    a = 1'b0; b = 1'b1; c = 1'b0; d = 1'b0; #60;
    a = 1'b0; b = 1'b1; c = 1'b0; d = 1'b1; #60;
    a = 1'b0; b = 1'b1; c = 1'b1; d = 1'b0; #60;
    a = 1'b0; b = 1'b1; c = 1'b1; d = 1'b1; #60;
    a = 1'b1; b = 1'b0; c = 1'b0; d = 1'b0; #60;
    a = 1'b1; b = 1'b0; c = 1'b0; d = 1'b1; #60;
    a = 1'b1; b = 1'b0; c = 1'b1; d = 1'b0; #60;
    a = 1'b1; b = 1'b0; c = 1'b1; d = 1'b1; #60;
    a = 1'b1; b = 1'b1; c = 1'b0; d = 1'b0; #60;
    a = 1'b1; b = 1'b1; c = 1'b0; d = 1'b1; #60;
    a = 1'b1; b = 1'b1; c = 1'b1; d = 1'b0; #60;
    a = 1'b1; b = 1'b1; c = 1'b1; d = 1'b1; #60;
    end
endmodule

module part5a_test();
  reg[2:0] in;
  wire C;

  part5 uut(in[0], in[1], in[2], C);

  initial begin
    in = 3'b000; #125;
    in = 3'b001; #125;
    in = 3'b010; #125;
    in = 3'b011; #125;
    in = 3'b100; #125;
    in = 3'b101; #125;
    in = 3'b110; #125;
    in = 3'b111; #125;
  end
endmodule

module part5b_test();
  reg[2:0] in;
  wire C;

  part5b uut(in[0], in[1], in[2], C);

  initial begin
    in = 3'b000; #125;
    in = 3'b001; #125;
    in = 3'b010; #125;
    in = 3'b011; #125;
    in = 3'b100; #125;
    in = 3'b101; #125;
    in = 3'b110; #125;
    in = 3'b111; #125;
  end
endmodule

module half_adder_test();
    reg A;
    reg B;
    wire carry;
    wire sum;
    
    half_adder uut(A, B, sum, carry);
    
    initial begin
        A = 1'b0; B = 1'b0; #250;
        A = 1'b1; B = 1'b0; #250;
        A = 1'b0; B = 1'b1; #250;
        A = 1'b1; B = 1'b1; #250;
     end
    
endmodule

module xor_gate_test();
    reg A;
    reg B;
    wire C;
    
    xor_gate uut(A, B, C);
    
    initial begin
        A = 1'b0; B = 1'b0; #250;
        A = 1'b1; B = 1'b0; #250;
        A = 1'b0; B = 1'b1; #250;
        A = 1'b1; B = 1'b1; #250;
     end
endmodule

module adder_subtractor_16bit_test();
    reg[15:0] a;
    reg[15:0] b;
    reg carry;
    wire carryOut;
    wire [15:0] sum;
    
    adder_subtractor_16bit uut(a, b, carry, sum, carryOut);
    
    initial begin
        a = 16'b0000000000000011; b = 16'b0000000000010111; carry = 0; #125;
        a = 16'b0000000000010101; b = 16'b0000000001001011; carry = 0; #125;
        a = 16'b0100000110100000; b = 16'b0100001000000100; carry = 0; #125;
        a = 16'b0001101101000111; b = 16'b0001100111111010; carry = 0; #125;
        a = 16'b0000000101000101; b = 16'b0000000001100001; carry = 0; #125;
        a = 16'b0000000000101100; b = 16'b0000000010111110; carry = 0; #125;
        a = 16'b0000000111001111; b = 16'b0000000011110001; carry = 0; #125;
        a = 16'b0000000001010110; b = 16'b0000001000111100; carry = 0; #125;
    end
endmodule

module and_gate_test();
    reg A;
    reg B;
    wire C;
    
    and_gate uut(A, B, C);
    
    initial begin
        A = 1'b0; B = 1'b0; #250;
        A = 1'b1; B = 1'b0; #250;
        A = 1'b0; B = 1'b1; #250;
        A = 1'b1; B = 1'b1; #250;
     end
endmodule

module b_minus_2a_test();
    reg[15:0] a;
    reg[15:0] b;
    wire carryOut;
    wire [15:0] sum;
    
    b_minus_2a uut(a, b, sum, carryOut);
    
    initial begin
        a = 16'b0000000000100000; b = 16'b0000000000000111;  #125;
        a = 16'b0000000000010101; b = 16'b0000000001010101;  #125;
        a = 16'b0000000000010000; b = 16'b0000000000100100;  #125;
        a = 16'b0000000100000000; b = 16'b0000000000000101;  #125;
        a = 16'b0000000011001000; b = 16'b0000000001011111;  #125;
        a = 16'b0000000000101101; b = 16'b0000000010000111;  #125;
        a = 16'b0000000000100100; b = 16'b0000000011111111;  #125;
        a = 16'b0000000000011001; b = 16'b0000000001000001;  #125;
    end
endmodule

module dec_test();
  reg[2:0] in;
  wire[7:0] C;

  decoder_3to8 uut(in, C);

  initial begin
    in = 3'b000; #125;
    in = 3'b001; #125;
    in = 3'b010; #125;
    in = 3'b011; #125;
    in = 3'b100; #125;
    in = 3'b101; #125;
    in = 3'b110; #125;
    in = 3'b111; #125;
  end
endmodule

module full_adder_4bit_test();
    reg[3:0] a;
    reg[3:0] b;
    reg carry = 1'b0;
    wire carryOut;
    wire [3:0] sum;
    
    full_adder_4bit uut(a, b, carry, sum, carryOut);
    
    initial begin
        a = 4'b1000; b = 4'b0001; #125;
        a = 4'b0010; b = 4'b0111; #125;
        a = 4'b0100; b = 4'b0101; #125;
        a = 4'b1011; b = 4'b1010; #125;
        a = 4'b1110; b = 4'b0101; #125;
        a = 4'b1111; b = 4'b1001; #125;
        a = 4'b0110; b = 4'b0011; #125;
        a = 4'b1000; b = 4'b1100; #125;
    end
endmodule

module full_adder_8bit_test();
    reg[7:0] a;
    reg[7:0] b;
    reg carry = 1'b0;
    wire carryOut;
    wire [7:0] sum;
    
    full_adder_8bit uut(a, b, carry, sum, carryOut);
    
    initial begin
        a = 8'b00011101; b = 8'b00000101; #125;
        a = 8'b00110011; b = 8'b01011100; #125;
        a = 8'b00010001; b = 8'b00011100; #125;
        a = 8'b10111111; b = 8'b00000010; #125;
        a = 8'b11001000; b = 8'b01011111; #125;
        a = 8'b00110001; b = 8'b00011001; #125;
        a = 8'b01001110; b = 8'b11111111; #125;
        a = 8'b00101011; b = 8'b00111011; #125;
    end
endmodule

module full_adder_test();
    reg a;
    reg b;
    reg carry;
    
    wire sum;
    wire carryOut;
    
    full_adder uut(a, b, carry, sum, carryOut);
    
    initial begin
       a = 1'b0; b = 1'b0; carry = 1'b0; #125;
       a = 1'b0; b = 1'b0; carry = 1'b1; #125;
       a = 1'b0; b = 1'b1; carry = 1'b0; #125;
       a = 1'b0; b = 1'b1; carry = 1'b1; #125;
       a = 1'b1; b = 1'b0; carry = 1'b0; #125;
       a = 1'b1; b = 1'b0; carry = 1'b1; #125;
       a = 1'b1; b = 1'b1; carry = 1'b0; #125;
       a = 1'b1; b = 1'b1; carry = 1'b1; #125;
    end
endmodule

module logicLab_test();
    reg A;
    reg B;
    wire C;
    
    and_gate uut(A, B, C);
    
    initial begin
        A = 1'b0; B = 1'b0; #250;
        A = 1'b1; B = 1'b0; #250;
        A = 1'b0; B = 1'b1; #250;
        A = 1'b1; B = 1'b1; #250;
     end
endmodule

module mux_8to1_test();
  reg[7:0] in;
  reg[2:0] sel;
  wire C;

  mux_8to1 uut(in, sel, C);

  initial begin
    in = 8'b10010010; sel = 3'b000; #125;
    in = 8'b10010010; sel = 3'b001; #125;
    in = 8'b10010010; sel = 3'b010; #125;
    in = 8'b10010010; sel = 3'b011; #125;
    in = 8'b10010010; sel = 3'b100; #125;
    in = 8'b10010010; sel = 3'b101; #125;
    in = 8'b10010010; sel = 3'b110; #125;
    in = 8'b10010010; sel = 3'b111; #125;
  end
endmodule


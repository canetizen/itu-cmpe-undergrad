`timescale 1ns / 1ps

module three_state_buffer_test();

    reg[7:0] data_in;
    wire[7:0] data_out;
    reg enable;

    three_state_buffer uut(data_in, enable, data_out);
    
    initial begin
        data_in = 8'b00011100;
        enable = 0; #200;
        enable = 1; #200;
        enable = 0; #200;
        enable = 1; #200;

    end
endmodule

module eight_bit_bus_test();

   reg[7:0] data_1;
   reg[7:0] data_2;
   reg Select;
   wire[7:0] Output;
   
   eight_bit_bus uut(data_1, data_2, Select, Output);
   
   initial begin
        data_1 = 8'b10101010;
        data_2 = 8'b00110011; #200;
        Select = 0; #200;
        Select = 1; #200;
        Select = 0; #200;
        Select = 1; #200;
   end
   
endmodule

module eight_bit_bus_two_out_test();
   reg[7:0] data_1;
   reg[7:0] data_2;
   reg Select;
   wire[7:0] Output_1;
   wire[7:0] Output_2;   
   eight_bit_bus_two_out uut(data_1, data_2, Select, Output_1, Output_2);
   
   initial begin
        data_1 = 8'b10101010;
        data_2 = 8'b00110011;
        Select = 0; #200;
        Select = 1; #200;
        Select = 0; #200;
        Select = 1; #200;
   end
endmodule

module memory_line_test();  
   reg [7:0]data_in;
   reg reset;
   reg clk;
   reg line_sel;
   reg rd_en;
   reg wr_en;
   wire [7:0] data_out;
   memory_line uut(data_in, reset, clk, line_sel, rd_en, wr_en, data_out);
   
   initial begin
        clk = 0;
   end
   always begin
       clk <= ~clk; #70;
   end

   initial begin
        data_in = 8'b00000000;  reset = 1; line_sel = 1;   rd_en = 0; wr_en = 1;     #200;
        data_in = 8'b00110011;  reset = 0; line_sel = 1;   rd_en = 0; wr_en = 1;     #200;
        data_in = 8'b10101010;  reset = 0; line_sel = 1;   rd_en = 1; wr_en = 0;     #200;
        data_in = 8'b11001100;  reset = 0; line_sel = 1;   rd_en = 0; wr_en = 1;     #200;
        data_in = 8'b11111111;  reset = 1; line_sel = 1;   rd_en = 1; wr_en = 0;     #200;
   end

endmodule

module memory_module_test();
   reg [7:0] data_in;
   reg reset;
   reg clk;
   reg rd_en;
   reg wr_en;
   reg chip_sel;
   reg [2:0] address;
   wire [7:0] data_out;
   memory_module uut(data_in, reset, clk, rd_en, wr_en, chip_sel, address, data_out);
   
   initial begin
        clk = 0;
   end
   always begin
       clk <= ~clk; #30;
   end
   
   initial begin
        data_in = 8'b00000011;  reset = 0; chip_sel = 1;   rd_en = 0; wr_en = 1; address = 3'b010;     #100;
        data_in = 8'b11000011;  reset = 0; chip_sel = 1;   rd_en = 1; wr_en = 0; address = 3'b010;     #100;
        data_in = 8'b11000000;  reset = 0; chip_sel = 1;   rd_en = 1; wr_en = 0; address = 3'b011;     #100;
        data_in = 8'b11110000;  reset = 0; chip_sel = 1;   rd_en = 0; wr_en = 1; address = 3'b011;     #100;
        data_in = 8'b10101010;  reset = 0; chip_sel = 1;   rd_en = 1; wr_en = 0; address = 3'b110;     #100;
        data_in = 8'b01010101;  reset = 0; chip_sel = 1;   rd_en = 0; wr_en = 1; address = 3'b110;     #100;
        data_in = 8'b11001100;  reset = 0; chip_sel = 1;   rd_en = 1; wr_en = 0; address = 3'b110;     #100;
        data_in = 8'b01011100;  reset = 0; chip_sel = 1;   rd_en = 0; wr_en = 1; address = 3'b000;     #100;
        data_in = 8'b11001100;  reset = 0; chip_sel = 1;   rd_en = 1; wr_en = 0; address = 3'b000;     #100;
        data_in = 8'b01010101;  reset = 0; chip_sel = 1;   rd_en = 1; wr_en = 0; address = 3'b010;     #100;
   end

endmodule

module memory_module_32_test();
   reg [7:0] data_in;
   reg [4:0] address;
   reg reset;
   reg clk;
   reg rd_en;
   reg wr_en;
   wire [7:0] data_out;
   memory_module_32 uut(data_in, address, reset, rd_en, wr_en, clk, data_out);
   
   always begin
       clk <= ~clk; #30;
   end

   initial begin
        clk = 0;  address = 5'd0 ; data_in = 8'd0;  reset = 1;  rd_en = 0; wr_en = 1;     #125;
        clk = 0;  address = 5'd30 ; data_in = 8'd25;  reset = 0;  rd_en = 0; wr_en = 1;     #125;
        clk = 0;  address = 5'd20 ; data_in = 8'd15;  reset = 0;  rd_en = 0; wr_en = 1;     #125;
        clk = 0;  address = 5'd12 ; data_in = 8'd0;  reset = 0;  rd_en = 1; wr_en = 0;     #125;
        clk = 0;  address = 5'd10 ; data_in = 8'd18;  reset = 0;  rd_en = 0; wr_en = 1;     #125;
        clk = 0;  address = 5'd15 ; data_in = 8'd0;  reset = 0;  rd_en = 1; wr_en = 0;     #125;
        clk = 0;  address = 5'd30 ; data_in = 8'd0;  reset = 0;  rd_en = 1; wr_en = 0;     #125;
        clk = 0;  address = 5'd10 ; data_in = 8'd0;  reset = 0;  rd_en = 1; wr_en = 0;     #125;
   end
endmodule

module memory_module_128_test();
   reg [31:0]data_in;
   reg [4:0]address;
   reg reset;
   reg clk;
   reg rd_en;
   reg wr_en;
   wire [31:0] data_out;
   memory_module_128 uut(data_in, address, reset, rd_en, wr_en, clk, data_out);
   
   initial begin
        clk = 0;
   end

   always begin
       clk <= ~clk; #30;
   end

   initial begin
        address = 5'd0 ; data_in = 32'd0;  reset = 1;  rd_en = 0; wr_en = 1;     #125;
        address = 5'd30 ; data_in = 32'd25;  reset = 0;  rd_en = 0; wr_en = 1;     #125;
        address = 5'd20 ; data_in = 32'd15;  reset = 0;  rd_en = 0; wr_en = 1;     #125;
        address = 5'd12 ; data_in = 32'd0;  reset = 0;  rd_en = 1; wr_en = 0;     #125;
        address = 5'd10 ; data_in = 32'd18;  reset = 0;  rd_en = 0; wr_en = 1;     #125;
        address = 5'd15 ; data_in = 32'd0;  reset = 0;  rd_en = 1; wr_en = 0;     #125;
        address = 5'd30 ; data_in = 32'd0;  reset = 0;  rd_en = 1; wr_en = 0;     #125;
        address = 5'd10 ; data_in = 32'd0;  reset = 0;  rd_en = 1; wr_en = 0;     #125;
   end
endmodule

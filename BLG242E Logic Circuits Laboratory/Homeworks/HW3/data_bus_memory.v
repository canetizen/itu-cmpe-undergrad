`timescale 1ns / 1ps

module and_gate(input A, input B, output C);
    assign C = A & B;
endmodule

module decoder_3to8(input A, input B, input C, output O0, output O1,
                    output O2, output O3, output O4, output O5, output O6, output O7
                    );
    assign O0 = ~A & ~C & ~B;
    assign O1 = ~C & ~B & A;
    assign O2 = ~C & B & ~A;
    assign O3 = ~C & B & A;
    assign O4 = ~A & C & ~B;
    assign O5 = C & ~B & A;
    assign O6 = C & B & ~A;
    assign O7 = C & B & A;
endmodule

module decoder_2to4(input A, input B, output O0, output O1, output O2, output O3);
    assign O0 = ~B & ~A;
    assign O1 = ~B & A;
    assign O2 = B & ~A;
    assign O3 = B & A;
endmodule

module three_state_buffer(input[7:0] data_in, input enable, output reg[7:0] data_out);
    always@(enable or data_in) begin
       if (enable)
          data_out = data_in;
       else
          data_out = 8'bZ;
    end
endmodule

module eight_bit_bus(input[7:0] data_1, input[7:0] data_2, input Select, output [7:0] Output);
    three_state_buffer b0(.data_in(data_1), .enable(~Select), .data_out(Output));
    three_state_buffer b1(.data_in(data_2), .enable(Select), .data_out(Output));
endmodule

module eight_bit_bus_two_out(input[7:0] data_1, input[7:0] data_2, 
                            input Select, output [7:0] Output_1, output[7:0] Output_2);

    wire [7:0] left_out;
    eight_bit_bus b0(data_1, data_2, Select, left_out);
    three_state_buffer b2(.data_in(left_out), .enable(~Select), .data_out(Output_1));
    three_state_buffer b3(.data_in(left_out), .enable(Select), .data_out(Output_2));

endmodule

module memory_line(input [7:0] data_in, input reset, input clk, input line_sel, input rd_en, input wr_en,
                    output reg [7:0] data_out);
    
    reg [7:0]stored_data;
    always@(negedge clk)
    begin
        if(reset)
        begin
            stored_data <= 8'd0;
            data_out <= 8'b0;
        end
    end
    always@(posedge clk)
        begin
            if(wr_en == 1 && line_sel == 1)
            begin
                stored_data <= data_in;
                data_out <= data_in;
            end
            else if(rd_en == 1 && line_sel == 1)
            begin
                data_out <= stored_data;
            end
            else
            begin
                data_out <= 8'bZ;
            end 
        end 
endmodule
        
module memory_module(input [7:0]data_in, input reset, input clk, input rd_en, input wr_en,
                   input chip_sel, input [2:0] address, output [7:0] data_out);
    wire [7:0]decoded_address;
    wire [7:0]decoded_chip_sel;
    
    decoder_3to8 dec2(address[0],address[1],address[2],decoded_address[0],
    decoded_address[1],decoded_address[2],decoded_address[3],decoded_address[4],
    decoded_address[5],decoded_address[6],decoded_address[7]);
    
    and_gate a0(chip_sel, decoded_address[0], decoded_chip_sel[0]);
    and_gate a1(chip_sel, decoded_address[1], decoded_chip_sel[1]);
    and_gate a2(chip_sel, decoded_address[2], decoded_chip_sel[2]);
    and_gate a3(chip_sel, decoded_address[3], decoded_chip_sel[3]);
    and_gate a4(chip_sel, decoded_address[4], decoded_chip_sel[4]);
    and_gate a5(chip_sel, decoded_address[5], decoded_chip_sel[5]);
    and_gate a6(chip_sel, decoded_address[6], decoded_chip_sel[6]);
    and_gate a7(chip_sel, decoded_address[7], decoded_chip_sel[7]);
    
    memory_line m0(data_in, reset, clk, decoded_chip_sel[0], rd_en, wr_en, data_out);
    memory_line m1(data_in, reset, clk, decoded_chip_sel[1], rd_en, wr_en, data_out);
    memory_line m2(data_in, reset, clk, decoded_chip_sel[2], rd_en, wr_en, data_out);
    memory_line m3(data_in, reset, clk, decoded_chip_sel[3], rd_en, wr_en, data_out);
    memory_line m4(data_in, reset, clk, decoded_chip_sel[4], rd_en, wr_en, data_out);
    memory_line m5(data_in, reset, clk, decoded_chip_sel[5], rd_en, wr_en, data_out);
    memory_line m6(data_in, reset, clk, decoded_chip_sel[6], rd_en, wr_en, data_out);
    memory_line m7(data_in, reset, clk, decoded_chip_sel[7], rd_en, wr_en, data_out);
endmodule

module memory_module_32(input [7:0] data_in, input [4:0]address, input reset,
                    input rd_en, input wr_en, input clk, output [7:0] data_out);
    wire O0, O1, O2, O3;
    decoder_2to4 dec0(address[4], address[3], O0, O1, O2, O3);
    memory_module x0(data_in, reset, clk, rd_en, wr_en, O0, address[2:0], data_out);
    memory_module x1(data_in, reset, clk, rd_en, wr_en, O1, address[2:0], data_out);
    memory_module x2(data_in, reset, clk, rd_en, wr_en, O2, address[2:0], data_out);
    memory_module x3(data_in, reset, clk, rd_en, wr_en, O3, address[2:0], data_out);
endmodule

module memory_module_128(input [31:0] data_in, input [4:0]address, input reset, input rd_en, input wr_en, input clk, output [31:0] data_out);
    wire [31:0] final_output;
    memory_module_32 b0(data_in[31:24], address, reset, rd_en, wr_en, clk, final_output[31:24]);
    memory_module_32 b1(data_in[23:16], address, reset, rd_en, wr_en, clk, final_output[23:16]);
    memory_module_32 b2(data_in[15:8], address, reset, rd_en, wr_en, clk, final_output[15:8]);
    memory_module_32 b3(data_in[7:0], address, reset, rd_en, wr_en, clk, final_output[7:0]);
    assign data_out = final_output;
endmodule
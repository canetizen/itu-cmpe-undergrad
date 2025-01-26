`timescale 1ns / 1ps

module nand_gate(input a, input b, output o);
    assign o = ~(a & b);
endmodule

module SR_latch_wo_enable(input S, input R, output Q, output not_Q);
    wire not_s;
    wire not_r;
    nand_gate n0(S, S, not_s);
    nand_gate n1(R, R, not_r);
    nand_gate n2(Q, not_r, not_Q);
    nand_gate n3(not_Q, not_s, Q);
endmodule

module SR_latch_w_enable(input S, input R, input E, output Q, output not_Q);
    wire s;
    wire r;
    nand_gate n0(S, E, s);
    nand_gate n1(R, E, r);
    nand_gate n2(Q, r, not_Q);
    nand_gate n3(not_Q, s, Q);
endmodule

module D_latch(input E, input D, output wire Q, output wire Q_not);
  wire n1;
  wire n2;
  wire n3;
  wire n4;
  nand_gate g0(~D, E, n1);
  nand_gate g1(n1, E, n2);
  nand_gate g2(n2, E, n3);
  nand_gate g3(n3, E, n4);

  assign Q = ~n4;
  assign Q_not = ~n3;
endmodule

module D_flip_flop(input clk, input D, output Q,output Qnot);
    wire qtemp;
    wire qtemp_not;
    D_latch g1(~clk, D, qtemp, qtemp_not);
    D_latch g2(clk, qtemp, Q, Qnot);
endmodule

module JK_flip_flop(input clk, input J, input K, output reg Q, output reg not_Q);
    always @(posedge clk)
        case ({J,K})
           2'b00 : begin 
                   Q <= Q; 
                   not_Q <= not_Q; 
                   end
           2'b01 : begin 
                    Q <= 0; 
                    not_Q <= 1; 
                    end
           2'b10 : begin 
                    Q <= 1; 
                    not_Q <= 0; 
                    end
           2'b11 : begin 
                    Q <= ~Q; 
                    not_Q <= ~not_Q; 
                    end
        endcase
    initial begin 
        Q = 0;
        not_Q = 1;
    end
endmodule

module asyn_up_counter(input clk, input j, input k, output[3:0] data_out);
    wire not_q0;
    wire not_q1;
    wire not_q2;
    wire not_q3;
    JK_flip_flop j0(clk, j, k, data_out[0], not_q0);
    JK_flip_flop j1(not_q0, j, k, data_out[1], not_q1);
    JK_flip_flop j2(not_q1, j, k, data_out[2], not_q2);
    JK_flip_flop j3(not_q2, j, k, data_out[3], not_q3);
endmodule

module syn_up_counter(input clk, output[3:0] data_out);
    wire Q0;
    wire Q1;
    wire Q2; 
    wire Q3;
    wire jk2;
    wire jk3;
    JK_flip_flop j0(clk, 1, 1, data_out[0], Q0);
    JK_flip_flop j1(clk, data_out[0], data_out[0], data_out[1], Q1);
    JK_flip_flop j2(clk, jk2, jk2, data_out[2], Q2);
    JK_flip_flop j3(clk, jk3, jk3, data_out[3], Q3);
    assign jk3 = jk2 & data_out[2];
    assign jk2 = data_out[0] & data_out[1];
endmodule

module shift_register(input [15:0] data_in, input clk, input load, output reg Q);
    reg [15:0] prev, new;
    always @(posedge clk) begin
        if (load) begin
            prev <= data_in;
            new <= data_in;
        end else begin
            prev <= new;
            new <= {prev[14:0], prev[15]};
        end
        Q <= new[0];
    end
endmodule
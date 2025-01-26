`timescale 1ns/1ns

module SR_latch_wo_enable_test();
	reg S;
	reg R;
	wire Q;
	wire not_Q;
	SR_latch_wo_enable  uut(.S(S), .R(R), .Q(Q), .not_Q(not_Q));
	
	initial begin
		S=1; R=0; #200;
		S=0; R=0; #200;
		S=0; R=1; #200;
		S=0; R=0; #200;
		S=1; R=1; #200;
	end
endmodule

module SR_latch_w_enable_test();
	reg S;
	reg R;
	reg E;
	wire Q;
	wire not_Q;
	
	SR_latch_w_enable  uut(.S(S), .R(R), .E(E), .Q(Q), .not_Q(not_Q));
	
	initial begin
		S=0; E=0; R=0; #200;
		S=1; E=1; R=0; #200;
		S=0; E=1; R=1; #200;
		S=0; E=0; R=0; #200;
		S=0; E=1; R=0; #200;
		S=1; E=1; R=1; #200;
	end
endmodule

module D_latch_test();
    reg D, E;

    wire Q, Q_not;

    D_latch  uut(.D(D), .E(E), .Q(Q), .Q_not(Q_not));

    initial begin
        D=0; E=0; #125;
        D=0; E=1; #125;
        D=1; E=0; #125;
        D=1; E=1; #125;
        D=0; E=0; #125;
        D=0; E=1; #125;
        D=1; E=0; #125;
        D=1; E=1; #125;
    end
endmodule

module d_flip_flop_test();
    reg D, clk;
    wire Q, Q_not;

    D_flip_flop uut(.clk(clk), .D(D), .Q(Q), .Qnot(Q_not));

    initial begin
        D=0; clk=0; #125;
        D=0; clk=1; #125;
        D=1; clk=0; #125;
        D=1; clk=1; #125;
        D=0; clk=0; #125;
        D=0; clk=1; #125;
        D=1; clk=0; #125;
        D=1; clk=1; #125;
    end
endmodule

module jk_flip_flop_test();
	reg J;
	reg K;
	reg clk;
	wire Q;
	wire not_Q;
	
	JK_flip_flop uut(clk, J, K, Q, not_Q);

    initial clk = 1;
        always #50 clk = ~clk;
    
    initial begin 
     J= 1; K= 0;
     #100; J= 0; K= 1; 
     #100; J= 0; K= 0; 
     #100; J= 1; K=1;
     end
initial
  #1000 $finish;
endmodule

module async_up_counter_test;
    reg clk;
    wire [3:0] Q;
    reg J, K;

    asyn_up_counter uut (clk, J, K, Q);

    initial begin
        clk = 0;
        J = 0; K = 1; #10;
        J = 1; K = 1;
    end
    always begin
        #10 clk = ~clk;
    end
endmodule
module sync_up_counter_test;
    reg clk;
    wire [3:0] Q;

    syn_up_counter uut (clk, Q);

    initial begin
        clk = 0;
    end

    always begin
        #10 clk = ~clk;
    end
endmodule

module shift_register_test();
       reg [15:0] data_in;
       reg clk;
       reg load;
       wire Q;
       
       shift_register uut(.data_in(data_in), .clk(clk), .load(load), .Q(Q));
       
       initial begin
            clk=0;
            data_in=16'b1010101010101010; load=1; #8;
            load=0; #128;
            data_in=16'b1100110011001100; load=1; #8;
            load=0; #128;
            data_in=16'b1111000011110000; load=1; #8;
            load=0; #128;
            data_in=16'b1000000010000000; load=1; #8;
            load=0; #128;
            data_in=16'b1110000000000000; load=1; #8;
            load=0; #128;
            data_in=16'b1111111111100000; load=1; #8;
            load=0; #128;
        end
        
        always begin 
            #4; clk=~clk;
        end 
endmodule 
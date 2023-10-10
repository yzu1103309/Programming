module SIPO(in, En, clk, rst, Q);

input in, En, clk, rst;
output [3:0] Q;

D_F(in, Q[0], En, clk, rst);
D_F(Q[0], Q[1], En, clk, rst);
D_F(Q[1], Q[2], En, clk, rst);
D_F(Q[2], Q[3], En, clk, rst);

endmodule

module D_F(D, Q, En, clk, rst);

input D, En, clk, rst;
output reg Q;

always @ (posedge clk)
	if(En)
	begin Q<=D; end

endmodule

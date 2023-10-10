module LFSR(seed, enable, clk, D);

input clk, enable, seed;
output [5:0] D;
wire o, x45; 

xor(x45, D[4], D[5]);
mux(o, x45, seed, enable);
D_flip_flop(D[0], o, clk);
D_flip_flop(D[1], D[0], clk);
D_flip_flop(D[2], D[1], clk);
D_flip_flop(D[3], D[2], clk);
D_flip_flop(D[4], D[3], clk);
D_flip_flop(D[5], D[4], clk);


endmodule

module D_flip_flop(Q, D, Clk);
  output Q;
  input D, Clk;
  reg Q;
  
  always @ (posedge Clk)    
    Q <= D;
endmodule

module mux(OUT,A,B,SEL);

input A, B, SEL;
output OUT;
wire SELB, OUT1, OUT2;

not NOT1(SELB, SEL);
and AND1(OUT1, SELB, A);
and AND2(OUT2, SEL, B);
or OR1(OUT, OUT1, OUT2);

endmodule

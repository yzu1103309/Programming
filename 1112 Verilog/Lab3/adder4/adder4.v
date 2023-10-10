module adder4(A, B, S, Cout);

input [3:0] A,B;
output [3:0] S;
output Cout;

wire Co0, Co1, Co2;

fadd r0(.A(A[0]), .B(B[0]), .S(S[0]) , .Cout(Co0));
fadd r1(.Ci(Co0) , .A(A[1]) , .B(B[1]), .S(S[1]), .Cout(Co1));
fadd r2(.Ci(Co1), .A(A[2]), .B(B[2]), .S(S[2]), .Cout(Co2));
fadd r3(.Ci(Co2), .A(A[3]),.B(B[3]), .S(S[3]), .Cout (Cout)) ;

endmodule

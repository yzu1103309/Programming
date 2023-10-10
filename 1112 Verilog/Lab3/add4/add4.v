module add4(Sum,C_out,A,B,C_in);
input [3:0]A,B;
input C_in;
output [3:0]Sum;
output C_out;

wire C1,C2,C3;

full_adder FAO(.sum(Sum[0]), .c_out(C1), .a(A[0]), .b(B[0]), .c_in(C_in));
full_adder FA1(.sum(Sum[1]), .c_out(C2), .a(A[1]), .b(B[1]), .c_in(C1));
full_adder FA2(.sum(Sum[2]), .c_out(C3), .a(A[2]), .b(B[2]), .c_in(C2));
full_adder FA3(.sum(Sum[3]), .c_out(C_out), .a(A[3]), .b(B[3]), .c_in(C3));

endmodule

module full_adder(sum, c_out, a, b, c_in);

	input a, b, c_in;
	output sum, c_out;
	
	assign sum = (a^b)^c_in;
	assign c_out = (a&b)|(c_in&(a^b));
	
endmodule

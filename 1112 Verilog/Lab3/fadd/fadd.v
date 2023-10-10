module fadd
(
	//input ports
	input Ci,
	input A,
	input B,
	
	//output ports
	output S,
	output Cout
);

	assign {Cout, S} = Ci + A + B;
	
endmodule

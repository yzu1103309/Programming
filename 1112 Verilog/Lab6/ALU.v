module ALU(A, B, sel, aluo);

	input [3:0] A;
	input [3:0] B;
	input [1:0] sel;
	
	//output ports
	output reg [4:0] aluo;

	always @ (A, B, sel)
	begin
		if(sel == 2'b00)
			aluo = A | B;
		else if(sel == 2'b01)
			aluo = A & B;
		else if(sel == 2'b10)
			aluo = A - B;
		else if(sel == 2'b11)
			aluo = A + B;
	end
endmodule

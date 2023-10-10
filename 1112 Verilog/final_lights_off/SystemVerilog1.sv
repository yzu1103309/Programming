module lights_off(sw, lights);
	input [9:0] sw;
	reg [9:0] last = 10'b0000000000;
	output reg [9:0] lights = 10'b0000000000;
	parameter [9:0] 
		c9 = 10'b1100000000,
		c8 = 10'b1110000000,
		c7 = 10'b0111000000;
		
	
	always@(*)
	begin 
		if(last[9] != sw[9])
		begin
			lights = lights ^ 10'b1100000000;
			last[9] = sw[9];
		end
	end	
	
endmodule

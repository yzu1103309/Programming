	module lights_off(sw, lights, clk, btn_fix, btn_rand);
	input [9:0] sw;
	input clk, btn_fix, btn_rand;
	reg fix_last = 0;
	reg [9:0] last = 10'b0000000000;
	reg [9:0] rd = 10'b0000000000;
	reg [23:0] fr;
	output reg [9:0] lights = 10'b0000000000;
	parameter [9:0] 
		c9 = 10'b1100000000,
		c8 = 10'b1110000000,
		c7 = 10'b0111000000,
		c6 = 10'b0011100000,
		c5 = 10'b0001110000,
		c4 = 10'b0000111000,
		c3 = 10'b0000011100,
		c2 = 10'b0000001110,
		c1 = 10'b0000000111,
		c0 = 10'b0000000011;
	
	parameter [9:0]
		q1 = 10'b1100000001,
		q2 = 10'b0111111110;

	always @ (posedge clk) 
	begin
	
		rd += 1;
		fr += 1;
		
		if(~btn_fix)
		begin
			lights = q2;
		end
		
		if(~btn_rand)
		begin
			lights = rd[0]*c0 ^ rd[1]*c1 ^ rd[2]*c2 ^ rd[3]*c3 ^ rd[4]*c4 ^ rd[5]*c5 ^ rd[6]*c6 ^ rd[7]*c7 ^ rd[8]*c8 ^ rd[9]*c9;
		end
		
		if(~fr[23])
		begin
			if(sw[9] != last[9])
			begin
				last[9] = sw[9];
				lights = lights^c9;	
			end
			if(sw[8] != last[8])
			begin
				last[8] = sw[8];
				lights = lights^c8;
			end
			if(sw[7] != last[7])
			begin
				last[7] = sw[7];
				lights = lights^c7;
			end
			if(sw[6] != last[6])
			begin
				last[6] = sw[6];
				lights = lights^c6;
			end
			if(sw[5] != last[5])
			begin
				last[5] = sw[5];
				lights = lights^c5;
			end
			if(sw[4] != last[4])
			begin
				last[4] = sw[4];
				lights = lights^c4;
			end
			if(sw[3] != last[3])
			begin
				last[3] = sw[3];
				lights = lights^c3;
			end
			if(sw[2] != last[2])
			begin
				last[2] = sw[2];
				lights = lights^c2;
			end
			if(sw[1] != last[1])
			begin
				last[1] = sw[1];
				lights = lights^c1;
			end
			if(sw[0] != last[0])
			begin
				last[0] = sw[0];
				lights = lights^c0;
			end
		end
	end
endmodule

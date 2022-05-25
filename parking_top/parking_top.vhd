----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    06:13:57 05/25/2022 
-- Design Name: 
-- Module Name:    parking_top - Behavioral 
-- Project Name: 
-- Target Devices: 
-- Tool versions: 
-- Description: 
--
-- Dependencies: 
--
-- Revision: 
-- Revision 0.01 - File Created
-- Additional Comments: 
--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity parking_top is
    Port ( RTC : in  STD_LOGIC;
           RFID : in  STD_LOGIC;
			  RST_DATA : in STD_LOGIC;
           SW_FPGA : in  STD_LOGIC;
           IR1_FPGA : in  STD_LOGIC;
           IR2_FPGA : in  STD_LOGIC;
           IR3_FPGA : in  STD_LOGIC;
           num_car_msb : out  STD_LOGIC;
           num_car_lsb : inout  STD_LOGIC;
           A, B, C, D, E, F, G : out  STD_LOGIC);
end parking_top;

architecture Behavioral of parking_top is
---------- count car in parking zone -----------------------
	component parking_encoder
	port (  IR1 : in  STD_LOGIC;
           IR2 : in  STD_LOGIC;
           IR3 : in  STD_LOGIC;
           A : out  STD_LOGIC;
           B : out  STD_LOGIC);
	end component parking_encoder;

------------- count number of cars come to park in 1 day --------
	component counter_4bit
	port ( clk : in  STD_LOGIC;
           rst : in  STD_LOGIC;
           o : out  STD_LOGIC_VECTOR (3 downto 0));
	end component counter_4bit;

------------ store number of cars come to park in 1 day ----------	
	component d_flipflop_out4bit
	port ( D : in  STD_LOGIC_VECTOR (3 downto 0);
           clk : in  STD_LOGIC;
           rst : in  STD_LOGIC;
           Q : out  STD_LOGIC_VECTOR (3 downto 0));
	end component d_flipflop_out4bit;

-------------- select data - now or last day - to show on 7 segment ----------------
	component select_num_cars
	port ( D0 : in  STD_LOGIC_VECTOR (3 downto 0);
           D1 : in  STD_LOGIC_VECTOR (3 downto 0);
           S0 : in  STD_LOGIC;
           Z : out  STD_LOGIC_VECTOR (3 downto 0));
	end component select_num_cars;
	
--------------- decode data to show on 7 segment ------------------------------------
	component bcd_7seg_decoder 
    Port ( B_in : in  STD_LOGIC_VECTOR(3 downto 0);
           A : out  STD_LOGIC;
           B : out  STD_LOGIC;
           C : out  STD_LOGIC;
           D : out  STD_LOGIC;
           E : out  STD_LOGIC;
           F : out  STD_LOGIC;
           G : out  STD_LOGIC);
	end component bcd_7seg_decoder; 
	
-----------------------------------------------------------------------	
--------------------- map port ----------------------------------------
-----------------------------------------------------------------------
signal out_counter, out_data_storage, out_select : STD_LOGIC_VECTOR(3 downto 0);


begin

	Block0 : entity work.parking_encoder
	port map(
				IR1 <= IR1_FPGA,
				IR2 <= IR2_FPGA,
				IR3 <= IR3_FPGA,
				A <= num_car_msb,
				B <= num_car_lsb
	);

	
	Block1 : entity work.counter_4bit
	port map(
				clk <= RFID,
				rst <= RTC,
				o <= out_counter	
	);
	
	Block2 : entity work.d_flipflop_out4bit
	port map(
				D <= out_counter,
				clk <= RTC,
				rst <= RST_DATA,
				Q <= out_data_storage
	);
	
	Block3 : entity work.select_num_cars
	port map(
				D0 <= out_counter,
				D1 <= out_data_storage,
				S0 <= SW_FPGA,
				Z <= out_select
	);
	
	Block4 : entity work.bcd_7seg_decoder
	port map(
				B_in <= out_select,
				A <= A,
				B <= B,
				C <= C,
				D <= D,
				E <= E,
				F <= F,
				G <= G
	);
	
	
end Behavioral;


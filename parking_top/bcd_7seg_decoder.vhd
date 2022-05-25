----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    06:18:50 05/25/2022 
-- Design Name: 
-- Module Name:    bcd_7seg_decoder - Behavioral 
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

entity bcd_7seg_decoder is
    Port ( B_in : in  STD_LOGIC_VECTOR(3 downto 0);
           A : out  STD_LOGIC;
           B : out  STD_LOGIC;
           C : out  STD_LOGIC;
           D : out  STD_LOGIC;
           E : out  STD_LOGIC;
           F : out  STD_LOGIC;
           G : out  STD_LOGIC);
end bcd_7seg_decoder;

architecture Behavioral of bcd_7seg_decoder is

begin
	A <= B_in(0) OR B_in(2) OR (B_in(1) AND B_in(3)) OR (NOT B_in(1) AND NOT B_in(3));
	B <= (NOT B_in(1)) OR (NOT B_in(2) AND NOT B_in(3)) OR (B_in(2) AND B_in(3));
	C <= B_in(1) OR NOT B_in(2) OR B_in(3);
	D <= (NOT B_in(1) AND NOT B_in(3)) OR (B_in(2) AND NOT B_in(3)) OR (B_in(1) AND NOT B_in(2) AND B_in(3)) OR (NOT B_in(1) AND B_in(2)) OR B_in(0);
	E <= (NOT B_in(1) AND NOT B_in(3)) OR (B_in(2) AND NOT B_in(3));
	F <= B_in(0) OR (NOT B_in(2) AND NOT B_in(3)) OR (B_in(1) AND NOT B_in(2)) OR (B_in(1) AND NOT B_in(3));
	G <= B_in(0) OR (B_in(1) AND NOT B_in(2)) OR ( NOT B_in(1) AND B_in(2)) OR (B_in(2) AND NOT B_in(3));



end Behavioral;


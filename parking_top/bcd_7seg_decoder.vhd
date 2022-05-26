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
           Seven_Segment : out STD_LOGIC_VECTOR (6 downto 0));
end bcd_7seg_decoder;

architecture Behavioral of bcd_7seg_decoder is

begin
	process(B_in)
begin
 
case B_in is
when "0000" =>
Seven_Segment <= "1111110"; --0

when "0001" =>
Seven_Segment <= "0110000"; --1

when "0010" =>
Seven_Segment <= "1101101"; --2

when "0011" =>
Seven_Segment <= "1111001"; --3

when "0100" =>
Seven_Segment <= "0110011"; --4

when "0101" =>
Seven_Segment <= "1011011"; --5

when "0110" =>
Seven_Segment <= "1011111"; --6

when "0111" =>
Seven_Segment <= "1110000"; --7

when "1000" =>
Seven_Segment <= "1111111"; --8

when "1001" =>
Seven_Segment <= "1111011"; --9

when others =>
Seven_Segment <= "0000000"; --null

end case;
 
end process;




end Behavioral;


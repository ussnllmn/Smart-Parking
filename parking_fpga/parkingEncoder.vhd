----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    21:17:50 05/22/2022 
-- Design Name: 
-- Module Name:    parkingEncoder - Behavioral 
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

entity parkingEncoder is
    Port ( IR1 : in  STD_LOGIC;
           IR2 : in  STD_LOGIC;
           IR3 : in  STD_LOGIC;
           A : out  STD_LOGIC;
           B : out  STD_LOGIC);
end parkingEncoder;

architecture Behavioral of parkingEncoder is

begin
	A <= (IR3 and IR2) or (IR1 and IR2) or (IR1 and IR3);
	B <= ((not IR1) and (not IR2) and IR3) or ((not IR1) and IR2 and (not IR3)) or (IR1 and (not IR2) and (not IR3)) or (IR1 and IR2 and IR3);

end Behavioral;


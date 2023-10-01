#include"Coding.h"
std::bitset<28> Shifting_Sub_Key(const std::bitset<28>& key)
{
	std::bitset<28> for_return;
	if (key[27] == 1)
	{
		for_return = (key << 1);
		for_return.set(0, true);
	}
	else
	{
		for_return = (key << 1);
	}
	return for_return;
}
inline bool return_valor_forbit(char bit)
{
	if (bit == '1')
		return true;
	else
		return false;
}
void Password_Coding(const int* pc1, const int* pc2)
{
	std::string string_password;
	std::bitset<64> password_in_bits = 0x133457799BBCDFF1;
	std::bitset<28> C[16]{ 0 };
	std::bitset<28> D[16]{ 0 };
	std::bitset<48> key[16]{ 0 };
	std::cout << "Introdu Parola: ";
	std::getline(std::cin, string_password);
	while(string_password.size()<8)
	{
		std::cout << "Parola nu trebue sa fie mai putin de 8 caractere, reintrodu: ";
		string_password.clear();
		std::getline(std::cin, string_password);
	}
	string_password = password_in_bits.to_string();
	std::cout << string_password;
	password_in_bits.reset();
	for(int i=0;i<56;i++)
	{
		if (i < 28) 
		{
			if (string_password.c_str()[pc1[i] - 1] == '1')
				C[0].set(27 - i, true);
			else
				C[0].set(27 - i, false);
		}
		else
		{
			if (string_password.c_str()[pc1[i] - 1] == '1')
				D[0].set(27 - (i-28), true);
			else
				D[0].set(27 - (i - 28), false);
		}
	}
	std::cout << "\n" << C[0] << "\n" << D[0] << "\n---------\n";
	for(int i=0;i<=16;i++)
	{
		if((i+1 == 1) || (i+1 == 2) || (i+1 == 9) || (i+1 == 16))
		{
			D[i + 1] = Shifting_Sub_Key(D[i]);
			C[i + 1] = Shifting_Sub_Key(C[i]);
		}
		else
		{
			for(int j=i;j<=i+1;j++)
			{
				D[i + 1] = Shifting_Sub_Key(D[j]);
				C[i + 1] = Shifting_Sub_Key(C[j]);
			}
		}
		if(i>=1)
		{
			std::cout << C[i] << "\n";
			uint64_t temporar;
			temporar = C[i].to_ullong();
			temporar <<= 28;
			temporar += D[i].to_ullong();
			std::bitset<56> temporar_key = temporar;
			string_password = temporar_key.to_string();
			std::cout << string_password << "\n";
			for(int j=0;j<48;j++)
			{
				if (string_password.c_str()[pc2[j] - 1] == '1') 
				{
					key[i - 1].set(j, true);
				}
				else 
				{
					key[i - 1].set(j, false);
				}
			}
		}
	}
}
void Coding_Message(const int* ip, const int* expansion_table)
{
	//std::cout << "Introdu Mesajul: ";
	std::string message = "0000000100100011010001010110011110001001101010111100110111101111";
	std::bitset<64> bit_message;
	std::bitset<32> left_message[16];
	std::bitset<32> right_message[16];
	//std::getline(std::cin, message);
	for (int i = 0; i < 64; i++)
	{
		if (i < 32)
			left_message[0].set(31 - i, return_valor_forbit(message.c_str()[ip[i] - 1]));
		else
			right_message[0].set(31- (i - 32), return_valor_forbit(message.c_str()[ip[i] - 1]));
	}
	for(int i=1;i<16;i++)
	{
		left_message[i] = right_message[i - 1];
		right_message[i] = left_message[i - 1];
		std::bitset<48> temporar = 0;
		for(int j = 0; j < 48; j++)
		{
			temporar.set(47 - j, return_valor_forbit(right_message[i - 1].to_string().c_str()[expansion_table[j] - 1]) );
		}
	}
}
int main(void)
{
	int pc1[56] = {
	57,49,41,33,25,17,9,
	1,58,50,42,34,26,18,
	10,2,59,51,43,35,27,
	19,11,3,60,52,44,36,
	63,55,47,39,31,23,15,
	7,62,54,46,38,30,22,
	14,6,61,53,45,37,29,
	21,13,5,28,20,12,4
	};
	int pc2[48] = {
	14,17,11,24,1,5,
	3,28,15,6,21,10,
	23,19,12,4,26,8,
	16,7,27,20,13,2,
	41,52,31,37,47,55,
	30,40,51,45,33,48,
	44,49,39,56,34,53,
	46,42,50,36,29,32
	};
	int ip[64] = { 
	58,50,42,34,26,18,10,2,
	60,52,44,36,28,20,12,4,
	62,54,46,38,30,22,14,6,
	64,56,48,40,32,24,16,8,
	57,49,41,33,25,17,9,1,
	59,51,43,35,27,19,11,3,
	61,53,45,37,29,21,13,5,
	63,55,47,39,31,23,15,7 
	};
	int expansion_table[48] = {
	32,1,2,3,4,5,4,5,
	6,7,8,9,8,9,10,11,
	12,13,12,13,14,15,16,17,
	16,17,18,19,20,21,20,21,
	22,23,24,25,24,25,26,27,
	28,29,28,29,30,31,32,1
	};
	Coding cod;
	cod.coding_password();
	cod.coding_message();
}
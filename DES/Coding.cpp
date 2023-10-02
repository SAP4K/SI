#include "Coding.h"
Coding::Coding() {};
Coding::Coding(std::string Password, std::string Message ): password(Password), message(Message)
{
}
void Coding::set_message(void)
{
	std::cout << "Introdu mesajul: ";
	std::getline(std::cin, this->message);
	std::bitset<64> temporar_buffer = 0;
	uint64_t message_to_64_bits = 0;
	while(this->message.empty())
	{
		std::cout << "Nu este introdu nimic, introdu text: "; 
		std::getline(std::cin, this->message);
	}
	for(uint8_t i = 0; i < this->message.size();i++)
	{
		message_to_64_bits = message_to_64_bits << 8;
		message_to_64_bits += (uint8_t) this->message.c_str()[i];
		temporar_buffer = message_to_64_bits;
	}
	std::cout<<"Mesajul in Decimal: " << message_to_64_bits<<"\n";
	this->message = temporar_buffer.to_string();
}
void Coding::set_password(void)
{
	std::cout << "Introdu parola: ";
	std::getline(std::cin, this->password);
	std::bitset<64> temporar_buffer = 0;
	uint64_t password_to_64_bits = 0;
	while((this->password.size()<8) || (this->password.size() > 8) )
	{
		std::cout << "Parola prea scurta sau prea lunga, introdu alta(8 caractere): ";
		std::getline(std::cin, this->password);
	} 
	for(uint8_t i=0;i<this->password.size();i++)
	{
		password_to_64_bits = password_to_64_bits << 8;
		password_to_64_bits += (uint8_t) this->password.c_str()[i];
	}
	temporar_buffer = password_to_64_bits;
	std::cout << "Parola In Decimal: " << password_to_64_bits << "\n";
	this->password = temporar_buffer.to_string();
}
std::bitset<28> Coding::Shifting_Sub_Key(const std::bitset<28>& key)
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
inline bool Coding::return_valor_from_bit(char bit)
{
	if (bit == '1')
		return true;
	else
		return false;
}
void Coding::coding_password(void)
{
	if(this->password.empty())
	{
		std::cout << "Nu este introdusa parola\n";
		return;
	}
	std::bitset<28> C[17]{ 0 };
	std::bitset<28> D[17]{ 0 };
	for (uint8_t i = 0; i < 56; i++)
	{
		if (i < 28)
			C[0].set(27 - i, this->return_valor_from_bit(this->password.c_str()[pc1[i] - 1]));
		
		else
			D[0].set(27 - (i - 28), this->return_valor_from_bit(this->password.c_str()[pc1[i] - 1]));
	}
	for (uint8_t i = 0; i < 17; i++)
	{
		if(i<16)
			if ((i + 1 == 1) || (i + 1 == 2) || (i + 1 == 9) || (i + 1 == 16))
			{
				D[i+1] = Shifting_Sub_Key(D[i]);
				C[i+1] = Shifting_Sub_Key(C[i]);
			}
			else
				for (uint8_t j = i; j <= i + 1; j++)
				{
					D[i+1] = Shifting_Sub_Key(D[j]);
					C[i+1] = Shifting_Sub_Key(C[j]);
				}
		if (i >= 1)
		{
			uint64_t temporar;
			temporar = C[i].to_ullong();
			temporar <<= 28;
			temporar += D[i].to_ullong();
			std::bitset<56> temporar_key = temporar;
			for (int j = 0; j < 48; j++)
				this->key[i-1].set(47 - j, this->return_valor_from_bit(temporar_key.to_string().c_str()[this->pc2[j] - 1]));
		}
	}
}
void Coding::coding_message(void)
{
	std::bitset<32> left_message[17];
	std::bitset<32> right_message[17];
	std::bitset<64> invers_permutation_result = 0;
	for (uint8_t i = 0; i < 64; i++)
	{
		if (i < 32)
			left_message[0].set(31 - i, this->return_valor_from_bit(this->message.c_str()[ip[i] - 1]));
		else
			right_message[0].set(31 - (i - 32), this->return_valor_from_bit(this->message.c_str()[ip[i] - 1]));
	}
	for (uint8_t i = 1; i < 17; i++)
	{
		left_message[i] = right_message[i - 1];
		std::bitset<48> function_for_coding = 0;

		for (uint8_t j = 0; j < 48; j++)
		{
			function_for_coding.set(47 - j, this->return_valor_from_bit(right_message[i - 1].to_string().c_str()[this->expansion_table[j] - 1]) );
		}
		function_for_coding ^= this->key[i - 1];
		uint32_t  valor = 0;
		std::bitset<32> s_box_result = 0;
		for(uint8_t j=1;j<=8;j++)
		{
			uint8_t from = (j*6)-6;
			uint8_t to = (j * 6);
			std::string temporar_valor =  function_for_coding.to_string().substr(from, to);
			std::bitset<2> y = 0;
			std::bitset<4> x = 0;
			for(uint8_t q=0;q<6;q++)
			{
				if(q == 0 || q==5)
				{
					y = y << 1;
					y.set(0,this->return_valor_from_bit( temporar_valor.c_str()[q] ));
				}
				else
				{
					x = x << 1;
					x.set(0, this->return_valor_from_bit( temporar_valor.c_str()[q] ));
				}
			}
			valor = valor << 4;
			valor += this->substition_boxes[j - 1][y.to_ullong()][x.to_ullong()];
			s_box_result = valor;
		}
		for(uint8_t j = 0; j<32; j++)
			right_message[i].set(31-j, this->return_valor_from_bit( s_box_result.to_string().c_str()[this->s_box_permutation[j] - 1]) );
		right_message[i] ^= left_message[i - 1];
	}
	uint64_t left_right_message = (right_message[16].to_ullong()<<32) + left_message[16].to_ullong();
	invers_permutation_result = left_right_message;
	for(uint8_t i=0;i<64;i++)
		this->encrypted_message.set(63 - i, this->return_valor_from_bit(invers_permutation_result.to_string().c_str()[inverse_permutation[i] - 1]  ));
	std::cout << this->encrypted_message.to_ullong();
}
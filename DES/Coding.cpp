#include "Coding.h"
void Coding::set_message()
{
	std::cout << "Introdu mesajul: ";
	std::getline(std::cin, this->message);
}
void Coding::set_password()
{
	std::cout << "Introdu parola: ";
	std::getline(std::cin, this->password);
	while(this->password.size()<8)
	{
		std::cout << "Parola prea scurta, introdu alta: ";
		std::getline(std::cin, this->password);
	}
}
void Coding::coding_password()
{

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
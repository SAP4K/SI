#pragma once
#include<iostream>
#include<sstream>
#include<bitset>
class Coding
{
public:
	Coding();
	Coding(std::string, std::string);
	void set_password();
	void coding_password();
	void set_message();
	void coding_message();
private:
	uint8_t pc1[56] = {57,49,41,33,25,17,9,1,58,50,42,34,26,18,10,2,59,51,43,35,27,19,11,3,60,52,44,36,63,55,47,39,31,23,15,7,62,54,46,38,30,22,14,6,61,53,45,37,29,21,13,5,28,20,12,4};
	uint8_t pc2[48] = {14,17,11,24,1,5,3,28,15,6,21,10,23,19,12,4,26,8,16,7,27,20,13,2,41,52,31,37,47,55,30,40,51,45,33,48,44,49,39,56,34,53,46,42,50,36,29,32};
	uint8_t  ip[64] =  {58,50,42,34,26,18,10,2,60,52,44,36,28,20,12,4,62,54,46,38,30,22,14,6,64,56,48,40,32,24,16,8,57,49,41,33,25,17,9,1,59,51,43,35,27,19,11,3,61,53,45,37,29,21,13,5,63,55,47,39,31,23,15,7};
	std::string password;
	std::string message;
	std::bitset<48> key[16]{ 0 };
	std::bitset<28> Shifting_Sub_Key(const std::bitset<28>&);
};


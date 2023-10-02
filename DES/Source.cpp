#include"Coding.h"
#include"Decoding.h"
int main(void)
{
	Coding cod;
	Decoding dec;
	cod.set_password();
	cod.set_message();
	cod.coding_password();
	cod.coding_message();
	//-------------decoding-------------
	std::cout << "\n";
	dec.set_password();
	dec.coding_password();
	dec.set_encrypted_message();
	dec.decrypting_message();
	dec.show_message();
}
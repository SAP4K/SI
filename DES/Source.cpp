#include"Coding.h"
#include"Decoding.h"
int main(void)
{
	Coding cod;
	cod.set_password();
	cod.coding_password();
	cod.coding_message();
	Decoding dec;
	dec.coding_password();
	dec.decrypting_message();
}
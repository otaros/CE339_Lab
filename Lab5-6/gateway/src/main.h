#ifndef __MAIN__
#define __MAIN__

#define PAIRED (1 << 0)

enum msg_type
{
	PAIRING,
	PAIRING_RESPONSE,
	DATA,
	DATA_RESPONSE,
};

#endif // !__MAIN__
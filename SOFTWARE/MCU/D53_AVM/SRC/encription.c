#define		SECURITYCONSTANT    0x26031961

WORD seedToKey (WORD wSeed, DWORD constData)
{ 
	DWORD wLastSeed ;
	WORD wLastKey;

	wLastSeed= wSeed; /*2 byte wSeed as LSB, and ¡° 0x0000¡± as MSB*/
	wLastSeed = (wLastSeed>>5) | (wLastSeed<<23);
	wLastSeed *= 7;
	wLastSeed ^= SECURITYCONSTANT;
	wLastKey = (WORD)wLastSeed;
	return wLastKey;
} 


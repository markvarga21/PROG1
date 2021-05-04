#include <stdio.h>
#include <stdlib.h>

void csere(int* a, int* b)
{
	*a = *a - *b;
	*b = *b + *a;
	*a = *b - *a;
}

int szohossz(char* szo)
{
	int cnt = 0, index = 0;
	while (szo[index] != '\0')
	{
		cnt++;
		index++;
	}
	return cnt;
}

int main()
{
	// valtozocsere
	int numb1 = 5, numb2 = 10;
	printf("Kezdeti szamparok: numb1 = %d, numb2 = %d\n", numb1, numb2);
	csere(&numb1, &numb2);
	printf("Cserelt szamparok: numb1 = %d, numb2 = %d\n\n", numb1, numb2);

	// szohossz
	char* szo = "Hello";
	printf("A %s szo hossza: %d\n", szo, szohossz(szo));
	return 0;
}
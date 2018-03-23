#include "damen.h"

int testbrett(int brett[], int n)
{
	int i, j, l, k;

	for(j = 0; j < n; j++)
	{
		for(i = 0; i < n; i++)
		{
			if(brett[j * n + i] )
			{
				for(k = 0; k < n; k++)
				{
					for(l = 0; l < n; l++)
					{
						if(!(i == l && j == k))
						{
							if(brett[k * n + l])
							{
								if(j == k || i == l || i + j == l + k)
								{
									return 0;
								}
							}
						}
					}
				}
			}
		}
	}

	return 1;
}

int dame(int brett[], int n)
{
	return -1;
}

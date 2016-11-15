#include<stdio.h>
#include<time.h>
#include<unistd.h>
#include<stdlib.h>

#define MAX 9
#define RREADY srand(time(NULL))
#define RANDOM rand()

int maker(int arr[][MAX], int i, int j, int depth);
int printer(int arr[][MAX]);
int search(int arr[][MAX], int i, int j, int buf2);

int ret = 0;
int tmp_i = 0;
int tmp_j = 0;
unsigned int try = 0;

int main(int argc, char* argv[])
{
        int mainsig = -1;
        int arr[MAX][MAX] = {0,};
        int para;

	if (argc < 2 || argv[1][0] < '0' || argv[1][0] > '8')
	{
		printf ("-- How to use --\n");
		printf ("%s [0-8]\n", argv[0]);
		return 1;
	}

	para = atoi(argv[1]);

	mainsig = maker(arr, 0, -1, para);
	printf ("mainsig = %d\n", mainsig);

	return 0;
}
int search(int arr[][MAX], int i, int j, int buf2)
{
	int k, l;

	for (k = 0; k < MAX; k++)
	{
		if (k == j)
			continue;

		if (arr[i][k] == buf2 + 1)
			return 1;
	}

	for (k = 0; k < MAX; k++)
	{
		if (k == i)
			continue;

		if (arr[k][j] == buf2 + 1)
			return 2;
	}

	if (i == j)
		for (k = 0; k < MAX; k++)
		{
			if (i == k && j == k)
				continue;

			if (arr[k][k] == buf2 + 1)
				return 3;
		}
	if ((i + j) == (MAX - 1))
		for (k = 0, l = MAX - 1; k < MAX || l > -1; k++, l--)
		{
			if (i == k && j == l)
				continue;

			if (arr[k][l] == buf2 + 1)
				return 4;
		}

	for (k = (i / 3) * 3; k < ((i / 3) * 3) + 3; k++)
		for (l = (j / 3) * 3; l < ((j / 3) * 3) + 3; l++)
		{
			if (i == k && j == l)
				continue;

			if (arr[k][l] == buf2 + 1)
				return 5;
		}

	return 0;
}
int maker(int arr[][MAX], int i, int j, int depth)
{
	int k, l, m, n;
	int buf2 = 0;
	int buf[MAX] = {0, };
	int sig = 0;

	j++;

	if (j > 8)
	{
		i++;
		j = 0;
	}

	if (i > 8)
	{
		printf ("\n\n");
		printer(arr);
		printf ("\n");
		printf ("the number of try : %u\n", try);
		exit(0);
	}

	while(i < 9)
	{
		if (i < depth)
		{
			sleep(1);
			RREADY;
			buf2 = RANDOM % MAX;
			try++;
		}

		else
		{
			for (l = 0; l < MAX; l++)
				if (!buf[l])
					break;
			buf2 = l;
			try++;
		}

		sig = search(arr, i, j, buf2);

		if (!sig && !buf[buf2])
		{
			buf[buf2] = 1;
			arr[i][j] = buf2 + 1;
			sig = maker(arr, i, j, depth);
		}

		else
			buf[buf2] = 1;

		for (k = 0; k < MAX; k++)
			if (!buf[k])
				break;
		if (k > (MAX - 1))
		{
			arr[i][j] = 0;
			return -1;
		}
	}
	return 0;
}
int printer(int arr[][MAX])
{
	int i;
	int j;

	for (i = 0; i < MAX; i++)
	{
		for (j = 0; j < MAX; j++)
			printf ("%d ", arr[i][j]);
		printf ("\n");
	}

	return 0;
}

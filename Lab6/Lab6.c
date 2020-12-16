#include <stdio.h>
#include <stdbool.h>

int Frame[10][100];
char s[100];
int n, f;
int In[100];
bool Err[100];

void init()
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 100; j++)
			Frame[i][j] = -1;
	for (int i = 0; i < 100; i++)
	{
		In[i] = -1;
		Err[i] = false;
	}
	In[0] = 1;
	In[1] = 8;
	In[2] = 5;
	In[3] = 2;
	In[4] = 0;
	In[5] = 3;
	In[6] = 8;
	In[7] = 1;
	In[8] = 0;
	In[9] = 0;
	In[10] = 7;
	n = 11;
}
void StrToInt(char s[100])
{
	n = 0;
	for (int i = 0; i <= 100; i++)
	{
		if (s[i] == '0')
		{
			In[n] = 0;
			n++;
		}
		if (s[i] == '1')
		{
			In[n] = 1;
			n++;
		}
		if (s[i] == '2')
		{
			In[n] = 2;
			n++;
		}
		if (s[i] == '3')
		{
			In[n] = 3;
			n++;
		}
		if (s[i] == '4')
		{
			In[n] = 4;
			n++;
		}
		if (s[i] == '5')
		{
			In[n] = 5;
			n++;
		}
		if (s[i] == '6')
		{
			In[n] = 6;
			n++;
		}
		if (s[i] == '7')
		{
			In[n] = 7;
			n++;
		}
		if (s[i] == '8')
		{
			In[n] = 8;
			n++;
		}
		if (s[i] == '9')
		{
			In[n] = 9;
			n++;
		}
	}
}
int NumErr()
{
	int t = 0;
	for (int i = 0; i < n; i++)
		if (Err[i]) t++;
	return t;
}
void Printf()
{
	for (int i = 0; i < n; i++)
		 printf("%d ", In[i]);
	printf("\n");
	for (int i = 0; i < f; i++)
	{
		for (int j = 0; j < n; j++)
			if (Frame[i][j] == -1)  printf("  ");
			else  printf("%d ", Frame[i][j]);
		printf("\n");
	}
	for (int i = 0; i < n; i++)
		if (Err[i])  printf("* ");
		else printf("  ");
	printf("\nTotal error: %d\n", NumErr());
}
void FIFO()
{
	int t = 0; bool ok = true; bool check;
	for (int i = 0; i < n; i++)
	{
		if (ok)
		{
			Frame[t][i] = In[i];
			for (int j = 0; j < t; j++) Frame[j][i] = Frame[j][i-1];
			t++;
			Err[i] = true;
			if (t == f) 
			{
				ok = false;
				t = 0;
			}
		}
		else
		{
			check = true;
			for (int j = 0; j < f; j++)
				if (In[i] == Frame[j][i - 1]) check = false;
			if (check)
			{
				for (int j = 0; j < f; j++) Frame[j][i] = Frame[j][i - 1];
				Frame[t][i] = In[i];
				Err[i] = true;
				t++;
				if (t == f) t = 0;
			}
			else
				for (int j = 0; j < f; j++) Frame[j][i] = Frame[j][i - 1];
		}
	}
	Printf();
}
int FindFuture(int x)
{
	int t = 0;
	int k[10];
	for (int i = 0; i < 10; i++) k[i] = 999;
	for (int i = x + 1; i < n; i++)
		for (int j = 0; j < f; j++)
			if ((In[i] == Frame[j][x]) && (k[j] == 999)) k[j] = i;
	for (int i = 0; i < f; i++)
		if (k[t] < k[i]) t = i;
	return t;
}
int FindPast(int x)
{
	int t = 0;
	int k[10];
	for (int i = 0; i < 10; i++) k[i] = -1;
	for (int i = 0; i < x; i++)
		for (int j = 0; j < f; j++)
			if (In[i] == Frame[j][x]) k[j] = i;
	for (int i = 0; i < f; i++)
		if (k[t] > k[i]) t = i;
	return t;
}
void OTP()
{
	int t = 0; bool ok = true; bool check;
	for (int i = 0; i < n; i++)
	{
		if (ok)
		{
			Frame[t][i] = In[i];
			for (int j = 0; j < t; j++) Frame[j][i] = Frame[j][i - 1];
			t++;
			Err[i] = true;
			if (t == f)
			{
				ok = false;
				t = 0;
			}
		}
		else
		{
			check = true;
			for (int j = 0; j < f; j++)
				if (In[i] == Frame[j][i - 1]) check = false;
			if (check)
			{
				for (int j = 0; j < f; j++) Frame[j][i] = Frame[j][i - 1];
				Frame[FindFuture(i)][i] = In[i];
				Err[i] = true;
			}
			else
				for (int j = 0; j < f; j++) Frame[j][i] = Frame[j][i - 1];
		}
	}
	Printf();
}
void LRU()
{
	int t = 0; bool ok = true; bool check;
	for (int i = 0; i < n; i++)
	{
		if (ok)
		{
			Frame[t][i] = In[i];
			for (int j = 0; j < t; j++) Frame[j][i] = Frame[j][i - 1];
			t++;
			Err[i] = true;
			if (t == f)
			{
				ok = false;
				t = 0;
			}
		}
		else
		{
			check = true;
			for (int j = 0; j < f; j++)
				if (In[i] == Frame[j][i - 1]) check = false;
			if (check)
			{
				for (int j = 0; j < f; j++) Frame[j][i] = Frame[j][i - 1];
				Frame[FindPast(i)][i] = In[i];
				Err[i] = true;
			}
			else
				for (int j = 0; j < f; j++) Frame[j][i] = Frame[j][i - 1];
		}
	}
	Printf();
}

int main()
{
	init();
	int t1, t2;
	printf("1.Default\t2.Manual: ");
	scanf("%d", &t1);
	if (t1 == 2)
	{
    getchar();
		printf("Input: ");
    fgets(s, sizeof s, stdin);
		StrToInt(s);
	}
  printf("Frame: ");
	scanf("%d", &f);
	printf("1.FIFO\t2.OTP\t3.LRU: ");
	scanf("%d", &t2);
  switch (t2)
	{
	case 1:
	{
		FIFO();
		break;
	}
	case 2:
	{
		OTP();
		break;
	}
	case 3:
	{
		LRU();
		break;
	}
	}
	return 0;
}
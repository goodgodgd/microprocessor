#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


void print_byte1(const char* title, unsigned char num)
{
	// 1 byte = 8 bit
	char binary[9];
	int div = 1;
	for (int i = 0; i < 8; i++)
	{
		int residue = (num / div) % 2;
		if (residue == 1)
			binary[7 - i] = '1';
		else
			binary[7 - i] = '0';
		div *= 2;
	}
	binary[8] = NULL;	// string end
	printf("%-10s: %3d = 0x%02x = 0b%s\n", title, num, num, binary);
}

void print_byte2(const char* title, unsigned char num)
{
	// 1 byte = 8 bit
	char binary[9];
	int div = 1;
	for (int i = 0; i < 8; i++)
	{
		binary[7 - i] = ((num / div) % 2) == 0 ? '0' : '1';
		div *= 2;
	}
	binary[8] = NULL;	// string end
	printf("%-10s: %3d = 0x%02x = 0b%s\n", title, num, num, binary);
}

void print_byte3(const char* title, unsigned char num)
{
	// 1 byte = 8 bit
	char binary[9];
	for (int i = 0; i < 8; i++)
	{
		binary[7 - i] = ((num / (1 << i)) % 2) == 0 ? '0' : '1';
	}
	binary[8] = NULL;	// string end
	printf("%-10s: %3d = 0x%02x = 0b%s\n", title, num, num, binary);
}

void print_byte4(const char* title, unsigned char num)
{
	// 1 byte = 8 bit
	char binary[9];
	for (int i = 0; i < 8; i++)
	{
		// i��° ��Ʈ�� 1�� �ִ��� Ȯ��
		binary[7 - i] = (num & (1 << i)) == 0 ? '0' : '1';
	}
	binary[8] = NULL;	// string end
	printf("%-10s: %3d = 0x%02x = 0b%s\n", title, num, num, binary);
}


int main()
{
	// {}: ���� scope ���� {}�ȿ��� ������ ������ {}�� ������ �Ҹ��

	{
		printf("===== printf ���� =====\n");
		// 4 byte ������
		int int_var = -10;
		// 1 byte ���� ������
		unsigned char uch_var = 10;
		// �������� %d
		printf("integer: %d, %d\n", int_var, uch_var);
		// 4 byte �Ǽ���: ���� ���� f�� �ٿ��� float���� �ν�
		float flo_var = 3.14159265359f;
		// 8 byte �Ǽ���: f�� ������ �⺻������ double
		double dou_var = 3.14159265359;
		// �Ǽ����� %f
		printf("real number: %f, %f\n", flo_var, dou_var);
		// ���ڴ� ''
		char cha_var = 'A';
		// ���ڿ��� ""
		const char* str_var = "hello atmega!";
		printf("string: %c, %s\n", cha_var, str_var);
	}

	if (0)
	{
		printf("\n===== ��� ���� =====\n");
		printf("use for loop when loop length is fixed\n");
		char string[20] = "hello atmega!";
		for (int i = 0; i < 20; i++)
		{
			if (string[i] == 'e')
				continue;
			if (string[i] == 'g')
				break;
			printf("%c", string[i]);
		}
		printf("\n");

		printf("use while loop when loop length is variable\n");
		int key = 1;
		printf("press 0 to continue\n");
		while (key != 0)
		{
			scanf("%d", &key);
			getchar();	// �ٳ���(enter) ���� ���
			printf("pressed: %d\n", key);
		}

		char ch = 'b';
		printf("press a to continue\n");
		while (ch != 'a')
		{
			ch = getchar();
			getchar(); // �ٳ���(enter) ���� ���
			printf("pressed: %c\n", ch);
		}
	}

	{
		printf("\n===== arithmetic operator ���� =====\n");
		int a = 0;
		printf("a++: %d\n", a++);
		printf("a++: %d\n", a++);
		int b = 0;
		printf("++b: %d\n", ++b);
		printf("++b: %d\n", ++b);

		a = 10;
		printf("a = %d\n", a);
		a += 2;
		printf("a += 2: %d\n", a);
		a *= 2;
		printf("a += 2: %d\n", a);
		a /= 3;
		printf("a /= 3: %d\n", a);
		a -= 5;
		printf("a -= 5: %d\n", a);
		a %= 2;
		printf("a %%= 2: %d\n", a);
	}

	{
		printf("\n===== 2����, 16���� ���� =====\n");
		// uchar range: 0~127
		unsigned char a = 101;
		print_byte1("6 lines", a);
		print_byte2("2 lines", a);
		print_byte3("1 long", a);
		print_byte4("1 short", a);

		unsigned char b = 20;
		print_byte1("b", b);

	}

	{
		printf("\n===== bit operator ���� =====\n");
		unsigned char a = 93;	// = 0x5d = 0b01011101
		unsigned char b = 20;	// = 0x14 = 0b00010100
		print_byte1("a | b", a | b);
		print_byte1("a & b", a & b);
		print_byte1("a ^ b", a ^ b);

		printf("\n|(bit-or)�� �̿��� 1 �����\n");
		printf("b�� 7��° �ڸ��� 1�Է�\n");
		print_byte1("b", b);
		print_byte1("1<<6", 1 << 6);
		print_byte1("b | 1<<6", b | 1 << 6);
		print_byte1("b | 64", b | 64);
		print_byte1("b | 0x40", b | 0x40);

		printf("b�� 2��° �ڸ��� 1�Է�\n");
		print_byte1("b | 0x02", b | 0x02);

		printf("b�� 7��°, 6��°, 2��° �ڸ��� 1�Է�\n");
		print_byte1("0x62", 0x62);
		print_byte1("b | 0x62", b | 0x62);

		printf("\n&(bit-and)�� �̿��� 0 �����\n");
		printf("a�� 5��° �ڸ��� 0�Է�\n");
		print_byte4("a", a);
		print_byte4("0xef", 0b11101111);
		print_byte4("a & 0xef", a & 0xef);

		printf("a�� 1��°, 5��°, 6��° �ڸ��� 0�Է�\n");
		print_byte4("0xe6", 0b11100110);
		print_byte4("0x19", 0x19);
		print_byte4("~0x19", ~0x19);
		print_byte4("a & 0xe6", a & 0xe6);
		print_byte4("a &~0x19", a &~0x19);

		printf("\n^(bit-xor)�� �̿��� ��Ʈ ���\n");
		print_byte4("a", a);
		a ^= 0x01;
		print_byte4("a ^= 0x01", a);
		a ^= 0x01;
		print_byte4("a ^= 0x01", a);
		a ^= 0x01;
		print_byte4("a ^= 0x01", a);
	}

	// �ܼ�â �ڵ����� ����
	printf("\n");
	system("pause");
	return 0;
}

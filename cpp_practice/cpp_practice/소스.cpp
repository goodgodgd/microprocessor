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
		// i번째 비트에 1이 있는지 확인
		binary[7 - i] = (num & (1 << i)) == 0 ? '0' : '1';
	}
	binary[8] = NULL;	// string end
	printf("%-10s: %3d = 0x%02x = 0b%s\n", title, num, num, binary);
}


int main()
{
	// {}: 변수 scope 지정 {}안에서 선언한 변수는 {}가 끝나면 소멸됨

	{
		printf("===== printf 연습 =====\n");
		// 4 byte 정수형
		int int_var = -10;
		// 1 byte 양의 정수형
		unsigned char uch_var = 10;
		// 정수형은 %d
		printf("integer: %d, %d\n", int_var, uch_var);
		// 4 byte 실수형: 숫자 끝에 f를 붙여야 float으로 인식
		float flo_var = 3.14159265359f;
		// 8 byte 실수형: f가 없으면 기본적으로 double
		double dou_var = 3.14159265359;
		// 실수형은 %f
		printf("real number: %f, %f\n", flo_var, dou_var);
		// 문자는 ''
		char cha_var = 'A';
		// 문자열은 ""
		const char* str_var = "hello atmega!";
		printf("string: %c, %s\n", cha_var, str_var);
	}

	if (0)
	{
		printf("\n===== 제어문 연습 =====\n");
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
			getchar();	// 줄내림(enter) 문자 비움
			printf("pressed: %d\n", key);
		}

		char ch = 'b';
		printf("press a to continue\n");
		while (ch != 'a')
		{
			ch = getchar();
			getchar(); // 줄내림(enter) 문자 비움
			printf("pressed: %c\n", ch);
		}
	}

	{
		printf("\n===== arithmetic operator 연습 =====\n");
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
		printf("\n===== 2진수, 16진수 연습 =====\n");
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
		printf("\n===== bit operator 연습 =====\n");
		unsigned char a = 93;	// = 0x5d = 0b01011101
		unsigned char b = 20;	// = 0x14 = 0b00010100
		print_byte1("a | b", a | b);
		print_byte1("a & b", a & b);
		print_byte1("a ^ b", a ^ b);

		printf("\n|(bit-or)를 이용한 1 덮어쓰기\n");
		printf("b의 7번째 자리에 1입력\n");
		print_byte1("b", b);
		print_byte1("1<<6", 1 << 6);
		print_byte1("b | 1<<6", b | 1 << 6);
		print_byte1("b | 64", b | 64);
		print_byte1("b | 0x40", b | 0x40);

		printf("b의 2번째 자리에 1입력\n");
		print_byte1("b | 0x02", b | 0x02);

		printf("b의 7번째, 6번째, 2번째 자리에 1입력\n");
		print_byte1("0x62", 0x62);
		print_byte1("b | 0x62", b | 0x62);

		printf("\n&(bit-and)를 이용한 0 덮어쓰기\n");
		printf("a의 5번째 자리에 0입력\n");
		print_byte4("a", a);
		print_byte4("0xef", 0b11101111);
		print_byte4("a & 0xef", a & 0xef);

		printf("a의 1번째, 5번째, 6번째 자리에 0입력\n");
		print_byte4("0xe6", 0b11100110);
		print_byte4("0x19", 0x19);
		print_byte4("~0x19", ~0x19);
		print_byte4("a & 0xe6", a & 0xe6);
		print_byte4("a &~0x19", a &~0x19);

		printf("\n^(bit-xor)를 이용한 비트 토글\n");
		print_byte4("a", a);
		a ^= 0x01;
		print_byte4("a ^= 0x01", a);
		a ^= 0x01;
		print_byte4("a ^= 0x01", a);
		a ^= 0x01;
		print_byte4("a ^= 0x01", a);
	}

	// 콘솔창 자동종료 방지
	printf("\n");
	system("pause");
	return 0;
}

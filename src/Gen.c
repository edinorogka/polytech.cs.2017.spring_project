/** @file Gen.c
*  @brief �������, ������������ �������� ������
*
*
*@author Larina Anna - anna_larina_99@bk.ru \n
*@author Latyshewa Regina - reggamer@mail.ru*/
#include "libs.h"
int count = 0;
/** \fn void gen( int star[STARS_ARRAY_SIZE][2])
������� ������� ������ � ��������� �������
\param  int star[STARS_ARRAY_SIZE][2] - ������� ��������� �����

*/
void gen( int star[STARS_ARRAY_SIZE][2]) {
	int i;
	int x;
	if (count >= STARS_ARRAY_SIZE) {
		count = 0;
	}
	{
		star[count][0] = (rand() % (SCREEN_W - 100) + 50);
		star[count++][1] = 0;
		star[count][0] = -1;
		star[count][1] = -1; }
}
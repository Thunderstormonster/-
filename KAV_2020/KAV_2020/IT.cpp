#include "stdafx.h"

namespace IT
{
	IdTable Create(int size)
	{
		IdTable idtable;
		idtable.table = new Entry[size];
		idtable.size = 0;
		return idtable;
	}

	void Add(IdTable& idtable, Entry entry)
	{
		strncpy_s(idtable.table[idtable.size].id, entry.id, ID_FOR_IT - 1); // 5 �������� �� ������������� + 5 �������� �� �������������� � �-��
		idtable.table[idtable.size].idxfirstLE = entry.idxfirstLE; // ��������������� � ������� ������(������ ����������)
		idtable.table[idtable.size].iddatatype = entry.iddatatype; // ��� ������ integer ...
		idtable.table[idtable.size].idtype = entry.idtype; // ������� ���������� ...
		if (entry.idtype == IT::F || entry.idtype == IT::S)
		{
			idtable.table[idtable.size].count_parm = 0; // �� ��������� ���������� 0
		}
		idtable.table[idtable.size].value.vNUM = TI_INT_DEFAULT; // �������� �� ��-�� ��� int
		idtable.table[idtable.size].value.vSTR.len = 0; // ����� ������ 0
		idtable.table[idtable.size].value.vSTR.str[0] = TI_STR_DEFAULT; // ������ ������
		idtable.table[idtable.size].value.vCHR.len1 = 0;
		idtable.table[idtable.size].value.vCHR.str1[0] = TI_STR_DEFAULT;
		idtable.size++;
	}

	int IsId(IdTable& idtable, char id[ID_MAXSIZE])
	{
		for (int i = 0; i < idtable.size; i++)
		{
			if (strcmp(idtable.table[i].id, id) == 0) //���� ����� ��� ��� ����
				return i;
		}
		return -1;
	}

	void SetValue(IdTable& idtable, int indTI, char* word) // ��������� �������� ����������
	{
		if (idtable.table[indTI].iddatatype == INT)
		{
			int tempInt = atoi(word); //��������������� ������ � �����
			if (tempInt > INT_MAX)
				tempInt = INT_MAX;
			else if (tempInt < INT_MINUS_MAXSIZE)
				tempInt = INT_MINUS_MAXSIZE;
			idtable.table[indTI].value.vNUM = tempInt;
		}
		else {
			if (idtable.table[indTI].iddatatype == STR)
			{
				idtable.table[indTI].value.vSTR.len = strlen(word);
				strcpy_s(idtable.table[indTI].value.vSTR.str, TI_STR_MAXSIZE, word);
			}
			else {
				idtable.table[indTI].value.vCHR.len1 = strlen(word);
				strcpy_s(idtable.table[indTI].value.vCHR.str1, TI_STR_MAXSIZE, word);
			}
		}

	}
	void SetI(IdTable& idtable, int indTI, int valu) {
		int tempIn = valu;
		if (tempIn > INT_MAX)
			tempIn = INT_MAX;
		else if (tempIn < INT_MINUS_MAXSIZE)
			tempIn = INT_MINUS_MAXSIZE;
		idtable.table[indTI].value.vNUM = tempIn;
	}
	int DecimalTrnsl(char* word) {
		char* pEnd = 0;
		char buf[15];
		int l, j;
		for (l = 1, j = 0; l < strlen(word); l++, j++) {
			buf[j] = word[l];
		}
		buf[j + 1] = '\0';
		return strtol(buf, &pEnd, 8);
	}
	int DecimalTrnsll(char* word) {
		char* pEnd = 0;
		char buf[15];
		int l, j;
		for (l = 1, j = 0; l < strlen(word); l++, j++) {
			buf[j] = word[l];
		}
		buf[j + 1] = '\0';
		return strtol(buf, &pEnd, 2);
	}
}
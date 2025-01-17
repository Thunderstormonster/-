#include <iostream>
#include <stack> 
#include "GraibachRules.h"
#include "LexAnalize.h"
#include "Log.h"
//������������ ��������� Mfst ��� ������������� ����������� ��������� �������� 

#define MFST_DIAGN_MAXSIZE 2*ERROR_MAXSIZE_MESSAGE
#define MFST_DIAGN_NUMBER 3

typedef std::vector<short> MFSTSTVECTOR;	//������ ��������

namespace MFST
{
	struct MfstState				//��������� ��������(��� ����������
	{
		short lenta_position;		//������� �� �����
		short nrule;				//����� �������� �������
		short nrulechain;			//����� ������� �������
		MFSTSTVECTOR st;				//�������
		MfstState();
		MfstState(
			short pposition,		//������� �� �����
			MFSTSTVECTOR pst,		//�������
			short pnrulechain		//����� ������� �������, �������� �������
		);
		MfstState(
			short pposition,		//������� �� �����
			MFSTSTVECTOR pst,		//�������
			short pnrule,			//����� �������� �������
			short pnrulechain		//����� ������� �������, �������� �������
		);
	};
	struct Mfst					//���������� �������	
	{
		enum RC_STEP			//��� �������� ������� step
		{
			NS_OK,				//������� ������� � �������, ������� ��������
			NS_NORULE,			//�� ������� ������� ���������� (������ � ����������)
			NS_NORULECHAIN,		//�� ������� ���������� ������� ������� (������ � �������� ����)
			NS_ERROR,			//����������� �������������� ������ ����������
			TS_OK,				//������� ������ ����� == , ������������ �����,
			TS_NOK,				//������� ������ ����� !=  ������������� ���������
			LENTA_END,			//������� ������� ����� >= lenta_size
			SURPRISE			//����������� ��� �������� ( ������ � stepen)
		};
		struct MfstDiagnosis		//�����������
		{
			short lenta_position;	//������� �� �����
			RC_STEP rc_step;		//��� ���������� ����
			short nrule;			//����� �������
			short nrule_chain;		//����� ������� �������
			MfstDiagnosis();
			MfstDiagnosis(			//�����������
				short plenta_position,	//������� �� �����
				RC_STEP prc_stepen,		//��� ���������� ����
				short pnrule,			//����� �������
				short pnrule_chain		//����� ������� �������
			);
		}
		diagnosis[MFST_DIAGN_NUMBER];	//��������� ����� �������� ���������
		GRBALPHABET* lenta;				//����������������(TS/NS) ����� (�� LEX)
		short lenta_position;			//������� ������� �� �����
		short nrule;					//����� �������� �������
		short nrulechain;				//����� ������� �������, �������� �������
		short lenta_size;				//������ �����
		GRB::Greibach grebach;			//���������� �������
		LA::LEX lex;					//��������� ������ ������������ �����������
		MFSTSTVECTOR st;					//���� ��������		
		std::vector<MfstState> storestate;	//���� ��� ���������� ���������
		Mfst();
		Mfst(
			LA::LEX plex,			//��������� ������ ������������ �����������
			GRB::Greibach pgrebach		//���������� �������
		);
		char* getCSt(char* buf);			//�������� ���������� 
		char* getCLenta(char* buf, short pos, short n = 25);//�����: n �������� � pos
		char* getDiagnosis(short n, char* buf);			//�������� n-�� ������ ����������� ��� 0�00
		bool savestate(const Log::LOG& log);					//��������� ��������� ��������
		bool reststate(const Log::LOG& log);					//������������ ��������� ��������
		bool push_chain(					//��������� ������� ������� 
			GRB::Rule::Chain chain				//������� �������
		);
		RC_STEP step(const Log::LOG& log);			//��������� ��� ��������
		bool start(const Log::LOG& log);			//��������� �������
		bool savediagnois(
			RC_STEP pprc_stepen			//��� ���������� ����
		);
		void printrules(const Log::LOG& log);		//������� ������������������ ������
		struct Deducation		//�����
		{
			short size;		//���������� ����� � ������
			short* nrules;	//������ ������ ����������
			short* nrulechains;//������ ������� ������ ���������� (nrules)
			Deducation() { size = 0; nrules = 0; nrulechains = 0; };
		}deducation;
		bool savededucation();	//��������� ������ ������
	};
};

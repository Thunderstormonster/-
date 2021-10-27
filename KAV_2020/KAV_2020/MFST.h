#include <iostream>
#include <stack> 
#include "GraibachRules.h"
#include "LexAnalize.h"
#include "Log.h"
//Спецификация структуры Mfst для моделирования магазинного конечного автомата 

#define MFST_DIAGN_MAXSIZE 2*ERROR_MAXSIZE_MESSAGE
#define MFST_DIAGN_NUMBER 3

typedef std::vector<short> MFSTSTVECTOR;	//вектор автомата

namespace MFST
{
	struct MfstState				//состояние автомата(для сохранения
	{
		short lenta_position;		//позиция на ленте
		short nrule;				//номер текущего правила
		short nrulechain;			//номер текущей цепочки
		MFSTSTVECTOR st;				//автомат
		MfstState();
		MfstState(
			short pposition,		//позиция на ленте
			MFSTSTVECTOR pst,		//автомат
			short pnrulechain		//номер текущей цепочки, текущего правила
		);
		MfstState(
			short pposition,		//позиция на ленте
			MFSTSTVECTOR pst,		//автомат
			short pnrule,			//номер текущего правила
			short pnrulechain		//номер текущей цепочки, текущего правила
		);
	};
	struct Mfst					//магазинный автомат	
	{
		enum RC_STEP			//код возврата функции step
		{
			NS_OK,				//найдено правило и цепочка, цепочка записана
			NS_NORULE,			//не найдено правило грамматики (ошибки в грамматике)
			NS_NORULECHAIN,		//не найдена подходящая цепочка правила (ошибка в исходном коде)
			NS_ERROR,			//неизвестный нетерминальный символ грамматики
			TS_OK,				//текущий символ ленты == , продвинулась лента,
			TS_NOK,				//текущий символ ленты !=  восстановлено состояние
			LENTA_END,			//текущая позиция ленты >= lenta_size
			SURPRISE			//неожиданный код возврата ( ошибка в stepen)
		};
		struct MfstDiagnosis		//диагностика
		{
			short lenta_position;	//позиция на ленте
			RC_STEP rc_step;		//код завершения шага
			short nrule;			//номер правила
			short nrule_chain;		//номер цепочки правила
			MfstDiagnosis();
			MfstDiagnosis(			//диагностика
				short plenta_position,	//позиция на ленте
				RC_STEP prc_stepen,		//код завершения шага
				short pnrule,			//номер правила
				short pnrule_chain		//номер цепочки правила
			);
		}
		diagnosis[MFST_DIAGN_NUMBER];	//последние самые глубокие сообщения
		GRBALPHABET* lenta;				//перекодированная(TS/NS) лента (из LEX)
		short lenta_position;			//текущая позиция на ленте
		short nrule;					//номер текущего правила
		short nrulechain;				//номер текущей цепочки, текущего правила
		short lenta_size;				//размер ленты
		GRB::Greibach grebach;			//грамматика Грейбах
		LA::LEX lex;					//результат работы лексического анализатора
		MFSTSTVECTOR st;					//стек автомата		
		std::vector<MfstState> storestate;	//стек для сохранения состояний
		Mfst();
		Mfst(
			LA::LEX plex,			//результат работы лексического анализатора
			GRB::Greibach pgrebach		//грамматика Грейбах
		);
		char* getCSt(char* buf);			//получить содержимое 
		char* getCLenta(char* buf, short pos, short n = 25);//лента: n символов с pos
		char* getDiagnosis(short n, char* buf);			//получить n-ую строку диагностики или 0х00
		bool savestate(const Log::LOG& log);					//сохранить состояние автомата
		bool reststate(const Log::LOG& log);					//восстановить состояние автомата
		bool push_chain(					//поместить уепочку правила 
			GRB::Rule::Chain chain				//цепочка правила
		);
		RC_STEP step(const Log::LOG& log);			//выполнить шаг автомата
		bool start(const Log::LOG& log);			//запустить автомат
		bool savediagnois(
			RC_STEP pprc_stepen			//код завершения шага
		);
		void printrules(const Log::LOG& log);		//вывести последовательность правил
		struct Deducation		//вывод
		{
			short size;		//количество шагов в выводе
			short* nrules;	//номера правил нрамматики
			short* nrulechains;//номера цепочек правил грамматики (nrules)
			Deducation() { size = 0; nrules = 0; nrulechains = 0; };
		}deducation;
		bool savededucation();	//сохранить дерево вывода
	};
};

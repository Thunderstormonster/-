#include "stdafx.h"

ofstream fout("Code.js");

void Generation(LT::LexTable& Lextable, IT::IdTable& IDtable, In::Words* words)
{
	for (int i = 0; i < Lextable.size; i++)
	{
		switch (Lextable.table[i].lexema)
		{
		case LEX_BOL: 
		{
			fout << ">=";
			break;
		}
		case LEX_MEN: 
		{
			fout << "<=";
			break;
		}
		case LEX_OR: 
		{
			fout << "==";
			break;
		}
		case LEX_NO: 
		{
			fout << Lextable.table[i].lexema<<"=";
			break;
		}
		case LEX_PLUS:
		case LEX_STAR:
		case LEX_MINUS:
		case LEX_DIRSLASH:
		case LEX_MORE:
		case LEX_LESS:
		case  LEX_EQUAL:
		{
			fout << Lextable.table[i].lexema;
			break;
		}
		case LEX_COMMA:
		case SPACE:
		{
			fout << Lextable.table[i].lexema << " ";
			break;
		}

		case LEX_RIGHTTHESIS:
		case LEX_LEFTTHESIS:
		{
			fout << Lextable.table[i].lexema;
			break;
		}
		case LEX_LEFTBRACE:
		{

			fout << endl << Lextable.table[i].lexema << endl;
			break;
		}
		case LEX_BRACELET:
		{

			fout << Lextable.table[i].lexema << endl;
			break;
		}
		case LEX_SEPARATOR:
		{
			fout << Lextable.table[i].lexema << endl;
			break;
		}
		case  LEX_TYPE:
		{
			fout << "var ";
			break;
		}

		case LEX_LITERAL:
		{
			if (IDtable.table[Lextable.table[i].idxTI].iddatatype == IT::INT)
				fout << IDtable.table[Lextable.table[i].idxTI].value.vNUM;
			else fout << IDtable.table[Lextable.table[i].idxTI].value.vSTR.str;
			break;
		}
		case LEX_ID:
		{
			fout << IDtable.table[Lextable.table[i].idxTI].id;
			break;
		}
		case LEX_OUTPUT:
		{
			fout << "document.write('<br>');" << endl;
			fout << "document.write";
			break;
		}
		case LEX_FUNCTION:
		{
			fout << "function ";
			break;
		}
		case LEX_RETURN:
		{
			fout << words[i].word << " ";
			break;
		}
		case LEX_LIBM:
		{
			fout << "document.write('Now you can use any functions<br>')";
			break;
		}
		case LEX_ROOT:
		{
			fout << "Math.sqrt";
			for (++i; Lextable.table[i].lexema != LEX_RIGHTTHESIS; i++)
				fout << words[i].word;
			fout << words[i].word;
			break;
		}
		case LEX_SRC:
		{   
			/*function src(a, b) {
				var zz;
				zz = a + b;
				return zz;
			}*/
			fout << "function src(a,b){"<<endl;
			fout << "var zz;"<<endl;
			fout << "zz=a+b;"<<endl;
			fout << "document.write('<br>'+zz);}"<<endl;
			fout << "src";
		/*for (++i; Lextable.table[i].lexema != LEX_RIGHTTHESIS; i++)
			 fout << words[i].word;
			fout << words[i].word;*/
			break;
		}
		case LEX_SRT:
		{
			/*function src(a, b) {
				var zz;
				zz = a + b;
				return zz;
			}*/
			fout << "function srt(a,b){" << endl;
			fout << "var z;" << endl;
			fout << "z=a;" << endl;
			fout << "a=b;" << endl;
			fout << "b=z;" << endl;
			fout << "document.write('<br>'+'первая строка: '+a);" << endl;
			fout << "document.write('<br>'+'вторая строка: '+b);}" << endl;
			fout << "srt";
			/*for (++i; Lextable.table[i].lexema != LEX_RIGHTTHESIS; i++)
				 fout << words[i].word;
				fout << words[i].word;*/
			break;
		}
		case LEX_POWER:
		{
			fout << "Math.pow";
			for (++i; Lextable.table[i].lexema != LEX_RIGHTTHESIS; i++)
				fout << words[i].word;
			fout << words[i].word;
			break;
		}
		case LEX_IF:
		{
			fout << "if";
	
			break;
		}
		case LEX_ELSE:
		{
			fout << "else";

			break;
		}
		case LEX_VOS:
		case LEX_DVO:
		{
			fout << IDtable.table[Lextable.table[i].idxTI].value.vNUM;
			break;
		}
		
		}
	}
	fout.close();
}

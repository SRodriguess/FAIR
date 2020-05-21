// MYERS 1999
//BUSCA O PADRÃO EM TODA A SEQUENCIA

#include "include/define.h"
#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <string>
#include <vector>
#include <utility>
#include <fstream>
#include <dirent.h>
#include <errno.h>
#include <ctime>
#define GRAM4(j) (B[y[j]] << 3) & (B[y[j - 1]] << 2) & (B[y[j - 2]] << 1) & B[y[j - 3]]
#include <string.h>

using namespace std;

vector<int> searchMyers(char *P, long m, char *T, long n, int mismatchMax){

	int k = mismatchMax;
	
	vector<int> indexx;

	int MAXCHAR = 256;
	int posicaoAnterior, quantGrupo, posicaoAtual, indiceMedio, acumulaPmedia;

	// ================== VARIAVEIS RESPONSAVEIS NO PROCESSO DE DEFINIR INDICES CORRETOS =====================
	int inicializador = 0;
	posicaoAnterior = 0;
	quantGrupo = 0;
	posicaoAtual = 0;
	indiceMedio = 0;
	acumulaPmedia = 0;
	// =======================================================================================================

	// ComputePM ////////////////////////////////////////
	long PM[MAXCHAR];
	for (int ii = 0; ii < MAXCHAR; ii++) PM[ii] = 0;
	for (int ii = 1; ii <= m; ii++){
		long temp = 1 << (ii-1);
		PM[P[ii-1]+127] = PM[P[ii-1]+127] | temp;
		// cerr << ii - 1 << ": " << PM[P[ii-1]+127] << endl;
	}
	////////////////////////////////////////////////////

	long VN = 0;
	long VP = 0xffffffff;
	long D0, HP, HN;

	long currDist = m;
	long currDistAnt = 0;
	int minorCurr = k;
	int posiMinorCurr;

	for (int j = 0; j < n; ++j){

		posicaoAtual = j+1;

		// Step(j); ///////////////////////////////////////////////
		D0 = (((PM[T[j]+127] & VP) + VP) ^ VP) | PM[T[j]+127] | VN;
		HP = VN | ~ (D0 | VP);
		HN = VP & D0;
		VP = (HN << 1) | ~ (D0 | (HP << 1));
		VN = (HP << 1) & D0;
		///////////////////////////////////////////////////////////

		if ((HP & 0x80000000) == 0x80000000) currDist += 1;
		else if((HN & 0x80000000) == 0x80000000) currDist -= 1;

		// printf("%d,%d\n", j, currDist);
		// MATCH =========

			// cerr << "" << endl;
			// cerr << posicaoAtual << ":" << currDist << endl;
			// cerr << "" << endl;

		// if(1 >= 90)
		// {

		// 	int m2 = 3;
		// 	currDist = m2;
		// 	string P2 = "";

		// 	for (int z = 0; z < m2; ++z)
		// 	{
		// 		if((j+z) < n) P2 += T[j+z];
		// 	}

		// 	// cerr << "J: " << j << endl;
		// 	// cerr << "P2: " << P2 << endl;

		// 	// ComputePM ////////////////////////////////////////
		// 	long PM2[MAXCHAR];
		// 	for (int ii = 0; ii < MAXCHAR; ii++) PM2[ii] = 0;
		// 	for (int ii = 1; ii <= P2.length(); ii++){
		// 		long temp = 1 << (ii-1);
		// 		PM2[P2[ii-1]+127] = PM2[P2[ii-1]+127] | temp;
		// 		// cerr << ii - 1 << ": " << PM[P[ii-1]+127] << endl;
		// 	}
		// 	////////////////////////////////////////////////////
		// 	long VN = 0;
		// 	long VP = 0xffffffff;
		// 	long D0 = 0, HP = 0, HN = 0;

		// 	inicializador = 0;
		// 	// quantGrupo = 0;

		// 	for (int jj = 0; jj < m; ++jj)
		// 	{

		// 		// posicaoAtual = j+jj+1;				

		// 	// Step(j); ///////////////////////////////////////////////
		// 		D0 = (((PM2[P[jj]+127] & VP) + VP) ^ VP) | PM2[P[jj]+127] | VN;
		// 		HP = VN | ~ (D0 | VP);
		// 		HN = VP & D0;
		// 		VP = (HN << 1) | ~ (D0 | (HP << 1));
		// 		VN = (HP << 1) & D0;
		// 	///////////////////////////////////////////////////////////

		// 		if ((HP & 0x80000000) == 0x80000000) currDist += 1;
		// 		else if((HN & 0x80000000) == 0x80000000) currDist -= 1;


		// 		if (currDist <= 1)
		// 		{

		// 			inicializador++;

		// 		}

		// 		if(jj == (m-1))
		// 		{

		// 			if(inicializador > 0)
		// 			{

		// 				int nega = m2*(-1);
		// 				indexx.insert(indexx.begin(), nega);
		// 				indexx.insert(indexx.begin(), posicaoAtual);

		// 			}

		// 		}

		// }	

		// // Janela deslizante em 3 posicoes
		// j += 2 - 1;

		// }else{

			// if(posicaoAtual >= 90)
			// {
			// 	k = m/2;
			// }

		if (currDist <= k){

			inicializador++;

				if(inicializador == 1)
				{

					// acumulaPmedia += posicaoAtual + minorCurr;
					quantGrupo++;
					minorCurr = currDist;
					posiMinorCurr = posicaoAtual;

				}else{

					if(currDist < minorCurr)
					{
						// acumulaPmedia += posicaoAtual + minorCurr;
						// quantGrupo++;
						minorCurr = currDist;
						posiMinorCurr = posicaoAtual;
					}
				}

				// currDistAnt = currDist;
				
		}else{

			if(quantGrupo >= 1)
			{

				// indiceMedio = acumulaPmedia/quantGrupo;
				// indexx.push_back(indiceMedio - m);


				indexx.insert(indexx.begin(), minorCurr);
				indexx.insert(indexx.begin(), posiMinorCurr - m);

				// indexx.push_back(posiMinorCurr - m);
				// indexx.push_back(minorCurr);

				// cerr << "posiMinorCurr > " << posiMinorCurr << endl;
				// cerr << "posiMinorCurr - m> " << posiMinorCurr - m << endl;

				inicializador = 0;
				// acumulaPmedia = 0;
				quantGrupo = 0;
				minorCurr = k;

			}

		}

		if (posicaoAtual == n){
			if(quantGrupo >= 1){

					// indiceMedio = acumulaPmedia/quantGrupo;
					indexx.insert(indexx.begin(), minorCurr);
					indexx.insert(indexx.begin(), posiMinorCurr - m);
					// indexx.push_back(indiceMedio - m);

					// indexx.push_back(posiMinorCurr - m);
					// indexx.push_back(minorCurr);

					// cerr << "posiMinorCurr > " << posiMinorCurr << endl;
					// cerr << "posiMinorCurr - m> " << posiMinorCurr - m << endl;
			}
	    }
	}

	// }

	// cerr << "----------- : " << endl;
	return indexx;

	}


vector<int> searchShiftAnd(char *P, long m, char *T, long n){

//	K = NUMERO MAXIMO DE ERROS PERMITIDOS (DELECAO, SUBSTITUICAO, INSERCAO)
	int k = 0;

	// ARMAZENA INDICES DE POSICOES CORRETAS DE MATCH APROXIMADO
	vector<int> indexx;

	// ===== VARIAVEIS RESPONSAVEIS NO PROCESSO DE DEFINIR INDICES CORRETOS DE MATCH NO CASAMENTO APROXIMADO
			int inicializador = 0;
			int posicaoAnterior = 0;
			int quantGrupo = 0;
			int posicaoAtual = 0;
			int indiceMedio = 0;
			int acumulaPmedia = 0;
	// =======================================================================================================

	int MAXCHAR = 256;

	long Masc[MAXCHAR], i, j, Ri, Rant, Rnovo;
		// R[2]
	long R[k];

	for (i = 0; i < MAXCHAR; i++) Masc[i] = 0;

	for (i = 1; i <= m; i++){
			Masc[P[i-1]+127] |= 1 << (m-i);
		 } 

		R[0] = 0;
		Ri = 1 << (m-1);
		for (j = 1; j <= k; j++) R[j] = (1 << (m-j)) | R[j-1];

		for (i = 0; i < n; i++){

			Rant = R[0];
			Rnovo = ((((unsigned long)Rant) >> 1) | Ri) & Masc[T[i] + 127];
			R[0] = Rnovo;

			for (j = 1; j <= k; j++)
			{

				Rnovo = ((((unsigned long) R[j]) >> 1) & Masc[T[i] + 127]) | Rant | (((unsigned long)(Rant | Rnovo))  >> 1);
				Rant = R[j];
				R[j] = Rnovo | Ri;

			}

			posicaoAtual = i+1;

			// SE VERDADEIRO - ACEITOU MATCH COM QUANTIDADE DE ERROS PERMITIDO
			if((Rnovo & 1) != 0){

				inicializador++;

				// INICIALIZA APENAS NO PRIMEIRO MATCH, PARA SALVAR HISTORICO DE POSICAO
				if(inicializador == 1){

					//SOMA 1 AO GRUPO
					quantGrupo++;
					//POSICAO ANTERIOR ARMAZENA POSICAO ATUAL
					posicaoAnterior = posicaoAtual;
					//SOMA VALOR DE POSICAO AO GRUPO
					acumulaPmedia += posicaoAtual;

				}
				// A PARTIR DO SEGUNDO MATCH
				else
				{

					//se posicao anterior +1 eh igual a posicao atual (significa que eh parte do grupo)
					if((posicaoAnterior+1) == posicaoAtual){

							quantGrupo++;
							posicaoAnterior = posicaoAtual;
							acumulaPmedia += posicaoAtual;

					}else{

						//TIRA A MEDIA DO GRUPO ANTERIOR - PEGANDO A SOMA ACUMULADA DO GRUPO DIVIDINDO-O PELA QUANTIDADE DE INDICES DO GRUPO 
						//PARA SABER O VALOR EXATO DE MATCH
						indiceMedio = acumulaPmedia/quantGrupo;
						indexx.insert(indexx.begin(), (indiceMedio - m));
		
						//ATRIBUI AO NOVO GRUPO SUCESSOR VALORES DE INICIALIZACAO - RECOMECA COM POSICAO ATUAL E QUANTIDADE DO GRUPO JA COM VALOR 1
						acumulaPmedia = posicaoAtual;
						posicaoAnterior = posicaoAtual;
						quantGrupo = 1;
						inicializador = 1;

					}

				}

			}

			// SE FOR O ULTIMO CARACTER DA SEQUENCIA, INSERE O ULTIMO MATCH CONSIDERADO
			if(posicaoAtual == n){

					if(quantGrupo >= 1)
					{

						indiceMedio = acumulaPmedia/quantGrupo;
						indexx.insert(indexx.begin(), (indiceMedio - m));

					}
			}

		}

	 	// cerr << "--------" << endl;

	 return indexx;


}
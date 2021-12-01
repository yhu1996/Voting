//analyze random ER network(Nnodes,p)

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define Nnodes  100
#define N 100


int combination(int a)  //calculating C_a^2
{
	int result;
	result = 1.0 * a * (a - 1) / 2.0;
	return (result);
}

void ER_network()
{
	double p, beta;
	int matrix[Nnodes][Nnodes];
	//int value[Nnodes];
	int degree[Nnodes];

	double Rewiring[N][3];
	//double SquareRed0[N][2];
	//double SquareRed1[N][2];
	//double SquareRed2a[N][2];
	//double SquareRed3[N][2];
	//double SquareRed4[N][2];
	//double SquareRed2b[N][2];
	//double C_R[N][2];
	//double C_B[N][2];
	//double TriangleRed0[N][2];
	//double TriangleRed1[N][2];
	//double TriangleRed2[N][2];
	//double TriangleRed3[N][2];
	//int M[100][10000] = {};
	int M;
	//int y;
	double x;

	//int value_test[Nnodes];
	//int delta_E;
	//int win_red;
	double step_red;
	//double M_all;

	//p = 0.01 * (m + 1);
	//data1[m][0] = p;
	//beta = 1;
	p = 0.3;
	beta = 1.0 / 0.03;
	//data1[m][0] =  0.01 * (m + 1) ;

// make random ER network
	for (int i = 0; i < Nnodes; i++)
	{
		for (int j = 0; j < Nnodes; j++)
		{
			matrix[i][j] = 0;
		}
	}
	for (int i = 0; i < Nnodes; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			if (j < i)
			{
				x = 1.0 * rand() / RAND_MAX;
				if (x <= p)
				{
					matrix[i][j] = 1;
				}
			}
		}
	}
	for (int i = 0; i < Nnodes; i++)
	{
		for (int j = 0; j < Nnodes; j++)
		{
			if (j > i)
			{
				matrix[i][j] = matrix[j][i];
			}
		}
	}


// make random BA network


// make random WS network


// calculate the distance matrix

	int distance[Nnodes][Nnodes];
	int matrix_test1[Nnodes][Nnodes];
	int matrix_test2[Nnodes][Nnodes];
	for (int i = 0; i < Nnodes; i++)
	{
		for (int j = 0; j < Nnodes; j++)
		{
			matrix_test1[i][j] = matrix[i][j];
			matrix_test2[i][j] = matrix[i][j];
			distance[i][j] = 0;
		}
	}
	for (int l = 1; l <= Nnodes; l++)
	{
		for (int i = 0; i < Nnodes; i++)
		{
			for (int j = 0; j <= i; j++)
			{
				if (j < i)
				{
					if (matrix_test1[i][j] != 0 && distance[i][j] == 0)
					{
						distance[i][j] = l;
						distance[j][i] = l;
					}
				}
			}
		}
		for (int i = 0; i < Nnodes; i++)
		{
			for (int j = 0; j < Nnodes; j++)
			{
				matrix_test2[i][j] = 0;
				for (int k = 0; k < Nnodes; k++)
				{
					matrix_test2[i][j] = matrix_test2[i][j] + matrix_test1[i][k] * matrix[k][j];
				}
			}
		}
		for (int i = 0; i < Nnodes; i++)
		{
			for (int j = 0; j < Nnodes; j++)
			{
				matrix_test1[i][j] = matrix_test2[i][j];
			}
		}
	}


// analyze this random network
	double ratio_rewiring;
	double ratio_no_rewiring;
	ratio_rewiring = 0;
	ratio_no_rewiring = 0;

	double distribution[50][2];
	for (int i = 0; i < 50; i++)
	{
		distribution[i][0] = i + 1;
		distribution[i][1] = 0;
	}

	for (int i = 0; i < N; i++)
	{
		Rewiring[i][0] = i;
		Rewiring[i][1] = 0; //rewiring N_red;
		Rewiring[i][2] = 0; //N_red without rewiring

		//set initial value,red=1,blue=-1

		int nred = 0;
		int value[Nnodes];
		for (int j = 0; j < Nnodes; j++)
		{
			value[j] = -1;
			x = 1.0 * rand() / RAND_MAX;
			if (x < ((0.5 * Nnodes - nred) / (Nnodes - j)))
			{
				value[j] = 1;
				nred++;
			}

			degree[j] = 0;
			for (int k = 0; k < Nnodes; k++)
			{
				if (matrix[j][k] == 1)
				{
					degree[j]++;
				}
			}
			//printf("%d", value[j]);
		}


		//rewiring
		int matrix_rewiring[Nnodes][Nnodes];
		int degree_rewiring[Nnodes];
		int distance_rewiring[Nnodes][Nnodes];
		for (int j = 0; j < Nnodes; j++)
		{
			for (int k = 0; k < Nnodes; k++)
			{
				matrix_rewiring[j][k] = matrix[j][k];
				distance_rewiring[j][k] = distance[j][k];
			}
			degree_rewiring[j] = degree[j];
		}

		// rewiring step = 30;
		for (int j = 0; j < 30; j++)
		{
			int f;
			f = (1.0 * rand() * Nnodes) / RAND_MAX;
			if (value[f] == -1 && degree_rewiring[f] >= 2)
			{
				for (int k = 0; k < Nnodes; k++)
				{
					if (matrix_rewiring[f][k] == 1)
					{
						for (int r = 0; r < Nnodes; r++)
						{
							if (matrix_rewiring[f][r] == 1 && matrix_rewiring[r][k] == 1)
							{
								if (value[k] == -1 && value[r] == -1)
								{
									matrix_rewiring[f][k] = 0;
									matrix_rewiring[k][f] = 0;
									int g = 0;
									for (int q = 0; q < Nnodes; q++)
									{
										if (distance_rewiring[f][g] < distance_rewiring[f][q])
										{
											g = q;
										}
									}
									matrix_rewiring[f][g] = 1;
									matrix_rewiring[g][f] = 1;
								}
								if (value[k] == -1 && value[r] == 1)
								{
									matrix_rewiring[f][k] = 0;
									matrix_rewiring[k][f] = 0;
									int g = 0;
									for (int q = 0; q < Nnodes; q++)
									{
										if (distance_rewiring[f][g] < distance_rewiring[f][q])
										{
											g = q;
										}
									}
									matrix_rewiring[f][g] = 1;
									matrix_rewiring[g][f] = 1;
								}
								if (value[k] == 1 && value[r] == -1)
								{
									matrix_rewiring[f][r] = 0;
									matrix_rewiring[r][f] = 0;
									int g = 0;
									for (int q = 0; q < Nnodes; q++)
									{
										if (distance_rewiring[f][g] < distance_rewiring[f][q])
										{
											g = q;
										}
									}
									matrix_rewiring[f][g] = 1;
									matrix_rewiring[g][f] = 1;
								}
							}
						}
					}
				}
			}
			//calculate degree_rewiring,distance_rewiring
			for (int k = 0; k < Nnodes; k++)
			{
				degree_rewiring[k] = 0;
				for (int r = 0; r < Nnodes; r++)
				{
					if (matrix_rewiring[k][r] == 1)
					{
						degree_rewiring[k]++;
					}
				}
			}
			int matrix_rewiring_test1[Nnodes][Nnodes];
			int matrix_rewiring_test2[Nnodes][Nnodes];
			for (int k = 0; k < Nnodes; k++)
			{
				for (int r = 0; r < Nnodes; r++)
				{
					matrix_rewiring_test1[k][r] = matrix_rewiring[k][r];
					matrix_rewiring_test2[k][r] = matrix_rewiring[k][r];
					distance_rewiring[k][r] = 0;
				}
			}
			for (int l = 1; l <= Nnodes; l++)
			{
				for (int k = 0; k < Nnodes; k++)
				{
					for (int r = 0; r <= k; r++)
					{
						if (r < k)
						{
							if (matrix_rewiring_test1[k][r] != 0 && distance_rewiring[k][r] == 0)
							{
								distance_rewiring[k][r] = l;
								distance_rewiring[r][k] = l;
							}
						}
					}
				}
				for (int k = 0; k < Nnodes; k++)
				{
					for (int r = 0; r < Nnodes; r++)
					{
						matrix_rewiring_test2[k][r] = 0;
						for (int a = 0; a < Nnodes; a++)
						{
							matrix_rewiring_test2[k][r] = matrix_rewiring_test2[k][r] + matrix_rewiring_test1[k][a] * matrix_rewiring[a][r];
						}
					}
				}
				for (int k = 0; k < Nnodes; k++)
				{
					for (int r = 0; r < Nnodes; r++)
					{
						matrix_rewiring_test1[k][r] = matrix_rewiring_test2[k][r];
					}
				}
			}
		}

		// calculate distribution of degree after rewiring
		for (int j = 0; j < 50; j++)
		{
			for (int k = 0; k < Nnodes; k++)
			{
				if (degree_rewiring[k] == (j + 1))
				{
					distribution[j][0]++;
				}
			}
		}


		/*
		for (int j = 0; j < Nnodes; j++)
		{
			value[j] = -1;
			degree[j] = 0;
			for (int k = 0; k < Nnodes; k++)
			{
				if (matrix[j][k] == 1)
				{
					degree[j]++;
				}
			}
		}

		nred = 0;
		for (int j = 0; j < Nnodes; j++)
		{
			int ser = 0;
			for (int k = 0; k < Nnodes; k++)
			{
				if (degree[j] >= degree[k])
				{
					ser++;
				}
			}
			if (ser >= 50 && nred < 50)
			{
				value[j] = 1;
				nred++;
			}
		}*/

		/*//calculate average degree of red nodes & average ratio of blue neighbor
		for (int j = 0; j < Nnodes; j++)
		{
			degree = 0;
			nblue = 0;
			if (value[j] == 1)
			{
				for (int k = 0; k < Nnodes; k++)
				{
					if (matrix[j][k] == 1)
					{
						degree++;
						if (value[k] == -1)
						{
							nblue++;
						}
					}
				}
				data1[i][0] += degree;
				data2[i][0] += (1.0 * nblue) / degree;
			}
		}
		data1[i][0] = 2.0 * data1[i][0] / Nnodes;
		data2[i][0] = 2.0 * data2[i][0] / Nnodes;*/


		/*
		//calculate C_R and C_B, TriangleRed
		C_R[i][0] = 0;
		C_B[i][0] = 0;
		TriangleRed0[i][0] = 0;
		TriangleRed1[i][0] = 0;
		TriangleRed2[i][0] = 0;
		TriangleRed3[i][0] = 0;
		for (int j = 0; j < Nnodes; j++)
		{
			double CC = 0;
			int max_triangle = 0;
			int triangle = 0;
			int test[Nnodes];
			int trianglered;

			if (degree[j] >= 2)
			{
				max_triangle = combination(degree[j]);
				//printf("%d\n", max_triangle);
				for (int k = 0; k < Nnodes; k++)
				{
					test[k] = -1;
					if (matrix[j][k] == 1)
					{
						test[k] = k;
					}
				}
				for (int k = 0; k < Nnodes; k++)
				{
					if (test[k] >= 0)
					{
						for (int r = 0; r < Nnodes; r++)
						{
							if (test[r] >= 0)
							{
								if (matrix[test[k]][test[r]] == 1)
								{
									triangle++;
									trianglered = value[j] + value[test[k]] + value[test[r]];
									if (trianglered == -3)
									{
										TriangleRed0[i][0]++;
									}
									if (trianglered == -1)
									{
										TriangleRed1[i][0]++;
									}
									if (trianglered == 1)
									{
										TriangleRed2[i][0]++;
									}
									if (trianglered == 3)
									{
										TriangleRed3[i][0]++;
									}
								}
							}
						}
					}
				}
				CC = triangle * 0.5 / max_triangle;
				//printf("%f\n", CC);
				if (value[j] == 1)
				{
					C_R[i][0] += CC;
				}
				if (value[j] == -1)
				{
					C_B[i][0] += CC;
				}
			}
		}

		C_R[i][0] = C_R[i][0] * 2.0 / Nnodes;
		C_B[i][0] = C_B[i][0] * 2.0 / Nnodes;
		TriangleRed0[i][0] = TriangleRed0[i][0] * 1.0 / 6.0;
		TriangleRed1[i][0] = TriangleRed1[i][0] * 1.0 / 6.0;
		TriangleRed2[i][0] = TriangleRed2[i][0] * 1.0 / 6.0;
		TriangleRed3[i][0] = TriangleRed3[i][0] * 1.0 / 6.0;


		//calculate SquareRed
		SquareRed1[i][0] = 0;
		SquareRed2a[i][0] = 0;
		SquareRed2b[i][0] = 0;
		SquareRed3[i][0] = 0;
		SquareRed4[i][0] = 0;
		SquareRed0[i][0] = 0;
		for (int j = 0; j < Nnodes; j++)
		{
			if (degree[j] >= 2)
			{
				for (int k = 0; k < Nnodes; k++)
				{
					if (matrix[j][k] == 1)
					{
						for (int r = 0; r < Nnodes; r++)
						{
							if (matrix[j][r] == 1 && matrix[k][r] == 0)
							{
								for (int s = 0; s < Nnodes; s++)
								{
									if (matrix[k][s] == 1 && matrix[r][s] == 1 && matrix[j][s] == 0)
									{
										int square = 0;
										square = value[j] + value[k] + value[r] + value[s];
										if (square == 4)
										{
											SquareRed4[i][0]++;
										}
										if (square == 2)
										{
											SquareRed3[i][0]++;
										}
										if (square == -2)
										{
											SquareRed1[i][0]++;
										}
										if (square == -4)
										{
											SquareRed0[i][0]++;
										}
										if (square == 0)
										{
											if (value[j] == value[k] || value[j] == value[r])
											{
												SquareRed2b[i][0]++;
											}
											if (value[j] != value[k] && value[j] != value[r])
											{
												SquareRed2a[i][0]++;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		SquareRed0[i][0] = 1.0 * SquareRed0[i][0] / 8.0;
		SquareRed1[i][0] = 1.0 * SquareRed1[i][0] / 8.0;
		SquareRed2a[i][0] = 1.0 * SquareRed2a[i][0] / 8.0;
		SquareRed2b[i][0] = 1.0 * SquareRed2b[i][0] / 8.0;
		SquareRed3[i][0] = 1.0 * SquareRed3[i][0] / 8.0;
		SquareRed4[i][0] = 1.0 * SquareRed4[i][0] / 8.0;
		*/



		//calculate average N_red without rewiring
		/*
		step_red = 0;
		//step_blue = 0;
		//win_red = 0;
		//win_blue = 0;
		for (int j = 0; j < 100; j++)
		{
			int value_test[Nnodes];
			for (int k = 0; k < Nnodes; k++)
			{
				value_test[k] = value[k];
			}
			//M = Nnodes * 0.5;
			//t = 0;
			//while ((0.3 < M || M < 0.7) && t < 10000)
			for (int l = 0; l < 1000; l++)
			{
				//E_same = 0;
				//E_diff = 0;
				int delta_E = 0;
				int y;
				y = (1.0 * rand() * Nnodes) / RAND_MAX;
				//printf("%d\n", y);
				for (int k = 0; k < Nnodes; k++)
				{
					if (matrix[y][k] == 1)
					{
						delta_E = delta_E + value_test[k];
					}
				}
				delta_E = 2 * value_test[y] * delta_E;

				if (delta_E <= 0)
				{
					value_test[y] = -1 * value_test[y];
				}
				if (delta_E > 0)
				{
					if ((1.0 * rand() / RAND_MAX) < exp(-1.0 * delta_E * beta))
					{
						value_test[y] = -1 * value_test[y];
					}
				}

				M = 0;
				for (int k = 0; k < Nnodes; k++)
				{
					if (value_test[k] == 1)
					{
						M++;
					}
				}
				//t++;
			}
			step_red += M;
			//step_blue += (100 - M);

			//M_all = 0;
			//for (int i = 0; i < Nnodes; i++)
			//{
			//	M_all = M_all + value_test[i];
			//}
			//data1[j][0] = j;
			//data1[j][1] = M;
			//step += M_all * 1.0 / 100.0;
		}

		Rewiring[i][2] = 1.0 * step_red / 100.0;
		//C_R[i][1] = step_red;
		//C_B[i][1] = step_blue;
		//C_R[i][1] = 1.0 * step_red / 100.0;
		//C_B[i][1] = 1.0 * step_blue / 100.0;
		//TriangleRed0[i][1] = C_R[i][1];
		//TriangleRed1[i][1] = C_R[i][1];
		//TriangleRed2[i][1] = C_R[i][1];
		//TriangleRed3[i][1] = C_R[i][1];
		//SquareRed0[i][1] = 1.0 * step_red / 100.0;
		//SquareRed1[i][1] = 1.0 * step_red / 100.0;
		//SquareRed2a[i][1] = 1.0 * step_red / 100.0;
		//SquareRed2b[i][1] = 1.0 * step_red / 100.0;
		//SquareRed3[i][1] = 1.0 * step_red / 100.0;
		//SquareRed4[i][1] = 1.0 * step_red / 100.0;
		if (Rewiring[i][2] > 70)
		{
			ratio_no_rewiring++;
		}


		//calculate average N_red after rewiring
		int step_red_rewiring = 0;
		int M_rewiring = 0;
		for (int j = 0; j < 100; j++)
		{
			int value_test_rewiring[Nnodes];
			for (int k = 0; k < Nnodes; k++)
			{
				value_test_rewiring[k] = value[k];
			}
			for (int l = 0; l < 1000; l++)
			{
				int delta_E = 0;
				int y;
				y = (1.0 * rand() * Nnodes) / RAND_MAX;
				for (int k = 0; k < Nnodes; k++)
				{
					if (matrix_rewiring[y][k] == 1)
					{
						delta_E = delta_E + value_test_rewiring[k];
					}
				}
				delta_E = 2 * value_test_rewiring[y] * delta_E;

				if (delta_E <= 0)
				{
					value_test_rewiring[y] = -1 * value_test_rewiring[y];
				}
				if (delta_E > 0)
				{
					if ((1.0 * rand() / RAND_MAX) < exp(-1.0 * delta_E * beta))
					{
						value_test_rewiring[y] = -1 * value_test_rewiring[y];
					}
				}

				M_rewiring = 0;
				for (int k = 0; k < Nnodes; k++)
				{
					if (value_test_rewiring[k] == 1)
					{
						M_rewiring++;
					}
				}
			}
			step_red_rewiring += M_rewiring;
		}

		Rewiring[i][1] = 1.0 * step_red_rewiring / 100.0;
		if (Rewiring[i][1] >= 70)
		{
			ratio_rewiring++;
		}
		}*/
	}
	/*
	ratio_rewiring = 1.0 * ratio_rewiring / N;
	ratio_no_rewiring = 1.0 * ratio_no_rewiring / N;
	*/
	for (int i = 0; i < 50; i++)
	{
		distribution[i][1] = 1.0 * distribution[i][1] / N;
	}

// write file
	FILE *fp1;
	//FILE *fp2;
	//FILE *fp3;
	//FILE *fp4;
	//FILE *fp5;
	//FILE *fp6;

	fp1 = fopen("Degree distribution(p=0.3,T=0.03,step=1000),30rewiring,100simul.dat", "w");
	for (int i = 0; i < 50; i++)
	{
		fprintf(fp1, "%f,%f\n", distribution[i][0], distribution[i][1]);
	}
	fclose(fp1);
	/*
		fp1 = fopen("SquareRed0~N_red(p=0.3,T=0.03,step=10000),1000simul.dat", "w");
		for (int i = 0; i < N; i++)
		{
			fprintf(fp1, "%f,%f\n", SquareRed0[i][0], SquareRed0[i][1]);
		}
		fclose(fp1);

		fp2 = fopen("SquareRed1~N_red(p=0.3,T=0.03,step=10000),1000simul.dat", "w");
		for (int i = 0; i < N; i++)
		{
			fprintf(fp2, "%f,%f\n", SquareRed1[i][0], SquareRed1[i][1]);
		}
		fclose(fp2);

		fp3 = fopen("SquareRed2a~N_red(p=0.3,T=0.03,step=10000),1000simul.dat", "w");
		for (int i = 0; i < N; i++)
		{
			fprintf(fp3, "%f,%f\n", SquareRed2a[i][0], SquareRed2a[i][1]);
		}
		fclose(fp3);

		fp4 = fopen("SquareRed3~N_red(p=0.3,T=0.03,step=10000),1000simul.dat", "w");
		for (int i = 0; i < N; i++)
		{
			fprintf(fp4, "%f,%f\n", SquareRed3[i][0], SquareRed3[i][1]);
		}
		fclose(fp4);

		fp5 = fopen("SquareRed2b~N_red(p=0.3,T=0.03,step=10000),1000simul.dat", "w");
		for (int i = 0; i < N; i++)
		{
			fprintf(fp5, "%f,%f\n", SquareRed2b[i][0], SquareRed2b[i][1]);
		}
		fclose(fp5);

		fp6 = fopen("SquareRed4~N_red(p=0.3,T=0.03,step=10000),1000simul.dat", "w");
		for (int i = 0; i < N; i++)
		{
			fprintf(fp6, "%f,%f\n", SquareRed4[i][0], SquareRed4[i][1]);
		}
		fclose(fp6);
	*/
}






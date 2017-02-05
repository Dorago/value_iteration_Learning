#include <stdio.h>
#include <math.h>
#include <string.h>

int main()
{
	const int start[2] = {0,0};									//開始位置
	const int end[2] = {2,2};									//終了位置
	double init_state[3][3] = { {0,0,0}, {0,0,0}, {0,0,10} };	//各マスにおける初期状態
	double state[3][3] = { {0,0,0}, {0,0,0}, {0,0,0} };			//各マスにおける現在の状態
	double old_state[3][3] = { {0,0,0}, {0,0,0}, {0,0,0} };		//各マスにおける一つ前の状態
	const double reward = -0.5;									//報酬
	const double gamma = 0.9;									//割引関数
	const double epsilon = 0.01;								//収束関数
	int srow,scolumn;											//行列判別
	double Up,Down,Right,Left;									//行動できる向き
	int cycle= 0;												//試行回数
	int convergence = 0;										//収束判定
	double delta = 0;											//偏差
	char vector[3][3][6];										//
	double test = 0;											//


	while(convergence != 9)	//loop条件
	{
		cycle++;
		convergence = 0;		//リセット

	for( srow = 0 ; srow < 3 ; srow++ )
	{
		for( scolumn = 0 ; scolumn < 3 ; scolumn++ )
		{
			switch(srow)
			{
				case 0 : Up = 0; Down = state[srow+1][scolumn];break;
				case 1 : Up = state[srow-1][scolumn]; Down = state[srow+1][scolumn];break;
				case 2 : Up = state[srow-1][scolumn]; Down = 0;break;
			}

			switch(scolumn)
			{
				case 0 : Right = state[srow][scolumn+1]; Left = 0;break;
				case 1 : Right = state[srow][scolumn+1]; Left = state[srow][scolumn-1];break;
				case 2 : Right = 0; Left = state[srow][scolumn-1];break;
			}

			if(init_state[srow][scolumn] == 0)
			{
				state[srow][scolumn] = reward + (gamma * ( 0.1*Up + 0.4*Down + 0.1*Right + 0.4*Left ));
			}
			else
			{
				state[srow][scolumn] = init_state[srow][scolumn];
			}

			delta = fabs(state[srow][scolumn] - old_state[srow][scolumn]);

			if( delta < epsilon * ( 1 - gamma ) / gamma )			//収束判定
			{
				convergence ++;
			}

			old_state[srow][scolumn] = state[srow][scolumn];		//記録
		}
	}

	printf("\n %d cycle\n",cycle);
	printf("|-----------------|\n");
	printf("|     |     |     |\n");
	printf("|%.3f|%.3f|%.3f|\n",state[0][0],state[0][1],state[0][2]);
	printf("|     |     |     |\n");
	printf("|-----------------|\n");
	printf("|     |     |     |\n");
	printf("|%.3f|%.3f|%.3f|\n",state[1][0],state[1][1],state[1][2]);
	printf("|     |     |     |\n");
	printf("|-----------------|\n");
	printf("|     |     |     |\n");
	printf("|%.3f|%.3f|%.3f|\n",state[2][0],state[2][1],state[2][2]);
	printf("|     |     |     |\n");
	printf("|-----------------|\n");

	}

	for( srow = 0 ; srow < 3 ; srow++ )
	{
		for( scolumn = 0 ; scolumn < 3 ; scolumn++ )
		{

			if(init_state[srow][scolumn] != 0)
			{
				strcpy_s(vector[srow][scolumn], "x");
			}

			else
			{
				switch(srow)
				{
					case 0 : strcpy_s(vector[srow][scolumn], "Down");
							 test = state[srow+1][scolumn];
							 break;

					case 1 : strcpy_s( vector[srow][scolumn], state[srow-1][scolumn] > state[srow+1][scolumn] ? "Up" : "Down" );
							 test = state[srow-1][scolumn] > state[srow+1][scolumn] ? state[srow-1][scolumn] : state[srow+1][scolumn];
							 break;
				
					case 2 : strcpy_s(vector[srow][scolumn], "Up");
							 test = state[srow-1][scolumn];
							 break;
				}

				switch(scolumn)
				{
					case 0 : if(test < state[srow][scolumn+1]) strcpy_s(vector[srow][scolumn], "Right");
							 break;

					case 1 : if(test < state[srow][scolumn-1]) strcpy_s(vector[srow][scolumn], "Left");
							 test = test > state[srow][scolumn-1] ? test : state[srow][scolumn-1];
							 if(test < state[srow][scolumn+1]) strcpy_s(vector[srow][scolumn], "Right");
							 break;

					case 2 : if(test < state[srow][scolumn-1]) strcpy_s(vector[srow][scolumn], "Left");
							 break;
				}	
			}
			test = 0;
		}
	}

	printf("\ndirection vector\n");
	printf("|-----------------|\n");
	printf("|     |     |     |\n");
	printf("|%5s|%5s|%5s|\n",vector[0][0],vector[0][1],vector[0][2]);
	printf("|     |     |     |\n");
	printf("|-----------------|\n");
	printf("|     |     |     |\n");
	printf("|%5s|%5s|%5s|\n",vector[1][0],vector[1][1],vector[1][2]);
	printf("|     |     |     |\n");
	printf("|-----------------|\n");
	printf("|     |     |     |\n");
	printf("|%5s|%5s|%5s|\n",vector[2][0],vector[2][1],vector[2][2]);
	printf("|     |     |     |\n");
	printf("|-----------------|\n");

	while(1){}		//デバック用
	return 0;
}
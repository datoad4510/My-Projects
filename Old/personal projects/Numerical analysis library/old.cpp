template<>
int Matrix<double>::rank()
{
	assert(rows == columns); //gavavseb kvadratamde da eg iqneba ara? ogond striqonebit gavavseb, torem ucnobebi daemateba svetebs tu gavuvseb
	for (int i = 0; i < rows; i++)
	{
		double max = data[i][i];
		int max_index = i;
		for (int k = i + 1; k < rows; k++) //rows da ara rows - 1, ese ipovis bolo row tu nulovania da gvetyvis aris tu ara singular
		{
			if (absolute(data[k][i]) > absolute(max))
			{
				max = data[k][i];
				max_index = k;
			}
		}
		if (max_index != i)
		{
			this->exchange_row(i, max_index);
		}
		if (data[i][i] == 0 && i != rows - 1) //trapeciul formaze dagvyavs
		{
			bool changed = false;
			for (int m = i; m < rows; m++)
			{
				for (int n = i + 1; n < columns; n++)
				{
					if (data[m][n] != 0)
					{
						this->exchange_row(i, m);
						this->exchange_column(i, n);
						changed = true;
					}
				}
			}
			if (changed == false)
				return rows - i;
		}
		for (int k = i + 1; k < rows; k++)
		{
			double m = data[k][i] / data[i][i];
			for (int j = i; j < columns; j++)
			{
				data[k][j] -= data[i][j] * m;
			}
		}
	}
	int ind_var = 0;
	for (int m = rows - 1; m >= 0; m--)
	{
		double temp = 0;
		for (int n = 0; n < columns; n++)
		{
			temp += absolute(data[m][n]);
		}
		if (temp == 0)
			ind_var++;
		else
			break;
	}
	return rows - ind_var;
}




template<>
void Matrix<double>::sol_num(Matrix<double>& x)
{
	assert(rows == columns); //rectangular array-ze unda ganvazogado rank... (igive ar iqneba? wrfivad damoukidebeli striqonebi)
	int rank = this->rank();//ise aq text-s jobs int-s abrunebdes
	if (rank == rows)
	{
		cout << "There is only one solution." << endl;
		return;
	}
	double sum = 0;
	for (int i = rank + 1; i < rows; i++)
	{
		sum += absolute(x[i][1]);
	}
	if (sum == 0)
	{
		cout << "There are infnitely many solutions. The number of free variables is " << rows - rank << "." << endl;
	}
	if (sum != 0)
	{
		cout << "There are no solutions" << endl;
	}
}
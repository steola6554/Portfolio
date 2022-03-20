#include <stdlib.h>

int	**init_grid(void)
{
	int	i;
	int	**grid;

	i = 0;
	grid = malloc(8 * 4);
	while (i < 4)
	{
	grid[i] = malloc(4 * 4);
	i++;
	}
	return (grid);
}

int	check_number_repition(int x, int y, int **grid)
{
	int	i;

	i = 0;
	while (i < x)
	{
		if (grid[y][i] == grid[y][x])
			return (0);
		i++;
	}
	i = 0;
	while (i < y)
	{
		if (grid[i][x] == grid[y][x])
			return (0);
		i++;
	}
	return (1);
}

int	check_row_clue_r(int x, int y, int **grid, int *clues)
{
	int	i;
	int	max;
	int	count;

	i = 3;
	max = -1;
	count = 0;
	if (x != 3 || clues[4 + y] == 0)
		return (1);
	while (i >= 0)
	{
		if (grid[y][i] > max)
		{
			max = grid[y][i];
			count++;
		}
		i--;
	}
	if (count != clues[4 + y])
		return (0);
	return (1);
}

int	check_row_clue_l(int x, int y, int **grid, int *clues)
{
	int	i;
	int	max;
	int	count;

	i = 0;
	max = -1;
	count = 0;
	if (clues[15 - y] == 0)
		return (1);
	while (i <= x)
	{
		if (grid[y][i] > max)
		{
			max = grid[y][i];
			count++;
		}
		if (count > clues[15 - y])
			return (0);
		i++;
	}
	if (count != clues[15 - y] && x == 3)
		return (0);
	return (1);
}

int	check_col_clue_u(int x, int y, int **grid, int *clues)
{
	int	i;
	int	max;
	int	count;

	i = 0;
	max = -1;
	count = 0;
	if (clues[x] == 0)
		return (1);
	while (i <= y)
	{
		if (grid[i][x] > max)
		{
			max = grid[i][x];
			count++;
		}
		if (count > clues[x])
			return (0);
		i++;
	}
	if (count != clues[x] && y == 3)
		return (0);
	return (1);
}

int	check_col_clue_d(int x, int y, int **grid, int *clues)
{
	int	i;
	int	max;
	int	count;

	i = 3;
	max = -1;
	count = 0;
	if (y != 3 || clues[11 - x] == 0)
		return (1);
	while (i >= 0)
	{
		if (grid[i][x] > max)
		{
			max = grid[i][x];
			count++;
		}
		i--;
	}
	if (count != clues[11 - x])
		return (0);
	return (1);
}

int	check_constraint(int x, int y, int **grid, int *clues)
{
	if (!check_number_repition(x, y, grid))
		return (0);
	if (!check_row_clue_r(x, y, grid, clues))
		return (0);
	if (!check_row_clue_l(x, y, grid, clues))
		return (0);
	if (!check_col_clue_u(x, y, grid, clues))
		return (0);
	if (!check_col_clue_d(x, y, grid, clues))
		return (0);
	return (1);
}

int	solve_recursive(int x, int y, int **grid, int *clues)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		grid[y][x] = i + 1;
		if (check_constraint(x, y, grid, clues))
		{
			if (x == 3 && y == 3)
				return (1);
			else if (solve_recursive((1 + x) % 4, y + x / 3, grid, clues))
				return (1);
		}
		i++;
	}
	return (0);
}

int	**solve_puzzle(int *clues)
{
	int	**grid;

	*grid = init_grid();
	solve_recursive(0, 0, grid, clues);
	return (grid);
}

int	main(void)
{
	int	clues[16];
	int	**res;
	int	i;
	int	j;

	clues[0] = 4;
	clues[1] = 3;
	clues[2] = 2;
	clues[3] = 1;
	clues[4] = 1;
	clues[5] = 2;
	clues[6] = 2;
	clues[7] = 2;
	clues[8] = 2;
	clues[9] = 2;
	clues[10] = 2;
	clues[11] = 1;
	clues[12] = 1;
	clues[13] = 2;
	clues[14] = 3;
	clues[15] = 4;
	i = 0;
	j = 0;
	*res = solve_puzzle(clues);
	while (i < 4)
	{
		while (j < 4)
		{
			printf("%d", res[i][j]);
		}
		printf("\n");
	}
	return (0);
}

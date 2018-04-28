#define CLR_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <map>
#include <tuple>
#include <set>
#include <string>
#include <queue>
#include <deque>
#include <stack>
#include <cstdio>
#include <regex>
#include <limits.h>
#include <float.h>
#include <utility>
#include <sstream>
#include <bitset>
#include <stdio.h>	
#include <list>
#include <Windows.h>
#include <WinBase.h>
#include <ctime>
#include <io.h>
#include <fcntl.h>
#define pub push_back
#define puf push_front
#define pob pop_back
#define pof pop_front



using namespace std;



typedef long long ll;
typedef long double ld;
typedef vector<ll> arr;
typedef vector<arr> matrix;
typedef vector<matrix> cube;



const int inf = 1e9 + 7;



ll m, n, main_counter, f_i, f_j, i_startcycle, j_startcycle, max_dr = 0;		//размер таблицы M*N; главный счетчик итераций поиска цикла; разницы по столбцу и строке; начало и конец цикла; абсолютный максимум по спросу и предложению
arr cycle_i, cycle_j, request, offer, request_leftover, offer_leftover, u, v;	//массивы с координатами цикла; спроса, предложения и их остатков; потенциалов по строкам и столбцам
matrix prices, shipment, basis_cells;											//матрицы тарифов, объемов поставок и базисных ячеек



void copy_arr(arr& from, arr& to) {
	to.resize(from.size());
	for (ll i = 0; i < from.size(); ++i) {
		to[i] = from[i];
	}
}



void copy_matrix(matrix& from, matrix& to) {
	to.resize(from.size());
	for (ll i = 0; i < from.size(); ++i) {
		copy_arr(from[i], to[i]);
	}
}



void copy_cube(cube& from, cube& to) {
	to.resize(from.size());
	for (ll i = 0; i < from.size(); ++i) {
		copy_matrix(from[i], to[i]);
	}
}



void input(string path) {
	fstream fin(path);
	fin >> m >> n;
	prices.resize(m + 1);
	shipment.resize(m + 1);
	basis_cells.resize(m + 1);
	for (ll i = 0; i <= m; ++i) {
		prices[i].resize(n + 1);
		shipment[i].resize(n + 1);
		basis_cells[i].resize(n + 1);
	}
	request.resize(n + 1);
	request_leftover.resize(n + 1);
	u.resize(m + 1);
	v.resize(n + 1);
	offer.resize(m + 1);
	offer_leftover.resize(m + 1);
	for (ll i = 1; i <= m; ++i) {
		for (ll j = 1; j <= n; ++j) {
			fin >> prices[i][j];
		}
	}
	for (ll i = 1; i <= n; ++i) {
		fin >> request[i];
		if (request[i] > max_dr) {
			max_dr = request[i];
		}
	}
	for (ll i = 1; i <= m; ++i) {
		fin >> offer[i];
		if (offer[i] > max_dr) {
			max_dr = offer[i];
		}
	}
	return;
}



void output() {
	for (ll i = 1; i <= m; ++i) {
		cout << endl;
		for (ll j = 1; j <= n; ++j) {
			cout << shipment[i][j] << '*' << prices[i][j] << '\t';
		}
	}
	cout << endl;
	return;
}



void to_zero() {
	for (ll j = 1; j <= n; ++j) {
		request_leftover[j] = request[j];
	}
	for (ll i = 1; i <= m; ++i) {
		offer_leftover[i] = offer[i];
	}
	for (ll i = 1; i <= m; ++i) {
		for (ll j = 1; j <= n; ++j) {
			basis_cells[i][j] = 0;
			shipment[i][j] = 0;
		}
	}
	return;
}



//---МЕТОД СЕВЕРО-ЗАПАДНОГО УГЛА---
//также заполняет БазисныеЯчейки[i][j] значениями 1 или 0 (если есть ненулевая отгрузка, то ячейка - базисная)
void nc_method() {
	for (ll i = 1; i <= m; ++i) {
		for (ll j = 1; j <= n; ++j) {
			if (offer_leftover[i] == 0) {
				break;
			}
			else {
				if (offer_leftover[i] < 0) {
					cerr << "Ошибка: leftover предложения меньше 0\n";
				}
			}
			ll space = request_leftover[j];
			if (space == 0) {
				continue;
			}
			else {
				if (space < 0) {
					cerr << "Ошибка: leftover спроса меньше 0\n";
				}
			}
			if (offer_leftover[i] < space) {
				space = offer_leftover[i];
			}
			request_leftover[j] -= space;
			offer_leftover[i] -= space;
			basis_cells[i][j] = 1;
			shipment[i][j] = space;
		}
	}
	return;
}



//---МЕТОД МИНИМАЛЬНОГО ЭЛЕМЕНТА---
void me_method() {
	for (ll max_count = 1; max_count <= m * n; ++max_count) {		//максимальное число итераций: M*N
		ll min_rate = inf, min_i = inf, min_j = inf;
		bool allcargowasshipped = true;
		ll i, j;
		for (i = 1; i <= m; ++i) {
			for (j = 1; j <= n; ++j) {
				if (basis_cells[i][j] == 1) {
					continue;
				}
				if (offer_leftover[i] == 0) {
					continue;
				}
				else {
					if (offer_leftover[i] < 0) {
						cerr << "Ошибка: leftover предложения меньше 0\n";
					}
				}

				if (request_leftover[j] == 0) {
					continue;
				}
				else {
					if (request_leftover[j] < 0) {
						cerr << "Ошибка: leftover спроса меньше 0\n";
					}
				}
				allcargowasshipped = false;
				ll fs = prices[i][j];
				if (min_rate == inf) {
					min_rate = fs;
					min_i = i;
					min_j = j;
				}
				else {
					if (fs < min_rate) {
						min_rate = fs;
						min_i = i;
						min_j = j;
					}
				}
			}
		}
		i = min_i;
		j = min_j;
		if (allcargowasshipped) {
			return;
		}
		if (min_rate == inf) {
			cerr << "Не удалось определить минимальный тариф\n";
		}
		ll space = request_leftover[j];		//минимальный тариф найден в ячейке i, j
		if (offer_leftover[i] < space) {
			space = offer_leftover[i];
		}
		request_leftover[j] = request_leftover[j] - space;
		offer_leftover[i] = offer_leftover[i] - space;
		basis_cells[i][j] = 1;
		shipment[i][j] = space;
	}
	cerr << "Не удалось распределить методом минимальных тарифов\n";
	return;
}



//вычисляет первую минимальную цену в указанной строке, обходит стороной ячейки, где остаток спроса = 0, возвращает минимальную цену, а j минимальной ячейки - в переменной f_j
ll f_first_min_price_by_string(ll i) {
	ll min1 = inf, f_j = inf;
	for (ll j = 1; j <= n; ++j) {
		if (request_leftover[j] == 0) {
			continue;
		}
		else {
			if (request_leftover[j] < 0) {
				cerr << "Ошибка: leftover спроса меньше 0\n";
			}
			ll max_count = prices[i][j];
			if (min1 == inf) {
				min1 = max_count;
				f_j = j;
			}
			else {
				if (min1 > max_count) {
					min1 = max_count;
					f_j = j;
				}
			}
		}
		return min1;
	}
}



//вычисляет вторую минимальную цену в указанной строке, обходит стороной ячейки, где остаток спроса = 0 и f_j, возвращает минимальную цену, а j минимальной ячейки - в переменной f_j
ll f_second_min_price_by_string(ll i) {
	ll min2 = inf;
	if (f_j == inf) {
		return inf;
	}
	for (ll j = 1; j <= n; ++j) {
		if (j == f_j) {
			continue;
		}
		if (request_leftover[j] == 0) {
			continue;
		}
		ll fs = prices[i][j];
		if (min2 == inf) {
			min2 = fs;
		}
		else {
			if (min2 > fs) {
				min2 = fs;
			}
		}
	}
	return min2;
}




//вычисляет первую минимальную цену по указанному столбцу, обходит стороной ячейки, где остаток предложения = 0, возвращает минимальную цену, а i минимальной ячейки - в переменной f_i
ll f_first_min_price_by_column(ll j) {
	ll min1 = inf, f_i = inf;
	for (ll i = 1; i <= m; ++i) {
		if (offer_leftover[i] == 0) {
			continue;
		}
		else {
			if (offer_leftover[i] < 0) {
				cerr << "Ошибка: leftover предложения меньше 0\n";
			}
		}
		ll max_count = prices[i][j];
		if (min1 == inf) {
			min1 = max_count;
			f_i = i;
		}
		else {
			if (min1 > max_count) {
				min1 = max_count;
				f_i = i;
			}
		}
	}
	return min1;
}




//вычисляет вторую минимальную цену по указанному столбцу, обходит стороной ячейки, где остаток предложения = 0 и f_i, возвращает минимальную цену, а i минимальной ячейки - в переменной f_i
ll f_second_min_price_by_column(ll j) {
	ll min2 = inf;
	if (f_i == inf) {
		return inf;
	}
	for (ll i = 1; i <= m; ++i) {
		if (i == f_i) {
			continue;
		}
		if (offer_leftover[i] == 0) {
			continue;
		}
		ll max_count = prices[i][j];
		if (min2 == inf) {
			min2 = max_count;
			f_i = i;
		}
		else {
			if (min2 > max_count) {
				min2 = max_count;
				f_i = i;
			}
		}
	}
	return min2;
}



ll f_difference_between_min_prices_by_string(ll i) {
	ll price1 = f_first_min_price_by_string(i), price2 = f_second_min_price_by_string(i);
	if (price2 == inf || price1 == inf) {
		return 0;
	}
	return price2 - price1;
}



ll f_difference_by_min_prices_by_column(ll j) {
	ll price1 = f_first_min_price_by_column(j), price2 = f_second_min_price_by_column(j);
	if (price1 == inf || price2 == inf) {
		return 0;
	}
	return price2 - price1;
}



//---МЕТОД АППРОКСИМАЦИИ ФОГЕЛЯ---
void f_method() {
	for (ll j = 1; j <= n; ++j) {
		request_leftover[j] = request[j];
	}

	for (ll i = 1; i <= m; ++i) {
		offer_leftover[i] = offer[i];
	}

	for (ll i = 1; i <= m; ++i) {
		for (ll j = 1; j <= n; ++j) {
			basis_cells[i][j] = 0;
			shipment[i][j] = 0;
		}
	}
	for (ll max_count = 1; max_count <= 100; ++max_count) {
		ll max1 = inf, max1_i = inf, i, max2 = inf, max2_j = inf, j;
		for (i = 1; i <= m; ++i) {
			if (offer_leftover[i] == 0) {
				continue;
			}
			ll delta = f_difference_between_min_prices_by_string(i);
			if (max1_i == inf) {
				max1 = delta;
				max1_i = i;
			}
			else {
				if (max1 < delta) {
					max1 = delta;
					max1_i = i;
				}
			}
		}
		for (j = 1; j <= n; ++j) {
			if (request_leftover[j] == 0) {
				continue;
			}
			ll delta = f_difference_by_min_prices_by_column(j);
			if (max2_j == inf) {
				max2 = delta;
				max2_j = j;
			}
			else {
				if (max2 < delta) {
					max2 = delta;
					max2_j = j;
				}
			}
		}
		if (max1 == inf && max2 == inf) {		//все отгрузили
			break;
		}
		else {
			if (max1 == inf) {
				max1 = max2 - 1;
			}
			else {
				if (max2 == inf) {
					max2 = max1 - 1;
				}
			}
		}
		if (max1 > max2) {		//предпочтительна строка max1
								//mn = f_first_min_price_by_string(max1_i);
			i = max1_i;
			j = f_j;
		}
		else {					//предпочтителен столбец max2
								//mn = f_first_min_price_by_column(max2_j);
			i = f_i;
			j = max2_j;
		}
		ll space = request_leftover[j];
		if (offer_leftover[i] < space) {
			space = offer_leftover[i];
		}
		request_leftover[j] = request_leftover[j] - space;
		offer_leftover[i] = offer_leftover[i] - space;
		basis_cells[i][j] = 1;
		shipment[i][j] = space;
	}
	return;
}



//---МЕТОД ПОТЕНЦИАЛОВ---
//проверяет правильность отгрузок: отгрузки по каждой строке должны быть равны предложению, а отгрузки по каждому столбцу - спросу потребителя
bool check_correctness_of_shipment() {
	for (ll i = 1; i <= m; ++i) {
		ll space = 0;
		for (ll j = 1; j <= n; ++j) {
			space += shipment[i][j];
		}
		if (space != offer[i]) {
			cerr << "Ошибка: shipment по строке не равны предложению в строке " << i << endl;
		}
	}
	for (ll j = 1; j <= n; ++j) {
		ll space = 0;
		for (ll i = 1; i <= m; ++i) {
			space += shipment[i][j];
		}
		if (space != request[j]) {
			cerr << "Ошибка: shipment по столбцу не равны спросу в столбце " << j << endl;
		}
	}
	return true;
}



void calc_potential_by_horizontal(ll i);



void calc_potential_by_vertical(ll j);



void calc_potential_by_vertical(ll j) {
	if (v[j] == inf) {
		cerr << "Ошибка Получения потенциала v[" << j << "]\n";
	}
	for (ll i = 1; i <= m; ++i) {
		if (basis_cells[i][j] == 0) {
			continue;
		}
		if (u[i] != inf) {
			continue;
		}
		else {
			u[i] = prices[i][j] - v[j];
			calc_potential_by_horizontal(i);
		}
	}
}


void calc_potential_by_horizontal(ll i) {
	main_counter--;
	if (main_counter == 0) {
		cerr << "Зацикливание при вычислении Потенциалов\n";
	}
	if (u[i] == inf) {
		cerr << "Ошибка получения потенциала u[" << i << "]\n";
	}
	for (ll j = 1; j <= n; ++j) {
		if (basis_cells[i][j] == 0) {
			continue;
		}
		if (v[j] != inf) {
			continue;
		}
		else {
			v[j] = prices[i][j] - u[i];
			calc_potential_by_vertical(j);
		}
	}
}



//вычисление потенциалов u[i] и v[j]
bool calc_potentials() {
	ll i, j;
	for (i = 1; i <= m; ++i) {
		u[i] = inf;
	}
	for (j = 1; j <= n; ++j) {
		v[j] = inf;
	}
	u[1] = 0;
	main_counter = m * n;					//максимальное число итераций
	calc_potential_by_horizontal(1);	//начало рекурсии
	for (ll i = 1; i <= m; ++i) {		//проверка
		if (u[i] == inf) {
			cout << "\nНе удалось вычислить Потенциал u[" << i << "]\n";
			return false;
		}
	}
	for (j = 1; j <= n; ++j) {
		if (v[j] == inf) {
			cout << "\nНе удалось вычислить Потенциал v[" << j << "]\n";
			return false;
		}
	}
	return true;
}



//по известным потенциалам u и v, а также ценам, вычисляет, оптимальное ли решение, если решение не оптимально, находит ячейку i1,j1 с минимальной отрицательной дельтой, откуда будем строить цикл
bool check_optimality_of_solving() {
	bool solvingisoptimal = true;
	ll mindelta = inf, i, j, delta;
	for (ll i = 1; i <= m; ++i) {
		for (ll j = 1; j <= n; ++j) {
			if (basis_cells[i][j] == 1) {
				delta = 0;
			}
			else {
				delta = prices[i][j] - u[i] - v[j];
			}
			if (delta < 0) {
				solvingisoptimal = false;
			}
			if (mindelta == inf) {
				mindelta = delta;
				i_startcycle = i;
				j_startcycle = j;
			}
			else {
				if (delta < mindelta) {
					mindelta = delta;
					i_startcycle = i;
					j_startcycle = j;
				}
			}
		}
	}
	return solvingisoptimal;
}



//вычисляет суммарную стоимость транспортировки
ll full_price_of_shipment() {
	ll sum = 0;
	for (ll i = 1; i <= m; ++i) {
		for (ll j = 1; j <= n; ++j) {
			sum += (shipment[i][j] * prices[i][j]);
		}
	}
	return sum;
}



//если решение вырождено, то надо ввести в число базисных переменную с нулевой отгрузкой
bool find_zero_cell_to_insert_in_basis() {
	ll is_ok = 0;					//проверка вселенной на стабильность
	for (ll i = 1; i <= m; ++i) {
		for (ll j = 1; j <= n; ++j) {
			if (basis_cells[i][j] == 0) {
				is_ok = 1;
				break;
			}
		}
		if (is_ok == 1) {
			break;
		}
	}
	if (is_ok == 0) {
		cerr << "Не существует не базисной (нулевой) ячейки цикла ввода в базис\n";
	}
	while (1) {
		/*случайные значения для предотвращения зацикливания, согласно рекомендации Данцига:
		Дж. Данциг «Линейное программирование, его применения и обобщения» 1966г. - стр. 312*/
		ll i = 1 + rand() % m, j = 1 + rand() % n;
		if (basis_cells[i][j] == 1) {	//пропускаем базисные ячейки
			continue;
		}
		if (shipment[i][j] != 0) {
			cerr << "Ненулевые shipment цикла не базисной ячейки\n";
		}
		/*if (Найти(i, j)) {			//Пропускаем ячейки, которые образуют цикл
		continue;
		}*/
		basis_cells[i][j] = 1;
		cout << "В базис введена ячейка " << i << " " << j << endl;
		return true;					//удалось найти ячейку
	}
}



/*bool find_cycle_by_horizontal(ll i0, ll j0);*/




/*bool find_cycle_by_vertical(ll i0, ll j0);*/



/*bool find_cycle_by_horizontal(ll i0, ll j0) {
main_counter--;
if (main_counter == 0) {
cerr << "Слишком большое число итераций при поиске цикла\n";
return false;
}
for (ll j = 1; j <= n; ++j) {
if (j == j0 || basis_cells[i0][j] == 0) {
continue;
}
if (find_cycle_by_vertical(i0, j)) {
cycle_i.push_back(i0);
cycle_j.push_back(j);
return true;
}
}
return false;
}*/



/*bool find_cycle_by_vertical(ll i0, ll j0) {
for (ll i = 1; i <= m; ++i) {
if (j0 == j_startcycle && i == i_startcycle) {		//попали в начальную точку
cycle_i.push_back(i);
cycle_j.push_back(j0);
return true;									//это победа, цикл найден
}
if (i == i0 || basis_cells[i][j0] == 0) {
continue;
}
if (find_cycle_by_horizontal(i, j0)) {
cycle_i.push_back(i);
cycle_j.push_back(j0);
return true;
}
}
return false;											//это не победа, цикл не найден
}*/



//поиск цикла для перераспределения поставок, заполняет массивы cycle_i и cycle_j с координатами вершин цикла
/*bool find_cycle(ll i0, ll j0) {
main_counter = 4*m*n;	//максимальное число итераций: M*N
cycle_i.clear();
cycle_j.clear();
if (find_cycle_by_horizontal(i0, j0)) {
return true;	//нашли цикл
}
return false;		//цикл не найден
}*/



//обходит граф в глубину
bool dfs(matrix& graph, arr& used, arr& parent, ll v, ll x, bool flag) {
	for (ll i = 0; i < graph[v].size(); ++i) {
		if (!used[graph[i][v]] && used[graph[i][v]] != 2) {		//если не были в вершине и с нее не начинается цикл, неокружающий клетку i0, j0
			used[graph[i][v]] = 1;
			parent[graph[i][v]] = v;
			dfs(graph, used, parent, graph[i][v], x, flag);
		}
		else {
			arr cycle;
			ll t = v;
			while (parent[t] != v) {
				cycle.pub(t);
				v = parent[t];
			}
			cycle.pub(v);
			sort(cycle.begin(), cycle.end());
			if (cycle[0] < x && cycle[n - 1] > x && cycle[0] < cycle[((cycle.size()) / 2 - 1) / 2] &&
				cycle[((cycle.size()) / 2 - 1) / 2] < x && cycle[cycle.size() - 1] > cycle[cycle.size() / 2 - 1 + (((cycle.size()) / 2 - 1) / 2)] &&
				cycle[cycle.size() / 2 - 1 + (((cycle.size()) / 2 - 1) / 2)] > x) {
				return true;
			}
			else {											//если цикл клетку окружает, то все плохо: помечаем вершину ОЧЕНЬ ПЛОХОЙ
				used[graph[i][v]] = 2;
				for (ll i = 0; i < n * m + n + m; ++i) {	//удалим все значения из массива предков и путей, кроме ОЧЕНЬ ПЛОХИХ КЛЕТОК
					if (used[i] == 1) {
						used[i] = 0;
					}
					parent[i] = -1;
				}
				if (flag) {
					flag = false;
					dfs(graph, used, parent, v, x, flag);				//попробуем еще разок
				}
				return false;
			}
		}
	}
	return false;
}



void dfs(matrix& graph, arr& used, ll v, ll counter) {
	for (ll i = 0; i < graph[v].size(); ++i) {
		if (!used[graph[v][i]]) {
			used[graph[v][i]] = 1;
			dfs(graph, used, graph[v][i], counter);
		}
	}
	return;
}



bool find_cycle(ll i0, ll j0) {
	cycle_i.clear();
	cycle_j.clear();
	vector<pair<ll, ll>>cycle;
	pair<ll, ll>top, top_right, right, down_right, down, down_left, left, top_left;
	ll i_now = i0, j_now = j0;
	while (i_now < m && j_now < n && !basis_cells[i_now][j_now]) {
		i_now++;
		j_now++;
	}
	if (i_now <= m && j_now <= n && basis_cells[i_now][j_now]) {
		top_right = { i_now, j_now };
	}
	else {
		return false;
	}
	i_now = i0;
	j_now = j0;
	while (i_now > 1 && j_now > 1 && !basis_cells[i_now][j_now]) {
		i_now--;
		j_now--;
	}
	if (i_now >= 1 && j_now >= 1 && basis_cells[i_now][j_now]) {
		down_left = { i_now, j_now };
	}
	else {
		return false;
	}
	i_now = i0;
	j_now = j0;
	while (i_now > 1 && !basis_cells[i_now][j_now]) {
		i_now--;
	}
	if (i_now >= 1 && basis_cells[i_now][j_now]) {
		down = { i_now, j_now };
	}
	else {
		return false;
	}
	i_now = i0;
	j_now = j0;
	while (i_now < m && !basis_cells[i_now][j_now]) {
		i_now++;
	}
	if (i_now <= m && basis_cells[i_now][j_now]) {
		top = { i_now, j_now };
	}
	else {
		return false;
	}
	i_now = i0;
	j_now = j0;
	while (i_now > 1 && j_now < n && !basis_cells[i_now][j_now]) {
		i_now--;
		j_now++;
	}
	if (i_now > 1 && j_now < n && basis_cells[i_now][j_now]) {
		down_right = { i_now, j_now };
	}
	else {
		return false;
	}
	i_now = i0;
	j_now = j0;
	while (i_now < m && j_now > 1 && !basis_cells[i_now][j_now]) {
		i_now++;
		j_now--;
	}
	if (i_now <= m && j_now >= 1 && basis_cells[i_now][j_now]) {
		top_left = { i_now, j_now };
	}
	else {
		return false;
	}
	i_now = i0;
	j_now = j0;
	while (j_now < n && !basis_cells[i_now][j_now]) {
		j_now++;
	}
	if (j_now <= n && basis_cells[i_now][j_now]) {
		right = { i_now, j_now };
	}
	else {
		return false;
	}
	i_now = i0;
	j_now = j0;
	while (j_now > 1 && !basis_cells[i_now][j_now]) {
		j_now--;
	}
	if (j_now >= 1 && basis_cells[i_now][j_now]) {
		left = { i_now, j_now };
	}
	else {
		return false;
	}
	i_now = i0;
	j_now = j0;
	matrix graph(n * m + n + m);
	for (ll i = 1; i <= m; ++i) {									//построим списки смежности для графа
		for (ll j = 1; j <= n; ++j) {
			if (basis_cells[i][j]) {
				if (j < n && basis_cells[i][j + 1]) {
					graph[(i - 1)*j + j].pub((i - 1) * j + j + 1);
				}
				if (j > 1 && basis_cells[i][j - 1]) {
					graph[(i - 1)*j + j].pub((i - 1) * j + j - 1);
				}
				if (i < m && basis_cells[i + 1][j]) {
					graph[(i - 1)*j + j].pub(i * j + j);
				}
				if (i > 1 && graph[i - 1][j]) {
					graph[(i - 1)*j + j].pub((i - 2) * j + j);
				}
			}
		}
	}
	arr used(n * m + n + m), parent(n * m + n + m);
	ll counter = 0;
	for (ll i = 1; i <= n * m + n + m; ++i) {					//разбиение и проверка компонент связности
		if (!used[i]) {
			counter++;
			dfs(graph, used, i, counter);
		}
	}
	if (!dfs(graph, used, parent, (top.first - 1) * top.second + top.second, (i0 - 1) * j0 + j0, true) &&
		!dfs(graph, used, parent, (down.first - 1) * down.second + down.second, (i0 - 1) * j0 + j0, true) &&
		!dfs(graph, used, parent, (left.first - 1) * left.second + left.second, (i0 - 1) * j0 + j0, true) &&
		!dfs(graph, used, parent, (top_right.first - 1) * top_right.second + top_right.second, (i0 - 1) * j0 + j0, true) &&
		!dfs(graph, used, parent, (top_left.first - 1) * top_left.second + top_left.second, (i0 - 1) * j0 + j0, true) &&
		!dfs(graph, used, parent, (down_right.first - 1) * down_right.second + down_right.second, (i0 - 1) * j0 + j0, true) &&
		!dfs(graph, used, parent, (down_left.first - 1) * down_left.second + down_left.second, (i0 - 1) * j0 + j0, true)) {		//попытаемся найти цикл обходом в глубину, использующим отсечение неокружающих клетку i0, j0
		cerr << "\nНе удалось найти цикл.\n";
		return false;
	}
	else {
		cycle_i.resize(cycle.size());
		cycle_j.resize(cycle.size());
		for (ll i = 0; i < cycle.size(); ++i) {
			cycle_i[i] = cycle[i].first;
			cycle_j[i] = cycle[i].second;
		}
		return true;
	}
}



//сдвиг по циклу пересчета cycle_i, cycle_j
bool recalc_by_cycle() {
	cout << "\nПерераспределение по циклу " << cycle_i.size() << endl;
	if (cycle_j.size() != cycle_i.size()) {
		cerr << "Не одинаковые размерности циклов координат цикла\n";
	}
	if (cycle_i.size() < 4) {
		cerr << "Цикл имеет меньше 4 элементов\n";
	}
	ll tetha = inf, sign = 1;
	for (ll max_count = 0; max_count <= cycle_i[cycle_i.size() - 1]; ++max_count) {
		ll i = cycle_i[max_count], j = cycle_j[max_count], amount;
		if (sign == -1) {
			amount = shipment[i][j];
			if (tetha == inf) {
				tetha = amount;
			}
			else {
				if (amount < tetha) {
					tetha = amount;
				}
			}
			sign = 1;
		}
		else {
			sign = -1;
		}
	}
	if (tetha == inf) {
		cerr << "Не удалось вычислить tetha\n";
	}
	cout << "\ntetha = " << tetha << endl;
	if (tetha == 0) {
		return false;
	}
	sign = 1;
	for (ll max_count = 0; max_count <= cycle_i[cycle_i.size() - 1]; ++max_count) {
		ll i = cycle_i[max_count], j = cycle_j[max_count];
		if (sign == -1) {
			shipment[i][j] -= tetha;
			sign = 1;
		}
		else {
			shipment[i][j] += tetha;
			sign = -1;
		}
	}
	return true;
}



void p_method() {
	cout << "\n\nМЕТОД ПОТЕНЦИАЛОВ\n\n";
	while (1) {
		check_correctness_of_shipment();
		ll countofbasis = 0;
		for (ll i = 1; i <= m; ++i) {
			for (ll j = 1; j <= n; ++j) {
				if (shipment[i][j] > 0) {
					basis_cells[i][j] = 1;
					countofbasis++;
				}
				else {
					if (shipment[i][j] < 0) {
						cerr << "shipment не должны быть отрицательными\n";
					}
					else {
						basis_cells[i][j] = 0;
					}
				}
			}
			while (countofbasis < (m + n - 1)) {
				cout << "Решение вырождено\n";
				find_zero_cell_to_insert_in_basis();
				countofbasis++;
			}
			if (!calc_potentials()) {
				continue;
			}
			if (check_optimality_of_solving()) {
				cout << "\nРЕШЕНИЕ ОПТИМАЛЬНО\n";	//нашли опимальное решение
				output();
				cout << "\nСтоимость перевозки: " << full_price_of_shipment() << endl;
				return;
			}
			cout << "Решение не оптимально\n";
			if (!find_cycle(i_startcycle, j_startcycle)) {
				cerr << "Не удалось найти цикл\n";
			}
			else {
				recalc_by_cycle();
			}
			cout << "Стоимость перевозки: " << full_price_of_shipment();
		}
	}
}



//---МЕТОД ДИФФЕРЕНЦИАЛЬНЫХ РЕНТ---
void dr_method() {
	cout << "\n\nМЕТОД ДИФФЕРЕНЦИАЛЬНЫХ РЕНТ\n\n";
	for (ll i = 1; i <= m; ++i) {
		for (ll j = 1; j <= n; ++j) {
			if (prices[i][j]) {

			}
		}
	}
}



/*bool kuhn(int from, arr& mt, arr& used, matrix& graph) {
if (used[from]) {
return false;
}
used[from] = true;
for (size_t i = 0; i < graph[from].size(); ++i) {
int to = graph[from][i];
if (mt[to] == -1 || kuhn(mt[to], mt, used, graph)) {
mt[to] = from;
return true;
}
}
return false;
}*/



//---МЕТОД ТЕОРИИ ГРАФОВ---
/*bool gt_method() {
ll n, s, counter = 0;
matrix graph(s);
arr used, mt(n, -1);
for (int i = 0; i < s; ++i) {
used.assign(s, false);
if (kuhn(i, mt, used, graph)) {
counter++;
}
}
}*/



//---МЕТОД 
/*bool s_method() {

}*/



void solve(char path[]) {
	setlocale(LC_ALL, "Russian");



	input(path);
	ll frequest = 0;
	for (ll j = 1; j <= n; ++j) {
		frequest += request[j];
	}
	ll foffer = 0;
	for (ll i = 1; i <= m; ++i) {
		foffer += offer[i];
	}
	if (foffer > frequest) {
		cout << "offer больше спроса на " << foffer - frequest << " единиц груза. Создайте фиктивного потребителя.\n";
	}
	else {
		if (foffer < frequest) {
			cout << "offer меньше спроса на " << frequest - foffer << " единиц груза. Создайте фиктивного поставщика.\n";
		}
	}
	/*добавление возмущений (эпсилон) во избежание зацикливания транспортной задачи
	литература:
	1) Дж. Данциг «Линейное программирование, его применения и обобщения», 1966г. - стр. 303
	2) С.Гасс. «Линейное программирование (методы и приложения)», - стр. 195,
	в данном случае не используется, поскольку применен метод случайного включения нулевой перевозки в базис, который также, согласно Данцигу, страхует от зацикливания*/
	/*ld epsilon = 0.0001, epsilon1= 0;
	for (ll j = 1; j <= n; ++j) {
	request[j] += epsilon;
	epsilon1 += epsilon;
	}
	offer[1] += epsilon1;*/
	cout << endl;
	to_zero();
	ll tick = clock();
	nc_method();
	ll now = clock();
	cout << endl << "Для вычисления понадобилось (сек): " << ((ld)(now - tick)) / CLOCKS_PER_SEC << endl;
	cout << "Стоимость перевозки методом северо-западного угла: " << full_price_of_shipment();
	output();
	to_zero();
	cout << endl;
	tick = clock();
	me_method();
	now = clock();
	cout << endl << "Для вычисления понадобилось (сек): " << ((ld)(now - tick)) / CLOCKS_PER_SEC << endl;
	cout << "Стоимость перевозки методом минимальных тарифов: " << full_price_of_shipment();
	output();
	to_zero();
	cout << endl;
	tick = clock();
	f_method();
	now = clock();
	cout << endl << "Для вычисления понадобилось (сек): " << ((ld)(now - tick)) / CLOCKS_PER_SEC << endl;
	cout << "Стоимость перевозки методом Фогеля: " << full_price_of_shipment();
	output();
	cout << endl;
	tick = clock();
	p_method();
	now = clock();
	cout << endl << "Для вычисления понадобилось (сек): " << ((float)(now - tick)) / CLOCKS_PER_SEC << endl;
	tick = clock();
	dr_method();
	now = clock();
	cout << endl << "Для вычисления понадобилось (сек): " << ((float)(now - tick)) / CLOCKS_PER_SEC << endl;
	tick = clock();
	//to be continued...



	system("pause");
}
/*EXAMPLES:
2 2
4 7
3 5
10 20
25 5

3 5
5 3 6 2 0
4 7 9 1 0
3 4 7 5 0
16 18 30 25 1
19 37 34

4 6
1 2 1 4 5 2
3 3 2 1 4 3
4 2 5 9 6 2
3 1 7 3 4 6
20 40 30 10 50 25
30 50 75 20

4 6
2 1 3 3 2 5
3 2 2 4 3 4
3 5 4 2 4 1
4 2 2 1 2 2
30 50 20 40 30 11
50 40 60 31
*/

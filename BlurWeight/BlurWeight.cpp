// BlurWeight.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
using namespace std;

/// <summary>
/// 暂停
/// </summary>
void _pause()
{
	int _ = getchar();
}
/// <summary>
/// 显示错误
/// </summary>
/// <param name="errorInfo">错误信息</param>
/// <returns></returns>
bool _showError(string errorInfo)
{
	_pause();
	cout << errorInfo.c_str() << endl;
	_pause();
	return false;
}
/// <summary>
/// 获取输入
/// </summary>
/// <param name="radius">半径</param>
/// <param name="variance">方差</param>
/// <param name="r">半径</param>
/// <param name="v">方差</param>
/// <returns></returns>
bool _getInput(string& radius, string& variance, int& r, double& v)
{
	system("cls");
	cout << "欢迎使用高斯模糊权重计算器" << endl;
	cout << "请输入模糊半径，必须是正整数：" << endl;
	cin >> radius;
	r = atoi(radius.c_str());
	if (r <= 0)
		return _showError("输入半径不合法！");
	cout << "请输入方差，必须正数" << endl;
	cin >> variance;
	v = atof(variance.c_str());
	if (v <= 0)
		return _showError("输入方差不合法！");
	return true;
}
/// <summary>
/// 展示结果
/// </summary>
/// <param name="weights">权重</param>
/// <param name="normalize">是否归一化，即缩放到总权重为1</param>
void _displayResult(vector<vector<double> > weights, bool normalize)
{
	cout << setiosflags(ios::fixed) << setprecision(6) << endl;
	double sumWeight = 1;
	if (normalize)
	{
		sumWeight = 0;
		for (vector<vector<double> >::iterator iter = weights.begin(); iter != weights.end(); ++iter)
		{
			vector<double> line = *iter;
			for (vector<double>::iterator iter2 = line.begin(); iter2 != line.end(); ++iter2)
			{
				sumWeight += *iter2;
			}
		}
	}
	for (vector<vector<double> >::iterator iter = weights.begin(); iter != weights.end(); ++iter)
	{
		vector<double> line = *iter;
		for (vector<double>::iterator iter2 = line.begin(); iter2 != line.end(); ++iter2)
		{
			double weight = *iter2 / sumWeight;
			cout << weight << '\t';
		}
		cout << endl;
	}
}
/// <summary>
/// 计算权重组
/// </summary>
/// <param name="radius">半径</param>
/// <param name="variance">方差</param>
/// <returns></returns>
vector<vector<double>> _calGaussianWeights(int radius, double variance)
{
	vector<vector<double>> result;
	int diameter = radius * 2 - 1;
	for (int iy = 0; iy < diameter; ++iy)
	{
		vector<double> weights;
		for (int ix = 0; ix < diameter; ++ix)
		{
			int x = abs(ix + 1 - radius);
			int y = abs(iy + 1 - radius);
			double w = (1 / (variance * sqrt(2 * PI))) * exp(-1 * (pow(x, 2) + pow(y, 2)) / (2 * pow(variance, 2)));
			weights.push_back(w);
		}
		result.push_back(weights);
	}
	return result;
}

int _tmain(int argc, _TCHAR* argv[])
{
	string radius = "";
	string variance = "";
	int r;
	double v;
	//获取输入
	while (!_getInput(radius, variance, r, v));
	//清除输入
	system("cls");
	//计算权重
	vector<vector<double>> weights = _calGaussianWeights(r, v);
	//展示结果
	cout << "公式结果:" << endl;
	_displayResult(weights, false);
	cout << "权重结果:" << endl;
	_displayResult(weights, true);
	//防止直接退出
	_pause();
	_pause();
	return 0;
}


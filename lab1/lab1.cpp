#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

enum Operations
{
    vv_sum = '+',
    vv_subtr = '-',
    vv_scMult = '*'
};

struct CalcProblemParams
{
    vector<string> filePath;
    Operations op;
};

vector<double> ReadVectorFromFile(const string& filePath)
{
    vector<double> vec;
    ifstream file(filePath);
    if (!file.is_open())
    {
        cout << "Ошибка чтения файла " << filePath << endl;
        return vec;
    }

    double value;
    while (file >> value)
    {
        vec.push_back(value);
    }

    file.close();
    return vec;
}

void WriteVectorToFile(const vector<double>& vec, const string& filePath)
{
    ofstream file(filePath);
    if (!file.is_open())
    {
        cout << "Ошибка записи файла " << filePath << endl;
        return;
    }

    for (size_t i = 0; i < vec.size(); ++i)
    {
        file << vec[i];
        if (i != vec.size() - 1)
        {
            file << " ";
        }
    }

    file.close();
}

vector<double> Calc_vv_sum(const vector<double>& v1, const vector<double>& v2)
{
    vector<double> vres;
    if (v1.size() != v2.size())
    {
        cout << "Векторы имеют разную длину" << endl;
        return vres;
    }

    for (size_t i = 0; i < v1.size(); ++i)
    {
        vres.push_back(v1[i] + v2[i]);
    }
    return vres;
}

vector<double> Calc_vv_sub(const vector<double>& v1, const vector<double>& v2)
{
    vector<double> vres;
    if (v1.size() != v2.size())
    {
        cout << "Векторы имеют разную длину" << endl;
        return vres;
    }

    for (size_t i = 0; i < v1.size(); ++i)
    {
        vres.push_back(v1[i] - v2[i]);
    }
    return vres;
}

vector<double> Calc_vv_Mul(const vector<double>& v1, const vector<double>& v2)
{
    vector<double> vres;
    if (v1.size() != v2.size())
    {
        cout << "Векторы имеют разную длину" << endl;
        return vres;
    }

    for (size_t i = 0; i < v1.size(); ++i)
    {
        vres.push_back(v1[i] * v2[i]);
    }
    return vres;
}

int main(int argc, char* argv[])
{

    setlocale(LC_ALL, "Ru");

    //for (int i = 0; i < argc; i++)
    //{
    //	cout << argv[i]<<" ";
    //}

    if (argc != 4)
    {
        cout << "Параметры заданы неправильно, Пример: vec1.txt vec2.txt *" << endl;
        return 0;
    }

    CalcProblemParams params;
    params.filePath.push_back(argv[1]);
    params.filePath.push_back(argv[2]);

    char operation = argv[3][0];
    if (operation == '+')
    {
        params.op = vv_sum;
    }
    else if (operation == '-')
    {
        params.op = vv_subtr;
    }
    else if (operation == '*')
    {
        params.op = vv_scMult;
    }
    else
    {
        cout << "Такой операции нет, используйте: +, -, *." << endl;
        return 0;
    }

    vector<double> vec1 = ReadVectorFromFile(params.filePath[0]);
    vector<double> vec2 = ReadVectorFromFile(params.filePath[1]);

    if (vec1.empty() || vec2.empty())
    {
        cout << "Проверьте заполнение файлов векторов" << endl;
        return 0;
    }

    vector<double> result;
    switch (params.op)
    {
    case vv_sum:
        result = Calc_vv_sum(vec1, vec2);
        break;
    case vv_subtr:
        result = Calc_vv_sub(vec1, vec2);
        break;
    case vv_scMult:
        result = Calc_vv_Mul(vec1, vec2);
        break;
    default:
        cerr << "Неправильная операция" << endl;
        return 0;
    }

    if (!result.empty())
    {
        WriteVectorToFile(result, "result.txt");
        cout << "Результат записан в файл result.txt" << endl;
    }

    return 0;
}

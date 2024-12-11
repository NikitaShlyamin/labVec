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


void Calc()
{

}

void Export()
{

}


vector<double> Calc_vv_sum()
{
	vector<double> v1 = { 1,2,3,4,5 };
	vector<double> v2 = { 1,2,3,4,5 };
	vector<double> vres;

	if (v1.size() != v2.size())
	{
		cout << "Вектора разной длины";
	}
	else
	{
		for (int i = 0; i < v1.size(); i++)
		{
			vres.push_back(v1[i] + v2[i]);
		}
	}
	return vres;
}
vector<double> Calc_vv_sub()
{
	vector<double> v1;
	vector<double> v2;
	vector<double> vres;

	if (v1.size() != v2.size())
	{
		cout << "Вектора разной длины";
	}
	else
	{
		for (int i = 0; i < v1.size(); i++)
		{
			vres.push_back(v1[i] - v2[i]);
		}
	}

	return vres;
}
vector<double> Calc_vv_Mul()
{
	vector<double> v1 = { 1,2,3,4,5 };
	vector<double> v2 = { 1,2,3,4,5 };
	vector<double> vres;

	if (v1.size() != v2.size())
	{
		cout << "Вектора разной длины";
	}
	else
	{
		for (int i = 0; i < v1.size(); i++)
		{
			vres.push_back(v1[i] * v2[i]);
		}
	}
	return vres;
}

int main(int argc, char* argv[])
{
	//for (int i = 1; i < argc; i++)
	//{
	//	cout << argv[i];
	//}


	CalcProblemParams params;
	params.filePath.push_back(argv[1]);
	params.filePath.push_back(argv[2]);
	params.op;
	cout << params.filePath[0];

	//ofstream out;       
	//out.open("hello.txt");      
	//if (out.is_open())
	//{
	//	out << "Hello World!" << endl;
	//}
	//out.close();
	//cout << "File has been written" << endl;
	//string line;

	//ifstream in("vec1.txt"); 
	//if (in.is_open())
	//{
	//	while (getline(in, line))
	//	{
	//		cout << line << endl;
	//	}
	//}
	//in.close();     // закрываем файл

	//cout << line;
	//Init();	
	//Calc();
	//Export();

	//vector<double> result = Calc_vv_Mul();
	//for (int i = 0; i < result.size(); i++)
	//{
	//	cout << result[i] << " ";
	//}
}


/*

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

// Перечисление доступных операций
enum Operations {
    vv_sum,
    vv_subtr,
    vv_scMult
};

// Структура для хранения параметров задачи
struct CalcProblemParams {
    std::vector<std::string> filePath; // Ожидается size() == 2
    Operations op;
};

// Функция для преобразования строки в перечисление Operations
bool parseOperation(const std::string& opStr, Operations& op) {
    if (opStr == "Sum") {
        op = vv_sum;
    }
    else if (opStr == "Subtr") {
        op = vv_subtr;
    }
    else if (opStr == "ScalarMult" || opStr == "ScalarMult") { // Поддержка разных регистров
        op = vv_scMult;
    }
    else {
        return false;
    }
    return true;
}

// Функция для парсинга аргументов командной строки
bool parseArguments(int argc, char* argv[], CalcProblemParams& params) {
    if (argc != 7) {
        std::cerr << "Неверное количество аргументов.\n";
        return false;
    }

    for(int i =1; i < argc; i+=2){
        std::string flag = argv[i];
        std::string value = argv[i+1];
        if(flag == "-fp1"){
            if(params.filePath.size() <2)
                params.filePath.resize(2);
            params.filePath[0] = value;
        }
        else if(flag == "-fp2"){
            if(params.filePath.size() <2)
                params.filePath.resize(2);
            params.filePath[1] = value;
        }
        else if(flag == "-op"){
            if(!parseOperation(value, params.op)){
                std::cerr << "Неизвестная операция: " << value << "\n";
                return false;
            }
        }
        else{
            std::cerr << "Неизвестный флаг: " << flag << "\n";
            return false;
        }
    }

    // Проверка, что оба пути к файлам заданы
    if(params.filePath.size() <2 || params.filePath[0].empty() || params.filePath[1].empty()){
        std::cerr << "Не заданы пути к обоим файлам.\n";
        return false;
    }

    return true;
}

// Функция для чтения вектора из файла
bool readVectorFromFile(const std::string& filePath, std::vector<int>& vec) {
    std::ifstream infile(filePath);
    if(!infile.is_open()){
        std::cerr << "Не удалось открыть файл: " << filePath << "\n";
        return false;
    }

    std::string line;

    // Чтение первой строки и проверка
    if(!std::getline(infile, line)){
        std::cerr << "Ошибка чтения первой строки из файла: " << filePath << "\n";
        return false;
    }
    if(line != "vector"){
        std::cerr << "Неверный формат файла (первая строка должна быть 'vector'): " << filePath << "\n";
        return false;
    }

    // Чтение второй строки - длина вектора
    if(!std::getline(infile, line)){
        std::cerr << "Ошибка чтения длины вектора из файла: " << filePath << "\n";
        return false;
    }
    int length;
    try{
        length = std::stoi(line);
    }
    catch(...){
        std::cerr << "Неверный формат длины вектора в файле: " << filePath << "\n";
        return false;
    }

    // Чтение третьей строки - элементы вектора
    if(!std::getline(infile, line)){
        std::cerr << "Ошибка чтения элементов вектора из файла: " << filePath << "\n";
        return false;
    }
    std::istringstream iss(line);
    int num;
    std::vector<int> temp;
    while(iss >> num){
        temp.push_back(num);
    }

    if(temp.size() != static_cast<size_t>(length)){
        std::cerr << "Количество элементов не совпадает с указанной длиной в файле: " << filePath << "\n";
        return false;
    }

    vec = temp;
    return true;
}

// Функции операций
std::vector<int> addVectors(const std::vector<int>& a, const std::vector<int>& b){
    std::vector<int> result;
    size_t n = a.size();
    result.reserve(n);
    for(size_t i=0; i<n; ++i){
        result.push_back(a[i] + b[i]);
    }
    return result;
}

std::vector<int> subtractVectors(const std::vector<int>& a, const std::vector<int>& b){
    std::vector<int> result;
    size_t n = a.size();
    result.reserve(n);
    for(size_t i=0; i<n; ++i){
        result.push_back(a[i] - b[i]);
    }
    return result;
}

std::vector<int> scalarMultiplyVectors(const std::vector<int>& a, const std::vector<int>& b){
    std::vector<int> result;
    size_t n = a.size();
    result.reserve(n);
    for(size_t i=0; i<n; ++i){
        result.push_back(a[i] * b[i]);
    }
    return result;
}

// Функция для записи вектора в файл
bool writeVectorToFile(const std::string& filePath, const std::vector<int>& vec){
    std::ofstream outfile(filePath);
    if(!outfile.is_open()){
        std::cerr << "Не удалось открыть файл для записи: " << filePath << "\n";
        return false;
    }

    outfile << "vector\n";
    outfile << vec.size() << "\n";
    for(size_t i=0; i < vec.size(); ++i){
        outfile << vec[i];
        if(i != vec.size()-1)
            outfile << " ";
    }
    outfile << "\n";
    return true;
}

// Главная функция
int main(int argc, char* argv[]){
    CalcProblemParams params;
    if(!parseArguments(argc, argv, params)){
        std::cerr << "Использование: " << argv[0] << " -fp1 <file1> -fp2 <file2> -op <Operation>\n";
        std::cerr << "Доступные операции: Sum, Subtr, ScalarMult\n";
        return 1;
    }

    std::vector<int> vec1, vec2;
    if(!readVectorFromFile(params.filePath[0], vec1)){
        return 1;
    }
    if(!readVectorFromFile(params.filePath[1], vec2)){
        return 1;
    }

    if(vec1.size() != vec2.size()){
        std::cerr << "Векторы имеют разную длину.\n";
        return 1;
    }

    std::vector<int> result;
    std::string operationName;
    switch(params.op){
        case vv_sum:
            result = addVectors(vec1, vec2);
            operationName = "Sum";
            break;
        case vv_subtr:
            result = subtractVectors(vec1, vec2);
            operationName = "Subtr";
            break;
        case vv_scMult:
            result = scalarMultiplyVectors(vec1, vec2);
            operationName = "ScalarMult";
            break;
        default:
            std::cerr << "Неизвестная операция.\n";
            return 1;
    }

    // Формирование имени выходного файла
    std::string outputFile = "result_" + operationName + ".txt";

    if(!writeVectorToFile(outputFile, result)){
        return 1;
    }

    std::cout << "Результат записан в файл: " << outputFile << "\n";
    return 0;
}

*/
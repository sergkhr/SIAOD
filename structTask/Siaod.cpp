// Siaod.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>

using namespace std;

static vector<string> disciplines = { "math", "science", "programming", "history" };

struct Exam_record
{
    int stud_id;
    int exam_id;
    int exam_score;
    int activity_score;
    int exam_mark;
};

int main()
{
    vector<Exam_record> records;
    
    return 0;
}


int score_to_mark(int summary_score)
{
    int mark;
    if (summary_score <= 16) mark = 2;
    else if (summary_score <= 45) mark = 3;
    else if (summary_score <= 60) mark = 4;
    else mark = 5;
    return mark;
}


void insert_record(vector<Exam_record> records, int stud_id, int exam_id, int exam_score, int activity_score) 
{
    Exam_record newRecord = {stud_id, exam_id, exam_score, activity_score, score_to_mark(exam_score + activity_score)};
    bool flag = true; // the records is not a dublicate
    for (int i = 0; i < records.size(); i++)
    {
        if (records[i].stud_id == newRecord.stud_id && records[i].exam_id == newRecord.exam_id) //existing record will be changed
        {
            records[i].exam_score = exam_score;
            records[i].activity_score = activity_score; 
            records[i].exam_mark = score_to_mark(exam_score + activity_score);
            flag = false;
            break;
        }
    }
    if (flag) records.push_back(newRecord);
}
void insert_record(vector<Exam_record> records) // input with a keyboard
{
    int stud_id, exam_id, exam_score, activity_score;
    cout << "insert student's id" << endl;
    cin >> stud_id;
    cout << "insert exam's id: ";
    for (int i = 0; i < disciplines.size(); i++) cout << disciplines[i] << " - " << i << ", ";
    cout << endl;
    cin >> exam_id;
    cout << "insert score for the exam" << endl;
    cin >> exam_score;
    cout << "insert score for the activity" << endl;
    cin >> activity_score;
    insert_record(records, stud_id, exam_id, exam_score, activity_score);
}


void change_exam_score(vector<Exam_record> records)
{
    int stud_id, exam_id, exam_score;
    cout << "insert student's id" << endl;
    cin >> stud_id;
    cout << "insert exam's id: ";
    for (int i = 0; i < disciplines.size(); i++) cout << disciplines[i] << " - " << i << ", ";
    cout << endl;
    cin >> exam_id;
    cout << "insert new exam's score" << endl;
    cin >> exam_score;
    bool flag = true; // the records does not exist
    for (int i = 0; i < records.size(); i++)
    {
        if (records[i].stud_id == stud_id && records[i].exam_id == exam_id) //existing record will be changed
        {
            records[i].exam_score = exam_score;
            records[i].exam_mark = score_to_mark(exam_score + records[i].activity_score);
            flag = false;
            break;
        }
    }
    if (flag) cout << "error: no existing record found" << endl;
}


void print_records(vector<Exam_record> records)
{
    sort(records.begin(), records.end(), []()) //do it with lambda  stud_id1 <  stud_id2
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.

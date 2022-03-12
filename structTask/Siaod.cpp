// Siaod.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <algorithm>

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

int score_to_mark(int summary_score);

void insert_record(vector<Exam_record>& records, int stud_id, int exam_id, int exam_score, int activity_score);
void insert_record(vector<Exam_record>& records);
void change_exam_score(vector<Exam_record>& records);
void print_records(vector<Exam_record>& records);
void print_records(vector<Exam_record>& records, int stud_id);
void print_records(vector<Exam_record>& records, int exam_id);
void print_records(vector<Exam_record>& records,int stud_id, int exam_id);


int main()
{
    vector<Exam_record> records;
    insert_record(records, 1, 0, 43, 20);
    insert_record(records, 1, 1, 39, 18);
    insert_record(records, 2, 0, 18, 3);
    insert_record(records, 2, 1, 43, 20);
    insert_record(records, 2, 2, 22, 7);
    //change_exam_score(records);
    //insert_record(records);
    print_records(records);
    cout << endl;
    print_records(records, 2);
    
    cout << "done" << endl;
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


void insert_record(vector<Exam_record>& records, int stud_id, int exam_id, int exam_score, int activity_score) 
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
void insert_record(vector<Exam_record>& records) // input with a keyboard
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


void change_exam_score(vector<Exam_record>& records)
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


void print_records(vector<Exam_record>& records)//printing all
{
    sort(records.begin(), records.end(), [](Exam_record a, Exam_record b){
        return (a.stud_id <= b.stud_id);
    });
    
    for(int i = 0; i < records.size(); i++)
    {
        cout << "student: " << records[i].stud_id << ", discipline: " << disciplines[records[i].exam_id] << ", exam score: "
        << records[i].exam_score << ", activity_score: " << records[i].activity_score << ", mark: " << records[i].exam_mark << endl;
    }
}
void print_records(vector<Exam_record>& records, int stud_id) //printing all for one student
{
    sort(records.begin(), records.end(), [](Exam_record a, Exam_record b){
        return (a.stud_id <= b.stud_id);
    });

    for(int i = 0; i < records.size(); i++)
    {
        if(records[i].stud_id == stud_id) cout << "student: " << records[i].stud_id << ", discipline: " << disciplines[records[i].exam_id] 
        << ", exam score: " << records[i].exam_score << ", activity_score: " << records[i].activity_score
        << ", mark: " << records[i].exam_mark << endl;
    }
}
void print_records(vector<Exam_record>& records,int stud_id, int exam_id) //printing one exam for one student
{
    sort(records.begin(), records.end(), [](Exam_record a, Exam_record b){
        return (a.stud_id <= b.stud_id);
    });

    for(int i = 0; i < records.size(); i++)
    {
        if(records[i].exam_id == exam_id && records[i].stud_id == stud_id) cout << "student: " << records[i].stud_id 
        << ", discipline: " << disciplines[records[i].exam_id] << ", exam score: "
        << records[i].exam_score << ", activity_score: " << records[i].activity_score << ", mark: " << records[i].exam_mark << endl;
    }
}

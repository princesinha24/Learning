#include<iostream>
#include<string>
#include<vector>
using namespace std;


class Student;  // Forward declaration
// create a abstract student builder class
class StudentBuilder {
    public:
        string name, email;
        int rollNo,age;
        vector<string>subjects;
        StudentBuilder* setName(string name) {
            this->name = name;
            return this;
        }
        StudentBuilder* setEmail(string email) {
            this->email = email;
            return this;
        }
        StudentBuilder* setRollNo(int rollNo) {
            this->rollNo = rollNo;
            return this;
        }
        StudentBuilder* setAge(int age) {
            this->age = age;
            return this;
        }
        StudentBuilder* addSubject(string sub){
            this->subjects.push_back(sub);
            return this;
        }
        Student* build();

        ~StudentBuilder() {
            // Destructor to clean up resources if needed
        }
};

class Student{
    string name, email;
    int rollNo,age;
    vector<string>subjects;
    public:
        Student(StudentBuilder* builder) {
            this->name = builder->name;
            this->email = builder->email;
            this->rollNo = builder->rollNo;
            this->age = builder->age;
            this->subjects = builder->subjects;
        }
        void display() {
            cout << "Name: " << name << endl;
            cout << "Email: " << email << endl;
            cout << "Roll No: " << rollNo << endl;
            cout << "Age: " << age << endl;
            cout << "Subjects: ";
            for (const auto& subject : subjects) {
                cout << subject << " ";
            }
            cout << endl;
        }
};

Student* StudentBuilder::build() {
    return new Student(this);
}

int main(){
    Student* student = (new StudentBuilder())
    ->setName("John Doe")
    ->setRollNo(12345)
    ->setAge(20)
    ->addSubject("Mathematics")
    ->build();
    student->display();
    delete student; // Clean up memory

}
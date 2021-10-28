#include <iostream>
#include <fstream>
#include <string>

using namespace std;

template<class T>
class Llist;

template<class T>
class Node;

class Person;

template<class F>
void open_file(F& file, const string init_list);

template<class T>
void import_file(Llist<T>& our_list, ifstream& input_file);

//////////////////// Person class
class Person {
private:
    string name;
    int age;
    double height;

protected:

public:
    //passing nothing
    Person():name(""),age(0),height(0.0){}
    ~Person(){}

    //pass all parameters
    Person(string init_name,int init_age, double init_height):name(init_name), age(init_age), height(init_height){}

    //getters
    string get_name(){return name;}
    int get_age(){return age;}
    double get_height(){return height;}


    //helper function
    void print(){cout << name << " " << age << " " << height;}

};

///////////////////// Node class

template<class T>
class Node{

private:
    Node* previous;
    Node* next;

    T data; //in this case it is Person*
public:
     Node(Node* init_previous, Node* init_next, T init_data):previous(init_previous),next(init_next),data(init_data){}
    ~Node(){cout << "Delete Node Containing " << data->get_name() << endl; previous= nullptr; next=nullptr; delete data;}

    //getters
    Node* get_previous(){return previous;}
    Node* get_next(){return next;}
    T get_data(){return data;}


    //setters

    void set_previous(Node* set_previous){previous = set_previous;}
    void set_next(Node* set_next){next = set_next;}
    void set_data(T set_data){data=set_data;}

};

///////////////////// Linked List

template< class T>
class Llist{

private:
    Node<T>* front; //beginning of list (head)
    Node<T>* back; //end of list

public:
    Llist():front(nullptr),back(nullptr){}
    ~Llist(){clear(); front=nullptr; back=nullptr;}

    //to implement
    Llist(const Llist<T>&rhs); //copy constructor
    Llist<T>& operator=(const Llist<T>& rhs);


    void clear();

    void push_front(const T new_node);

    bool is_empty() const {return front==nullptr;}

    //getters
    Node<T>* get_front() {return front;}
    Node<T>* get_back() {return back;}

    //helper functions
    void print_list_forward();

};


int main() {
    // list of people
    // put them in a linked list
    // people is a type (object)
    // perhaps a Person class, for person objects
    // linked list contains nodes

    // a node in a linked list will contain data
    // we do not know what that data is, but in this case it's a Person object

    Llist<Person*> people;

    Person* jim = new Person("Jim",14, 194);
    Person* cindy = new Person("Cindy", 24, 172);

    cout << cindy->get_name() << " " << cindy->get_age() << " " << cindy->get_height() << endl;
    cout << endl;

    people.push_front(jim);
    people.push_front(cindy);

    people.print_list_forward();
    cout << endl;

    cout << "In main" << endl;
    people.clear();
    cout << endl;

    people.print_list_forward();
    cout << endl;

    //Import Employee File
    ifstream input_file;
    open_file<ifstream>(input_file,"people.txt");
    import_file(people, input_file);
    input_file.close();

    people.print_list_forward();
    cout << endl;

    jim = new Person("Jim",14, 194);
    cindy = new Person("Cindy", 24, 172);

    people.push_front(jim);
    people.push_front(cindy);

    people.print_list_forward();
    cout << endl;

    cout << "Program Ended"  << endl;
    return 0;
}

//file open verification
template<class F>
void open_file(F& file, const string init_list){
    string filename;
    filename = init_list;

    file.open(filename);

    //Todo: counter, exit after 3 tries
    while(!file){
        cout << "Error! Couldn't open file!" << endl;
        cout << "Re-Enter Filename: ";

        cin >> filename;
        file.clear();
        file.open(filename);
    }
}

//file import
template<class T>
void import_file(Llist<T>& our_list, ifstream& input_file){
    //let's just make this import specifically for Person objects

    Person* temp;

    string name;
    int age;
    double height;

    temp = nullptr;
    while(input_file >> name >> age >> height){

        temp = new Person(name,age,height);
        our_list.push_front(temp);

    }

}

template<class T> //T is Person*
void Llist<T>::push_front(const T new_person){
    if(front == nullptr){
        Node<T>* new_node = new Node<T>(nullptr,nullptr,new_person);

        front = new_node;
        back = new_node;

        return;
    } else{
        Node<T>* new_node = new Node<T>(nullptr,nullptr,new_person);

        front->set_previous(new_node);
        new_node->set_next(front);

        front = new_node;

    }


}

template<class T>
void Llist<T>::print_list_forward(){
    if(front==nullptr){
        cout << "EMPTY LIST!" << endl;
    } else{
        Node<T>* here = front; //a pointer to a node in the list

        while(here!=nullptr){
            here->get_data()->print();
            cout << endl;

            here = here->get_next();

        }


    }

}

template<class T>
void Llist<T>::clear(){
    Node<T>* here;
    Node<T>* temp;

    temp = front;

    while(!is_empty()){
        here = temp;
        temp = front->get_next();
        delete here;
        front = temp;


    }


}
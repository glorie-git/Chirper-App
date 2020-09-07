//  chirper.cpp
//  LA03
//  Created by Glorie on 2020-06-14.
//  This program allows user to post about their feelings and thoughts, view their feelings and thoughts and also see their friends' feelings and thoughts

#include <stdio.h>
#include <iostream>
#include "chirper.h"

using namespace std;

// Precondition: head is initialized to nullptr
// Postcondition: returns true if chirps exist, false if otherwise
bool Chirp::isEmpty(){
    if (head == nullptr && feet == nullptr) {
        return true ;
    }
    else { return false ;}
}

// Precondition: str is of length 180
// Postcondition: add chirp to timeline feed
void Chirp::add_chirp_post(string str){
    if (str.length() <= 180){
        // if this is the first chirp then
        // make sure feet->previous is nullptr
        if(isEmpty() && str.length() <= 180){
            head = new post;
            feet = new post;
            feet->message = str;
            feet->previous = nullptr;
            feet->next = nullptr;
            head = feet;
        }
        // link new chirp to latest chirp
        else{
            postPtr tmp = new post;
            tmp->message = str;
            tmp->next = nullptr;
            head->next = tmp ;
            tmp->previous = head;
            head = tmp;
            if (feet->next == nullptr){
                feet->next = head;
            }
        }
    }
    else
        cout << "this too long bruv" << endl << endl;
}

// Precondition: a intialized postPtr is passed
// Postcondition: changes value of reChirp to true
void reChirp(postPtr pt){
    pt->reChirp = true ;
}


// Precondtion: postPtr is intialized & there are atleast to chirps on timeline.
// Postcondition: returns the previous chirp pointed to by the variable passed to the function.
// interate to next chirp.
// iterate to previous chirp.
postPtr Chirp::previous_chirp(postPtr pt){
    return pt->previous ;
}


// Precondtion: postPtr is intialized & there are atleast to chirps on timeline
// Postcondition: returns the next chirp pointed to by the variable passed to the function
// interate to next chirp
postPtr Chirp::next_chirp(postPtr pt){
    pt = pt->next ;
    return pt ;
}

// Precondition: an initialized variable of type postPtr is passed as an argument
// Postcondition: adds heart to post and increases number of likes by one
// adds heart to post
// only allows one like from user
void Chirp::add_like(postPtr pt){
    if (!pt->like){
        pt->like = true;
        pt->num_likes++;
    }
}

// rechirps friends post and adds it to current users feed as a new post
void Chirp::reChirp(postPtr pt){
    if (!pt->reChirp){
        pt->reChirp = true ;
        add_chirp_post(pt->message);
    }
}

// Precondition: there's atleast one node that exists in the stack
// Postcondition: deletes the passed node from postPtr
void Chirp::delete_chirp(postPtr pt, postPtr& hd, postPtr& ft)
{
    postPtr tmp1;
    postPtr tmp2;
    // if the node is between two other nodes
    if (pt->next != nullptr && pt -> previous != nullptr){
        tmp1 = pt->previous ;
        tmp2 = pt->next ;
        tmp1->next = tmp2;
        tmp2->previous = tmp1 ;
        delete pt ; //allows pt not to dangle
    }
    // if the chirp is the first chirp in the queue
    else if (pt == ft && pt->next != nullptr){
        ft = pt->next ;
        delete pt; //allows pt not to dangle
    }
    // if chirp is at the last chirp in queue
    else if (pt == ft && pt ->next == nullptr){
        delete pt; //allows pt not to dangle
        ft = nullptr;
        hd = nullptr;
    }
    else {  // if node is at the top of the queue
        tmp1 = pt->previous;
        tmp1->next = nullptr;
        hd = tmp1;
        delete pt; //allows pt not to dangle
    }
}

// Precondition: pt is a valid postPtr and the second passed parameter is is an integer
// Postcondition:
// function enables user to scroll chirps on their wall
void Chirp::scroll_my_posts(postPtr& pt, postPtr& hd)
{
    int count = 1;
    char choice = NULL;
    bool done = false;  // lets function know if user wants to exit the function and return to the funtion that called it
    postPtr tmp = pt ;
    
    // checks if the user has entered x or if user is 'done'
    // loops if both these conditions are not true
    while (!done && choice != 'x'){
        display_chirp(tmp, count) ;
        
        // user options/operations for the current chirp
        cout << "(p)revious, (n)ext\n(L)ike, (r)echirp, (d)elete or e(x)it: " ;
        
        // user input for operation
        cin >> choice ;
        cout << endl ;
        
        // iterates to previous chirp using previous_chirp only if there is a previous chirp to go to
        if (choice == 'p')
        {
            if (tmp->previous != nullptr){
                count-- ;
                tmp = previous_chirp(tmp) ;
            }
            else {
                while (!(choice == 'n' || choice == 'l' || choice == 'r' || choice == 'x' || choice == 'd')) {
                    cout << "(p)revious, (n)ext\n(L)ike, (r)etweet, (d)elete or e(x)it: " ;
                    cin >> choice ;
                    cout << endl;
                }
               // show = false;
                if (count > 1){
                    if (choice == 'n'){
                        count++ ;
                        tmp = next_chirp(tmp);
                    }
                }
            }
        }
        // iterates to the next node using the next_chirp function only if there is a next chirp to go to
        if (choice == 'n'){
            if (tmp->next != nullptr){
                count++;
                tmp = next_chirp(tmp);
            }
            else {
                while (!(choice == 'p' || choice == 'l' || choice == 'r' || choice == 'x' || choice == 'd')){
                    cout << "(p)revious, (n)ext\n(L)ike, (r)etweet, (d)elete or e(x)it: " ;
                    cin >> choice ;
                    cout << endl;
                }
                if (count > 1){
                    if (choice == 'p'){
                        count-- ;
                        tmp = previous_chirp(tmp);
                    }
                }
            }
        }
        // like post if user entered both lower and upper case L
        if (choice == 'l' || choice == 'L') { add_like(tmp);}
        
        // rechirp if user entered r
        if (choice == 'r'){
            if (this_a_friend){ reChirp(tmp); }
            else {
                cout << "**sorry,\n**can't rechirp your own chirps\n";
            }
        }
        if (choice == 'd'){
            delete_chirp(tmp, hd, pt);
            if (pt != nullptr){
                count = 1;
                tmp = pt;
            }
            else {
                cout << "nothing to see here\n\n";
                done = true;
            }
        }
        if (choice == 'x'){ done = true; }
    }
}

// Precondition: friends variable has already been set up
// Postcondition: user is able to scroll through friends posts
// uses scroll_my_post function
void Chirp::scroll_thru_friend_posts(){
    this_a_friend = true;
    if (friends->isEmpty()){
        cout << "nothing to see here"<< endl ;
        cout << endl ;
    }
    else { scroll_my_posts(friends->feet, friends->head); }
    this_a_friend = false;
}

// Precondition: variable has to be of type Chirp
// Postcondition: changes the current Chirp display naem to what ever is inputed
void Chirp::change_dn(){
    string name, disName ;
    cout << "Enter your new display name: " ;
    cin >> disName ;
    setDN(disName) ;
}

// deconstructor
// deletes head and feet
Chirp::~Chirp(){
    delete feet;
    delete head;
}


Chirp::Chirp(){
    head = nullptr;
    feet = nullptr;
    display_name = " ";
}

// Precondition: variable has to be of type Chirp
// Postcondition: displays menu choices
// user has to enter a numerical between 1 and 5 inclusive.
void Chirp::menu(){
    char choice = NULL;
    while (choice != '5' && choice != '5') {
        
        // display menu options
        cout << "Select an option: \n" ;
        cout << "1. Chirp\n" ;
        cout << "2. Scroll through your Chirps\n" ;
        cout << "3. Scroll through a friend's feed\n" ;
        cout << "4. Change your display name\n" ;
        cout << "5. Exit\n\n" ;
        
        // read user input
        cin >> choice;
        cin.ignore();
        
        // validate that the entered value is an integer
        if (isdigit(choice)) {
            int digit = choice - '0';
            
            // user choice the option to enter a new chirp
            if (digit == 1){
                string str;
                cout << "write your post here:\n";
                getline(cin, str) ;
                add_chirp_post(str) ;
                cout << endl;
            }
            
            // user entered option two, scroll through chirps
            else if (digit == 2){
                cout << getDN() << "\'s Posts:\n"; // displays users display name
                cout << endl ; // print blank line
                
                 if (isEmpty()){
                     cout << "nothing to see here"<< endl ;
                     cout << endl ;
                 }
                 else{ scroll_my_posts(feet,head); }
            }
            
            // user choice the option to scroll though their friend's post
            else if (digit == 3){
                cout << friends->display_name << "\'s Posts:\n"; // displays friend's display name
                cout << endl ; // print blank line
                
                if (friends->isEmpty()){
                    cout << "nothing to see here"<< endl ;
                    cout << endl;
                }
                else { scroll_thru_friend_posts() ;}
            }
            
            else if (digit == 4) { change_dn(); }
            
            else if (digit == 5) { return ; }
        }
        else { cout << "Let's try again\n" ; }
    }
}

// Returns the user's display name
// If the user name has not been set prompt user to enter one
std::string Chirp::getDN(){
    if (display_name == " "){
        string disName ;
        char choice = NULL;
        
        cout << "no name set yet, would you like to set one now? (y/n): ";
        cin >> choice;
        
        if(choice == 'y' || choice == 'Y'){
            cout << "Display Name: " ;
            cin.ignore();
            getline(cin, disName, '\n') ;
            setDN(disName) ; // set display name
            return display_name;
        }
        else
            return "\n";
    }
    else
        return display_name;
}

// Precondition: is intialized postPtr, int is a digit
// Postcondition: displays the chirp on the screen
// display's chirp
void Chirp::display_chirp(postPtr it, int i){
  int count = 0;
  cout <<" _______________________________________________________" << endl; //55x
  cout << "|"<< setw(25) << right << ">>>>> Post #" << i << " <<<<"<< setw(24) << "|" << endl;
  cout << "| ";
  for(int j = 0; j < it->message.length(); j++){
     cout << it->message[j];
     count++;
     if((count > 45 && it->message[j] == ' ') || it->message[j+1] == '\0'){
       for(int k = 0; k < 53-count; k++) { cout << " "; }
       cout << "|" << endl;
       count = 0;
       if(it->message[j+1] == '\0') { break; }
         cout << "| ";
     }
  }

  cout << "\tLikes: ";
  if(it->like)
      cout << heart << it->num_likes << "\t";
  else
      cout << "\t";
  cout << "\tReChirps: ";
  if(it->reChirp)
      cout << arrow << endl;
  else
      cout << endl;
  cout <<" _______________________________________________________\n\n"; //55x
}


// and friend of user
// creates an account for friend and set's their user and display names and adds their chirps to their feed
void Chirp::add_friends(){
    cout << "adding your friend...." << endl ;
    
    ifstream file("friends_list.dat");
    string word;
    
    if(!file){
        cout << "Can not find the specified file\n";
        exit(1); //terminate with an error
    } //else opened just fine
    
    
    file >> word;
    
    friends = new Chirp;
    
    friends->setUser(word);
    file >> word;
    friends->setDN(word);
    for(std::string line; getline(file, line); ){
        if(line == "")
            continue;
        line.resize(MSG); //as a precaution
        friends->add_chirp_post(line);
    }
}

// sets the user's display name
void Chirp::setDN(string str){
    display_name = str ;
}

// Sets user's user name
void Chirp::setUser(string str){
    user = str ;
}

// Precondition: variable is of type Chirp
// Postcondition: sets up user name and display, adds friends and their chirps to their account
void Chirp::setup_account(){
    string name, disName ;
    cout << "Let's set up your Chirper account..." << endl ;
    cout << "User name: " ;
    
    getline(cin, name, '\n') ;
    setUser(name) ; // set user name
    
    cout << "Display Name: " ;
    getline(cin, disName, '\n') ;
    setDN(disName) ; // set display name
    
    // sets up friends' account and adds their chirps to their profile
    add_friends() ;
    cout << ">>Okay, you're ready to start chirpping";
    cout << endl ;
    cout << endl ;
}

// copy constructor
Chirp::Chirp(const Chirp &o){
    head = o.head;
    feet = o.feet;
}

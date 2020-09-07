//  chirper.h
//  This is the header file for the Chirper App
//  LA03
//  Created by Glorie on 2020-06-14.
//  header file for thr Chirper class

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>

#define MSG 180
const char heart[] = "\xe2\x99\xa5"; // heart icon
const char arrow[] = "\xe2\x86\x94"; // arrow icon

#ifndef chirper_h
#define chirper_h


#endif /* chirper_h */

struct post{
    std::string message; //must not exceed 180 characters bool like;
    int num_likes = 0;
    bool reChirp = false;
    bool like = false;
    post *previous;
    post *next;
};
typedef post* postPtr;

class Chirp{
private:
    std::string user;
    std::string display_name;
    postPtr head; // top of queue
    postPtr feet; // bottom of queue
    
    bool isEmpty(); // returns true if queue is empty, false if not
    postPtr previous_chirp(postPtr); // returns previous chirp, if any
    postPtr next_chirp(postPtr);    // returns next chirp, if any
    void display_chirp(postPtr, int); // display chirp of passed node
    void add_like(postPtr); // adds like to the current post
    void add_chirp_post(std::string); // adds chirp to queue
    void delete_chirp(postPtr, postPtr&, postPtr&); // deletes chirps
    
    bool this_a_friend = false; // lets the app know if user wants to view a friends feed or not
    void scroll_my_posts(postPtr&, postPtr&); // enables user to scroll through their post
    void scroll_thru_friend_posts(); // enables user to scroll through their friends feed
    void add_friends(); // adds friends to user profile
    void reChirp(postPtr);  // copies friends' chirp to user's feed
    void change_dn();   // changes user's display name
    
public:
    Chirp(); //constructor
    Chirp(const Chirp &o);//copy constructor
    Chirp *friends; //one friend
    ~Chirp(); //destructor
    void setup_account(); // sets up user account
    void menu();    // displays menu options
    void setUser(std::string); // set user's name
    std::string getUser();  // return user's name
    void setDN(std::string);    // set user's display name
    std::string getDN();    // return user's display name
};

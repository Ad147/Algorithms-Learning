// Exercise13.34.cpp
// Ad147
// Write the Message class as described in this section.

#include <iostream>
#include <set>
// class =======================================================================

class Folder;

class Message
{
    friend class Folder;
    friend void swap(Message &lhs, Message &rhs);

  public:
    // folders is implicitly initialized to the empty set
    explicit Message(const std::string &str = "") : contents(str) {}

    // copy control to manage pointers to this Message
    Message(const Message &);            // copy constructor
    Message &operator=(const Message &); // copy assignment
    ~Message();                          // destructor

    // add/remove this Message from the specified Folder's set of messages
    void save(Folder &);
    void remove(Folder &);

  private:
    std::string contents;       // actual message text
    std::set<Folder *> folders; // Folders that have this Message

    // utility functions used by copy constructor, assignment, and destructor
    // add this Message to the Folders that point to the parameter
    void add_to_Folders(const Message &);
    // remove this Message from every Folder in folders
    void remove_from_Folders();
};

// member functions ============================================================

void Message::save(Folder &f)
{
    folders.insert(&f); // add the given Folder to our list
    f.addMsg(this);     // add this Message to f's set
}

void Message::remove(Folder &f)
{
    folders.erase(&f); // take the given Folder to our list
    f.remMsg(this);    // remove this Message to f's set
}

// add this Message to Folders that point to m
void Message::add_to_Folders(const Message &m)
{
    for (auto f : m.folders) // for each Folder that holds m
        f->addMsg(this);     // add a pointers to this Message to that Folder
}

Message::Message(const Message &m) : contents(m.contents), folders(m.folders)
{
    add_to_Folders(m); // add this Message to the Folders that point to m
}

// remove this Message from the cooresponding Folders
void Message::remove_from_Folders()
{
    for (auto f : folders) // for each pointer in the folders
        f->remMsg(this);   // remove this Message from that Foler
}

Message::~Message()
{
    remove_from_Folders();
    // the compiler automatically invokes the string destructor to free contents and the set destructor to clean up the memory used by thos members
}

Message &Message::operator=(const Message &rhs)
{
    // handle self-assignment by removing pointers before inserting them
    remove_from_Folders();   // update existing Folders
    contents = rhs.contents; // copy message contents from rhs
    folders = rhs.folders;   // copy Folder pointers from rhs
    add_to_Folders(*this);    // add this Message to those Folders
    return *this;
}

void swap(Message &lhs, Message &rhs)
{
    using std::swap; // not strictly needed in this case, but good habit
    // remove pointers to each Message from their (original) respective Folders
    for (auto f : lhs.folders)
        f->remMsg(&lhs);
    for (auto f : rhs.folders)
        f->remMsg(&rhs);

    // swap the contents and Folder pointer sets
    swap(lhs.folders, rhs.folders);   // uses swap(set&, set&)
    swap(lhs.contents, rhs.contents); // swap(string&, string&)

    // add pointers to each Message to their (new) respective Folders
    for (auto f : lhs.folders)
        f->addMsg(&lhs);
    for (auto f : rhs.folders)
        f->addMsg(&rhs);
}

#include <iostream>
#include <exception>
#include <typeinfo>
using namespace std;

class GameEntry
{
public:
    GameEntry(const string &n = "", int s = 0);
    string getName() const;
    void setName(const string);
    int getScore() const;
    void setScore(const int);

private:
    string name;
    int score;
};
GameEntry::GameEntry(const string &n, int s) : name(n), score(s)
{
}
string GameEntry::getName() const { return name; }
void GameEntry::setName(const string newName) { name = newName; }
int GameEntry::getScore() const { return score; }
void GameEntry::setScore(const int newScore) { score = newScore; }
class Scores
{
public:
    Scores(int maxEnt = 10);
    ~Scores();
    void add(const GameEntry &e);
    GameEntry remove(int i);
    int search(string);
    void printAllScores();

private:
    int maxEntries;     // maximum number of entries
    int numEntries;     // actual number of entries
    GameEntry *entries; // array of game entries
    bool isEqual(string, string);
    void swap(int i, int j);
};
Scores::Scores(int maxEnt)
{                                        // constructor
    maxEntries = maxEnt;                 // save the max size
    entries = new GameEntry[maxEntries]; // allocate array storage
    numEntries = 0;                      // initially no elements
}
Scores::~Scores()
{
    delete[] entries;
}
void Scores::add(const GameEntry &e)
{
    string playerName = e.getName();
    int playerScore = e.getScore();

    // first, check if this player already exists in the array or not
    int index = search(playerName);

    if (index != -1)
    {
        // this player already exists in the array

        // check if this player's previous score is greater than
        // this new entry or not
        if (entries[index].getScore() > playerScore){
            // if currently existing score is already greater
            // we simply return
            return;
        }
        
        else{
            
        // otherwise,
        // update the currently exisiting score
            entries[index].setScore(playerScore);
        }

        

        // we are not done here,
        // remember that we always need to keep entries[] sorted
        for (int i = index; i > 0; i--)
        {
            // compare the entry to the left

            // if this entry is not high enough to be swapped,
            // break out of the loop
            if (entries[i].getScore() <= entries[i - 1].getScore())
                break;

            // swap with the entry to the left
            int tempScore = entries[i].getScore();
            entries[i].setScore(entries[i-1].getScore());
            entries[i-1].setScore(tempScore);
        }
    }
    else
    {
        int newScore = e.getScore(); // score to add
        if (numEntries == maxEntries)
        { // the array is full
            if (newScore <= entries[maxEntries - 1].getScore())
                return; // not high enough - ignore
        }
        else
            numEntries++;       // if not full, one more entry
        int i = numEntries - 2; // start with the next to last
        while (i >= 0 && newScore > entries[i].getScore())
        {
            entries[i + 1] = entries[i]; // shift right if smaller
            i--;
        }
        entries[i + 1] = e; // put e in the empty spot
    }
}
GameEntry Scores::remove(int i)
{
    if ((i < 0) || (i >= numEntries)) // invalid index
        throw("IndexOutOfBounds - Invalid index");
    GameEntry e = entries[i]; // save the removed object
    for (int j = i + 1; j < numEntries; j++)
        entries[j - 1] = entries[j]; // shift entries left
    numEntries--;                    // one fewer entry
    return e;                        // return the removed object
}

// searches for the given player in the entries[] array
// return the index location of this player if present
// otherwise return -1.
int Scores ::search(string newPlayerName)
{
    for (int i = 0; i < numEntries; i++)
    {
        string currPlayerName = entries[i].getName();

        if (isEqual(newPlayerName, currPlayerName))
            return i;
    }
    return -1;
}

// checks whether two strings are equal or not
bool Scores ::isEqual(string a, string b)
{
    if (a.length() != b.length())
        return false;
    for (int i = 0; i < a.length(); i++)
        if (a[i] != b[i])
            return false;
    return true;
}

// swap the entry at given indices.
void Scores::swap(int i, int j)
{
    GameEntry t = entries[i];
    entries[i] = entries[j];
    entries[j] = t;
}

void Scores::printAllScores()
{
    for (int i = 0; i < numEntries; i++)
    {
        cout << entries[i].getName() << " : " << entries[i].getScore() << "\n";
    }
}
void showOptions()
{
    cout
        << "1:	Add Player\n"
        << "2:	Remove Player By Index\n"
        << "3:	Print Scores\n"
        << "4:	Exit\n";
}
int main()
{
    Scores scoresObj;
    int option;
    string playerName;
    int score;

    while (1)
    {
        showOptions();
        cin >> option;
        switch (option)
        {
        case 1:
            cout << "Enter Player Name and Score\n";
            cin >> playerName >> score;
            scoresObj.add(GameEntry(playerName, score));
            break;
        case 2:
            int index;
            cout << "Enter the index\n";
            cin >> index;
            scoresObj.remove(index);
            break;
        case 3:
            scoresObj.printAllScores();
            break;
        case 4:
            return EXIT_SUCCESS;
        }
    }
}
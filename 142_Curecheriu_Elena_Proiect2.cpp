#include <iostream>
#include <vector>

using namespace std;

//clasa abstracta/interfata

class IOInterface
{
public:
    virtual void citire(istream&) = 0;
    virtual void afisare(ostream&) const = 0;
};

class Song;
//clasa de baza / parinte

class Playlist : public IOInterface
{
protected:
    const int typeOfPlaylist = 0;
    string name;
    string creator;
    int nrSongs;
    vector <Song> songs;
    int duration;

public:
    //constructori
    Playlist();
    Playlist(string name, string creator, int nrSongs, vector <Song> songs, int duration);
    Playlist(const Playlist& obj);

    //operatorul egal
    Playlist& operator = (const Playlist& obj);

    //operatorii de citire si afisare
    friend istream& operator >> (istream& in, Playlist& obj);
    friend ostream& operator << (ostream& out, const Playlist& obj);

    //functiile de citire si afisare
    virtual void citire(istream& in);
    virtual void afisare(ostream& out) const;


    //getters and setters
    virtual string getName() const = 0;
//    {
//        return this->name;
//    }

    virtual string getCreator() const = 0;
//    {
//        return this->creator;
//    }

    virtual int getNrSongs() const = 0;
//    {
//        return this->nrSongs;
//    }

    virtual vector <Song> getSongs() const = 0;
//    {
//        return this->songs;
//    }

    virtual int getDuration() const = 0;
//    {
//        return this->duration;
//    }

    virtual void setName(string _name) = 0;
//    {
//        this->name = _name;
//    }

    virtual void setCreator(string _creator) = 0;
//    {
//        this->creator = _creator;
//    }

    virtual void setNrSongs(int _nrSongs) = 0;
//    {
//        this->nrSongs = _nrSongs;
//    }

    virtual void setSongs(vector <Song> _songs) = 0;
//    {
//        this->songs = _songs;
//    }

    virtual void setDuration(int _duration) = 0;
//    {
//        this->duration = _duration;
//    }

//functionalitati

    virtual int numberOfListeners () = 0;
//    virtual void changeVisibility () = 0;
//    virtual void changeGenre () = 0;
//    virtual void addCollaborator () = 0;
//    virtual void removeCollaborator () = 0;
//

//destructor
    virtual ~Playlist() = default;

};

Playlist::Playlist()
{
    this->name = "unknown";
    this->creator = "unknown";
    this->nrSongs = 0;
    this->duration = 0;
}

Playlist::Playlist(string name, string creator, int nrSongs, vector <Song> songs, int duration): name(name), creator(creator), nrSongs(nrSongs), songs(songs), duration(duration)
{
}

Playlist::Playlist(const Playlist& obj)
{
    this->name = obj.name;
    this->creator = obj.creator;
    this->nrSongs = obj.nrSongs;
    this->songs = obj.songs;
    this->duration = obj.duration;
}

Playlist& Playlist::operator = (const Playlist& obj)
{
    if(this != &obj)
    {
        this->name = obj.name;
        this->creator = obj.creator;
        this->nrSongs = obj.nrSongs;
        this->songs = obj.songs;
        this->duration = obj.duration;
    }
    return *this;
}



istream& operator >> (istream& in, Playlist& obj)
{
    obj.citire(in);
    return in;
}

ostream& operator << (ostream& out, const Playlist& obj)
{
    obj.afisare(out);
    return out;
}

//clasa derivata 1 / copil 1

class GeneratedPlaylist : virtual public Playlist
{
protected:
    const int typeOfPlaylist = 1;
    string genre;
    bool isGeneratedByUserActivity; //daca playlistul a fost generat de gusturile utilizatorului sau nu
public:
    //constructori
    GeneratedPlaylist();
    GeneratedPlaylist(string name, string creator, int nrSongs, vector <Song> songs, int duration, string genre, bool isGeneratedByUserActivity);
    GeneratedPlaylist(const GeneratedPlaylist& obj);

    //operatorul egal
    GeneratedPlaylist& operator = (const GeneratedPlaylist& obj);

    //functiile de citire si afisare
    void citire(istream& in);
    void afisare(ostream& out) const;

    //getters and setters

    string getName() const
    {
        return this->name;
    }

    string getCreator() const
    {
        return this->creator;
    }

    int getNrSongs () const
    {
        return this->nrSongs;
    }

    vector <Song> getSongs() const
    {
        return this->songs;
    }

    int getDuration() const
    {
        return this->duration;
    }

    string getGenre() const
    {
        return this->genre;
    }

    bool getIsGeneratedByUserActivity() const
    {
        return this->isGeneratedByUserActivity;
    }

    void setName(string _name)
    {
        this->name = _name;
    }

    void setCreator(string _creator)
    {
        this->creator = _creator;
    }

    void setNrSongs(int _nrSongs)
    {
        this->nrSongs = _nrSongs;
    }

    void setSongs(vector <Song> _songs)
    {
        this->songs = _songs;
    }

    void setDuration(int _duration)
    {
        this->duration = _duration;
    }

    void setGenre(string _genre)
    {
        this->genre = _genre;
    }

    void setIsGeneratedByUserActivity(bool _isGeneratedByUserActivity)
    {
        this->isGeneratedByUserActivity = _isGeneratedByUserActivity;
    }

    //functionalitati

    int numberOfListeners();
    void changeGenre(string);

    GeneratedPlaylist operator + (GeneratedPlaylist &obj1) //modifica this
    {
        GeneratedPlaylist copy = *this;
        copy.genre = copy.genre + " " + obj1.genre;
        for (int i = 0; i < obj1.songs.size(); i++)
            copy.songs.push_back(obj1.songs[i]);
        copy.nrSongs += obj1.nrSongs;
        copy.name = copy.name + " modified";
        copy.duration += obj1.duration;
        return copy;
    }

    //destructor
    virtual ~GeneratedPlaylist() = default;
};

GeneratedPlaylist::GeneratedPlaylist()
{
    this->genre = "unknown";
    this->isGeneratedByUserActivity = false;
}

GeneratedPlaylist::GeneratedPlaylist(string name, string creator, int nrSongs, vector <Song> songs, int duration, string genre, bool isGeneratedByUserActivity): Playlist(name, creator, nrSongs, songs, duration), genre(genre), isGeneratedByUserActivity(isGeneratedByUserActivity)
{
}

GeneratedPlaylist::GeneratedPlaylist(const GeneratedPlaylist& obj)
{
    Playlist::operator = (obj);
    this->genre = obj.genre;
    this->isGeneratedByUserActivity = obj.isGeneratedByUserActivity;
}

GeneratedPlaylist& GeneratedPlaylist::operator = (const GeneratedPlaylist& obj)
{
    if(this != &obj)
    {
        Playlist::operator = (obj);
        this->genre = obj.genre;
        this->isGeneratedByUserActivity = obj.isGeneratedByUserActivity;
    }
    return *this;
}

void GeneratedPlaylist::citire(istream& in)
{
    Playlist::citire(in);
    in.get();
    cout << "Genre: ";
    getline(in, genre);
    cout << "Is the playlist generated by user activity?: ";
    in >> this->isGeneratedByUserActivity;
}

void GeneratedPlaylist::afisare(ostream& out) const
{
    Playlist::afisare(out);
    out << "Genre: " << this->genre << endl;
    out << "Is the playlist generated by user activity?: " ;
    if (this->isGeneratedByUserActivity)
        out << "Yes" << endl;
    else
        out << "No" << endl;
}

int GeneratedPlaylist :: numberOfListeners()
{
    return this->nrSongs * 1209 + 707;
}

void GeneratedPlaylist :: changeGenre(string newName)
{
    this->genre = newName + "- Generated Playlist";
}

//clasa derivata 2 / copil 2

class CreatedPlaylist : virtual public Playlist {
protected:
    const int typeOfPlaylist = 2;
    bool isPublic;
    bool isCollaborative;
    vector <string> collaborators;
public:
    //constructori
    CreatedPlaylist();
    CreatedPlaylist(string name, string creator, int nrSongs, vector <Song> songs, int duration, bool isPublic, bool isCollaborative, vector <string> collaborators);
    CreatedPlaylist(const CreatedPlaylist& obj);

    //operatorul egal
    CreatedPlaylist& operator = (const CreatedPlaylist& obj);

    //functiile de citire si afisare
    void citire(istream& in);
    void afisare(ostream& out) const;

    //getters and setters
    string getName() const
    {
        return this->name;
    }

    string getCreator() const
    {
        return this->creator;
    }

    int getNrSongs () const
    {
        return this->nrSongs;
    }

    vector <Song> getSongs() const
    {
        return this->songs;
    }

    int getDuration() const
    {
        return this->duration;
    }

    bool getIsPublic() const
    {
        return this->isPublic;
    }

    bool getIsCollaborative() const
    {
        return this->isCollaborative;
    }

    vector <string> getCollaborators() const
    {
        return this->collaborators;
    }

    void setName(string _name)
    {
        this->name = _name;
    }

    void setCreator(string _creator)
    {
        this->creator = _creator;
    }

    void setNrSongs(int _nrSongs)
    {
        this->nrSongs = _nrSongs;
    }

    void setSongs(vector <Song> _songs)
    {
        this->songs = _songs;
    }

    void setDuration(int _duration)
    {
        this->duration = _duration;
    }

    void setIsPublic(bool _isPublic)
    {
        this->isPublic = _isPublic;
    }

    void setIsCollaborative(bool _isCollaborative)
    {
        this->isCollaborative = _isCollaborative;
    }

    void setCollaborators(vector <string> _collaborators)
    {
        this->collaborators = _collaborators;
    }

    //functionalitati

    void changeVisibility(const string);
    int numberOfListeners();
    void addCollaborator(string);
    void removeCollaborator(string);

    CreatedPlaylist operator + (CreatedPlaylist &obj1) //modifica this
    {
        CreatedPlaylist copy = *this;
        for (int i = 0; i < obj1.songs.size(); i++)
            copy.songs.push_back(obj1.songs[i]);
        for (int i = 0; i < obj1.collaborators.size(); i++)
            copy.collaborators.push_back(obj1.collaborators[i]);
        copy.nrSongs += obj1.nrSongs;
        copy.name = copy.name + " modified";
        copy.duration += obj1.duration;
        return copy;
    }

    //destructor
    virtual ~CreatedPlaylist() = default;
};

CreatedPlaylist::CreatedPlaylist() : Playlist()
{
    this->isPublic = false;
    this->isCollaborative = false;
}

CreatedPlaylist::CreatedPlaylist(string name, string creator, int nrSongs, vector <Song> songs, int duration, bool isPublic, bool isCollaborative, vector <string> collaborators): Playlist(name, creator, nrSongs, songs, duration), isPublic(isPublic), isCollaborative(isCollaborative), collaborators(collaborators)
{
}

CreatedPlaylist::CreatedPlaylist(const CreatedPlaylist& obj)
{
    Playlist::operator = (obj);
    this->isPublic = obj.isPublic;
    this->isCollaborative = obj.isCollaborative;
    this->collaborators = obj.collaborators;
}

CreatedPlaylist& CreatedPlaylist::operator = (const CreatedPlaylist& obj)
{
    if(this != &obj)
    {
        Playlist::operator = (obj);
        this->isPublic = obj.isPublic;
        this->isCollaborative = obj.isCollaborative;
        this->collaborators = obj.collaborators;
    }
    return *this;
}

void CreatedPlaylist::citire(istream& in)
{
    Playlist::citire(in);
    cout << "Is the playlist public?: ";
    in >> this->isPublic;
    cout << "Is the playlist collaborative?: ";
    in >> this->isCollaborative;
    if(this->isCollaborative)
    {
        cout << "Number of collaborators: ";
        int nr;
        in >> nr;
        cout << "Collaborators: " << endl;
        for(int i = 0; i < nr; i++)
        {
            cout << i+1 << ". ";
            string s;
            in.get();
            getline(in, s);
            this->collaborators.push_back(s);
        }
    }
}

void CreatedPlaylist::afisare(ostream& out) const
{
    Playlist::afisare(out);
    out << "Is the playlist public?: " << (this->isPublic == 1 ? "Yes" : "No")<< endl;
    out << "Is the playlist collaborative?: " << (this->isCollaborative == 1 ? "Yes" : "No") << endl;
    if(this->isCollaborative)
    {
        out << "Number of collaborators: " << this->collaborators.size() << endl;
        out << "Collaborators: " << endl;
        for(int i = 0; i < this->collaborators.size(); i++)
        {
            out << i+1 << ". " << this->collaborators[i] << endl;
        }
    }
}

int CreatedPlaylist ::numberOfListeners() {
    return this->nrSongs * 323 + 90;
}

void CreatedPlaylist ::addCollaborator(string collaborator) {
    this->collaborators.push_back(collaborator);
}

void CreatedPlaylist ::removeCollaborator(string collaborator) {
    for (int i = 0; i < this->collaborators.size(); i++)
        if(this->collaborators[i] == collaborator)
            collaborators.erase(collaborators.begin() + i);

}

// clasa derivata 3 / nepot
class SpecialPlaylist : public GeneratedPlaylist, public CreatedPlaylist {
private:
    const int typeOfPlaylist = 3;
public:
    //constructori
    SpecialPlaylist();
    SpecialPlaylist(string name, string creator, int nrSongs, vector <Song> songs, int duration, string genre, bool isGeneratedByUserActivity, bool isPublic, bool isCollaborative, vector <string> collaborators);
    SpecialPlaylist(const SpecialPlaylist& obj);

    //operatorul egal
    SpecialPlaylist& operator = (const SpecialPlaylist& obj);

    //functiile de citire si afisare
    void citire(istream& in);
    void afisare(ostream& out) const;

    //getters + setters

    string getName() const
    {
        return this -> name;
    }

    string getCreator() const
    {
        return this->creator;
    }

    int getNrSongs () const
    {
        return this->nrSongs;
    }

    vector <Song> getSongs() const
    {
        return this->songs;
    }

    int getDuration() const
    {
        return this->duration;
    }

    int getTypeOfPlaylist() const
    {
        return this->typeOfPlaylist;
    }

    string getGenre() const
    {
        return this->genre;
    }

    bool getIsGeneratedByUserActivity() const
    {
        return this->isGeneratedByUserActivity;
    }

    bool getIsPublic() const
    {
        return this->isPublic;
    }

    bool getIsCollaborative() const
    {
        return this->isCollaborative;
    }

    vector <string> getCollaborators() const
    {
        return this->collaborators;
    }

    void setName(string _name)
    {
        this->name = _name;
    }

    void setCreator(string _creator)
    {
        this->creator = _creator;
    }

    void setNrSongs(int _nrSongs)
    {
        this->nrSongs = _nrSongs;
    }

    void setSongs(vector <Song> _songs)
    {
        this->songs = _songs;
    }

    void setDuration(int _duration)
    {
        this->duration = _duration;
    }

    void setGenre(string _genre)
    {
        this->genre = _genre;
    }

    void setIsGeneratedByUserActivity(bool _isGeneratedByUserActivity)
    {
        this->isGeneratedByUserActivity = _isGeneratedByUserActivity;
    }

    void setIsPublic(bool _isPublic)
    {
        this->isPublic = _isPublic;
    }

    void setIsCollaborative(bool _isCollaborative)
    {
        this->isCollaborative = _isCollaborative;
    }

    void setCollaborators(vector <string> _collaborators)
    {
        this->collaborators = _collaborators;
    }

    //functionalitati

    int numberOfListeners();
    void changeGenre(string);
    void addCollaborator(string);
    void removeCollaborator(string);

    SpecialPlaylist operator + (SpecialPlaylist &obj1) //modifica this
    {
        SpecialPlaylist copy = *this;
        copy.genre = copy.genre + " " + obj1.genre;
        for (int i = 0; i < obj1.songs.size(); i++)
            copy.songs.push_back(obj1.songs[i]);
        for (int i = 0; i < obj1.collaborators.size(); i++)
            copy.collaborators.push_back(obj1.collaborators[i]);
        copy.nrSongs += obj1.nrSongs;
        copy.name = copy.name + " modified";
        copy.duration += obj1.duration;
        return copy;
    }

    friend SpecialPlaylist operator + (const GeneratedPlaylist &obj1, const CreatedPlaylist &obj2);
    friend SpecialPlaylist operator + (const CreatedPlaylist &obj2, const GeneratedPlaylist &obj1);

    SpecialPlaylist operator + (const GeneratedPlaylist &obj) //combina this-ul cu obj
    {
        SpecialPlaylist copy = *this;
        vector <Song> temp1 = obj.getSongs();
        for (int i = 0; i < temp1.size(); i++)
            copy.songs.push_back(temp1[i]);
        copy.duration += obj.getDuration();
        copy.genre = copy.genre + " " + obj.getGenre();
        return copy;
    }

    SpecialPlaylist operator + (const CreatedPlaylist &obj) //combina this-ul cu obj
    {
        SpecialPlaylist copy = *this;
        vector <Song> temp1 = obj.getSongs();
        for (int i = 0; i < temp1.size(); i++)
            copy.songs.push_back(temp1[i]);
        copy.duration += obj.getDuration();
        vector <string> temp2 = obj.getCollaborators();
        for (int i = 0; i < temp2.size(); i++)
            copy.collaborators.push_back(temp2[i]);
        return copy;
    }
    //destructor
    virtual ~SpecialPlaylist() = default;
};

SpecialPlaylist::SpecialPlaylist() : Playlist(), GeneratedPlaylist(), CreatedPlaylist()
{
}

SpecialPlaylist::SpecialPlaylist(string name, string creator, int nrSongs, vector <Song> songs, int duration, string genre, bool isGeneratedByUserActivity, bool isPublic, bool isCollaborative, vector <string> collaborators): Playlist(name, creator, nrSongs, songs, duration), GeneratedPlaylist(name, creator, nrSongs, songs, duration, genre, isGeneratedByUserActivity), CreatedPlaylist(name, creator, nrSongs, songs, duration, isPublic, isCollaborative, collaborators)
{
}

SpecialPlaylist::SpecialPlaylist(const SpecialPlaylist& obj) : Playlist(obj), GeneratedPlaylist(obj), CreatedPlaylist(obj)
{
}

SpecialPlaylist& SpecialPlaylist::operator = (const SpecialPlaylist& obj)
{
    if(this != &obj)
    {
        GeneratedPlaylist::operator = (obj);
        this->isPublic = obj.isPublic;
        this->isCollaborative = obj.isCollaborative;
        this->collaborators = obj.collaborators;
    }
    return *this;
}

void SpecialPlaylist::citire(istream& in)
{
    GeneratedPlaylist::citire(in);
    cout << "Is the playlist public?: ";
    in >> this->isPublic;
    cout << "Is the playlist collaborative?: ";
    in >> this->isCollaborative;
    if(this->isCollaborative)
    {
        cout << "Number of collaborators: ";
        int n;
        in >> n;
        cout << "Collaborators: " << endl;
        for(int i = 1; i <= n; i++)
        {
            cout << i << ". ";
            string s;
            in.get();
            getline(in, s);
            this->collaborators.push_back(s);
        }
    }
}

void SpecialPlaylist::afisare(ostream& out) const
{
    GeneratedPlaylist::afisare(out);
    out << "Is the playlist public?: " << (this->isPublic == 1 ? "Yes" : "No") << endl;
    out << "Is the playlist collaborative?: " << (this->isCollaborative == 1 ? "Yes" : "No") << endl;
    if(this->isCollaborative)
    {
        out << "Number of collaborators: " << this->collaborators.size() << endl;
        out << "Collaborators: " << endl;
        for(int i = 0; i < this->collaborators.size(); i++)
        {
            out << i+1 << ". " << this->collaborators[i] << endl;
        }
    }
}

int SpecialPlaylist::numberOfListeners() {
    int copy = GeneratedPlaylist :: numberOfListeners();
    return copy;
}

void SpecialPlaylist :: changeGenre(string newName)
{
    this->genre = newName + "- Special Playlist";
}

void SpecialPlaylist ::addCollaborator(string collaborator) {
    this->collaborators.push_back(collaborator);
}

void SpecialPlaylist :: removeCollaborator(string collaborator) {
    for (int i = 0; i < this->collaborators.size(); i++)
        if(this->collaborators[i] == collaborator)
            collaborators.erase(collaborators.begin() + i);

}

//class Song;
class Song
{
private:
    string songTitle;
    string songArtistName;
    string songAlbum;
    char firstLetter;
    int songDuration;
    bool isLiked; //in liked songs playlist

public:
    Song(); //constructor fara parametri

    //constructor cu toti parametrii
    Song(string songTitle, string songArtistName, string songAlbum, char firstLetter, int songDuration, bool isLiked); //constructor cu toti parametrii

    //constructor cu un parametru
    Song(string x)
    {
        this -> songTitle = x;
    }

    //constructor cu mai multi parametri
    Song(string x, bool fav)
    {
        this -> songTitle = x;
        this -> isLiked = fav;
    }

    void Print() //afisare
    {
        cout << "Song title: " << this->songTitle << endl;
        cout << "Song artist: " << this->songArtistName << endl;
        cout << "Song album: " << this->songAlbum << endl;
        cout << "Alphabetical order: " << this->firstLetter << endl;
        cout << "Duration: " << ((this->songDuration/60 < 10) ? "0" : "") << this->songDuration/60 << ":" << ((this->songDuration%60 < 10) ? "0" : "") << this->songDuration%60 << endl;
        cout << "Is it in 'Liked Songs'?: " << ((this->isLiked == 1) ? "Yes" : "No");
    }

    friend ostream& operator<< (ostream&, const Song&); //supraincarcare << pentru citire

    void Read() // functie de citire
    {
        cout << "Song title: ";
        getline(cin, this->songTitle);

        cout << "Song artist: ";
        getline(cin, this->songArtistName);

        cout << "Song album: ";
        getline(cin, this->songAlbum);

        cout << "Song duration: ";
        cin >> this->songDuration;

        cout << "Add to Liked Songs? ";
        cin >> this->isLiked;
        if (this->isLiked)
            cout << "Added to Liked Songs!";

        this->firstLetter = tolower(this->songTitle[0]);
    }

    friend istream& operator>> (istream &in, Song &obj); //supraincarcare >> pentru afisare

    Song(const Song& obj)//copy constructor
    {
        this->songTitle = obj.songTitle;
        this->songArtistName = obj.songArtistName;
        this->songAlbum = obj.songAlbum;
        this->firstLetter = obj.firstLetter;
        this->songDuration = obj.songDuration;
        this->isLiked = obj.isLiked;
    }

    //getters

    string getSongTitle()
    {
        return songTitle;
    }

    string getSongArtistName()
    {
        return songArtistName;
    }

    string getSongAlbum()
    {
        return songAlbum;
    }

    char getFirstLetter()
    {
        return firstLetter;
    }

    int getSongDuration()
    {
        return songDuration;
    }


    bool getIsLiked()
    {
        return isLiked;
    }

    //setters

    void setTitle(string _songTitle)
    {
        songTitle = _songTitle;
    }

    void setArtistName (string _songArtistName)
    {
        songArtistName = _songArtistName;
    }

    void setAlbumName (string _songAlbum)
    {
        songAlbum = _songAlbum;
    }

    void setFirstLetter (char _firstLetter)
    {
        this->firstLetter = _firstLetter;
    }

    void setSongDuration (int _songDuration)
    {
        this->songDuration = _songDuration;
    }

    void setIsLiked (bool _isLiked)
    {
        this->isLiked = _isLiked;
    }

    Song& operator = (const Song&); //OPERATORUL EGAL

    //supraincarcare operatori: [], ++, -- (both forms), minimum 2 operatori matematici
    //un operator conditional, operatorul pentru egalitate ==

    bool operator < (const Song &obj) //supraincarcare <
    {
        return this->songDuration < obj.songDuration;
    }

    bool operator == (const Song &obj) //supraincarcare ==
    {
        return this->songDuration == obj.songDuration;
    }

    Song& operator ++ () //supraincarcare ++ (pre-incrementare)
    {
        this->songDuration++;
        return *this;
    }

    Song operator ++ (int)   //supraincarcare ++ (post-incrementare)
    {
        Song copy = *this;
        ++(*this);
        return copy;
    }

    Song& operator -- ()  //supraincarcare -- (pre-decrementare)
    {
        this->songDuration--;
        return *this;
    }

    Song operator -- (int)  //supraincarcare -- (post-decrementare)
    {
        Song copy = *this;
        --(*this);
        return copy;
    }

//    Playlist operator + (const Song& obj) //tipul returnat este un obiect de tipul Playlist, dar am folosit doua obiecte de tip Song
//    {
//        Playlist toReturnPlaylist("Playlist", "New User", 2, {this->songTitle, obj.songTitle}, this->songDuration + obj.songDuration);
//        return toReturnPlaylist;
//    }

    // operatorul + cu obiect din alta clasa in dreapta
    Song operator + (int n)
    {
        Song copy = *this;
        copy.songDuration += n;
        return copy;
    } // se adauga n secunde la durata melodiei

    friend Song operator + (int n, Song obj);

    // *

    //operatorul cu 2 obiecte din clasa
    Song operator * (const Song& obj)
    {
        Song copy = *this;
        copy.songDuration *= obj.songDuration;
        return copy;
    }

//    Playlist operator * (int n) //operatorul * cu obiect din alta clasa in dreapta
//    {
//        vector <string> newPlaylist = {};
//        for (int i = 0; i < n; i++)
//            newPlaylist.push_back(this->songTitle);
//        Playlist toReturnPlaylist("Playlist", n, this->songDuration * n, newPlaylist);
//        return toReturnPlaylist;
//    }

    //operatorul * cu obiect din alta clasa in stanga
    friend Playlist operator * (int n, const Song& obj);

    operator string()
    {
        return this->songTitle;
    }

    explicit operator string() const
    {
        return this->songTitle;
    }
//    friend Playlist operator + (const Song &obj1, Playlist &obj2);
//    friend Playlist operator + (Playlist &obj1, const Song &obj2);
    ~Song()=default;//destructor

    void showAllSongs(char ch);

    void showAllSongs(int duration);



//    friend GeneratedPlaylist operator + (const Song&, GeneratedPlaylist);
//    friend GeneratedPlaylist operator + (GeneratedPlaylist , const Song&);
};

Song :: Song()//constructor fara parametri
{
    songTitle = "unknown";
    songArtistName = "unknown";
    songAlbum = "unknown";
    firstLetter = 'a';
    songDuration = 0;
    isLiked = false;
}

Song :: Song (string songTitle, string songArtistName, string songAlbum, char firstLetter, int songDuration, bool isLiked) : songTitle(songTitle), songArtistName(songArtistName), songAlbum(songAlbum),firstLetter(firstLetter), songDuration(songDuration), isLiked(isLiked)
{

}//constructor cu toti parametrii

ostream& operator<<(ostream &out, const Song &obj) //supraincarcare << pentru citire
{
    out << "Song title: " << obj.songTitle << endl;
    out << "Song artist: " << obj.songArtistName << endl;
    out << "Song album: " << obj.songAlbum << endl;
    out << "Alphabetical order: " << obj.firstLetter << endl;
    out << "Duration: " << ((obj.songDuration/60 < 10) ? "0" : "") << obj.songDuration/60 << ":" << ((obj.songDuration%60 < 10) ? "0" : "") << obj.songDuration%60 << endl;
    out << "Is it in 'Liked Songs'?: " << ((obj.isLiked == 1) ? "Yes" : "No") << endl;
    return out;
}

istream& operator>>(istream &in, Song &obj) //supraincarcare >> pentru afisare
{
    cout << "Song title: ";
    in.get();
    getline(in, obj.songTitle);

    cout << "Song artist: ";
    getline(in, obj.songArtistName);

    cout << "Song album: ";
    getline(in, obj.songAlbum);

    cout << "Song duration: ";
    in >> obj.songDuration;

    cout << "Add to Liked Songs? ";
    in >> obj.isLiked;
    if (obj.isLiked)
        cout << "Added to Liked Songs! ";

    obj.firstLetter = tolower(obj.songTitle[0]);
    return in;
}

Song& Song :: operator = (const Song& obj) //supraincarcare = pentru atribuire
{
    if (this != &obj)
    {
        this->songTitle = obj.songTitle;
        this->songArtistName = obj.songArtistName;
        this->songAlbum = obj.songAlbum;
        this->firstLetter = obj.firstLetter;
        this->songDuration = obj.songDuration;
        this->isLiked = obj.isLiked;
    }
    return *this;
}

Song operator + (int n, Song obj)
{
    obj.songDuration += n;
    return obj;
}

//Playlist operator * (int n, const Song& obj)
//{
//    vector <string> newPlaylist = {};
//    for (int i = 0; i<n; i++)
//        newPlaylist.push_back(obj.songTitle);
//    Playlist toReturnPlaylist("Playlist", n, obj.songDuration * n, newPlaylist);
//    return toReturnPlaylist;
//}

void Playlist::citire(istream& in)
{
    in.get();
    cout << "Playlist name: ";
    getline(in, this->name);
    cout << "Playlist creator: ";
    getline(in, this->creator);
    cout << "Number of songs in playlist: ";
    in >> this->nrSongs;
//    cout << "Duration: ";
//    in >> this->duration;
//    durata playlistului depinde de melodiile pe care le adaugam, deci nu o citim
    cout << "Songs in playlist: " << endl;
    for(int i = 0; i <this->nrSongs; i++)
    {
        cout << "Song number " << i+1 << ":\n";
        Song s;
        in >> s;
        this->songs.push_back(s);
        this->duration += s.getSongDuration();
    }
}

void Playlist::afisare(std::ostream &out) const {
    out << "Playlist name: " << this->name << endl;
    out << "Playlist creator: " << this->creator << endl;
    out << "Number of songs in playlist: " << this->nrSongs << endl;
    out << "Playlist duration: " << ((this->duration/60 < 10) ? "0" : "") << this->duration/60 << ":" << ((this->duration%60 < 10) ? "0" : "") << this->duration%60 << endl;
    out << "Songs: ";
    int i = 1;
    for(auto obj : songs)
    {
        out << "Song number "<< i++ << ": " << endl;
        out << obj << endl;
    }
}

void CreatedPlaylist :: changeVisibility(string status)
{
    if (status == "Public")
        setIsPublic(true);
    else if (status == "Private")
        setIsPublic(false);
    else
        cout << "Invalid keyword.";
}

GeneratedPlaylist operator + (const Song &obj1, GeneratedPlaylist &obj2) //face un playlist nou in care e adaugat obj1
{
    vector <Song> copy = obj2.getSongs();
    copy.push_back(obj1);
    obj2.setSongs(copy);
    return obj2;
}

GeneratedPlaylist operator + (GeneratedPlaylist &obj2, const Song &obj1) //face un playlist nou in care e adaugat obj1
{
    vector <Song> copy = obj2.getSongs();
    copy.push_back(obj1);
    obj2.setSongs(copy);
    return obj2;
}

CreatedPlaylist operator + (const Song &obj1, CreatedPlaylist &obj2) //face un playlist nou in care e adaugat obj1
{
    vector <Song> copy = obj2.getSongs();
    copy.push_back(obj1);
    obj2.setSongs(copy);
    return obj2;
}

CreatedPlaylist operator + (CreatedPlaylist &obj2, const Song &obj1) //face un playlist nou in care e adaugat obj1
{
    vector <Song> copy = obj2.getSongs();
    copy.push_back(obj1);
    obj2.setSongs(copy);
    return obj2;
}

SpecialPlaylist operator + (const Song &obj1, SpecialPlaylist &obj2) //face un playlist nou in care e adaugat obj1
{
    vector <Song> copy = obj2.getSongs();
    copy.push_back(obj1);
    obj2.setSongs(copy);
    return obj2;
}

SpecialPlaylist operator + (SpecialPlaylist &obj2, const Song &obj1) //face un playlist nou in care e adaugat obj1
{
    vector <Song> copy = obj2.getSongs();
    copy.push_back(obj1);
    obj2.setSongs(copy);
    return obj2;
}

SpecialPlaylist operator + (const GeneratedPlaylist &obj1, const CreatedPlaylist &obj2) //face un playlist nou in care sunt combinate obj1 si obj2
{
    SpecialPlaylist p;
    p.setName("new special playlist");
    p.setCreator(obj2.getCreator());
    vector <Song> temp1 = obj1.getSongs();
    vector <Song> temp2 = obj2.getSongs();
    for (int i = 0; i < temp1.size(); i++)
        temp2.push_back(temp1[i]);
    p.setSongs(temp2);
    p.setDuration(obj1.getDuration() + obj2.getDuration());
    p.setGenre(obj1.getGenre());
    p.setIsGeneratedByUserActivity(obj1.getIsGeneratedByUserActivity());
    p.setIsPublic(obj2.getIsPublic());
    p.setIsCollaborative(obj2.getIsCollaborative());
    vector <string> temp3 = obj2.getCollaborators();
    for (int i = 0; i < temp3.size(); i++)
    {
        p.collaborators.push_back(temp3[i]);
    }
    return p;
}

SpecialPlaylist operator + (const CreatedPlaylist &obj2, const GeneratedPlaylist &obj1) //face un playlist nou in care sunt combinate obj1 si obj2
{
    SpecialPlaylist p;
    p.setName("new special playlist");
    p.setCreator(obj2.getCreator());
    vector <Song> temp1 = obj1.getSongs();
    vector <Song> temp2 = obj2.getSongs();
    for (int i = 0; i < temp1.size(); i++)
        temp2.push_back(temp1[i]);
    p.setSongs(temp2);
    p.setDuration(obj1.getDuration() + obj2.getDuration());
    p.setGenre(obj1.getGenre());
    p.setIsGeneratedByUserActivity(obj1.getIsGeneratedByUserActivity());
    p.setIsPublic(obj2.getIsPublic());
    p.setIsCollaborative(obj2.getIsCollaborative());
    vector <string> temp3 = obj2.getCollaborators();
    for (int i = 0; i < temp3.size(); i++)
    {
        p.collaborators.push_back(temp3[i]);
    }
    return p;
}


int main() {

    vector <Playlist*> playlists; //Playlist *p = new CreatedPlaylist/GeneratedPlaylist/SpecialPlaylist
    bool isRunning = true;
    int input;
    while (isRunning)
    {
        cout << "*** Welcome to Music Player! ***";
        cout << endl;
        cout << endl;
        cout << "What would you like to do? \n";
        cout << endl;
        cout << endl;
        cout << "1) Create playlist\n";
        cout << "2) Read all playlists\n"; // de verificat fiecare const int typeOfPlaylist pentru a afisa "type of playlist: x" inainte de fiecare playlist
        cout << "3) Update a playlist\n"; // aici sa se foloseasca operatorii supraincarcati
        cout << "4) Delete playlist\n"; //stergerea unui playlist in functie de nume, de cautat in vector
        cout << endl;
        cout << endl;
        cin >> input;
        switch (input)
        {
            case 1:
            {
                cout << "What would you like to create? \n";
                cout << endl;
                cout << endl;
                cout << "1) User created playlist\n";
                cout << "2) App generated playlist \n";
                cout << "3) Special playlist \n";
                cout << endl;
                cin >> input;
                switch (input) {
                    case 1:
                    {
                        playlists.push_back(new CreatedPlaylist);
                        cin >> *playlists.back();
                        cout << endl;
                        cout << "User created playlist has been created." << endl;
                        break;
                    }
                    case 2:
                    {
                        playlists.push_back(new GeneratedPlaylist);
                        cin >> *playlists.back();
                        cout << endl;
                        cout << "App generated playlist has been created." << endl;
                        break;
                    }
                    case 3:
                    {
                        playlists.push_back(new SpecialPlaylist);
                        cin >> *playlists.back();
                        cout << endl;
                        cout << "Special playlist has been created." << endl;
                        break;
                    }
                    default:
                    {
                        cout << "Invalid action, please try again." << endl;
                        break;
                    }
                }
                break;
            }
            case 2:
            {
                cout << "What would you like to see? \n";
                cout << endl;
                cout << endl;
                cout << "1) All user created playlists\n";
                cout << "2) All generated playlists \n";
                cout << "3) All special playlists \n";
                cout << "4) All playlists \n"; //afiseaza toate playlisturile, indiferent de tip
                cout << endl;
                cin>>input;
                switch(input)
                {
                    case 1:
                    {
                        for (auto & playlist : playlists)
                        {
                            if (typeid(*playlist) == typeid(CreatedPlaylist))
                            {
                                cout << *playlist;
                                cout << endl;
                            }
                        }
                        break;
                    }
                    case 2:
                    {
                        for (auto & playlist : playlists)
                        {
                            if (typeid(*playlist) == typeid(GeneratedPlaylist))
                            {
                                cout << *playlist;
                                cout << endl;
                            }
                        }
                        break;
                    }
                    case 3:
                    {
                        for (auto & playlist : playlists)
                        {
                            if (typeid(*playlist) == typeid(SpecialPlaylist))
                            {
                                cout << *playlist;
                                cout << endl;
                            }
                        }
                        break;
                    }
                    case 4:
                    {
                        for (auto & playlist : playlists)
                        {
                            cout << *playlist;
                            cout << endl;
                        }
                        break;
                    }
                    default:
                    {
                        cout << "Invalid action, please try again." << endl;
                        break;
                    }

                }
                break;
            }
            case 3:
            {
                cout<<endl;
                cout<<"Select an action: "<<endl;
                cout<<endl;
                cout<<"1) Add a song to a playlist"<<endl;
                cout<<"2) Combine two playlists"<<endl;
                cin >> input;
                switch(input)
                {
                    case 1:
                    {
                        if (playlists.empty())
                        {
                            cout << "No playlists available. Please create a playlist first.";
                            break;
                        }
                        else {
                            cout << "Select a playlist: \n";
                            cout << endl;
                            for (int i = 0; i < playlists.size(); i++) {
                                cout << i + 1 << ". " << playlists[i]->getName() << endl;
                            }
                            string name;
                            cin >> name;
                            for (auto &playlist : playlists) {
                                if (playlist->getName() == name) {
                                    Song s;
                                    cin >> s;
                                    if (typeid(*playlist) == typeid(CreatedPlaylist))
                                    {
                                        CreatedPlaylist *p = dynamic_cast<CreatedPlaylist*>(playlist);
                                        *p = s + *p;
                                        playlists.push_back(p);
                                    }
                                    else if (typeid(*playlist) == typeid(GeneratedPlaylist))
                                    {
                                        GeneratedPlaylist *p = dynamic_cast<GeneratedPlaylist*>(playlist);
                                        *p = s + *p;
                                        playlists.push_back(p);
                                    }
                                    else if (typeid(*playlist) == typeid(SpecialPlaylist))
                                    {
                                        SpecialPlaylist *p = dynamic_cast<SpecialPlaylist*>(playlist);
                                        *p = s + *p;
                                        playlists.push_back(p);
                                    }
                                    cout << "Song added to playlist.";
                                    break;
                                }
                            }
                        }
                        break;
                    }
                    case 2:
                    {
                        if (playlists.empty())
                        {
                            cout << "No playlists available. Please create a playlist first.";
                            break;
                        }
                        else {
                            cout << "Select a playlist: \n";
                            cout << endl;
                            for (int i = 0; i < playlists.size(); i++) {
                                cout << i + 1 << ". " << playlists[i]->getName() << endl;
                            }
                            string name;
                            cin >> name;
                            for (auto &playlist : playlists) {
                                if (playlist->getName() == name) {
                                    cout << "Select another playlist: \n";
                                    cout << endl;
                                    for (int i = 0; i < playlists.size(); i++) {
                                        cout << i + 1 << ". " << playlists[i]->getName() << endl;
                                    }
                                    string name2;
                                    cin >> name2;
                                    for (auto &playlist2 : playlists) {
                                        if (playlist2->getName() == name2) {
                                            if (typeid(*playlist) == typeid(CreatedPlaylist) && typeid(*playlist2) == typeid(CreatedPlaylist))
                                            {
                                                CreatedPlaylist *p1 = dynamic_cast<CreatedPlaylist*>(playlist);
                                                CreatedPlaylist *p2 = dynamic_cast<CreatedPlaylist*>(playlist2);
                                                *p1 = *p1 + *p2;
                                                playlists.push_back(p1);
                                            }
                                            else if (typeid(*playlist) == typeid(GeneratedPlaylist) && typeid(*playlist2) == typeid(GeneratedPlaylist))
                                            {
                                                GeneratedPlaylist *p1 = dynamic_cast<GeneratedPlaylist*>(playlist);
                                                GeneratedPlaylist *p2 = dynamic_cast<GeneratedPlaylist*>(playlist2);
                                                *p1 = *p1 + *p2;
                                                playlists.push_back(p1);
                                            }
                                            else if (typeid(*playlist) == typeid(SpecialPlaylist) && typeid(*playlist2) == typeid(SpecialPlaylist))
                                            {
                                                SpecialPlaylist *p1 = dynamic_cast<SpecialPlaylist*>(playlist);
                                                SpecialPlaylist *p2 = dynamic_cast<SpecialPlaylist*>(playlist2);
                                                *p1 = *p1 + *p2;
                                                playlists.push_back(p1);
                                            }
                                            else if (typeid(*playlist) == typeid(SpecialPlaylist) && typeid(*playlist2) == typeid(CreatedPlaylist))
                                            {
                                                SpecialPlaylist *p1 = dynamic_cast<SpecialPlaylist*>(playlist);
                                                CreatedPlaylist *p2 = dynamic_cast<CreatedPlaylist*>(playlist2);
                                                *p1 = *p1 + *p2;
                                                playlists.push_back(p1);
                                            }

                                            else if (typeid(*playlist) == typeid(SpecialPlaylist) && typeid(*playlist2) == typeid(GeneratedPlaylist))
                                            {
                                                SpecialPlaylist *p1 = dynamic_cast<SpecialPlaylist*>(playlist);
                                                GeneratedPlaylist *p2 = dynamic_cast<GeneratedPlaylist*>(playlist2);
                                                *p1 = *p1 + *p2;
                                                playlists.push_back(p1);
                                            }

                                            else if (typeid(*playlist) == typeid(GeneratedPlaylist) && typeid(*playlist2) == typeid(CreatedPlaylist))
                                            {
                                                SpecialPlaylist *p = dynamic_cast<SpecialPlaylist*>(playlist);
                                                GeneratedPlaylist *p1 = dynamic_cast<GeneratedPlaylist*>(playlist);
                                                CreatedPlaylist *p2 = dynamic_cast<CreatedPlaylist*>(playlist2);
                                                *p = *p1 + *p2;
                                                playlists.push_back(p);
                                            }
                                            cout << "Playlists combined.";
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                        break;
                    }
                    default:
                    {
                        cout << "Invalid action, please try again." << endl;
                        break;
                    }
                }

                break;
            }
            case 4:
            {
                if (playlists.empty())
                {
                    cout << "No playlists available. Please create a playlist first.";
                    break;
                }
                else {
                    cout << "Select a playlist to delete: \n";
                    cout << endl;
                    for (int i = 0; i < playlists.size(); i++) {
                        cout << i + 1 << ". " << playlists[i]->getName() << endl;
                    }
                    string name;
                    cin >> name;
                    for (int i = 0; i < playlists.size(); i++) {
                        if (playlists[i]->getName() == name) {
                            playlists.erase(playlists.begin() + i);
                            cout << "Playlist deleted.";
                            break;
                        }
                    }
                    cout << endl;
                    if(playlists.empty())
                    {
                        cout << "No more playlists available.";
                        cout << endl;
                    }
                    break;
                }
            }
            default:
            {
                cout << "Invalid command, please try again.";
                break;
            }
        }
    }
    return 0;


}

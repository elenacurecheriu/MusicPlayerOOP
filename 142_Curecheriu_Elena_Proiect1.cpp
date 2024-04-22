#include <iostream>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

class Song;

class Playlist
{
private:
    string playlistName;
    int playlistNumberOfSongs;
    int playlistDuration;
    vector <string> songs;
public:

    Playlist(); //constructor fara parametri

    Playlist(string playlistName, int playlistNumberOfSongs, int playlistDuration, vector <string> songs); //constructor cu toti parametri

    Playlist(string _playlistName) //constructor cu un parametru
    {
        this -> playlistName = _playlistName;
    }

    Playlist(string _playlistName, vector <string> _songs) //constructor cu 2 parametri
    {
        this -> playlistName = _playlistName;
        this->songs = _songs;
    }

    Playlist(const Playlist& obj) //copy constructor
    {
        this->playlistName = obj.playlistName;
        this->playlistNumberOfSongs = obj.playlistNumberOfSongs;
        this->playlistDuration = obj.playlistDuration;
        this->songs = obj.songs;
    }

    Playlist& operator = (const Playlist&);

    void Read()
    {
        cout << "Playlist name: ";
        cin.get();
        getline(cin, this->playlistName);

        cout << "Number of songs in playlist: ";
        cin >> this->playlistNumberOfSongs;

//        durata playlistului depinde de melodiile care se afla in el, deci nu il citim
//        cout << "Playlist duration: ";
//        cin >> this->playlistDuration;

        string playlistSongName;
        cout << "Songs in playlist: " << endl;
        for (int i = 0; i < this->playlistNumberOfSongs; i++)
        {
            cin >> playlistSongName;
            this->songs.push_back(playlistSongName);
        }
    }

    void Print()
    {
        cout << "Playlist name: " << this->playlistName << endl;
        cout << "Number of songs in playlist: " << this->playlistNumberOfSongs << endl;
        cout << "Playlist duration: " << ((this->playlistDuration/60 < 10) ? "0" : "") << this->playlistDuration/60 << ":" << ((this->playlistDuration%60 < 10) ? "0" : "") << this->playlistDuration%60 << endl;
        cout << "Songs in playlist: " << endl;

        for (int i = 0; i < this->playlistNumberOfSongs; i++)
        {
            cout << i+1 << ". ";
            cout<<this->songs[i]<<endl;
        }
    }

    friend ostream& operator << (ostream&, const Playlist&);

    friend istream& operator >> (istream &in, Playlist &obj);

    Playlist& operator ++ () //pre
    {
        this -> playlistNumberOfSongs++;
        this->songs.resize(this->playlistNumberOfSongs, "NEW UNKNOWN SONG");
        return *this;
    }

    Playlist& operator ++ (int) //post
    {
        Playlist copy = *this;
        ++(*this);
        return copy;
    }

    Playlist& operator -- () //pre
    {
        this -> playlistNumberOfSongs--;
        this->songs.resize(this->playlistNumberOfSongs);
        return *this;
    }

    Playlist& operator -- (int) //post
    {
        Playlist copy = *this;
        --(*this);
        return copy;
    }

    string operator [] (int index) //operatorul de indexare
    {
        if (index >= 0 && index < this->playlistNumberOfSongs)
            return this -> songs[index];
        else throw runtime_error ("Index invalid");
    }

    bool operator < (const Playlist &obj)
    {
        return this -> playlistNumberOfSongs < obj.playlistNumberOfSongs;
    }

    bool operator == (const Playlist &obj)
    {
        return this -> playlistNumberOfSongs == obj.playlistNumberOfSongs;
    }

    //getters

    string getPlaylistName ()
    {
        return playlistName;
    }

    int getPlaylistNumberOfSongs ()
    {
        return playlistNumberOfSongs;
    }

    int getPlaylistDuration ()
    {
        return playlistDuration;
    }

    vector <string> getSongs()
    {
        return songs;
    }

    //setters

    void setPlaylistName (string _playlistName)
    {
        this->playlistName = _playlistName;
    }

    void setPlaylistNumberOfSongs (int _playlistNumberOfSongs)
    {
        this->playlistNumberOfSongs = _playlistNumberOfSongs;
    }

    void setPlaylistDuration (int _playlistDuration)
    {
        this->playlistDuration = _playlistDuration;
    }

    void setSongs (vector <string> _songs)
    {
        int songsSize = _songs.size();
        for (int i=0; i < songsSize; i++)
            songs[i] = _songs[i];
    }

    //cast

    operator string()
    {
        return this->playlistName;
    }

    explicit operator string() const
    {
        return this->playlistName;
    }

    //operatorul + cu 2 obiecte din clasa

    Playlist operator + (const Playlist& obj) // se unesc cele doua playlist-uri intr-unul mai mare; se modifica si
    {                                         // numele, se memoreaza in this si melodiile se pot repeta, nu este un set
        Playlist copy = *this;
        for (int i = 0; i < obj.playlistNumberOfSongs; i++)
            copy.songs.push_back(obj.songs[i]);
        copy.playlistName = copy.playlistName + " modified";
        copy.playlistNumberOfSongs += obj.playlistNumberOfSongs;
        copy.playlistDuration += obj.playlistDuration;
        return copy;
    }

    //operatorul + cu un alt obiect din alta clasa la dreapta

    //functionalitatea de a adauga melodie in playlist cu operatorul + a fost implementata in clasa Song
    Playlist operator + (string s)
    {
        Playlist copy = *this;
        copy.playlistName = copy.playlistName + " " + s;
        return copy;
    }

    //operatorul + cu un alt obiect din alta clasa la stanga
    friend Playlist operator + (string s, Playlist obj);

    //operatorul - cu 2 obiecte din clasa

    Playlist operator - (const Playlist& obj) //se elimina din this melodiile din this
    {
        int contor = 0; //cate melodii au fost eliminate
        Playlist copy = *this;
        vector <string> newSongs = {};
        for (auto i : copy.songs)
            for (auto j : obj.songs)
            {
                if (i != j)
                {
                    newSongs.push_back(i);
                    contor++;
                }
            }
        copy.playlistNumberOfSongs -= contor;
        copy.songs.clear();
        for (auto i : newSongs)
            copy.songs.push_back(i);
        return copy;
    }

    // operatorul - cu obiect din alta clasa in dreapta
    Playlist operator - (string s)
    {
        Playlist copy = *this;
        vector <string> newSongs = {};
        for (auto i : copy.songs)
        {
            if (i != s) {
                newSongs.push_back(i);
            }
        }
        copy.playlistNumberOfSongs--;
        copy.songs.clear();
        for (auto i : newSongs)
            copy.songs.push_back(i);
        return copy;
    }

    //operatorul - cu obiect din alta clasa in stanga
    friend Playlist operator - (string s, Playlist obj);

    friend Playlist operator + (const Song &obj1, Playlist &obj2);
    friend Playlist operator + (Playlist &obj1, const Song &obj2);

    ~Playlist() = default;

    void showAllPlaylists(int number);
};

Playlist :: Playlist()
{
    playlistName = "unknown";
    playlistNumberOfSongs = 0;
    playlistDuration = 0;
    songs = {};
}

Playlist :: Playlist(string playlistName, int playlistNumberOfSongs, int playlistDuration, vector <string> songs):playlistName(playlistName), playlistNumberOfSongs(playlistNumberOfSongs), playlistDuration(playlistDuration), songs(songs)
{

}

Playlist& Playlist :: operator = (const Playlist& obj)
{
    if (this != &obj)
    {
        this->playlistName = obj.playlistName;
        this->playlistNumberOfSongs = obj.playlistNumberOfSongs;
        this->playlistDuration = obj.playlistDuration;
        this->songs = obj.songs;
    }
    return *this;
}

ostream& operator << (ostream &out, const Playlist &obj)
{
    out << "Playlist name: " << obj.playlistName << endl;
    out << "Number of songs in playlist: " << obj.playlistNumberOfSongs << endl;
    out << "Playlist duration: " << ((obj.playlistDuration/60 < 10) ? "0" : "") << obj.playlistDuration/60 << ":" << ((obj.playlistDuration%60 < 10) ? "0" : "") << obj.playlistDuration%60 << endl;
    out << "Songs in playlist: " << endl;

    for (int i = 0; i < obj.playlistNumberOfSongs; i++)
    {
        out << i+1 << ". ";
        out<<obj.songs[i]<<endl;
    }
    return out;
}

istream& operator >> (istream &in, Playlist &obj)
{
    cout << "Playlist name: ";
    in.get();
    getline(in, obj.playlistName);

    cout << "Number of songs in playlist: ";
    in >> obj.playlistNumberOfSongs;

    //nu citim playlistDuration pentru ca depinde de melodiile care se afla in playlist

    string playlistSongName;
    cout << "Songs in playlist: " << endl;
    for (int i = 0; i < obj.playlistNumberOfSongs; i++)
    {
        in >> playlistSongName;
        obj.songs.push_back(playlistSongName);
    }
    return in;
}

Playlist operator + (string s, Playlist obj)
{
    obj.playlistName = obj.playlistName + " " + s;
    return obj;
}

Playlist operator - (string s, Playlist obj)
{
    vector <string> newSongs = {};
    for (auto i : obj.songs)
    {
        if (i != s) {
            newSongs.push_back(i);
        }
    }
    obj.playlistNumberOfSongs--;
    obj.songs.clear();
    for (auto i : newSongs)
        obj.songs.push_back(i);
    return obj;
}

class Song
{
private:
    const int user;
    static int numberOfSongs;
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
    Song(string x):user(numberOfSongs++)
    {
        this -> songTitle = x;
    }

    //constructor cu mai multi parametri
    Song(string x, bool fav):user(numberOfSongs++)
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

    Song(const Song& obj):user(obj.user) //copy constructor
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

    // +
    /*Song operator + (const Song& obj) // operatorul + cu 2 obiecte din clasa
    {
        Song copy = *this;
        copy.songTitle = copy.songTitle + " " + obj.songTitle;
        return copy;
    }
    */

    //operatorul + cu doua obiecte din clasa

    Playlist operator + (const Song& obj) //tipul returnat este un obiect de tipul Playlist, dar am folosit doua obiecte de tip Song
    {
            Playlist toReturnPlaylist("Playlist", 2, this->songDuration + obj.songDuration, {this->songTitle, obj.songTitle});
            return toReturnPlaylist;
    }

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

    Playlist operator * (int n) //operatorul * cu obiect din alta clasa in dreapta
    {
            vector <string> newPlaylist = {};
            for (int i = 0; i < n; i++)
                newPlaylist.push_back(this->songTitle);
            Playlist toReturnPlaylist("Playlist", n, this->songDuration * n, newPlaylist);
            return toReturnPlaylist;
    }

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
    friend Playlist operator + (const Song &obj1, Playlist &obj2);
    friend Playlist operator + (Playlist &obj1, const Song &obj2);
    ~Song()=default;//destructor



    void showAllSongs(char ch);

    void showAllSongs(int duration);
};

Song :: Song():user(numberOfSongs++) //constructor fara parametri
    {
        songTitle = "unknown";
        songArtistName = "unknown";
        songAlbum = "unknown";
        firstLetter = 'a';
        songDuration = 0;
        isLiked = false;
    }

Song :: Song (string songTitle, string songArtistName, string songAlbum, char firstLetter, int songDuration, bool isLiked) : user(numberOfSongs++), songTitle(songTitle), songArtistName(songArtistName), songAlbum(songAlbum),firstLetter(firstLetter), songDuration(songDuration), isLiked(isLiked)
{

}//constructor cu toti parametrii

ostream& operator<<(ostream &out, const Song &obj) //supraincarcare << pentru citire
{
    out << "Song number: "<< obj.numberOfSongs << endl;
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

Playlist operator * (int n, const Song& obj)
{
    vector <string> newPlaylist = {};
    for (int i = 0; i<n; i++)
        newPlaylist.push_back(obj.songTitle);
    Playlist toReturnPlaylist("Playlist", n, obj.songDuration * n, newPlaylist);
    return toReturnPlaylist;
}

class Artist
{
private:
    const int id;
    static int numberOfArtists;
    string artistName;
    int artistNumberOfAlbums;
    int debutYear;
    string genre;
    long monthlyListeners;
    double artistRating;

public:

    Artist(); //constructor fara parametri

    //constructor cu toti parametrii
    Artist(string artistName, int artistNumberOfAlbums, int debutYear, string genre, long monthlyListeners, double artistRating); //constructor cu toti parametrii

    //constructor cu un parametru
    Artist(string x):id(numberOfArtists++)
    {
        this -> artistName = x;
    }

    //constructor cu mai multi parametri1
    Artist(string x, string _genre):id(numberOfArtists++)
    {
        this -> artistName = x;
        this -> genre = _genre;
    }

    void Print() //afisare
    {
        cout << "Artist's number: " << this->numberOfArtists << endl;
        cout << "Artist's name: " << this->artistName << endl;
        cout << "Artist's number of albums" << this->artistNumberOfAlbums << endl;
        cout << "Artist's debut year " << this->debutYear << endl;
        cout << "Genre: " << this->genre << endl;
        cout << "Monthly listeners:" << this->monthlyListeners << endl;
        cout << "Artist rating: " << this->artistRating << endl;
    }

    friend ostream& operator<< (ostream&, const Artist&);

    void Read()
    {
        cout << "Artist's name: ";
        getline(cin, this->artistName);

        cout << "Artist's number of albums: ";
        cin >> this->artistNumberOfAlbums;

        cout << "Artist's debut year: ";
        cin >> this->debutYear;

        cout << "Genre: ";
        cin.get();
        getline(cin, this->genre);

        cout << "Monthly listeners: ";
        cin >> this->monthlyListeners;

        cout << "Artist rating: ";
        cin >> this->artistRating;

    }

    friend istream& operator>> (istream &in, Artist &obj);

    Artist(const Artist& obj):id(obj.id) //copy constructor
    {
        this->artistName = obj.artistName;
        this->artistNumberOfAlbums = obj.artistNumberOfAlbums;
	    this->debutYear = obj.debutYear;
	    this->genre = obj.genre;
        this->monthlyListeners = obj.monthlyListeners;
        this->artistRating = obj.artistRating;
    }


    //getters

    string getArtistName()
    {
        return artistName;
    }

    int getArtistNumberOfAlbums()
    {
        return artistNumberOfAlbums;
    }

    int getDebutYear()
    {
        return debutYear;
    }

    string getGenre()
    {
        return genre;
    }

    long getMonthlyListeners()
    {
        return monthlyListeners;
    }

    double getArtistRating()
    {
        return artistRating;
    }

    //setters

    void setName(string _artistName)
    {
        artistName = _artistName;
    }

    void setNumberOfAlbums (int _NumberOfAlbums)
    {
        artistNumberOfAlbums = _NumberOfAlbums;
    }

    void setDebutYear (int _debutYear)
    {
        debutYear = _debutYear;
    }

    void setGenre (string _genre)
    {
        genre = _genre;
    }

    void setMonthlyListeners (long _monthlyListeners)
    {
        monthlyListeners = _monthlyListeners;
    }

    void setArtistRating (double _artistRating)
    {
        artistRating = _artistRating;
    }

    //getters

    Artist& operator = (const Artist&);

    bool operator == (const Artist &obj)
    {
        return this->artistName == obj.artistName;
    }

    bool operator < (const Artist &obj) //supraincarcare <
    {
        return this->monthlyListeners < obj.monthlyListeners;
    }

    Artist& operator ++ () //supraincarcare ++ (pre-incrementare)
    {
        this->monthlyListeners++;
        return *this;
    }

    Artist& operator ++ (int) //supraincarcare ++ (post-incrementare)
    {
        Artist copy = *this;
        ++(*this);
        return copy;
    }

    Artist& operator -- () //supraincarcare -- (pre-incrementare)
    {
        this->monthlyListeners--;
        return *this;
    }

    Artist& operator -- (int) //supraincarcare -- (post-incrementare)
    {
        Artist copy = *this;
        --(*this);
        return copy;
    }

    operator string()
    {
        return this->artistName;
    }

    explicit operator string() const
    {
        return this->artistName;
    }

    Artist operator +(const Artist& obj)
    {
        Artist copy = *this;
        copy.artistName = copy.artistName + " " + obj.artistName;
        return copy;
    }

    /// OPERATORUL + cu obiect din alta clasa IN DREAPTA
    Artist operator +(string s)
    {
        Artist copy = *this;
        copy.artistName = copy.artistName + " " + s;
        return copy;
    }

    /// OPERATORUL + cu obiect din alta clasa IN STANGA

    friend Artist operator +(string s, Artist obj);

    Artist operator - (const Artist& obj)
    {
        Artist copy = *this;
        copy.monthlyListeners = abs(copy.monthlyListeners - obj.monthlyListeners);
        return copy;
    }

    /// OPERATORUL - cu obiect din alta clasa IN DREAPTA
    Artist operator -(long nr)
    {
        Artist copy = *this;
        copy.monthlyListeners = abs(copy.monthlyListeners - nr);
        return copy;
    }

    /// OPERATORUL - cu obiect din alta clasa IN STANGA

    friend Artist operator - (long nr, Artist obj);


    ~Artist()=default;


    void showAllArtists(int year);

    void showAllArtists(long numberOfListeners);
};

Artist operator +(string s, Artist obj)
{
    obj.artistName = s + " " + obj.artistName;
    return obj;
}

Artist operator - (long nr, Artist obj)
{
    obj.monthlyListeners = abs(obj.monthlyListeners - nr);
    return obj;
}

Artist :: Artist():id(numberOfArtists++)
{
    artistName = "unknown";
    artistNumberOfAlbums = 0;
    debutYear = 1970;
    genre = "unknown";
    monthlyListeners = 0;
    artistRating = 0.0;
}

Artist :: Artist (string artistName, int artistNumberOfAlbums, int debutYear, string genre, long monthlyListeners, double artistRating) : id(numberOfArtists++), artistName(artistName), artistNumberOfAlbums(artistNumberOfAlbums), debutYear(debutYear), genre(genre), monthlyListeners(monthlyListeners), artistRating(artistRating)
{

}

ostream& operator << (ostream &out, const Artist &obj) //supraincarcare << pentru afisare
{
    out << "Artist's number: " << obj.numberOfArtists << endl;
    out << "Artist's name: " << obj.artistName << endl;
    out << "Artist's number of albums: " << obj.artistNumberOfAlbums << endl;
    out << "Artist's debut year: " << obj.debutYear << endl;
    out << "Genre: " << obj.genre << endl;
    out << "Monthly listeners:" << obj.monthlyListeners << endl;
    out << "Artist rating: " << obj.artistRating << endl;
    return out;
}

istream& operator >>(istream &in, Artist &obj) //supraincarcare >> pentru citire
{
    cout << "Artist name: ";
    getline(in, obj.artistName);

    cout << "Artist number of albums: ";
    in >> obj.artistNumberOfAlbums;

    cout << "Debut year: ";
    in >> obj.debutYear;

    cout << "Genre: ";
    in.get();
    getline(in, obj.genre);

    cout << "Monthly listeners: ";
    in >> obj.monthlyListeners;

    cout << "Artist rating: ";
    in >> obj.artistRating;

    return in;
}

Artist& Artist :: operator = (const Artist& obj) //supraincarcare = pentru atribuire
{
    if(this != &obj) {
        this->artistName = obj.artistName;
        this->artistNumberOfAlbums = obj.artistNumberOfAlbums;
        this->debutYear = obj.debutYear;
        this->genre = obj.genre;
        this->monthlyListeners = obj.monthlyListeners;
        this->artistRating = obj.artistRating;
    }
    return *this;
}


class Album {
private:
    char *albumName;
    char *albumArtist;
    int releaseYear;
    int albumNumberOfSongs;
    float albumRating;
    int *songInLikedSongs;

public:
    Album(); //constructor fara parametri

    Album(char *albumName, char *albumArtist, int releaseYear, int albumNumberOfSongs, float albumRating, int *songInLikedSongs); //constuctor cu toti parametrii

    Album(char *albumName, char *albumArtist) //constructor cu doi parametri
    {
        this->albumName = new char[strlen(albumName) + 1];
        strcpy(this->albumName, albumName);
        this->albumArtist = new char[strlen(albumArtist) + 1];
        strcpy(this->albumArtist, albumArtist);
    }

    Album(char *albumName, char *albumArtist, int albumNumberOfSongs, int *songInLikedSongs) //constructor cu 4 parametri
    {
        this->albumName = new char[strlen(albumName) + 1];
        strcpy(this->albumName, albumName);
        this->albumArtist = new char[strlen(albumArtist) + 1];
        strcpy(this->albumArtist, albumArtist);
        this->albumNumberOfSongs = albumNumberOfSongs;
        this->songInLikedSongs = new int[albumNumberOfSongs];
        for (int i = 0; i < albumNumberOfSongs; i++)
            this->songInLikedSongs[i] = songInLikedSongs[i];
    }

    Album(const Album &obj) //copy constructor
    {
        this->albumName = new char[strlen(obj.albumName) + 1];
        strcpy(this->albumName, obj.albumName);
        this->albumArtist = new char[strlen(obj.albumArtist) + 1];
        strcpy(this->albumArtist, obj.albumArtist);
        this->releaseYear = obj.releaseYear;
        this->albumNumberOfSongs = obj.albumNumberOfSongs;
        this->albumRating = obj.albumRating;
        this->songInLikedSongs = new int[obj.albumNumberOfSongs];
        for (int i = 0; i < obj.albumNumberOfSongs; i++)
            this->songInLikedSongs[i] = obj.songInLikedSongs[i];
    }

    Album &operator=(const Album &);

    void Read() {
        cout << "Album name: ";
        char name[101];
        cin.get();
        cin.getline(name, 101);
        if (this->albumName != NULL)
            delete[] this->albumName;
        this->albumName = new char[strlen(name) + 1];
        strcpy(this->albumName, name);

        cout << "Album artist: ";
        char artist[101];
        cin.get();
        cin.getline(artist, 101);
        if (this->albumArtist != NULL)
            delete[] this->albumArtist;
        this->albumArtist = new char[strlen(artist) + 1];
        strcpy(this->albumArtist, artist);

        cout << "Release year: ";
        cin >> this->releaseYear;

        cout << "Number of songs on the album: ";
        cin >> this->albumNumberOfSongs;

        cout << "Album rating: ";
        cin >> this->albumRating;

        if (this->songInLikedSongs != NULL)
            delete[] this->songInLikedSongs;
        this->songInLikedSongs = new int[this->albumNumberOfSongs];
        cout << "Say if each song is in Liked Songs: ";
        for (int i = 0; i < this->albumNumberOfSongs; i++)
            cin >> this->songInLikedSongs[i];
    }

    void Print() {
        cout << "Album name: " << this->albumName << endl;
        cout << "Album artist: " << this->albumArtist << endl;
        cout << "Release year: " << this->releaseYear << endl;
        cout << "Number of songs on the album: " << this->albumNumberOfSongs << endl;
        cout << "Album rating: " << this->albumRating << endl;
        for (int i = 0; i < this->albumNumberOfSongs; i++)
            if (this->songInLikedSongs[i] == 0)
                cout << "Song number " << i + 1 << " is not in Liked Songs"<<endl;
            else
                cout << "Song number " << i + 1 << " is in Liked Songs"<<endl;
    }

    friend ostream& operator << (ostream &out, const Album &);

    friend istream& operator >> (istream &in, Album &obj);

    //setters

    void setAlbumName(char *albumName) {
        if (this->albumName != NULL)
            delete[] this->albumName;
        this->albumName = new char[strlen(albumName) + 1];
        strcpy(this->albumName, albumName);
    }

    void setAlbumArtist(char *albumArtist) {
        if (this->albumArtist != NULL)
            delete[] this->albumArtist;
        this->albumArtist = new char[strlen(albumArtist) + 1];
        strcpy(this->albumArtist, albumArtist);
    }

    void setReleaseYear(int releaseYear) {
        this->releaseYear = releaseYear;
    }

    void setAlbumNumberOfSongs(int albumNumberOfSongs) {
        this->albumNumberOfSongs = albumNumberOfSongs;
    }


    void setAlbumRating(float albumRating) {
        this->albumRating = albumRating;
    }

    void setSongInLikedSongs(int *songInLikedSongs) {
        if (this->songInLikedSongs != NULL)
            delete[] this->songInLikedSongs;
        this->songInLikedSongs = new int[albumNumberOfSongs];
        for (int i = 0; i < albumNumberOfSongs; i++)
            this->songInLikedSongs[i] = songInLikedSongs[i];
    }

    //getters

    const char* getAlbumName()
    {
        return albumName;
    }

    const char* getAlbumArtist()
    {
        return albumArtist;
    }

    int getReleaseYear()
    {
        return releaseYear;
    }

    int getAlbumNumberOfSongs()
    {
        return albumNumberOfSongs;
    }


    float getAlbumRating()
    {
        return albumRating;
    }

    const int* getSongInLikedSongs()
    {
        return songInLikedSongs;
    }

    bool operator < (const Album &obj)
    {
        return this->albumNumberOfSongs < obj.albumNumberOfSongs;
    }

    bool operator == (const Album &obj)
    {
        return this->albumNumberOfSongs == obj.albumNumberOfSongs;
    }

    //operatorul ++ (cu pre-incrementare si post-incrementare)
    Album& operator ++ () //pre
    {
        this->albumNumberOfSongs++;
        int* v = new int[this->albumNumberOfSongs];
        for(int i = 0; i < this->albumNumberOfSongs; i++)
            v[i] = this->songInLikedSongs[i];
        v[this->albumNumberOfSongs] = 0;
        if (this-> songInLikedSongs != NULL)
            delete [] this->songInLikedSongs;
        this->songInLikedSongs = v;
        return *this;
    }

    Album& operator ++ (int) //post
    {
        Album copy = *this;
        ++(*this);
        return copy;
    }

    //operatorul -- (cu pre-decrementare si post-decrementare)

    Album& operator -- () //pre
    {
        this -> albumNumberOfSongs--;
        int* v = new int[this->albumNumberOfSongs];
        for(int i = 0; i < this->albumNumberOfSongs; i++)
            v[i] = this->songInLikedSongs[i];
        v[this->albumNumberOfSongs] = 0;
        if (this-> songInLikedSongs != NULL)
            delete [] this->songInLikedSongs;
        this->songInLikedSongs = v;
        return *this;
    }

    Album& operator -- (int) //post
    {
        Album copy = *this;
        --(*this);
        return copy;
    }

    //operatorul de indexare []

    int operator [] (int index)
    {
        if (index>=0 && index < this->albumNumberOfSongs)
            return this -> songInLikedSongs[index];
        else throw runtime_error("Index invalid");
    }

    operator string()
    {
        return this->albumName;
    }

    explicit operator string() const
    {
        return this->albumName;
    }

    Album operator +(const Album& obj)
    {
        Album copy = *this;
        copy.albumRating = copy.albumRating + obj.albumRating;
        return copy;
    }

    /// OPERATORUL + cu obiect din alta clasa IN DREAPTA
    Album operator +(float nr)
    {
        Album copy = *this;
        copy.albumRating = copy.albumRating + nr;
        return copy;
    }

    /// OPERATORUL + cu obiect din alta clasa IN STANGA

    friend Album operator +(float nr, Album obj);

    Album operator / (const Album& obj)
    {
        Album copy = *this;
        copy.albumRating = (copy.albumRating + obj.albumRating) / 2.0;
        return copy;
    }

    Album operator / (float nr)
    {
        Album copy = *this;
        copy.albumRating = (copy.albumRating + nr) / 2.0;
        return copy;
    }

    friend Album operator / (float nr, Album obj);

    ~Album() //destructor
    {
        if (this->albumName != NULL)
            delete [] this->albumName;
        if (this->albumArtist != NULL)
            delete [] this->albumArtist;
        if (this->songInLikedSongs != NULL)
            delete [] this->songInLikedSongs;
    }

    void showAllAlbums(string artist);

    void showAllAlbums(int year);
};

Album operator / (float nr, Album obj)
{
    obj.albumRating = (obj.albumRating + nr) / 2.0;
    return obj;
}

Album operator +(float nr, Album obj)
{
    obj.albumRating = obj.albumRating + nr;
    return obj;
}

ostream& operator << (ostream &out, const Album &obj)
{
    out << "Album name: " << obj.albumName << endl;
    out << "Album artist: " << obj.albumArtist << endl;
    out << "Release year: " << obj.releaseYear << endl;
    out << "Number of songs on the album: " << obj.albumNumberOfSongs << endl;
    out << "Album rating: " << obj.albumRating << endl;
    for (int i=0; i<obj.albumNumberOfSongs; i++)
        if(obj.songInLikedSongs[i] == 0)
            out<<"Song number "<<i+1<<" is not in Liked Songs"<<endl;
        else
            out<<"Song number "<<i+1<<" is in Liked Songs"<<endl;
    return out;
}

istream& operator >> (istream &in, Album &obj)
{
    cout << "Album name: ";
    char name[101];
    in.get();
    in.getline(name, 101);
    if (obj.albumName != NULL)
        delete [] obj.albumName;
    obj.albumName = new char[strlen(name) + 1];
    strcpy(obj.albumName, name);

    cout<< "Album artist: ";
    char artist[101];
    in.get();
    in.getline(artist, 101);
    if (obj.albumArtist != NULL)
        delete [] obj.albumArtist;
    obj.albumArtist = new char[strlen(artist) + 1];
    strcpy(obj.albumArtist, artist);

    cout << "Release year: ";
    in >> obj.releaseYear;

    cout << "Number of songs on the album: ";
    in >> obj.albumNumberOfSongs;


    cout << "Album rating: ";
    in >> obj.albumRating;

    if (obj.songInLikedSongs != NULL)
        delete [] obj.songInLikedSongs;

    obj.songInLikedSongs = new int[obj.albumNumberOfSongs];

    cout << "Say if each song is in Liked Songs: ";
    for (int i=0; i<obj.albumNumberOfSongs; i++)
        in>>obj.songInLikedSongs[i];
    return in;
}

Album :: Album() //constructor fara parametri
{
    albumName = new char[strlen("unknown") + 1];
    strcpy(albumName, "unknown");
    albumArtist = new char[strlen("unknown") + 1];
    strcpy(albumArtist, "unknown");
    releaseYear = 1970;
    albumNumberOfSongs = 0;
    albumRating = 0.0;
    songInLikedSongs = NULL;
}

Album :: Album (char* albumName, char *albumArtist, int releaseYear, int albumNumberOfSongs, float albumRating, int* songInLikedSongs):releaseYear(releaseYear), albumNumberOfSongs(albumNumberOfSongs), albumRating(albumRating)
{
    this->albumName = new char[strlen(albumName)+1];
    strcpy(this->albumName, albumName);
    this->albumArtist = new char[strlen(albumArtist)+1];
    strcpy(this->albumArtist, albumArtist);
    this->songInLikedSongs = new int[this->albumNumberOfSongs];
    for (int i = 0; i < albumNumberOfSongs; i++)
        this -> songInLikedSongs[i] = songInLikedSongs[i];
} //constructor cu parametri

Album& Album ::operator = (const Album &obj)
{
    if (this != &obj)
    {
        if(this->albumName != NULL)
            delete [] this->albumName;
        if(this->albumArtist != NULL)
            delete [] this->albumArtist;
        if(this->songInLikedSongs != NULL)
            delete [] this->songInLikedSongs;

        this->albumName = new char[strlen(obj.albumName)+1];
        strcpy(this->albumName, obj.albumName);
        this->albumArtist = new char[strlen(obj.albumArtist)+1];
        strcpy(this->albumArtist, obj.albumArtist);
        this->releaseYear = obj.releaseYear;
        this -> albumNumberOfSongs = obj.albumNumberOfSongs;
        this -> albumRating = obj.albumRating;
        this -> songInLikedSongs = new int [albumNumberOfSongs];
        for (int i=0; i<obj.albumNumberOfSongs; i++)
            this->songInLikedSongs[i] = obj.songInLikedSongs[i];
    }
    return *this;
} //supraincarcare = pentru atribuire

class Queue
{
private:
    queue <Song> songQueue;
    int numberOfSongsInQueue;
    int queueDuration;
    bool isOnRepeat;

public:
    Queue(); //constructor fara parametri

    Queue(queue <Song> songQueue, int numberOfSongsInQueue, int queueDuration, bool isOnRepeat); //constructor cu toti parametrii

    Queue(queue <Song> songQueue, int numberOfSongsInQueue) //constructor cu parametri
    {
        this->songQueue = songQueue;
        this->numberOfSongsInQueue = numberOfSongsInQueue;
    }

    Queue(queue <Song> songQueue, int numberOfSongsInQueue, bool isOnRepeat) //constructor cu parametri
    {
        this->songQueue = songQueue;
        this->numberOfSongsInQueue = numberOfSongsInQueue;
        this->isOnRepeat = isOnRepeat;
    }

    Queue (const Queue& obj) //copy constructor
    {
        this-> songQueue = obj.songQueue;
        this-> numberOfSongsInQueue = obj.numberOfSongsInQueue;
        this-> queueDuration = queueDuration;
        this -> isOnRepeat = isOnRepeat;
    }

    Queue& operator = (const Queue&); //operatorul =

    void Read()
    {
        cout << "How many songs in queue: ";
        cout << endl;

        cin >> this->numberOfSongsInQueue;

        cout << endl;
        cout << "Enter songs in queue: ";
        for (int i=0; i<this->numberOfSongsInQueue; i++)
        {
            Song s;
            cin >> s;
            this->songQueue.push(s);
            this->queueDuration += s.getSongDuration();
        }
        cout << "Is the queue on repeat? \n";
        cin >> this->isOnRepeat;

    }

    void Print()
    {
        cout << "Number of songs in queue: " << this->numberOfSongsInQueue << endl;
        cout << "Songs in queue: \n";
        queue <Song> temp = this->songQueue;
        while(!temp.empty())
        {
            cout << temp.front() << endl;
            temp.pop();
        }
        cout << "Queue duration: " << this->queueDuration << endl;
        cout << "Is the queue on repeat? " << this->isOnRepeat << endl;
    }

    friend istream& operator >> (istream &in, Queue& obj);

    friend ostream& operator << (ostream &out, const Queue& obj);

    Queue& operator ++() //pre
    {
        this->numberOfSongsInQueue++;
        return *this;
    }

    Queue& operator ++(int) //post
    {
        Queue copy = *this;
        ++(*this);
        return copy;
    }

    Queue& operator --() //pre
    {
        this->numberOfSongsInQueue--;
        return *this;
    }

    Queue& operator --(int) //post
    {
        Queue copy = *this;
        --(*this);
        return copy;
    }

    Queue operator + (const Queue& obj) //operatorul + cu doua cozi, in this adaugam coada lui obj
    {
        queue <Song> temp = obj.songQueue;
        while(!temp.empty())
        {
            this->songQueue.push(temp.front());
            temp.pop();
        }
        return *this;
    }

    Queue operator + (int n)
    {
        Queue copy = *this;
        copy.numberOfSongsInQueue += n;
        return copy;
    }

    friend Queue operator +(int n, Queue obj);

    operator long() //cast implicit
    {
        return this->queueDuration;
    }

    explicit operator long() const //cast explicit
    {
        return this->queueDuration;
    }

    string operator [] (int index)
    {
        if (index >= 0 && index < this->numberOfSongsInQueue)
        {
            queue <Song> temp = this->songQueue;
            int numberOfPops = this -> numberOfSongsInQueue - index - 1;
            while(numberOfPops--)
                temp.pop();
            return temp.back();
        }
        else throw runtime_error("Invalid index");
    }

    bool operator < (const Queue &obj)
    {
        return this->numberOfSongsInQueue < obj.numberOfSongsInQueue;
    }

    bool operator == (const Queue &obj)
    {
        return this->numberOfSongsInQueue == obj.numberOfSongsInQueue;
    }

    //getters

    queue <Song> getSongQueue()
    {
        return songQueue;
    }

    int getNumberOfSongsInQueue()
    {
        return numberOfSongsInQueue;
    }

    int getQueueDuration()
    {
        return queueDuration;
    }

    bool getIsOnRepeat()
    {
        return isOnRepeat;
    }

    void setSongQueue (queue <Song> q)
    {
        this->songQueue = q;
    }

    void setNumberOfSongsInQueue (int n)
    {
        this->numberOfSongsInQueue = n;
    }

    void setQueueDuration (int n)
    {
        this->queueDuration = n;
    }

    void setIsOnRepeat (bool ok)
    {
        this->isOnRepeat = ok;
    }

    friend Queue operator + (const Song &obj1, Queue &obj2);
    friend Queue operator + (Queue &obj1, const Song &obj2);
    friend Queue operator + (const Playlist &obj1, Queue &obj2);
    friend Queue operator + (Queue &obj1, const Playlist &obj2);
    ~Queue() = default;
};

Queue :: Queue()
{
    numberOfSongsInQueue = 0;
    queueDuration = 0;
    songQueue;
    isOnRepeat = false;
}

Queue :: Queue(queue <Song> songQueue, int numberOfSongsInQueue, int queueDuration, bool isOnRepeat) : songQueue(songQueue), numberOfSongsInQueue(numberOfSongsInQueue), queueDuration(queueDuration), isOnRepeat(isOnRepeat)
{

}

Queue& Queue :: operator = (const Queue& obj)
{
    if (this != &obj)
    {
        this-> songQueue = obj.songQueue;
        this-> numberOfSongsInQueue = obj.numberOfSongsInQueue;
        this-> queueDuration = queueDuration;
        this-> isOnRepeat = isOnRepeat;
    }
    return *this;
}

ostream& operator << (ostream &out, const Queue& obj)
{
    out << "Number of songs in queue: " << obj.numberOfSongsInQueue << endl;
    out << "Songs in queue: \n";
    queue <Song> temp = obj.songQueue;
    while(!temp.empty())
    {
        out << temp.front() << endl;
        temp.pop();
    }
    out << "Queue duration: " << obj.queueDuration << endl;
    out << "Is the queue on repeat? " << obj.isOnRepeat << endl;
    return out;
}

istream& operator >> (istream &in, Queue& obj)
{
    cout << "How many songs in queue: ";
    cout << endl;

    in >> obj.numberOfSongsInQueue;

    cout << endl;
    cout << "Enter songs in queue: ";
    for (int i=0; i<obj.numberOfSongsInQueue; i++)
    {
        Song s;
        in >> s;
        obj.songQueue.push(s);
        obj.queueDuration += s.getSongDuration();
    }
    cout << "Is the queue on repeat? \n";
    in >> obj.isOnRepeat;
    return in;
}

Queue operator +(int n, Queue obj)
{
    obj.numberOfSongsInQueue += n;
    return obj;
}

int Song::numberOfSongs = 0;

int Artist::numberOfArtists = 0;

//Song + Playlist

Playlist operator + (const Song &obj1, Playlist &obj2)
{
    obj2.songs.push_back(obj1.songTitle);
    obj2.playlistNumberOfSongs++;
    obj2.playlistDuration += obj1.songDuration;
    return obj2;
}

Playlist operator + (Playlist &obj1, const Song &obj2)
{
    obj1.songs.push_back(obj2.songTitle);
    obj1.playlistNumberOfSongs++;
    obj1.playlistDuration += obj2.songDuration;
    return obj1;
}

//Queue + Song

Queue operator + (const Song &obj1, Queue &obj2)
{
    obj2.songQueue.push(obj1);
    return obj2;
}

Queue operator + (Queue &obj1, const Song &obj2)
{
    obj1.songQueue.push(obj2);
    return obj1;
}

vector <Song> songs;
vector <Album> albums;
vector <Artist> artists;
vector <Playlist> playlists;

Queue queue1;


void Song :: showAllSongs (char ch)
{
    int index = 0;
    for (auto i : songs)
    {
        cout << "The songs that start with the letter " << ch << " are: " << endl;
        if (i.firstLetter == ch)
            cout << ++index << ". " << i.songTitle << endl;
    }
    if (index == 0)
        cout << "There are no songs that start with the letter " << ch << endl;
}

void Song :: showAllSongs (int duration)
{
    int index = 0;
    for (auto i : songs)
    {
        cout << "The songs that are less than " << duration/60 << " minutes and " <<duration%60 <<" seconds are: " << endl;
        if (i.songDuration < duration)
            cout << ++index << ". " << i.songTitle << endl;
    }
    if (index == 0)
        cout << "There are no songs that are less than " << duration/60 << " minutes and " <<duration%60 <<" seconds" << endl;

}

void Artist :: showAllArtists (int year)
{
    int index = 0;
    for (auto i : artists)
    {
        cout << "The artists that have debuted before the year " << year << " are: " << endl;
        if (i.debutYear < year)
            cout << ++index << ". " << i.artistName << endl;
    }
    if (index == 0)
        cout << "There are no artists that have debuted before the year " << year << endl;
}

void Artist :: showAllArtists (long numberOfListeners)
{
    int index = 0;
    for (auto i : artists)
    {
        cout << "The artists that have over " << numberOfListeners << " monthly listeners are: " << endl;
        if (i.monthlyListeners > numberOfListeners)
            cout << ++index << ". " << i.artistName << endl;
    }
    if (index == 0)
        cout << "There are no artists that have more than " << numberOfListeners << " monthly listeners" << endl;
}

void Album :: showAllAlbums (int year)
{
    int index = 0;
    for (auto i : albums)
    {
        cout << "The albums that have been released after the year " << year << " are: " << endl;
        if (i.releaseYear > year)
            cout << ++index << ". " << i.albumName << endl;
    }
    if (index == 0)
        cout << "There are no album released after the year " << year << endl;
}

void Album :: showAllAlbums (string artist)
{
    int index = 0;
    for (auto i : albums)
    {
        cout << "The albums that have been released by " << artist << " are: " << endl;
        if (i.albumArtist == artist)
            cout << ++index << ". " << i.albumName << endl;
    }
    if (index == 0)
        cout << "There are no album released by " << artist << endl;
}

void Playlist :: showAllPlaylists (int number)
{
    int index = 0;
    for (auto i : playlists)
    {
        cout << "The playlists that contain " << number << " songs are: " << endl;
        if (i.playlistNumberOfSongs == number)
            cout << ++index << ". " << i.playlistName << endl;
    }
    if (index == 0)
        cout << "There are no playlists that contain " << number << " songs";
}

int main() {
    bool isRunning = 1;
    while (isRunning) {
        cout << "*** Welcome to Music Player! ***";
        cout << endl;
        cout << endl;
        cout << "What would you like to do? \n";
        cout << endl;
        cout << endl;
        cout << "1) Create \n";
        cout << "2) Read \n";
        cout << "3) Update \n";
        cout << "4) Delete \n";
        cout << "5) Start the queue \n";
        cout << endl;
        cout << endl;
        int command1;
        cin >> command1;
        switch (command1) {
            case 1: {
                cout << "What would you like to create? \n";
                cout << endl;
                cout << endl;
                cout << "1) Song \n";
                cout << "2) Artist \n";
                cout << "3) Album \n";
                cout << "4) Playlist \n";
                cout << endl;
                int command2;
                cin >> command2;
                switch (command2) {
                    case 1: {
                        Song s;
                        cin >> s;
                        songs.push_back(s);
                        cout << endl;
                        cout << "Song created! \n";
                        break;
                    }
                    case 2: {
                        Artist art;
                        cin >> art;
                        artists.push_back(art);
                        cout << endl;
                        cout << "Artist created! \n";
                        break;
                    }
                    case 3: {
                        Album alb;
                        cin >> alb;
                        albums.push_back(alb);
                        cout << endl;
                        cout << "Album created! \n";
                        break;

                    }
                    case 4: {
                        Playlist p;
                        cin >> p;
                        playlists.push_back(p);
                        cout << endl;
                        cout << "Playlist created! \n";
                        break;
                    }
                    default: {
                        cout << "Invalid command, please try again.";
                        break;
                    }
                }
                break;
            }
            case 2: {
                cout << "What would you like to see? \n";
                cout << endl;
                cout << endl;
                cout << "1) Song \n";
                cout << "2) Artist \n";
                cout << "3) Album \n";
                cout << "4) Playlist \n";
                cout << endl;
                int command3;
                cin >> command3;
                switch (command3) {
                    case 1: {
                        cout << endl;
                        cout << endl;
                        cout << "Choose an option: \n";
                        cout << "1) View all the songs \n";
                        cout << "2) View all the songs that are shorter than a certain duration \n";
                        cout << "3) View all the songs that start with a certain letter";
                        cout << endl;
                        int command4;
                        cin >> command4;
                        switch (command4) {
                            case 1: {
                                int index = 0;
                                for (auto i: songs)
                                    cout << ++index << ". " << i.getSongTitle() << "-" << i.getSongArtistName() << endl ;
                                if (songs.empty())
                                    cout << "There are no songs registered." << endl;
                                break;
                            }
                            case 2: {
                                Song s;
                                int n;
                                cout << "Enter a duration (in seconds): ";
                                cin >> n;
                                s.showAllSongs(n);
                                break;
                            }
                            case 3: {
                                Song s;
                                char ch;
                                cout << "Enter a letter: ";
                                cin >> ch;
                                s.showAllSongs(ch);
                                break;
                            }
                            default: {
                                cout << "Invalid command, please try again.";
                                break;
                            }
                        }
                        break;
                    }
                    case 2: {
                        cout << endl;
                        cout << endl;
                        cout << "Choose an option: \n";
                        cout << "1) View all the artists \n";
                        cout << "2) View all the artists that have debuted before a certain year \n";
                        cout << "3) View all the artists that have over a certain number of monthly listeners \n";
                        cout << endl;
                        int command4;
                        cin >> command4;
                        switch (command4) {
                            case 1: {
                                int index = 0;
                                for (auto i: artists)
                                    cout << ++index << ". " << i.getArtistName() << endl;
                                if (artists.empty())
                                    cout << "There are no artists registered." << endl;
                                break;
                            }
                            case 2: {
                                Artist art;
                                int n;
                                cout << "Enter a year: ";
                                cin >> n;
                                art.showAllArtists(n);
                                break;
                            }
                            case 3: {
                                Artist art;
                                long n;
                                cout << "Enter a number of monthly listeners: ";
                                cin >> n;
                                art.showAllArtists(n);
                                break;
                            }
                            default: {
                                cout << "Invalid command, please try again.";
                                break;
                            }
                        }
                        break;
                    }
                    case 3: {
                        cout << endl;
                        cout << endl;
                        cout << "Choose an option: \n";
                        cout << "1) View all the albums \n";
                        cout << "2) View all the albums released after a certain year \n";
                        cout << "3) View all the albums that have been released by a certain artist \n";
                        cout << endl;
                        int command4;
                        cin >> command4;
                        switch (command4) {
                            case 1: {
                                int index = 0;
                                for (auto i: albums)
                                    cout << ++index << ". " << i.getAlbumName() << endl;
                                if (albums.empty())
                                    cout << "There are no albums registered." << endl;
                                break;
                            }
                            case 2: {
                                Album alb;
                                int n;
                                cout << "Enter a year: ";
                                cin >> n;
                                alb.showAllAlbums(n);
                                break;
                            }
                            case 3: {
                                Album alb;
                                string name;
                                cout << "Enter an artist: ";
                                cin.get();
                                getline(cin, name);
                                alb.showAllAlbums(name);
                                break;
                            }
                            default: {
                                cout << "Invalid command, please try again.";
                                break;
                            }
                        }
                        break;
                    }
                    case 4: {
                        cout << endl;
                        cout << endl;
                        cout << "Choose an option: \n";
                        cout << "1) View all the playlists \n";
                        cout << "2) View all the playlists with a certain amount of songs \n";
                        cout << endl;
                        int command4;
                        cin >> command4;
                        switch (command4) {
                            case 1: {
                                int index = 0;
                                if (playlists.empty())
                                    cout << "There are no playlists registered." << endl;
                                for (auto i: playlists) {
                                    cout << ++index << ". " << i.getPlaylistName() << endl;
                                    vector <string> copySongs = i.getSongs();
                                    for (auto j : copySongs) {
                                        cout << "//" << j << endl;
                                    }
                                }
                                break;
                            }
                            case 2: {
                                Playlist P;
                                int n;
                                cout << "Enter a number of songs: ";
                                cin >> n;
                                P.showAllPlaylists(n);
                                break;
                            }
                            default: {
                                cout << "Invalid command, please try again.";
                                break;
                            }
                        }
                        break;
                    }
                    default: {
                        cout << "Invalid command, please try again.";
                        break;
                    }
                }
                break;
            }
            case 3: {
                cout << "You can update your playlist using the following options: \n";
                cout << "1) Make a new playlist using two songs \n";
                cout << "2) Merge two existing playlists together \n";
                cout << "3) Add a new song in an existing playlist \n";
                cout << endl;
                int command;
                cin >> command;
                switch (command) {
                    case 1: {
                        Song s1, s2;
                        cout << "Enter the songs: \n";
                        cin >> s1;
                        cout << endl;
                        cin >> s2;
                        Playlist P1 = s1 + s2;
                        P1.setPlaylistName("New playlist");
                        playlists.push_back(P1);
                        cout << endl;
                        cout << "Playlist added! \n";
                        break;
                    }
                    case 2: {
                        if (playlists.size() < 2)
                        {
                            cout << "Invalid action, not enough playlists" << endl;
                            break;
                        }
                        Playlist p1, p2, P;
                        string name1, name2;
                        cout << "Enter the playlists' names: \n";
                        cin.get();
                        getline(cin, name1);
                        cin.get();
                        getline(cin, name2);
                        for (auto i: playlists) {
                            if (i.getPlaylistName() == name1)
                                for (auto j: playlists)
                                    if (j.getPlaylistName() == name2) {
                                        P = i + j;
                                        P.setPlaylistName("new_playlist");
                                        playlists.push_back(P);
                                        break;
                                    }
                        }
                        break;
                    }
                    case 3: {
                        if (playlists.size() < 1)
                        {
                            cout << "Invalid action, not enough playlists" << endl;
                            break;
                        }
                        Song s;
                        Playlist newPlaylist;
                        string playlistName;
                        cout << "Enter song\n";
                        cin >> s;

                        cout << "Enter playlist name: \n";
                        cin.get();
                        getline(cin, playlistName);

                        for (auto i : playlists)
                        {
                            if (i.getPlaylistName() == playlistName) {
                                newPlaylist = i + s;
                                playlists.push_back(newPlaylist);
                                break;
                            }
                        }
                        break;
                    }
                    default: {
                        cout << "Invalid command, please try again.";
                        break;
                    }
                }
                break;
            }
            case 4: {
                cout << endl;
                cout << endl;
                cout << "Where do you want to delete from? \n";
                cout << "1) Songs \n";
                cout << "2) Artists \n";
                cout << "3) Albums \n";
                cout << "4) Playlists \n";
                cout << endl;
                int command;
                cin >> command;
                switch (command)
                {
                    case 1:
                    {
                        if (songs.empty())
                        {
                            cout << "Already empty! " << endl;
                            break;
                        }
                        songs.pop_back();
                        cout << "The most recently added song was deleted. \n";
                        break;
                    }
                    case 2:
                    {
                        if (artists.empty())
                        {
                            cout << "Already empty! " << endl;
                            break;
                        }
                        artists.pop_back();
                        cout << "The most recently added artist was deleted. \n";
                        break;
                    }
                    case 3:
                    {
                        if (albums.empty())
                        {
                            cout << "Already empty! " << endl;
                            break;
                        }
                        albums.pop_back();
                        cout << "The most recently added album was deleted. \n";
                        break;
                    }
                    case 4:
                    {
                        if (playlists.empty())
                        {
                            cout << "Already empty! " << endl;
                            break;
                        }
                        playlists.pop_back();
                        cout << "The most recently added playlist was deleted. \n";
                        break;
                    }
                    default: {
                        cout << "Invalid command, please try again.";
                        break;
                    }
                }
                break;
            }
            case 5:
            {
                cout << "Select options: \n";
                cout << "1) Play a song ahead of the queue \n";
                cout << "2) Show what song is playing \n";
                cout << "3) Next song \n";
                cout << "4) Set queue on repeat \n";
                cout << "5) Empty queue \n";
                cout << endl;
                cin >> command1;
                switch (command1)
                {
                    case 1:
                    {
                        cout << "Input a song: \n";
                        string name;
                        cin.get();
                        getline(cin, name);
                        bool ok = 0;
                        for (auto i : songs)
                        {
                            if (i.getSongTitle() == name)
                            {
                                queue <Song> temp = queue1.getSongQueue();
                                temp.push(i);
                                queue1.setSongQueue(temp);
                                ok = 1;
                                break;
                            }
                        }
                        if (ok == 0)
                        {
                            cout << "Song is not registered \n";
                            break;
                        }
                        break;
                    }
                    case 2:
                    {
                        queue <Song> temp = queue1.getSongQueue();
                        Song currentSong = temp.front();
                        cout << "Now playing: \n";
                        cout << currentSong.getSongTitle()  << " - " << currentSong.getSongArtistName() << " " << currentSong.getSongDuration()/60 << ":" << currentSong.getSongDuration()%60 << endl;
                        break;
                    }
                    case 3:
                    {
                        queue <Song> temp = queue1.getSongQueue();
                        temp.pop();
                        queue1.setSongQueue(temp);
                        break;
                    }
                    case 4:
                    {
                        queue1.setIsOnRepeat(1);
                        break;
                    }
                    case 5:
                    {
                        queue <Song> temp = queue1.getSongQueue();
                        temp.empty();
                        queue1.setSongQueue(temp);
                        break;
                    }
                    default:
                    {
                        cout << "Invalid command, please try again.";
                        break;
                    }
                }
                break;
            }
            default: {
                cout << "Invalid command, please try again.";
                break;
            }
        }

    }
    return 0;
}

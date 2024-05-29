#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <map>
#include <set>

using namespace std;

//clasa abstracta: IOInterface, User
//clase: Song, User, Listener, StudentListener, Artist, Album, Playlist
//Queue trebuie sa fie list din STL
//clasa template - data container manager cu metode de search si sort in clasele care permit asta din punct de vedere al logicii (Artist, Album, Playlist)
//singleton
//vector, list, set, map

//in fiecare clasa:
//constructor cu parametri
//constructor fara parametri
//constructor de copiere
//operatorul =
//operatorul de citire
//operatorul de afisare
//destructor

class Playlist;
class Album;
class Song;
class User;
class Artist;
class Listener;
class StudentListener;


//map: metadata cu id si Song; caching recently played songs; media controls

class IOInterface
{
public:
    virtual void read(istream&) = 0;
    virtual void print(ostream&) const = 0;
};

class Song : public IOInterface{
private:
    string title;
    string artist;
    string album;
    string genre;
    int duration;
    bool isLiked;
    bool isExplicit;
public:
    Song(string title, string artist, string album, int duration, bool isLiked, bool isExplicit);
    Song();
    Song(const Song &song);

    Song& operator = (const Song &song);
    const bool operator < (const Song &song) const;

    friend istream& operator >> (istream &in, Song &song);
    friend ostream& operator << (ostream &out, const Song &song);

    void read(istream &in);
    void print(ostream &out) const;

    string getTitle() const
    {
        return title;
    }

    string getArtist() const
    {
        return artist;
    }

    string getAlbum() const
    {
        return album;
    }

    string getGenre() const
    {
        return genre;
    }

    int getDuration() const
    {
        return duration;
    }

    bool getIsLiked() const
    {
        return isLiked;
    }

    bool getIsExplicit() const
    {
        return isExplicit;
    }

    void setTitle(string title)
    {
        this->title = title;
    }

    void setArtist(string artist)
    {
        this->artist = artist;
    }

    void setAlbum(string album)
    {
        this->album = album;
    }

    void setGenre(string genre)
    {
        this->genre = genre;
    }

    void setDuration(int duration)
    {
        this->duration = duration;
    }

    void setIsLiked(bool isLiked)
    {
        this->isLiked = isLiked;
    }

    void setIsExplicit(bool isExplicit)
    {
        this->isExplicit = isExplicit;
    }

    ~Song() = default;
};

Song::Song()
{
    title = "unknown";
    artist = "unknown";
    album = "unknown";
    genre = "unknown";
    duration = 0;
    isLiked = 0;
    isExplicit = 0;
}

Song::Song(string title, string artist, string album, int duration, bool isLiked, bool isExplicit):title(title), artist(artist), album(album), duration(duration), isLiked(isLiked), isExplicit(isExplicit)
{

}

Song::Song(const Song &song)
{
    this->title = song.title;
    this->artist = song.artist;
    this->album = song.album;
    this->duration = song.duration;
    this->isLiked = song.isLiked;
    this->isExplicit = song.isExplicit;
}

Song& Song::operator = (const Song &song)
{
    this->title = song.title;
    this->artist = song.artist;
    this->album = song.album;
    this->duration = song.duration;
    this->isLiked = song.isLiked;
    this->isExplicit = song.isExplicit;
    return *this;
}

const bool Song::operator < (const Song &song) const
{
    return this->title < song.title;
}

void Song::read(istream &in)
{
    cout << "Title: ";
    in >> title;
    cout << "Artist: ";
    in >> artist;
    cout << "Album: ";
    in >> album;
    cout << "Duration: ";
    in >> duration;
    cout << "Is the song in the 'Liked Songs' playlist? (1/0): ";
    in >> isLiked;
    cout << "Is the song explicit? (1/0): ";
    in >> isExplicit;
}

void Song::print(ostream &out) const
{
    out << "Title: " << title << endl;
    out << "Artist: " << artist << endl;
    out << "Album: " << album << endl;
    out << "Duration: " << duration << endl;
    out << "Is the song in the 'Liked Songs' playlist?: " << endl;
    if (isLiked == 1)
    {
        out << "Yes" << endl;
    }
    else
    {
        out << "No" << endl;
    }
    out << "Is the song explicit?" << endl;
    if (isExplicit == 1)
    {
        out << "Yes" << endl;
    }
    else
    {
        out << "No" << endl;
    }
}

istream& operator >> (istream &in, Song &song)
{
    song.read(in);
    return in;
}

ostream& operator << (ostream &out, const Song &song)
{
    song.print(out);
    return out;
}

class Playlist : public IOInterface
{
private:
    string name;
    string creator;
    int numberOfSongs;
    set <Song> songs;
public:
    Playlist();
    Playlist(string name, string creator, int numberOfSongs, set <Song> songs);
    Playlist(const Playlist &obj);

    Playlist& operator = (const Playlist &obj);

    void read(istream &in);
    void print(ostream &out) const;

    friend istream& operator >> (istream &in, Playlist &obj);
    friend ostream& operator << (ostream &out, const Playlist &obj);

    void setName(string name)
    {
        this->name = name;
    }

    void setCreator(string creator)
    {
        this->creator = creator;
    }

    void setNumberOfSongs(int numberOfSongs)
    {
        this->numberOfSongs = numberOfSongs;
    }

    void setSongs(set <Song> songs)
    {
        this->songs = songs;
    }

    string getName() const
    {
        return name;
    }

    string getCreator() const
    {
        return creator;
    }

    int getNumberOfSongs() const
    {
        return numberOfSongs;
    }

    set <Song> getSongs() const
    {
        return songs;
    }

    ~Playlist() = default;
};

Playlist::Playlist(string name, string creator, int numberOfSongs, set <Song> songs): name(name), creator(creator), numberOfSongs(numberOfSongs), songs(songs)
{

}

Playlist::Playlist()
{
    name = "unknown";
    creator = "unknown";
    numberOfSongs = 0;
}

Playlist::Playlist(const Playlist &obj)
{
    this->name = obj.name;
    this->creator = obj.creator;
    this->numberOfSongs = obj.numberOfSongs;
    this->songs = obj.songs;
}

Playlist& Playlist::operator = (const Playlist &obj)
{
    if (this != &obj)
    {
        this->name = obj.name;
        this->creator = obj.creator;
        this->numberOfSongs = obj.numberOfSongs;
        this->songs = obj.songs;
    }
    return *this;
}

void Playlist::read(istream &in)
{
    cout << "Name: ";
    in >> name;
    cout << "Creator: ";
    in >> creator;
    cout << "Number of songs: ";
    in >> numberOfSongs;
    cout << "Songs: " << endl;
    for (int i = 0; i < numberOfSongs; i++)
    {

        Song song;
        in >> song;
        songs.insert(song);
    }
}

void Playlist::print(ostream &out) const
{
    out << "Name: " << name << endl;
    out << "Creator: " << creator << endl;
    out << "Number of songs: " << numberOfSongs << endl;
    out << "Songs: " << endl;
    int i = 1;
    for (auto it = songs.begin(); it != songs.end(); it++)
    {
        out << i++ << ". " << *it << endl;
    }
}

istream& operator >> (istream &in, Playlist &obj)
{
    obj.read(in);
    return in;
}

ostream& operator << (ostream &out, const Playlist &obj)
{
    obj.print(out);
    return out;
}

class User : public IOInterface
{
protected:
    string username;
    string password;
    string email;
    string country;

public:
    User();
    User(string username, string password, string email, string country);
    User(const User &obj);

    User& operator = (const User &obj);

    friend istream& operator >> (istream &in, User &obj);
    friend ostream& operator << (ostream &out, const User &obj);

    virtual void read(istream &in);
    virtual void print(ostream &out) const;

    virtual ~User() = default;

    virtual string getUsername() const = 0;
    virtual string getPassword() const = 0;
    virtual string getEmail() const = 0;
    virtual string getCountry() const = 0;

    virtual void setUsername(string username) = 0;
    virtual void setPassword(string password) = 0;
    virtual void setEmail(string email) = 0;
    virtual void setCountry(string country) = 0;
};

//constructorul cu parametri
User::User(string username, string password, string email, string country): username(username), password(password), email(email), country(country)
{
}

//constructorul fara parametri
User::User()
{
    username = "unknown";
    password = "unknown";
    email = "unknown";
    country = "unknown";
}

//copy constructor
User::User(const User &obj)
{
    this->username = obj.username;
    this->password = obj.password;
    this->email = obj.email;
    this->country = obj.country;
}

//operatorul =
User& User::operator = (const User &obj)
{
    if (this != &obj)
    {
        this->username = obj.username;
        this->password = obj.password;
        this->email = obj.email;
        this->country = obj.country;
    }
    return *this;
}

//functia de citire
void User::read(istream &in)
{
    cout << "Username: ";
    in >> username;
    cout << "Password: ";
    in >> password;
    cout << "Email: ";
    in >> email;
    cout << "Country: ";
    in >> country;
}

//functia de afisare
void User::print(ostream &out) const
{
    cout << "Username: ";
    out << username << endl;
    cout << "Password: " ;
    out << password << endl;
    cout << "Email: " ;
    out << email << endl;
    cout << "Country: " ;
    out  << country << endl;
}

//operatorul >>
istream &operator >> (istream &in, User &obj)
{
    obj.read(in);
    return in;
}

//operatorul <<
ostream &operator << (ostream &out, const User &obj)
{
    obj.print(out);
    return out;
}


////

class Listener : virtual public User{
protected:
    int age;
    int numberOfPlaylists;
    vector <Playlist> playlists;
    int numberOfLikedSongs;
    set <Song> likedSongs;
public:
    Listener();
    Listener(string username, string password, string email, string country, int age, int numberOfPlaylists, vector <Playlist> playlists, int numberOfLikedSongs, set <Song> likedSongs);
    Listener(const Listener &obj);

    Listener& operator = (const Listener &obj);

    void read(istream &in);
    void print(ostream &out) const;

    string getUsername() const override
    {
        return username;
    }

    string getPassword() const override
    {
        return password;
    }

    string getEmail() const override
    {
        return email;
    }

    string getCountry() const override
    {
        return country;
    }

    int getAge() const
    {
        return age;
    }

    int getNumberOfPlaylists() const
    {
        return numberOfPlaylists;
    }

    vector <Playlist> getPlaylists() const
    {
        return playlists;
    }

    int getNumberOfLikedSongs() const
    {
        return numberOfLikedSongs;
    }

    set <Song> getLikedSongs() const
    {
        return likedSongs;
    }

    void setUsername(string username) override
    {
        this->username = username;
    }

    void setPassword(string password) override
    {
        this->password = password;
    }

    void setEmail(string email) override
    {
        this->email = email;
    }

    void setCountry(string country) override
    {
        this->country = country;
    }

    void setAge(int age)
    {
        this->age = age;
    }

    void setNumberOfPlaylists(int numberOfPlaylists)
    {
        this->numberOfPlaylists = numberOfPlaylists;
    }

    void setPlaylists(vector <Playlist> playlists)
    {
        this->playlists = playlists;
    }

    void setNumberOfLikedSongs(int numberOfLikedSongs)
    {
        this->numberOfLikedSongs = numberOfLikedSongs;
    }

    void setLikedSongs(set <Song> likedSongs)
    {
        this->likedSongs = likedSongs;
    }


    virtual ~Listener() = default;

};

Listener::Listener(string username, string password, string email, string country, int age, int numberOfPlaylists, vector <Playlist> playlists, int numberOfLikedSongs, set <Song> likedSongs) : User(username, password, email, country), age(age), numberOfPlaylists(numberOfPlaylists), playlists(playlists), likedSongs(likedSongs)
{

}

Listener::Listener() : User()
{
    age = 0;
    numberOfPlaylists = 0;
    numberOfLikedSongs = 0;
}

Listener::Listener(const Listener &obj)
{
    User :: operator = (obj);
    this->age = obj.age;
    this->numberOfPlaylists = obj.numberOfPlaylists;
    this->playlists = obj.playlists;
    this->numberOfLikedSongs = obj.numberOfLikedSongs;
    this->likedSongs = obj.likedSongs;
}

Listener& Listener::operator = (const Listener &obj)
{
    if (this != &obj)
    {
        User :: operator = (obj);
        this->age = obj.age;
        this->numberOfPlaylists = obj.numberOfPlaylists;
        this->playlists = obj.playlists;
        this->numberOfLikedSongs = obj.numberOfLikedSongs;
        this->likedSongs = obj.likedSongs;
    }
    return *this;
}

void Listener::read(istream &in)
{
    User::read(in);
    cout << "Age: ";
    in >> age;
    cout << "Number of playlists: ";
    in >> numberOfPlaylists;
    cout << "Playlists: " << endl;
    for (int i = 0; i < numberOfPlaylists; i++)
    {
        Playlist playlist;
        in >> playlist;
        playlists.push_back(playlist);
    }
    cout << "Number of liked songs: ";
    in >> numberOfLikedSongs;
    cout << "Liked songs: " << endl;
    for (int i = 0; i < numberOfLikedSongs; i++)
    {
        Song song;
        in >> song;
        likedSongs.insert(song);
    }
}

void Listener::print(ostream &out) const
{
    User::print(out);
    out << "Age: " << age << endl;
    out << "Number of playlists: " << numberOfPlaylists << endl;
    out << "Playlists: " << endl;
    for (int i = 0; i < numberOfPlaylists; i++)
    {
        out << i+1 << ". " << playlists[i] << endl;
    }
    out << "Number of liked songs: " << likedSongs.size() << endl;
    out << "Liked songs: " << endl;
    int i = 1;
    for (auto it = likedSongs.begin(); it != likedSongs.end(); it++)
    {
        out << i++ << ". " << *it << endl;
    }
}


class StudentListener : public Listener{
private:
    string university;
    int graduationYear;
public:
    StudentListener();
    StudentListener(string username, string password, string email, string country, int age, int numberOfPlaylists, vector <Playlist> playlists, int numberOfLikedSongs, set <Song> likedSongs, string university, int graduationYear);
    StudentListener(const StudentListener &obj);

    StudentListener& operator = (const StudentListener &obj);

    void read(istream &in);
    void print(ostream &out) const;

    string getUniversity() const
    {
        return university;
    }

    int getGraduationYear() const
    {
        return graduationYear;
    }

    void setUniversity(string university)
    {
        this->university = university;
    }

    void setGraduationYear(int graduationYear)
    {
        this->graduationYear = graduationYear;
    }

    ~StudentListener() = default;
};

StudentListener::StudentListener(string username, string password, string email, string country, int age, int numberOfPlaylists, vector <Playlist> playlists, int numberOfLikedSongs, set <Song> likedSongs, string university, int graduationYear) : User(username, password, email, country), Listener(username, password, email, country, age, numberOfPlaylists, playlists, numberOfLikedSongs, likedSongs), university(university), graduationYear(graduationYear)
{

}

StudentListener::StudentListener() : User(), Listener()
{
    university = "unknown";
    graduationYear = 0;
}

StudentListener::StudentListener(const StudentListener &obj)
{
    User :: operator = (obj);
    Listener :: operator = (obj);
    this->university = obj.university;
    this->graduationYear = obj.graduationYear;
}

StudentListener& StudentListener::operator = (const StudentListener &obj)
{
    if (this != &obj)
    {
        User :: operator = (obj);
        Listener :: operator = (obj);
        this->university = obj.university;
        this->graduationYear = obj.graduationYear;
    }
    return *this;
}

void StudentListener::read(istream &in)
{
    Listener::read(in);
    cout << "University: ";
    in >> university;
    cout << "Graduation year: ";
    in >> graduationYear;
}

void StudentListener::print(ostream &out) const
{
    Listener::print(out);
    out << "University: " << university << endl;
    out << "Graduation year: " << graduationYear << endl;
}

class Album : public IOInterface
{
private:
    string title;
    string artist;
    string genre;
    int releaseYear;
    int numberOfSongs;
    set <Song> songs;
public:
    Album();
    Album(string title, string artist, string genre, int releaseYear, int numberOfSongs, set <Song> songs);
    Album(const Album &obj);

    Album& operator = (const Album &obj);
    const bool operator < (const Album &obj) const;

    void read(istream &in);
    void print(ostream &out) const;

    friend istream& operator >> (istream &in, Album &obj);
    friend ostream& operator << (ostream &out, const Album &obj);

    void setTitle(string title)
    {
        this->title = title;
    }

    void setArtist(string artist)
    {
        this->artist = artist;
    }

    void setGenre(string genre)
    {
        this->genre = genre;
    }

    void setReleaseYear(int releaseYear)
    {
        this->releaseYear = releaseYear;
    }

    void setNumberOfSongs(int numberOfSongs)
    {
        this->numberOfSongs = numberOfSongs;
    }

    void setSongs(set <Song> songs)
    {
        this->songs = songs;
    }

    string getTitle() const
    {
        return title;
    }

    string getArtist() const
    {
        return artist;
    }

    string getGenre() const
    {
        return genre;
    }

    int getReleaseYear() const
    {
        return releaseYear;
    }

    int getNumberOfSongs() const
    {
        return numberOfSongs;
    }

    set <Song> getSongs() const
    {
        return songs;
    }

    ~Album() = default;
};

Album::Album(string title, string artist, string genre, int releaseYear, int numberOfSongs, set <Song> songs): title(title), artist(artist), genre(genre), releaseYear(releaseYear), numberOfSongs(numberOfSongs), songs(songs)
{

}

Album::Album()
{
    title = "unknown";
    artist = "unknown";
    genre = "unknown";
    releaseYear = 0;
    numberOfSongs = 0;
}

Album::Album(const Album &obj)
{
    this->title = obj.title;
    this->artist = obj.artist;
    this->genre = obj.genre;
    this->releaseYear = obj.releaseYear;
    this->numberOfSongs = obj.numberOfSongs;
    this->songs = obj.songs;
}

Album& Album::operator = (const Album &obj)
{
    if (this != &obj)
    {
        this->title = obj.title;
        this->artist = obj.artist;
        this->genre = obj.genre;
        this->releaseYear = obj.releaseYear;
        this->numberOfSongs = obj.numberOfSongs;
        this->songs = obj.songs;
    }
    return *this;
}

const bool Album::operator < (const Album &obj) const
{
    return this->title < obj.title;
}

void Album::read(istream &in)
{
    cout << "Title: ";
    in >> title;
    cout << "Artist: ";
    in >> artist;
    cout << "Genre: ";
    in >> genre;
    cout << "Release year: ";
    in >> releaseYear;
    cout << "Number of songs: ";
    in >> numberOfSongs;
    cout << "Songs: " << endl;
    for (int i = 0; i < numberOfSongs; i++)
    {
        Song song;
        in >> song;
        songs.insert(song);
    }
}

void Album::print(ostream &out) const
{
    out << "Title: " << title << endl;
    out << "Artist: " << artist << endl;
    out << "Genre: " << genre << endl;
    out << "Release year: " << releaseYear << endl;
    out << "Number of songs: " << numberOfSongs << endl;
    out << "Songs: " << endl;
    int i = 1;
    for (auto it = songs.begin(); it != songs.end(); it++)
    {
        out << i++ << ". " << *it << endl;
    }
}

istream& operator >> (istream &in, Album &obj)
{
    obj.read(in);
    return in;
}

ostream& operator << (ostream &out, const Album &obj)
{
    obj.print(out);
    return out;
}


class Artist : virtual public User{
private:
    string name;
    int debutYear;
    int numberOfAlbums;
    int monthlyListeners;
    set <Album> albums;

public:
    Artist();
    Artist(string username, string password, string email, string country, string name, int debutYear, int numberOfAlbums, int monthlyListeners, set <Album> albums);
    Artist(const Artist &obj);

    Artist& operator = (const Artist &obj);

    void read(istream &in);
    void print(ostream &out) const;

    string getUsername() const override
    {
        return username;
    }

    string getPassword() const override
    {
        return password;
    }

    string getEmail() const override
    {
        return email;
    }

    string getCountry() const override
    {
        return country;
    }

    string getName() const
    {
        return name;
    }

    int getDebutYear() const
    {
        return debutYear;
    }

    int getNumberOfAlbums() const
    {
        return numberOfAlbums;
    }

    int getMonthlyListeners() const
    {
        return monthlyListeners;
    }

    set <Album> getAlbums() const
    {
        return albums;
    }

    void setUsername(string username) override
    {
        this->username = username;
    }

    void setPassword(string password) override
    {
        this->password = password;
    }

    void setEmail(string email) override
    {
        this->email = email;
    }

    void setCountry(string country) override
    {
        this->country = country;
    }

    void setName(string name)
    {
        this->name = name;
    }

    void setDebutYear(int debutYear)
    {
        this->debutYear = debutYear;
    }

    void setNumberOfAlbums(int numberOfAlbums)
    {
        this->numberOfAlbums = numberOfAlbums;
    }

    void setMonthlyListeners(int monthlyListeners)
    {
        this->monthlyListeners = monthlyListeners;
    }

    void setAlbums(set <Album> albums)
    {
        this->albums = albums;
    }

    virtual ~Artist() = default;
};

Artist::Artist(string username, string password, string email, string country, string name, int debutYear, int numberOfAlbums, int monthlyListeners, set <Album> albums) : User(username, password, email, country), name(name), debutYear(debutYear), numberOfAlbums(numberOfAlbums), monthlyListeners(monthlyListeners), albums(albums)
{

}

Artist::Artist() : User()
{
    name = "unknown";
    debutYear = 0;
    numberOfAlbums = 0;
    monthlyListeners = 0;
}

Artist::Artist(const Artist &obj)
{
    User :: operator = (obj);
    this->name = obj.name;
    this->debutYear = obj.debutYear;
    this->numberOfAlbums = obj.numberOfAlbums;
    this->monthlyListeners = obj.monthlyListeners;
    this->albums = obj.albums;
}

Artist& Artist::operator = (const Artist &obj)
{
    if (this != &obj)
    {
        User :: operator = (obj);
        this->name = obj.name;
        this->debutYear = obj.debutYear;
        this->numberOfAlbums = obj.numberOfAlbums;
        this->monthlyListeners = obj.monthlyListeners;
        this->albums = obj.albums;
    }
    return *this;
}

void Artist::read(istream &in)
{
    User::read(in);
    cout << "Name: ";
    in >> name;
    cout << "Debut year: ";
    in >> debutYear;
    cout << "Number of albums: ";
    in >> numberOfAlbums;
    cout << "Albums: " << endl;
    for (int i = 0; i < numberOfAlbums; i++)
    {
        Album album;
        in >> album;
        albums.insert(album);
    }
    cout << "Monthly listeners: ";
    in >> monthlyListeners;
}

void Artist::print(ostream &out) const
{
    User::print(out);
    out << "Name: " << name << endl;
    out << "Debut year: " << debutYear << endl;
    out << "Number of albums: " << numberOfAlbums << endl;
    out << "Albums: " << endl;
    int i = 1;
    for (auto it = albums.begin(); it != albums.end(); it++)
    {
        out << i++ << ". " << *it << endl;
    }
    out << "Monthly listeners: " << monthlyListeners << endl;
}

////template

template <typename T>
class DataManager
{
private:
    set <T> items;
public:
    void addItem(const T& item)
    {
        items.insert(item);
    }

    void removeItem(const T& item)
    {
        items.erase(item);
    }

    void searchItem(const T& item)
    {
        auto it = items.find(item);
        if (it != items.end())
        {
            cout << "Item found!" << endl;
        }
        else
        {
            cout << "Item not found!" << endl;
        }
    }

    void getItem(int index) const{
        if (index >= 0 && index < items.size())
        {
            return items[index];
        }
        else
        {
            cout << "Index out of bounds!" << endl; //DE FACUT O EXCEPTIE
        }
    }

    //sortare in functie de nume, artist, gen;

    void sortItemsName()
    {
        for (auto it = items.begin(); it != items.end(); it++)
        {
            for (auto it2 = it+1; it2 != items.end(); it2++)
            {
                if (it->getTitle() < it2->getTitle())
                {
                    swap(*it, *it2);
                }
            }
        }
    }

    void sortItemsArtist()
    {
        for (auto it = items.begin(); it != items.end(); it++)
        {
            for (auto it2 = it+1; it2 != items.end(); it2++)
            {
                if (it->getArtist() < it2->getArtist())
                {
                    swap(*it, *it2);
                }
            }
        }
    }

    void sortItemsGenre()
    {

        for (auto it = items.begin(); it != items.end(); it++)
        {
            for (auto it2 = it+1; it2 != items.end(); it2++)
            {
                if (it->getGenre() < it2->getGenre())
                {
                    swap(*it, *it2);
                }
            }
        }
    }

};

//clasa Singleton
class MusicPlayer
{
private:
    list <Song> queue;
    map <int, Song> recentlyPlayed;
    vector <User*> users;
    static MusicPlayer* instance;
    MusicPlayer() = default;
    MusicPlayer(const MusicPlayer&) = delete; //pentru a preveni instantierea obiectului de tip singleton de mai multe ori
    MusicPlayer& operator = (const MusicPlayer&) = delete;
public:

    //de implementat urmatoarele metode:

    //listener si student listener:

    //adaugare melodie in playlist
    //schimbare tipul de abonament
    //adaugare melodie in liked songs
    //creare playlist
    //adaugare melodie si playlist in queue
    //adaugare melodie in recently played
    //schimbare detalii cont
    //stergere cont
    //start queue

    //artist:
    //adaugare album
    //afisare venit in functie de monthly listeners
    //afisare toate albumele
    //afisare toate melodiile dintr-un album
    //schimbare detalii cont
    //stergere cont

    static MusicPlayer* getInstance()
    {
        if (MusicPlayer::instance != NULL)
        {
            return MusicPlayer::instance;
        }
        else
        {
            instance = new MusicPlayer();
            return instance;
        }
    }

    string getUserUsername(int i) const
    {
        return this->users[i]->getUsername();
    }

    string getUserPassword(int i) const
    {
        return this->users[i]->getPassword();
    }

    string getUserEmail(int i) const
    {
        return this->users[i]->getEmail();
    }

    string getUserCountry(int i) const
    {
        return this->users[i]->getCountry();
    }

    void setUserUsername(int i, string username)
    {
        this->users[i]->setUsername(username);
    }

    void setUserPassword(int i, string password)
    {
        this->users[i]->setPassword(password);
    }

    void setUserEmail(int i, string email)
    {
        this->users[i]->setEmail(email);
    }

    void setUserCountry(int i, string country)
    {
        this->users[i]->setCountry(country);
    }

    void addSongToPlaylist (int i, Song song)
    {
        if(typeid(*users[i])==typeid(Listener))
        {
            Listener* listener = dynamic_cast<Listener*>(users[i]);
            vector <Playlist> aux = listener->getPlaylists();
            cout << "Select the playlist you want to add the song to: " << endl;
            for (int i = 0; i < aux.size(); i++)
            {
                cout << i+1 << ". " << aux[i].getName() << endl;
            }
            cout << "Your option: ";
            int option;
            cin >> option;
            aux[option-1].setNumberOfSongs(aux[option-1].getNumberOfSongs()+1);
            aux[option-1].getSongs().insert(song);
            listener->setPlaylists(aux);
        }
        if(typeid(*users[i])==typeid(StudentListener))
        {
            StudentListener* studentListener = dynamic_cast<StudentListener*>(users[i]);
            vector <Playlist> aux = studentListener->getPlaylists();
            cout << "Select the playlist you want to add the song to: " << endl;
            for (int i = 0; i < aux.size(); i++)
            {
                cout << i+1 << ". " << aux[i].getName() << endl;
            }
            cout << "Your option: ";
            int option;
            cin >> option;
            aux[option-1].setNumberOfSongs(aux[option-1].getNumberOfSongs()+1);
            aux[option-1].getSongs().insert(song);
            studentListener->setPlaylists(aux);
        }
    }

    void addSongToLikedSongs(int i, Song song)
    {
        if(typeid(*users[i])==typeid(Listener))
        {
            Listener* listener = dynamic_cast<Listener*>(users[i]);
            set <Song> aux = listener->getLikedSongs();
            aux.insert(song);
            listener->setLikedSongs(aux);
        }
        if(typeid(*users[i])==typeid(StudentListener))
        {
            StudentListener* studentListener = dynamic_cast<StudentListener*>(users[i]);
            set <Song> aux = studentListener->getLikedSongs();
            aux.insert(song);
            studentListener->setLikedSongs(aux);
        }
    }

    void createPlaylist(int i)
    {
        if(typeid(*users[i])==typeid(Listener))
        {
            Listener* listener = dynamic_cast<Listener*>(users[i]);
            vector <Playlist> aux = listener->getPlaylists();
            Playlist playlist;
            cin >> playlist;
            aux.push_back(playlist);
            listener->setPlaylists(aux);
        }
        if(typeid(*users[i])==typeid(StudentListener))
        {
            StudentListener* studentListener = dynamic_cast<StudentListener*>(users[i]);
            vector <Playlist> aux = studentListener->getPlaylists();
            Playlist playlist;
            cin >> playlist;
            aux.push_back(playlist);
            studentListener->setPlaylists(aux);
        }
    }

    void startQueue()
    {
        try
        {
            //daca coada nu este goala, se afiseaza melodia curenta cu "now playing"
            if(!queue.empty())
            {
                cout << "Now playing: " << queue.front() << endl;
                recentlyPlayed.insert({recentlyPlayed.size()+1, queue.front()});
                queue.pop_front();
            }
            else
            {
                throw runtime_error("Queue is empty!");
            }
        }
        catch(const exception& e)
        {
            cout << "Exception occurred: " << e.what() << endl;
        }
    }

    void addSongToQueue(Song song)
    {
        queue.push_back(song);
    }

    void addPlaylistToQueue(int i)
    {
        if(typeid(*users[i])==typeid(Listener))
        {
            Listener* listener = dynamic_cast<Listener*>(users[i]);
            vector <Playlist> aux = listener->getPlaylists();
            cout << "Select the playlist you want to add to the queue: " << endl;
            for (int i = 0; i < aux.size(); i++)
            {
                cout << i+1 << ". " << aux[i].getName() << endl;
            }
            cout << "Your option: ";
            int option;
            cin >> option;
            set <Song> songs = aux[option-1].getSongs();
            for (auto it = songs.begin(); it != songs.end(); it++)
            {
                queue.push_back(*it);
            }
        }
        if(typeid(*users[i])==typeid(StudentListener))
        {
            StudentListener* studentListener = dynamic_cast<StudentListener*>(users[i]);
            vector <Playlist> aux = studentListener->getPlaylists();
            cout << "Select the playlist you want to add to the queue: " << endl;
            for (int i = 0; i < aux.size(); i++)
            {
                cout << i+1 << ". " << aux[i].getName() << endl;
            }
            cout << "Your option: ";
            int option;
            cin >> option;
            set <Song> songs = aux[option-1].getSongs();
            for (auto it = songs.begin(); it != songs.end(); it++)
            {
                queue.push_back(*it);
            }
        }
    }

    void changeSubscriptionType(int i)
    {
        try
        {
            if(typeid(*users[i]) == typeid(Listener))
            {
                Listener* listener = dynamic_cast<Listener*>(users[i]);
                StudentListener* studentListener = static_cast<StudentListener*>(listener);
                if (studentListener != nullptr) {
                    int graduationYear;
                    string university;
                    cout << "Enter graduation year: ";
                    cin >> graduationYear;
                    cout << "Enter university: ";
                    cin >> university;
                    studentListener->setGraduationYear(graduationYear);
                    studentListener->setUniversity(university);
                    users[i] = new StudentListener(*studentListener);
                    cout << "Subscription type changed successfully" << endl;
                } else {
                    throw runtime_error("Unable to change subscription type");
                }
            }

            if(typeid(*users[i]) == typeid(StudentListener))
            {
                StudentListener* studentListener = dynamic_cast<StudentListener*>(users[i]);
                Listener* listener = dynamic_cast<Listener*>(studentListener);
                if (listener != nullptr) {
                    users[i] = new Listener(*listener);
                    cout << "Subscription type changed successfully" << endl;
                } else {
                    throw runtime_error("Unable to change subscription type");
                }
            }
        }
        catch(const exception& e)
        {
            cout << "Error: " << e.what() << endl;
        }
    }

    void changeAccountDetails(int i)
    {
        try
        {
            cout << "Select the detail you want to change: " << endl;
            cout << "1. Username" << endl;
            cout << "2. Password" << endl;
            cout << "3. Email" << endl;
            cout << "4. Country" << endl;
            cout << "Your option: ";
            int option;
            cin >> option;
            if (option == 1)
            {
                cout << "Enter the new username: ";
                string username;
                cin >> username;
                users[i]->setUsername(username);
            }
            else if (option == 2)
            {
                cout << "Enter the new password: ";
                string password;
                cin >> password;
                users[i]->setPassword(password);
            }
            else if (option == 3)
            {
                cout << "Enter the new email: ";
                string email;
                cin >> email;
                users[i]->setEmail(email);
            }
            else if (option == 4)
            {
                cout << "Enter the new country: ";
                string country;
                cin >> country;
                users[i]->setCountry(country);
            }
            else
            {
                throw "Invalid option!";
            }
        }
        catch (const char* message)
        {
            cout << message << endl;
        }
    }

    void addAlbum(int i)
    {
        if(typeid(*users[i])==typeid(Artist))
        {
            Artist* artist = dynamic_cast<Artist*>(users[i]);
            set <Album> aux = artist->getAlbums();
            Album album;
            cin >> album;
            aux.insert(album);
            artist->setAlbums(aux);
        }
    }

    void income(int i)
    {
        if(typeid(*users[i])==typeid(Artist))
        {
            Artist* artist = dynamic_cast<Artist*>(users[i]);
            cout << "Income: " << artist->getMonthlyListeners()*0.07 << endl;
        }
    }

    void displayAllAlbums(int i)
    {
        if(typeid(*users[i])==typeid(Artist))
        {
            Artist* artist = dynamic_cast<Artist*>(users[i]);
            set <Album> aux = artist->getAlbums();
            int i = 1;
            cout << "Albums: " << endl;
            for (auto it = aux.begin(); it != aux.end(); it++)
            {
                cout << i++ << ". " << *it << endl;
            }
        }
    }

    void displayAllSongsFromAlbum(int i)
    {
        if(typeid(*users[i])==typeid(Artist))
        {
            Artist* artist = dynamic_cast<Artist*>(users[i]);
            set <Album> aux = artist->getAlbums();
            cout << "Select the album you want to see: " << endl;
            int i = 1;
            for (auto it = aux.begin(); it != aux.end(); it++)
            {
                cout << i++ << ". " << *it << endl;
            }
            cout << "Your option: ";
            int option;
            cin >> option;
            cout << "Songs: " << endl;
            for (auto it = aux.begin(); it != aux.end(); it++)
            {
                if (option == i)
                {
                    set <Song> songs = it->getSongs();
                    int j = 1;
                    for (auto it2 = songs.begin(); it2 != songs.end(); it2++)
                    {
                        cout << j++ << ". " << *it2 << endl;
                    }
                }
            }
        }
    }

    
    void deleteAccount(int i)
    {
        users.erase(users.begin()+i);
    }

    void createAccount()
    {
        try
        {
            cout << "Select the type of account you want to create: " << endl;
            cout << "1. Listener" << endl;
            cout << "2. Artist" << endl;
            cout << "3. Student Listener" << endl;
            cout << "Your option: ";
            int option;
            cin >> option;
            if (option == 1)
            {
                users.push_back(new Listener());
                cin >> *users.back();
            }
            else if (option == 2)
            {
                users.push_back(new Artist());
                cin >> *users.back();
            }
            else if (option == 3)
            {
                users.push_back(new StudentListener());
                cin >> *users.back();
            }
            else
            {
                throw "Invalid option!";
            }
        }
        catch (const char* message)
        {
            cerr << "Error: " << message << endl;
        }
    }

    void selectAccount()
    {
        cout << "Select the account you want to access: " << endl;
        try{
        if (users.empty())
        {
            throw runtime_error("No accounts available!");
        }
        else
        {
        for (int i = 0; i < users.size(); i++)
        {
            cout << i+1 << ". " << getUserUsername(i) << endl;
        }
        }
        }
        catch(const exception& e)
        {
            cout << "Exception occurred: " << e.what() << endl;
            return;
        }
        cout << "Your option: ";
        int option;
        cin >> option;
        cout << "Enter the password: ";
        string password;
        try
        {
            cin >> password;
        
            if (password != getUserPassword(option-1))
            {
                throw invalid_argument("Invalid password!");
            }
        }
        catch(const exception& e)
        {
            cout << "Exception occurred: " << e.what() << endl;
        }
        if (password == getUserPassword(option-1))
        {
            cout << "Access granted!" << endl;
            cout << endl;
            cout << "Welcome, " << getUserUsername(option-1) << "!" << endl;
            cout << endl;
            cout << "Select an option available below: " << endl;
            cout << endl;
            if(typeid(*users[option-1])==typeid(Listener) || typeid(*users[option-1])==typeid(StudentListener))
            {
                cout << "1. Add song to playlist" << endl;
                cout << "2. Add song to liked songs" << endl;
                cout << "3. Create playlist" << endl;
                cout << "4. Start queue" << endl;
                cout << "5. Add song to queue" << endl;
                cout << "6. Add playlist to queue" << endl;
                cout << "7. Change subscription type" << endl;
                cout << "8. Change account details" << endl;
                cout << "9. Delete account" << endl;
                cout << "10. Exit" << endl;
                cout << endl;
                cout << "Your option: ";
                int user_number = option-1;
                try{
                    int command;
                cin >> command;
                if (command == 1)
                {
                    Song x;
                    cin>>x;
                    addSongToPlaylist(user_number, x);
                }
                else if (command == 2)
                {
                    Song x;
                    cin>>x;
                    addSongToLikedSongs(user_number, x);
                }
                else if (command == 3)
                {
                    createPlaylist(user_number);
                }
                else if (command == 4)
                {
                    startQueue();
                }

                else if (command == 5)
                {
                    Song x;
                    cin>>x;
                    addSongToQueue(x);
                }

                else if (command == 6)
                {
                    addPlaylistToQueue(user_number);
                }
                else if (command == 7)
                {
                    changeSubscriptionType(user_number);
                }
                else if (command == 8)
                {
                    changeAccountDetails(user_number);
                }
                else if (command == 9)
                {
                    deleteAccount(user_number);
                }
                else if (command == 10)
                {
                    cout << "See you next time. ^^" << endl;
                    exit;
                }
                else
                {
                    throw "Invalid option!";
                }
                }
                catch(const char* message)
                {
                    cout << "Error: " << message << endl;
                }  
            }

                if(typeid(*users[option-1])==typeid(Artist))
                {
                    cout << "1. Add album" << endl;
                    cout << "2. Display income based on monthly listeners" << endl;
                    cout << "3. Display all albums" << endl;
                    cout << "4. Display all songs from an album" << endl;
                    cout << "5. Change account details" << endl;
                    cout << "6. Delete account" << endl;
                    cout << "7. Exit" << endl;
                    cout << endl;
                    cout << "Your option: ";
                    int command;
                    cin >> command;
                    if (command == 1)
                    {
                        addAlbum(option-1);
                    }
                    else if (command == 2)
                    {
                        income(option-1);
                    }
                    else if (command == 3)
                    {
                        displayAllAlbums(option-1);
                    }
                    else if (command == 4)
                    {
                        displayAllSongsFromAlbum(option-1);
                    }
                    else if (command == 5)
                    {
                        changeAccountDetails(option-1);
                    }
                    else if (command == 6)
                    {
                        deleteAccount(option-1);
                    }
                    else if (command == 7)
                    {
                        cout << "See you next time. ^^" << endl;
                        exit;
                    }
                    else
                    {
                        cout << "Invalid option!" << endl;
                    }
                }
    
    }
    }


    void menu()
    {
        bool run = true;
        while(run)
        {
            cout << "Welcome to Music Player. Select an option available below: " << endl;
            cout << endl;
            cout << "1. Create account" << endl;
            cout << "2. Select account" << endl;
            cout << "3. Exit" << endl;
            cout << endl;
            cout << "Your option: ";
            int option;
            try{
            cin >> option;
            if (option == 1)
            {
                createAccount();
            }
            else if (option == 2)
            {
                selectAccount();
            }
            else if (option == 3)
            {
                run = false;
                cout << "See you next time. ^^" << endl;
            }
            else
            {
                throw "Invalid option!";
            }
            }
            catch(const char* message)
            {
                cout << "Error: " << message << endl;
            
            }
            
        }
    }
};
    


MusicPlayer* MusicPlayer::instance = NULL;

int main() {
    MusicPlayer* player = player->getInstance();
    player->menu();
    return 0;
}

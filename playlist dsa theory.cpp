#include <iostream>
using namespace std;

struct Song {
    string name;
    Song* next;
    Song* prev;

    Song(string songName) {
        name = songName;
        next = NULL;
        prev = NULL;
    }
};

Song* head = NULL;

void addSong(string name) {
    Song* newSong = new Song(name);
    if (head == NULL) {
        head = newSong;
        head->next = head;
        head->prev = head;
    } else {
        Song* last = head->prev;

        last->next = newSong;
        newSong->prev = last;
        newSong->next = head;
        head->prev = newSong;
    }
    cout << "Song added: " << name << endl;
}

void showPlaylist() {
    if (head == NULL) {
        cout << "Playlist is empty.\n";
        return;
    }

    Song* temp = head;
    cout << "Playlist:\n";
    do {
        cout << "- " << temp->name << "\n";
        temp = temp->next;
    } while (temp != head);
}

void searchSong(string name) {
    if (head == NULL) {
        cout << "Playlist is empty.\n";
        return;
    }

    Song* temp = head;
    int pos = 0;
    do {
        if (temp->name == name) {
            cout << "Song \"" << name << "\" found at position " << pos << ".\n";
            return;
        }
        temp = temp->next;
        pos++;
    } while (temp != head);

    cout << "Song not found.\n";
}

void deleteSong() {
    if (head == NULL) {
        cout << "Playlist is empty.\n";
        return;
    }

    if (head->next == head) {
        delete head;
        head = NULL;
    } else {
        Song* last = head->prev;
        Song* temp = head;

        head = head->next;
        head->prev = last;
        last->next = head;

        delete temp;
    }

    cout << "First song deleted.\n";
}

int main() {
    int choice;
    string songName;

    do {
        cout << "\n=== Playlist Menu ===\n";
        cout << "1. Add Song\n";
        cout << "2. Show Playlist\n";
        cout << "3. Search Song\n";
        cout << "4. Delete First Song\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Enter song name to add: ";
                getline(cin, songName);
                addSong(songName);
                break;

            case 2:
                showPlaylist();
                break;

            case 3:
                cout << "Enter song name to search: ";
                getline(cin, songName);
                searchSong(songName);
                break;

            case 4:
                deleteSong();
                break;

            case 5:
                cout << "Exiting playlist...\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
	}

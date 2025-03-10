#include <iostream>
#include <fstream>
#include <clocale>
using namespace std;

struct Team {
    char name[50];
    char city[50];
    int players;
    int points;
};

int main() {
    setlocale(LC_ALL, "Ru");
    system("chcp 1251");
    system("cls");
    int count;
    const char* filename = "teams.dat";
    Team team;
    int minPoints;

    cout << "Создание файла..." << endl;
    ofstream fout(filename, ios::binary);

    cout << "Введите количество команд:" << endl;
    cin >> count;
    cin.ignore();
    for (int i = 0; i < count; i++) {
        cout << "\nКоманда #" << i + 1 << endl;
        cout << "Название: "; cin.getline(team.name, 50);
        cout << "Город: "; cin.getline(team.city, 50);
        cout << "Игроков: "; cin >> team.players;
        cout << "Очков: "; cin >> team.points;
        cin.ignore();
        fout.write(reinterpret_cast<char*>(&team), sizeof(Team));
    }
    fout.close();

    cout << "\n\nСодержимое файла после создания:" << endl;
    ifstream fin(filename, ios::binary);
    while (fin.read(reinterpret_cast<char*>(&team), sizeof(Team))) {
        cout << "\nНазвание: " << team.name;
        cout << "\nГород: " << team.city;
        cout << "\nИгроков: " << team.players;
        cout << "\nОчков: " << team.points << endl;
    }
    fin.close();

    cout << "\n\nВведите минимальное количество очков: ";
    cin >> minPoints;
    cin.ignore();
    
    {
        ifstream inFile(filename, ios::binary);
        ofstream outFile("temp.dat", ios::binary);

        while (inFile.read(reinterpret_cast<char*>(&team), sizeof(Team))) {
            if (team.points >= minPoints) {
                outFile.write(reinterpret_cast<char*>(&team), sizeof(Team));
            }
        }
        inFile.close();
        outFile.close();
    }
    remove(filename);
    rename("temp.dat", filename);

    cout << "\n\nСодержимое файла после удаления:" << endl;
    fin.open(filename, ios::binary);
    while (fin.read(reinterpret_cast<char*>(&team), sizeof(Team))) {
        cout << "\nНазвание: " << team.name;
        cout << "\nГород: " << team.city;
        cout << "\nИгроков: " << team.players;
        cout << "\nОчков: " << team.points << endl;
    }
    fin.close();

    cout << "\n\nДобавление 2 команд в начало..." << endl;
    {
        Team newTeams[2];
        ofstream tempFile("temp.dat", ios::binary);

        for (int i = 0; i < 2; i++) {
            cout << "\nКоманда #" << i + 1 << endl;
            cout << "Название: "; cin.getline(newTeams[i].name, 50);
            cout << "Город: "; cin.getline(newTeams[i].city, 50);
            cout << "Игроков: "; cin >> newTeams[i].players;
            cout << "Очков: "; cin >> newTeams[i].points;
            cin.ignore();
            tempFile.write(reinterpret_cast<char*>(&newTeams[i]), sizeof(Team));
        }

        ifstream inFile(filename, ios::binary);
        while (inFile.read(reinterpret_cast<char*>(&team), sizeof(Team))) {
            tempFile.write(reinterpret_cast<char*>(&team), sizeof(Team));
        }
        inFile.close();
        tempFile.close();

        remove(filename);
        rename("temp.dat", filename);
    }

    cout << "\n\nИтоговое содержимое файла:" << endl;
    fin.open(filename, ios::binary);
    while (fin.read(reinterpret_cast<char*>(&team), sizeof(Team))) {
        cout << "\nНазвание: " << team.name;
        cout << "\nГород: " << team.city;
        cout << "\nИгроков: " << team.players;
        cout << "\nОчков: " << team.points << endl;
    }
    fin.close();

    return 0;
}
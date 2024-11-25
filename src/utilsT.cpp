#include <string.h>
#define MAX_USERS 4
#define ADMIN_INDEX 0


struct OnlyAccessUsers{
    char**_users;
    int _countUsers = 0;
    bool _hasAdmin = false;

    OnlyAccessUsers() {
        _users = new char*[MAX_USERS + 1]; // выделяем место под пользователей
        for (int i = 0; i <= MAX_USERS; ++i) {
            _users[i] = nullptr;
        }
    }
    bool HasAdmin() { 
        return _hasAdmin;
    }

    bool ExistUser(const char* userId){
        if (!_countUsers) return false;

        for( int i = 1; i <= _countUsers; i++){
            if (!strcmp(_users[i], userId)) return true;
        }
        return false;
    }
    bool ResetAdmin(){
        if (HasAdmin()){
            delete[] _users[0];
            _users[0] = nullptr;
            _hasAdmin = false;
            return true;
        }
        return false;
    }
    bool DeleteUsers(){
        // Удаляет всех пользователей, кроме админа.
        if (_countUsers == 0) return false;
        short i = _countUsers;
        for( ; i >= 1; i--){
            delete[] _users[i];
            _users[i] = nullptr;
        }
        _countUsers = i;
        return true;

    }
    bool AddUser(const char* userId){
        if (_countUsers == MAX_USERS)
            return false;
        _users[++_countUsers] = new char[strlen(userId) + 1];
        if( !_users[_countUsers]){
            _countUsers--;
            return false;
        }
        strcpy( _users[_countUsers], userId);
        return true;
    }
    bool AddAdmin(const char* userId){
        if (HasAdmin()) return false;
        _users[ADMIN_INDEX] = new char[strlen(userId) + 1];
        if (_users[ADMIN_INDEX] == nullptr)
            return false;
        _hasAdmin = true;
        strcpy(_users[ADMIN_INDEX], userId);
    }

    bool IsAdmin(const char* userId){
        if (!HasAdmin()) return false;

        return !strcmp(_users[0], userId);
    }

};

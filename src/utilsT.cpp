#include <string.h>
#include <cctype>
#include <FastBot2.h>
#define MAX_USERS 4
#define ADMIN_INDEX 0
#define LEN_USER_ID 11


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
    bool _IsValidUserId(const char* userId){
        // Полагаем, что длина UserId in [6, 11]
        short len = strlen(userId);
        if (len <= 5 || len > 11) return false; // maybe will be bug
        for (short i = 0; i < len; i++)
            if (!isdigit( userId[i])) return false;
        return true;
    }
    char * _ParseUserId(const char* cmd){
        char * ans = new char[strlen(cmd) + 1]{};
        if (!ans) return ans;
        for(short i = 9; i < strlen(cmd); i++){
            ans[i - 9] = cmd[i]; 
        }
        return ans;

    }
    bool AddUser(const char* cmd){
        //TODO
        if (_countUsers == MAX_USERS)
            return false;
        char *userId = _ParseUserId(cmd);
        if (!userId) return false; // значит, что памяти нет под юзера(нулевой указатель)
        if(!_IsValidUserId(userId)) return false;
        _users[++_countUsers] = userId;
        return true;
    }
    bool AddAdmin(const char* userId){
        if (HasAdmin()) return false;
        _users[ADMIN_INDEX] = new char[strlen(userId) + 1];
        if (_users[ADMIN_INDEX] == nullptr)
            return false;
        _hasAdmin = true;
        strcpy(_users[ADMIN_INDEX], userId);
        return true;
    }

    bool IsAdmin(const char* userId){
        if (!HasAdmin()) return false;

        return Text(_users[0]) ==  Text(userId);
    }

};
